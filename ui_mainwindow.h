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
#include <QtWidgets/QPushButton>
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
    QAction *actionEspejo_Reflejar;
    QAction *actionEscalar_c_direccion_arbr;
    QWidget *centralwidget;
    QLabel *label_2;
    QLabel *modo_actual;
    QPushButton *btnVuelta;
    QPushButton *btnMarometa;
    QPushButton *btnGiro;
    QPushButton *btnGiroCabeza;
    QMenuBar *menubar;
    QMenu *menuMen;
    QMenu *menuL_nea;
    QMenu *menuHerramienta;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(801, 611);
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
        actionDibujar->setMenuRole(QAction::MenuRole::AboutQtRole);
        actionTrasladar = new QAction(MainWindow);
        actionTrasladar->setObjectName("actionTrasladar");
        actionRotar = new QAction(MainWindow);
        actionRotar->setObjectName("actionRotar");
        actionEscalar = new QAction(MainWindow);
        actionEscalar->setObjectName("actionEscalar");
        actionEspejo_Reflejar = new QAction(MainWindow);
        actionEspejo_Reflejar->setObjectName("actionEspejo_Reflejar");
        actionEscalar_c_direccion_arbr = new QAction(MainWindow);
        actionEscalar_c_direccion_arbr->setObjectName("actionEscalar_c_direccion_arbr");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setEnabled(true);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(420, 530, 361, 20));
        modo_actual = new QLabel(centralwidget);
        modo_actual->setObjectName("modo_actual");
        modo_actual->setGeometry(QRect(590, 10, 201, 31));
        btnVuelta = new QPushButton(centralwidget);
        btnVuelta->setObjectName("btnVuelta");
        btnVuelta->setGeometry(QRect(260, 490, 80, 18));
        btnMarometa = new QPushButton(centralwidget);
        btnMarometa->setObjectName("btnMarometa");
        btnMarometa->setGeometry(QRect(350, 490, 80, 18));
        btnGiro = new QPushButton(centralwidget);
        btnGiro->setObjectName("btnGiro");
        btnGiro->setGeometry(QRect(440, 490, 80, 18));
        btnGiroCabeza = new QPushButton(centralwidget);
        btnGiroCabeza->setObjectName("btnGiroCabeza");
        btnGiroCabeza->setGeometry(QRect(700, 50, 80, 18));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 801, 17));
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
        menuHerramienta->addAction(actionEspejo_Reflejar);
        menuHerramienta->addAction(actionEscalar_c_direccion_arbr);

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
        actionDibujar->setText(QCoreApplication::translate("MainWindow", "Dibujar", nullptr));
#if QT_CONFIG(tooltip)
        actionDibujar->setToolTip(QCoreApplication::translate("MainWindow", "A", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionDibujar->setShortcut(QCoreApplication::translate("MainWindow", "A", nullptr));
#endif // QT_CONFIG(shortcut)
        actionTrasladar->setText(QCoreApplication::translate("MainWindow", "Trasladar", nullptr));
#if QT_CONFIG(shortcut)
        actionTrasladar->setShortcut(QCoreApplication::translate("MainWindow", "T", nullptr));
#endif // QT_CONFIG(shortcut)
        actionRotar->setText(QCoreApplication::translate("MainWindow", "Rotar", nullptr));
#if QT_CONFIG(shortcut)
        actionRotar->setShortcut(QCoreApplication::translate("MainWindow", "R", nullptr));
#endif // QT_CONFIG(shortcut)
        actionEscalar->setText(QCoreApplication::translate("MainWindow", "Escalar", nullptr));
#if QT_CONFIG(shortcut)
        actionEscalar->setShortcut(QCoreApplication::translate("MainWindow", "E", nullptr));
#endif // QT_CONFIG(shortcut)
        actionEspejo_Reflejar->setText(QCoreApplication::translate("MainWindow", "Espejo/Reflejar", nullptr));
        actionEscalar_c_direccion_arbr->setText(QCoreApplication::translate("MainWindow", "Escalar c/direccion arbr.", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Hecho Por Kristan Ru\303\255z Lim\303\263n y Ra\303\272l Armando M\303\251ndez Ar\303\241mbula", nullptr));
        modo_actual->setText(QCoreApplication::translate("MainWindow", "Modo actual: Normal", nullptr));
        btnVuelta->setText(QCoreApplication::translate("MainWindow", "Vuelta", nullptr));
        btnMarometa->setText(QCoreApplication::translate("MainWindow", "Marometa", nullptr));
        btnGiro->setText(QCoreApplication::translate("MainWindow", "Giro", nullptr));
        btnGiroCabeza->setText(QCoreApplication::translate("MainWindow", "Girar cabeza", nullptr));
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
