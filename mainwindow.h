#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "objeto2d.h"
#include <stack>

namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

enum Mode {
    Normal,
    Edit,
    Trasladar,
    Rotar,
    Escalar,
    Reflejar,
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Ui::MainWindow *ui;
    Objeto2D *objeto2D;
    Linea *actualLine = nullptr;
    Linea *lastLine = nullptr;
    Punto* pointToMove = nullptr;
    Mode actualMode = Normal;
    std::stack<Objeto2D*> objectStack;
    std::stack<Objeto2D*> deletedObjectStack;

    //Setter for actualMode. Used for update logic on window every time mode changes.
    void setActualMode(Mode newMode);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);

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
};
#endif // MAINWINDOW_H






