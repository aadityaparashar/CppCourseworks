#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "workerthread.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->m_runButton, &QPushButton::clicked, this, &MainWindow::run);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::run()
{
    m_pWorkerThread = new WorkerThread;
    connect(m_pWorkerThread, &WorkerThread::finished, this, &MainWindow::showMessage);
    connect(m_pWorkerThread, &WorkerThread::finished, m_pWorkerThread, &QObject::deleteLater);
    m_pWorkerThread->start();
}

void MainWindow::showMessage()
{
    m_pWorkerThread->wait();
    QMessageBox msgBox;
    msgBox.setText("Thread finished");
    msgBox.exec();
}
