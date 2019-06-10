#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "Worker.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Worker *m_pWorker = nullptr;
    QThread *m_pWorkerThread;

signals:
    void stop();
    void start();

private slots:
    void exit();
    void showResults(QString);
    void startThread();
    void stopThread();
};

#endif // MAINWINDOW_H
