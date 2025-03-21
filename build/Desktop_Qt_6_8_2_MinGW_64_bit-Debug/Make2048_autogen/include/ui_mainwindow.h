/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
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
    QPushButton *newGameButton;
    QLabel *scoreLabel;
    QPushButton *btnRight;
    QPushButton *btnDown;
    QPushButton *btnLeft;
    QPushButton *btnUp;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        newGameButton = new QPushButton(centralwidget);
        newGameButton->setObjectName("newGameButton");
        newGameButton->setGeometry(QRect(10, 0, 141, 61));
        scoreLabel = new QLabel(centralwidget);
        scoreLabel->setObjectName("scoreLabel");
        scoreLabel->setGeometry(QRect(550, 0, 241, 131));
        btnRight = new QPushButton(centralwidget);
        btnRight->setObjectName("btnRight");
        btnRight->setGeometry(QRect(710, 490, 61, 61));
        btnDown = new QPushButton(centralwidget);
        btnDown->setObjectName("btnDown");
        btnDown->setGeometry(QRect(650, 490, 61, 61));
        btnLeft = new QPushButton(centralwidget);
        btnLeft->setObjectName("btnLeft");
        btnLeft->setGeometry(QRect(590, 490, 61, 61));
        btnUp = new QPushButton(centralwidget);
        btnUp->setObjectName("btnUp");
        btnUp->setGeometry(QRect(650, 428, 61, 61));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        newGameButton->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        scoreLabel->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        btnRight->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        btnDown->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        btnLeft->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        btnUp->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
