#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_pCounter = new Counter();
    ui->setupUi(this);
    connect(ui->m_exitButton, &QPushButton::clicked, this, &MainWindow::exit);
    connect(ui->m_counterButton, &QPushButton::clicked, m_pCounter, &Counter::Increment);
    connect(m_pCounter, &Counter::valueChanged, this, &MainWindow::showValue);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::exit()
{
    QApplication::exit();
}

void MainWindow::showValue(int value)
{
    ui->m_counterLineEdit->setText(QString::number(value));
}
