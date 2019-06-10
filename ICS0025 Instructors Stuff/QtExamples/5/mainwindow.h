#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <workerthread.h>

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
    WorkerThread *m_pWorkerThread  = nullptr;

private slots:
    void exit();
    void showResults(QString);
    void startThread();
    void stopThread();
    void destroyThread();

signals:
    void stopSignal();
};

#endif // MAINWINDOW_H
