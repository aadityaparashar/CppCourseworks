/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QCustomPlot *graph_plot;
    QTextEdit *connection_log;
    QPushButton *send_data;
    QPushButton *server_connect;
    QPushButton *server_disconnect;
    QComboBox *special_functions;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *order_label;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLineEdit *start_value;
    QLineEdit *end_value;
    QLineEdit *points_value;
    QLineEdit *order_value;
    QLineEdit *server_address;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(607, 496);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        graph_plot = new QCustomPlot(centralWidget);
        graph_plot->setObjectName(QString::fromUtf8("graph_plot"));
        graph_plot->setGeometry(QRect(10, 200, 401, 221));
        connection_log = new QTextEdit(centralWidget);
        connection_log->setObjectName(QString::fromUtf8("connection_log"));
        connection_log->setGeometry(QRect(450, 150, 141, 281));
        send_data = new QPushButton(centralWidget);
        send_data->setObjectName(QString::fromUtf8("send_data"));
        send_data->setGeometry(QRect(10, 170, 111, 23));
        server_connect = new QPushButton(centralWidget);
        server_connect->setObjectName(QString::fromUtf8("server_connect"));
        server_connect->setGeometry(QRect(480, 80, 75, 23));
        server_disconnect = new QPushButton(centralWidget);
        server_disconnect->setObjectName(QString::fromUtf8("server_disconnect"));
        server_disconnect->setGeometry(QRect(480, 100, 75, 23));
        special_functions = new QComboBox(centralWidget);
        special_functions->setObjectName(QString::fromUtf8("special_functions"));
        special_functions->setGeometry(QRect(110, 10, 111, 22));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 50, 47, 13));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 80, 47, 13));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 110, 47, 13));
        order_label = new QLabel(centralWidget);
        order_label->setObjectName(QString::fromUtf8("order_label"));
        order_label->setGeometry(QRect(20, 140, 47, 13));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 10, 91, 16));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(500, 10, 47, 13));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(460, 130, 47, 13));
        start_value = new QLineEdit(centralWidget);
        start_value->setObjectName(QString::fromUtf8("start_value"));
        start_value->setGeometry(QRect(80, 50, 41, 20));
        end_value = new QLineEdit(centralWidget);
        end_value->setObjectName(QString::fromUtf8("end_value"));
        end_value->setGeometry(QRect(80, 80, 41, 20));
        points_value = new QLineEdit(centralWidget);
        points_value->setObjectName(QString::fromUtf8("points_value"));
        points_value->setGeometry(QRect(80, 110, 41, 20));
        order_value = new QLineEdit(centralWidget);
        order_value->setObjectName(QString::fromUtf8("order_value"));
        order_value->setGeometry(QRect(80, 140, 41, 20));
        server_address = new QLineEdit(centralWidget);
        server_address->setObjectName(QString::fromUtf8("server_address"));
        server_address->setGeometry(QRect(460, 40, 113, 20));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 607, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        send_data->setText(QApplication::translate("MainWindow", "Send data", nullptr));
        server_connect->setText(QApplication::translate("MainWindow", "Connect", nullptr));
        server_disconnect->setText(QApplication::translate("MainWindow", "Disconnect", nullptr));
        label->setText(QApplication::translate("MainWindow", "Start", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Stop", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Points", nullptr));
        order_label->setText(QApplication::translate("MainWindow", "Order", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Special Functions", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "Server", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "Log", nullptr));
        server_address->setText(QApplication::translate("MainWindow", "\\\\.\\pipe\\ICS0025", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
