#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

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

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H






