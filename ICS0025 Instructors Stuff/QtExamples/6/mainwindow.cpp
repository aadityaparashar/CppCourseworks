#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->m_exitButton, &QPushButton::clicked, this, &MainWindow::exit);
    connect(ui->m_startButton, &QPushButton::clicked, this, &MainWindow::startThread);
    connect(ui->m_stopButton, &QPushButton::clicked, this, &MainWindow::stopThread);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::exit()
{
    QApplication::exit();
}

void MainWindow::showResults(QString msg)
{
    ui->m_resultLineEdit->clear();
    ui->m_resultLineEdit->setText(msg);
}

void MainWindow::startThread()
{
    m_pWorker = new Worker;
    m_pWorkerThread = new QThread;
    m_pWorker->moveToThread(m_pWorkerThread);
    connect(m_pWorkerThread, &QThread::started, m_pWorker, &Worker::createRandomVector, Qt::DirectConnection);
    connect(m_pWorker, &Worker::ready, this, &MainWindow::showResults, Qt::QueuedConnection);
    connect(m_pWorkerThread, &QThread::finished, m_pWorker, &QObject::deleteLater);
    connect(m_pWorker, &Worker::finished, m_pWorker, &QObject::deleteLater);
    connect(this, &MainWindow::stop, m_pWorker, &Worker::stop, Qt::DirectConnection);
    m_pWorkerThread->start();
    ui->m_startButton->setEnabled(false);
    ui->m_stopButton->setEnabled(true);
}

void MainWindow::stopThread()
{
    emit stop();
    m_pWorkerThread->quit();
    m_pWorkerThread->wait();
    delete m_pWorkerThread;
    ui->m_startButton->setEnabled(true);
    ui->m_stopButton->setEnabled(false);
}


