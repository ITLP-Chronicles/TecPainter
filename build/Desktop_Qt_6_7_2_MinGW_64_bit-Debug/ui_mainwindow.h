/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionGuardar;
    QAction *actionCargar;
    QAction *actionGuardar_2;
    QAction *actionLeer;
    QWidget *centralwidget;
    QLabel *label;
    QMenuBar *menubar;
    QMenu *menuMen;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        MainWindow->setStyleSheet(QString::fromUtf8("color: black;"));
        actionGuardar = new QAction(MainWindow);
        actionGuardar->setObjectName("actionGuardar");
        actionCargar = new QAction(MainWindow);
        actionCargar->setObjectName("actionCargar");
        actionGuardar_2 = new QAction(MainWindow);
        actionGuardar_2->setObjectName("actionGuardar_2");
        actionLeer = new QAction(MainWindow);
        actionLeer->setObjectName("actionLeer");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 520, 331, 20));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        menuMen = new QMenu(menubar);
        menuMen->setObjectName("menuMen");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuMen->menuAction());
        menuMen->addAction(actionGuardar_2);
        menuMen->addAction(actionLeer);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Ejemplo Unidad I", nullptr));
        actionGuardar->setText(QCoreApplication::translate("MainWindow", "Guardar", nullptr));
        actionCargar->setText(QCoreApplication::translate("MainWindow", "Cargar", nullptr));
        actionGuardar_2->setText(QCoreApplication::translate("MainWindow", "Guardar", nullptr));
        actionLeer->setText(QCoreApplication::translate("MainWindow", "Leer", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\342\234\250 Funci\303\263n: Puede deshacer cambios con ctrl + z", nullptr));
        menuMen->setTitle(QCoreApplication::translate("MainWindow", "Men\303\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
