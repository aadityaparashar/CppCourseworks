#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->m_exitButton, &QPushButton::clicked, this, &MainWindow::exit, Qt::DirectConnection);
    connect(ui->m_startButton, &QPushButton::clicked, this, &MainWindow::startThread, Qt::DirectConnection);
    connect(ui->m_stopButton, &QPushButton::clicked, this, &MainWindow::stopThread, Qt::DirectConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::exit()
{
    QApplication::exit();
}

void MainWindow::startThread()
{
    m_pWorkerThread = new WorkerThread;
    connect(m_pWorkerThread, &WorkerThread::ready, this, &MainWindow::showResults, Qt::QueuedConnection);
    connect(m_pWorkerThread, &QThread::finished, m_pWorkerThread, &QObject::deleteLater);
    connect(m_pWorkerThread, &WorkerThread::finished, this, &MainWindow::destroyThread);
    connect(this, &MainWindow::stopSignal, m_pWorkerThread, &WorkerThread::stop, Qt::DirectConnection);
    m_pWorkerThread->start();
    ui->m_startButton->setEnabled(false);
    ui->m_stopButton->setEnabled(true);
}

void MainWindow::stopThread()
{
    emit stopSignal();
}

void MainWindow::destroyThread()
{
    ui->m_startButton->setEnabled(true);
    ui->m_stopButton->setEnabled(false);
}

void MainWindow::showResults(QString msg)
{
    ui->m_resultLineEdit->clear();
    ui->m_resultLineEdit->setText(msg);
}
