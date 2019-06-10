#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "counter.h"

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
    Counter *m_pCounter = nullptr;
private slots:
    void exit();
    void showValue(int);
};

#endif // MAINWINDOW_H
