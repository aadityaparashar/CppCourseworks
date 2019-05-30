#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtNetwork>
#include <QStatusBar>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QLocalSocket            *m_pLocalSocket;
    QFile                   *m_pLogFile;
    bool                    m_isSkipLoggingFile;

public:
    explicit                MainWindow(QWidget *parent = nullptr);
                            ~MainWindow();
public slots:
    void                    onConnectedToServer();
    void                    onDisconnectedFromServer();
    void                    onOccuredError(QLocalSocket::LocalSocketError);
    void                    onArrivedData();

    void                    onConnectButtonClicked();
    void                    onDisconnectButtonClicked();
    void                    onSendCommandButtonClicked();

    void                    onSpecialFuncChanged(const QString &);
    bool                    validatePararms();

    void                    log(QString log);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
