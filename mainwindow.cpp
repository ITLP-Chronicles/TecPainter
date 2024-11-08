#include <QtXml>
#include <qfiledialog.h>
#include <QMouseEvent>
#include <QPainter>
#include <QLabel>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "matrix.h"
#include "displayer.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    // ------------------------- Setting colors ------------------------------
    setStyleSheet(
    "QMenu {"
    "	background-color: white;"
    "	color: black;"
    "}"
    "QMenu::item:selected {"
    "	background-color: lightgray;"
    "	color:black;"
    "}"
    "QWidget {"
    "	color: black;"
    "}"
    );

    // -------------------- Constructor ---------------------
    ui->setupUi(this);
    actualMode = Normal;
    ui->label->setText(""); //"Puede hacer ctrl + z" text reset.
    ui->label_2->setText("Hecho por Raul Armando y Kristan");
    ui->label_3->setText("-- 3D --");

    // ------------- Obj3D creation ----------------

    obj3D = new Object3D();
    obj3D->addPrism(200,100,200,100,100,100);
    obj3D->addPrism(215,200,185,70,200,70);
    obj3D->addPrism(195,400,205,20,40,20);
    obj3D->addPrism(285,400,205,20,40,20);
    obj3D->addPrism(195,400,115,20,40,20);
    obj3D->addPrism(285,400,115,20,40,20);


    double ang = (10 * 3.14159) / 180.0;
    Matrix t1 = Matrix::generateGraphicableSquareMatrix(4, {
                                                            {1,0,0, -250},
                                                            {0,1,0, -250},
                                                            {0,0,1, -150}});
    Matrix t2 = Matrix::generateGraphicableSquareMatrix(4, {
                                                            {1, 0,        0,          0},
                                                            {0, cos(ang), -sin(ang),  0},
                                                            {0, sin(ang), cos(ang),   0}});
    Matrix t3 = Matrix::generateGraphicableSquareMatrix(4, {
                                                            {1,0,0, 250},
                                                            {0,1,0, 250},
                                                            {0,0,1, 150}});

    obj3D->transform(t3 * (t2 * t1));

    this->timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateObj()));
    this->timer->start(30);
}

void MainWindow::updateObj(){
    float ang = (1 * 3.14159) / 180.0;
    Matrix traslateToOrigin = Matrix::generateGraphicableSquareMatrix(4, {
                                                                          {1,0,0, -250},
                                                                          {0,1,0, -250},
                                                                          {0,0,1, -150}
                                                                         });

    Matrix rotate = Matrix::generateGraphicableSquareMatrix(4,
                                                            {
                                                             {cos(ang), 0, sin(ang), 0},
                                                             {0,		1, 0, 	     0},
                                                             {-sin(ang),0, cos(ang), 0}
                                                            });

    Matrix traslateBackToOrigin = Matrix::generateGraphicableSquareMatrix(4,
                                                                          {
                                                                           {1,0,0, 250},
                                                                           {0,1,0, 250},
                                                                           {0,0,1, 150}
                                                                          });

    obj3D->transform(traslateBackToOrigin * (rotate * traslateToOrigin));
    repaint();
}

void MainWindow::paintEvent(QPaintEvent *) {
    //Basic window rendering settings
    QPainter *painter= new QPainter(this);
    painter->setRenderHint(QPainter::Antialiasing,true);
    painter->fillRect(this->rect(), Qt::white);

    //Basic pen settings
    QPen pen;
    pen.setColor(QColor(0,0,0));
    painter->setPen(pen);

    Displayer::object3d(painter, *obj3D);
    delete painter;
}

MainWindow::~MainWindow(){
    delete ui;
    delete obj3D;
}

void MainWindow::mousePressEvent(QMouseEvent *e) {
    QMainWindow::mousePressEvent(e);
}

void MainWindow::mouseMoveEvent(QMouseEvent *e) {}
void MainWindow::mouseReleaseEvent(QMouseEvent* _) {}
void MainWindow::keyPressEvent(QKeyEvent *e){};
void MainWindow::on_actionLeer_triggered() {}
void MainWindow::on_actionGuardar_triggered() {}
void MainWindow::on_actionNormal_triggered() {}
void MainWindow::on_actionInterlineado_triggered() {}

//Herramientas - Ninguno/Modo normal
void MainWindow::on_actionDibujar_triggered() {}
void MainWindow::on_actionTrasladar_triggered() {}
void MainWindow::on_actionRotar_triggered(){}
void MainWindow::on_actionEscalar_triggered(){}
void MainWindow::on_actionEspejo_Reflejar_triggered() {}
void MainWindow::on_actionEscalar_c_direccion_arbr_triggered() {}

///Old code
QString GetActualModeMsg(std::string msg){
    std::string beginning = "Modo actual: ";
    QString algo = QString((beginning + msg).data());
    return algo;
}

std::string ModeToString(Mode mode){
    switch(mode){
        case Normal: return "Normal";
        case Edit: return "Edición";
        case Escalar: return "Escalar";
        case Rotar: return "Rotar";
        case Trasladar: return "Trasladar";
        case Reflejar: return "Reflejar";
        case EscalarArbitrario: return "Escalar Arbitrario";
        case Curvas: return "Bezier";
    }
    return "---";
}

void MainWindow::setActualMode(Mode newMode){
    this->actualMode = newMode;
    this->ui->modo_actual->setText(GetActualModeMsg(ModeToString(newMode)));
}
