#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "objeto2d.h"
#include <stack>

namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

//Modos posibles del programa completo. Perteneciente a MainWindow
enum Mode {
    //Modo predeterminado al arrancar el programa. Permite el dibujo arbitrario. Se activa mediante GUI y atajo de teclado
    Normal,

    //Modo al utilizar el click derecho. Permite modificar líneas actuales. No se activa mediante GUI pero si con atajo de teclado.
    Edit,

    //Modo para mover todo el dibujo. Se activa mediante el GUI y atajo de teclado.
    Trasladar,

    //Modo para rotar todo el dibujo. Se activa mediante el GUI y atajo de teclado.
    Rotar,

    //Modo para escalar todo el dibujo. Se activa mediante el GUI y atajo de teclado.
    Escalar,

    //Modo para reflejar todo el dibujo. Se activa mediante el GUI y atajo de teclado. Permite el dibujo
    //de una línea temporal y luego aplicar el efecto automáticamente.
    Reflejar,

    EscalarArbitrario
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Ui::MainWindow *ui;

    //Obj que administra el dibujo principal
    Objeto2D *objeto2D;

    //Línea temporal del usuario al realizar sus trazos (1 a la vez)
    Linea *actualLine = nullptr;

    //Línea que indica la penúltima línea hecha
    Linea *lastLine = nullptr;

    //TODO: Raul, que es esto?
    Punto* pointToMove = nullptr;

    //Modo de renderizado de las líneas hechas sobre el vuelo y guardadas en "actualLine"
    Mode actualMode = Normal;

    //Lógica para implementar el ctrl + z  y  el ctrl + y
    std::stack<Objeto2D*> objectStack;
    std::stack<Objeto2D*> deletedObjectStack;

    //Getter de la propiedad "actualMode", realiza lógica además de solo establecer el modo actual
    void setActualMode(Mode newMode);

    // GUI Eventos QT PRINCIPALES de uso (Interacción con mouse y teclado)
    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
        void mousePressEvent(QMouseEvent *);
        void mouseMoveEvent(QMouseEvent *);
        void mouseReleaseEvent(QMouseEvent *);
        void paintEvent(QPaintEvent *);
        void keyPressEvent(QKeyEvent *);

    // GUI Eventos QT Generados Automáticamente (No tocar)
    private slots:
        void on_actionGuardar_triggered();
        void on_actionLeer_triggered();
        void on_actionNormal_triggered();
        void on_actionInterlineado_triggered();
        void on_actionDibujar_triggered();
        void on_actionTrasladar_triggered();
        void on_actionRotar_triggered();
        void on_actionEscalar_triggered();
        void on_actionEspejo_Reflejar_triggered();
        void on_actionEscalar_c_direccion_arbr_triggered();
};
#endif // MAINWINDOW_H






