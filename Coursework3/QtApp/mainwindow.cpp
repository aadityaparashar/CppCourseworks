#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qpacket.h"

#define WARNING(X, Y)                           (QMessageBox::warning(X, tr("Warning"), Y))
#define NOTIFY(X, Y)                            (QMessageBox::information(X, tr("Notify"), Y))
#define CRITICAL(X, Y)                          (QMessageBox::critical(X, tr("Error"), Y))
#define STATUS_MESSAGE(X)                       ((ui->statusBar->showMessage(X)));
#define STATUS_MESSAGE_WITH_TIME(X, Y)          (ui->statusBar->showMessage(X, Y))
#define STATUS_NORMAL_MESSAGE()                 (ui->statusBar->clearMessage())

#define RESPONSE_OK                             "Curve"

// had better managing state machine
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_pLocalSocket = new QLocalSocket(this);
    QString strLogFileName = QDateTime::currentDateTime().toString(Qt::ISODate) + ".log";
    strLogFileName.replace(":", "-");

    m_pLogFile = new QFile(strLogFileName);
    m_isSkipLoggingFile = false;

    if (!m_pLogFile->open(QIODevice::WriteOnly)) {
        QMessageBox::StandardButton clickedButton = QMessageBox::question(this, tr("Question"), tr("Could not create log file. Do you want to continue without it?"));
        if (clickedButton == QMessageBox::No) {
            delete m_pLogFile;
            delete m_pLocalSocket;
            qApp->quit();
            return;
        }
        m_isSkipLoggingFile = true;
    }

    QObject::connect(m_pLocalSocket, SIGNAL(connected()), this, SLOT(onConnectedToServer()));
    QObject::connect(m_pLocalSocket, SIGNAL(error(QLocalSocket::LocalSocketError)),this, SLOT(onOccuredError(QLocalSocket::LocalSocketError)));
    QObject::connect(m_pLocalSocket, SIGNAL(disconnected()), this, SLOT(onDisconnectedFromServer()));
    QObject::connect(m_pLocalSocket, SIGNAL(readyRead()), this, SLOT(onArrivedData()));

    QObject::connect(ui->server_connect, SIGNAL(clicked()), this, SLOT(onConnectButtonClicked()));
    QObject::connect(ui->server_disconnect, SIGNAL(clicked()), this, SLOT(onDisconnectButtonClicked()));
    QObject::connect(ui->send_data, SIGNAL(clicked()), this, SLOT(onSendCommandButtonClicked()) );
    QObject::connect(ui->special_functions, SIGNAL(currentTextChanged(const QString &)), this, SLOT(onSpecialFuncChanged(const QString &)));

    QStringList strlstSpecialFuncs;
    strlstSpecialFuncs << "Sine integral" << "Cosine integral" << "Bessel function" << "Fresnel integral S" << "Fresnel integral C";
    ui->special_functions->addItems(strlstSpecialFuncs);
}

MainWindow::~MainWindow()
{
    delete ui;

    if (m_pLocalSocket->state() == QLocalSocket::ConnectedState) {
        onDisconnectButtonClicked();
    }

    delete m_pLocalSocket;

    if (m_pLogFile->isOpen()) {
        m_pLogFile->close();
        delete m_pLogFile;
    }
}

// public slots
void MainWindow::onConnectedToServer()
{
    QString strMessage = tr("Connected to the server");
    qDebug() << strMessage;
    STATUS_MESSAGE(strMessage);

    ui->server_disconnect->setEnabled(true);
    ui->server_connect->setEnabled(false);
}

void MainWindow::onDisconnectedFromServer()
{
    QString strMessage = tr("Disconnected to the server");
    qDebug() << strMessage;
    STATUS_MESSAGE(strMessage);

    ui->server_disconnect->setEnabled(false);
    ui->server_connect->setEnabled(true);
}

void MainWindow::onOccuredError(QLocalSocket::LocalSocketError socketError)
{
    QString strLog;

    switch (socketError) {

    case QLocalSocket::ServerNotFoundError:
        strLog = tr("Server Not Found Error");
        STATUS_MESSAGE(strLog);
        NOTIFY(this, tr("The host was not found. Please check the host name and port settings."));
        STATUS_NORMAL_MESSAGE();
        break;
    case QLocalSocket::ConnectionRefusedError:
        strLog = tr("Connection Refused Error");
        STATUS_MESSAGE(strLog);
        NOTIFY(this, tr("The connection was refused by the peer. Make sure the server is running,and check that the host name and port settings are correct."));
        STATUS_NORMAL_MESSAGE();
        break;
    case QLocalSocket::PeerClosedError:
        strLog = tr("Peer Closed Error");
        STATUS_MESSAGE(strLog);
        break;
    default:
        strLog = tr("The following error occurred: %1.").arg(m_pLocalSocket->errorString());
        STATUS_MESSAGE(strLog);
        NOTIFY(this, tr("The following error occurred: %1.").arg(m_pLocalSocket->errorString()));
        STATUS_NORMAL_MESSAGE();
    }

    log(strLog);
}

void MainWindow::onConnectButtonClicked()
{
    QLineEdit *ptxtServerAddress = ui->server_address;
    QString strServerAddress = ptxtServerAddress->text();
    strServerAddress = strServerAddress.trimmed();
    //strServerAddress = "\\.\pipe\ICS0025";

    if (strServerAddress.isEmpty()) {
        WARNING(this, tr("Input the server address"));
        return;
    }

    STATUS_MESSAGE(tr("Connecting to the server..."));
    QString strLog = "Connected to the server";
    m_pLocalSocket->connectToServer(strServerAddress, QIODevice::ReadWrite);

    // Client waits 3 seconds for server connection
    if (!m_pLocalSocket->waitForConnected(3000)) {
        strLog = tr("Connection timeout");
        STATUS_MESSAGE(strLog);
        QString strMessage = tr("Fail to connect to the server. Please retry");
        NOTIFY(this, strMessage);
        STATUS_NORMAL_MESSAGE();
        log(strLog);
        return;
    }

    log(strLog);
}

void MainWindow::onDisconnectButtonClicked()
{
    QByteArray btarrayData;
    QPacket packet(&btarrayData, QDataStream::LittleEndian, m_pLocalSocket);
    packet.writeWStringData("Stop");
    packet.setPacketLengthField();

    if (-1 == packet.flushData()) {
        NOTIFY(this, tr("Fail to send command, could not close the connection"));
        return;
    }
    m_pLocalSocket->disconnectFromServer();
    log(tr("Disconnected to the server"));
}

void MainWindow::onSendCommandButtonClicked()
{
    QString strFunctionName = ui->special_functions->currentText();
    QString strStart = ui->start_value->text().trimmed();
    QString strEnd = ui->end_value->text().trimmed();
    QString strPoints = ui->points_value->text().trimmed();
    QString strOrder = ui->order_value->text().trimmed();

    bool isOK = true;
    double dfStart = strStart.toDouble(&isOK);
    double dfEnd = strEnd.toDouble(&isOK);
    qint32 nPoints = strPoints.toInt(&isOK);
    qint32 nOrder = strOrder.toInt(&isOK);

    QByteArray btarrayData;
    QPacket packet(&btarrayData, QDataStream::LittleEndian, m_pLocalSocket);
    packet.writeWStringData(strFunctionName);
    packet.writeDoubleData(dfStart);
    packet.writeDoubleData(dfEnd);
    packet.writeInt32Data(nPoints);

    if (ui->order_value->isEnabled())
        packet.writeInt32Data(nOrder);

    packet.setPacketLengthField();
    qint64 nSentLen = packet.flushData();
    if (nSentLen == -1) {
        NOTIFY(this, tr("Fail to send command"));
        return;
    }

    log(tr("CLIENT'S COMMAND: ") + strFunctionName);
}

void MainWindow::onArrivedData()
{
    QByteArray btarrayPacket = m_pLocalSocket->readAll(); // An array of bytes
    QDataStream dataStream(btarrayPacket); // data stream is a binary stream of encoded information
    dataStream.setByteOrder(QDataStream::LittleEndian); // Least significant byte first (Least significant byte first)

// parsing response packet
    qint32 nLen = 0;
    dataStream >> nLen;

    if (btarrayPacket.length() != nLen) {
        NOTIFY(this, tr("Invalid length of Packet received from server"));
        return;
    }

    QString strMessage;

    while (true) {
        ushort wChar = 0;
        dataStream >> wChar;
        if (wChar == 0)
            break;
        strMessage.append(QChar(wChar));
    }

    QString strServerMsg = "SUCCESS TO CALCULATE";

    if (strMessage != RESPONSE_OK) {
        STATUS_MESSAGE("Error Response received");
        NOTIFY(this, tr("Error message: ") + strMessage);
        STATUS_NORMAL_MESSAGE();
        strServerMsg = strMessage;
    } else {
        QVector<double> vctXsamples, vctYsamples;
        double dfMinX = 0, dfMaxX = 0, dfMinY = 0, dfMaxY = 0;
        while (!dataStream.atEnd()) {
            double dfX, dfY;
            dataStream >> dfX >> dfY;
            vctXsamples.push_back(dfX);
            vctYsamples.push_back(dfY);

            if (dfX > dfMaxX) dfMaxX = dfX;
            if (dfX < dfMinX) dfMinX = dfX;
            if (dfY > dfMaxY) dfMaxY = dfY;
            if (dfY < dfMinY) dfMinY = dfY;
        }

        ui->graph_plot->addGraph();
        ui->graph_plot->graph(0)->setData(vctXsamples, vctYsamples);
        ui->graph_plot->xAxis->setLabel("X");
        ui->graph_plot->yAxis->setLabel("Y");
        ui->graph_plot->xAxis->setRange(dfMinX, dfMaxX);
        ui->graph_plot->yAxis->setRange(dfMinY, dfMaxY);
        ui->graph_plot->replot();
    }

    log(tr("Reply from Server: ") + strServerMsg);

    qDebug() << btarrayPacket.toHex();
}

void MainWindow::onSpecialFuncChanged(const QString &text)
{
    if (text == "Bessel function") {
        ui->order_label->setEnabled(true);
        ui->order_value->setEnabled(true);
    } else {
        ui->order_label->setEnabled(false);
        ui->order_value->setEnabled(false);
    }
}

bool MainWindow::validatePararms()
{
    return true;
}

void MainWindow::log(QString log)
{
    ui->connection_log->append(log);
    if (!m_isSkipLoggingFile) {
        m_pLogFile->write(log.toLocal8Bit());
        m_pLogFile->write("\r\n", 2);
    }
}
