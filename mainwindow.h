#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "objeto2d.h"

namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

enum Mode {
    Normal,
    Edit
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
    void on_actionGuardar_2_triggered();

};
#endif // MAINWINDOW_H






