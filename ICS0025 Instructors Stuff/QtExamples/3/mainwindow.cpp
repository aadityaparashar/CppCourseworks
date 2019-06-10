#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->m_exitButton, &QPushButton::clicked, this, &MainWindow::exit);
    connect(ui->m_counterButton, &QPushButton::clicked, this, &MainWindow::incrementCounter);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::exit()
{
    QApplication::exit();
}

void MainWindow::incrementCounter()
{
    QString currentText = ui->m_counterLineEdit->text();
    int currentCounter = currentText.toInt();
    currentCounter++;
    ui->m_counterLineEdit->setText(currentText.setNum(currentCounter));
}
