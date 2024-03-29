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
    void                    error_hapened(QLocalSocket::LocalSocketError);
    void                    incoming_data();

    void                    onConnectButtonClicked();
    void                    server_disconnect_clicked();
    void                    send_data_clicked();

    void                    special_function_changed(const QString &);
    bool                    validatePararms();

    void                    log(QString log);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
