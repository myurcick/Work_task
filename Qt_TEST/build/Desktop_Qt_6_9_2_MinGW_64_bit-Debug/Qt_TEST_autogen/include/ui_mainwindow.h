/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QListWidget *listGen;
    QListWidget *listQ;
    QListWidget *listCuns;
    QPushButton *btnGen;
    QPushButton *btnCons;
    QPushButton *btnExit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(821, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        listGen = new QListWidget(centralwidget);
        listGen->setObjectName("listGen");
        listGen->setGeometry(QRect(10, 10, 256, 381));
        listQ = new QListWidget(centralwidget);
        listQ->setObjectName("listQ");
        listQ->setGeometry(QRect(280, 10, 256, 381));
        listCuns = new QListWidget(centralwidget);
        listCuns->setObjectName("listCuns");
        listCuns->setGeometry(QRect(550, 10, 256, 381));
        btnGen = new QPushButton(centralwidget);
        btnGen->setObjectName("btnGen");
        btnGen->setGeometry(QRect(40, 410, 151, 29));
        btnCons = new QPushButton(centralwidget);
        btnCons->setObjectName("btnCons");
        btnCons->setGeometry(QRect(570, 400, 151, 29));
        btnExit = new QPushButton(centralwidget);
        btnExit->setObjectName("btnExit");
        btnExit->setGeometry(QRect(310, 440, 161, 29));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 821, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);
        QObject::connect(btnExit, &QPushButton::clicked, MainWindow, qOverload<>(&QMainWindow::close));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btnGen->setText(QCoreApplication::translate("MainWindow", "Start/Stop 1 thread", nullptr));
        btnCons->setText(QCoreApplication::translate("MainWindow", "Start/Stop 3 thread", nullptr));
        btnExit->setText(QCoreApplication::translate("MainWindow", "EXIT", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
