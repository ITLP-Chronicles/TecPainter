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
    QAction *actionLeer;
    QAction *actionNormal;
    QAction *actionInterlineado;
    QAction *actionDibujar;
    QAction *actionTrasladar;
    QAction *actionRotar;
    QAction *actionEscalar;
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QMenuBar *menubar;
    QMenu *menuMen;
    QMenu *menuL_nea;
    QMenu *menuHerramienta;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        MainWindow->setStyleSheet(QString::fromUtf8("color: black;"));
        actionGuardar = new QAction(MainWindow);
        actionGuardar->setObjectName("actionGuardar");
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::DocumentSave));
        actionGuardar->setIcon(icon);
        actionCargar = new QAction(MainWindow);
        actionCargar->setObjectName("actionCargar");
        actionLeer = new QAction(MainWindow);
        actionLeer->setObjectName("actionLeer");
        QIcon icon1(QIcon::fromTheme(QIcon::ThemeIcon::EditFind));
        actionLeer->setIcon(icon1);
        actionNormal = new QAction(MainWindow);
        actionNormal->setObjectName("actionNormal");
        actionInterlineado = new QAction(MainWindow);
        actionInterlineado->setObjectName("actionInterlineado");
        actionDibujar = new QAction(MainWindow);
        actionDibujar->setObjectName("actionDibujar");
        actionTrasladar = new QAction(MainWindow);
        actionTrasladar->setObjectName("actionTrasladar");
        actionRotar = new QAction(MainWindow);
        actionRotar->setObjectName("actionRotar");
        actionEscalar = new QAction(MainWindow);
        actionEscalar->setObjectName("actionEscalar");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 490, 501, 20));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 520, 361, 20));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(370, 10, 51, 21));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        menuMen = new QMenu(menubar);
        menuMen->setObjectName("menuMen");
        menuL_nea = new QMenu(menubar);
        menuL_nea->setObjectName("menuL_nea");
        menuHerramienta = new QMenu(menubar);
        menuHerramienta->setObjectName("menuHerramienta");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuMen->menuAction());
        menubar->addAction(menuL_nea->menuAction());
        menubar->addAction(menuHerramienta->menuAction());
        menuMen->addAction(actionLeer);
        menuMen->addAction(actionGuardar);
        menuL_nea->addAction(actionNormal);
        menuL_nea->addAction(actionInterlineado);
        menuHerramienta->addAction(actionDibujar);
        menuHerramienta->addAction(actionTrasladar);
        menuHerramienta->addAction(actionRotar);
        menuHerramienta->addAction(actionEscalar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "TecPainter", nullptr));
        actionGuardar->setText(QCoreApplication::translate("MainWindow", "Guardar", nullptr));
        actionCargar->setText(QCoreApplication::translate("MainWindow", "Cargar", nullptr));
        actionLeer->setText(QCoreApplication::translate("MainWindow", "Leer", nullptr));
        actionNormal->setText(QCoreApplication::translate("MainWindow", "Normal", nullptr));
        actionInterlineado->setText(QCoreApplication::translate("MainWindow", "Interlineado", nullptr));
        actionDibujar->setText(QCoreApplication::translate("MainWindow", "Ninguno", nullptr));
        actionTrasladar->setText(QCoreApplication::translate("MainWindow", "Trasladar", nullptr));
        actionRotar->setText(QCoreApplication::translate("MainWindow", "Rotar", nullptr));
        actionEscalar->setText(QCoreApplication::translate("MainWindow", "Escalar", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\342\234\250 Funci\303\263n: Puede deshacer cambios con ctrl + z con las l\303\255neas", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Hecho Por Kristan Ru\303\255z Lim\303\263n y Ra\303\272l Armando", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Examen", nullptr));
        menuMen->setTitle(QCoreApplication::translate("MainWindow", "Men\303\272", nullptr));
        menuL_nea->setTitle(QCoreApplication::translate("MainWindow", "L\303\255nea", nullptr));
        menuHerramienta->setTitle(QCoreApplication::translate("MainWindow", "Herramienta", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
