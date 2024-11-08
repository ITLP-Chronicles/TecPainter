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

float ang = (1 * 3.14159) / 180.0;
Axis currentAxis = Y_AXIS;

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

void MainWindow::updateObj() {
    Matrix traslateToOrigin = Matrix::generateGraphicableSquareMatrix(4, {
                                                                             {1, 0, 0, -250},
                                                                             {0, 1, 0, -250},
                                                                             {0, 0, 1, -150}
                                                                         });

    Matrix rotate = getRotationMatrix(currentAxis); // Usa el eje seleccionado

    Matrix traslateBackToOrigin = Matrix::generateGraphicableSquareMatrix(4, {
                                                                                 {1, 0, 0, 250},
                                                                                 {0, 1, 0, 250},
                                                                                 {0, 0, 1, 150}
                                                                             });

    obj3D->transform(traslateBackToOrigin * (rotate * traslateToOrigin));
    repaint();
}


Matrix MainWindow::getRotationMatrix(Axis axis) {
    switch (axis) {
    case X_AXIS:
        return Matrix::generateGraphicableSquareMatrix(4, {
                                                           {1, 0,        0,         0},
                                                           {0, cos(ang), -sin(ang), 0},
                                                           {0, sin(ang), cos(ang),  0}});
    case Y_AXIS:
        return Matrix::generateGraphicableSquareMatrix(4, {
                                                           {cos(ang), 0, sin(ang), 0},
                                                           {0,        1, 0,        0},
                                                           {-sin(ang), 0, cos(ang), 0}});
    case Z_AXIS:
        return Matrix::generateGraphicableSquareMatrix(4, {
                                                           {cos(ang), -sin(ang), 0, 0},
                                                           {sin(ang), cos(ang),  0, 0},
                                                           {0,        0,         1, 0}});
    }
    return Matrix::generateGraphicableSquareMatrix(4, {
                                                           {1, 0, 0, 0},
                                                           {0, 1, 0, 0},
                                                           {0, 0, 1, 0}});
}

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

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::RightButton){
        this->updateObj();
    }
    QMainWindow::mousePressEvent(e);
}


void MainWindow::mouseMoveEvent(QMouseEvent *e) {}

void MainWindow::mouseReleaseEvent(QMouseEvent* _) {
}

void MainWindow::keyPressEvent(QKeyEvent *e){
    if (e->key() == Qt::Key_A) setActualMode(Normal);
    if (e->key() == Qt::Key_E) setActualMode(Escalar);
    if (e->key() == Qt::Key_R) setActualMode(Rotar);
    if (e->key() == Qt::Key_T) setActualMode(Trasladar);
    if (e->key() == Qt::Key_V) setActualMode(Trasladar);
    if (e->key() == Qt::Key_W) setActualMode(Reflejar);
    if (e->key() == Qt::Key_Q) setActualMode(EscalarArbitrario);
};

void MainWindow::paintEvent(QPaintEvent *) {
    //Basic window rendering settings
    QPainter *painter= new QPainter(this);
    painter->setRenderHint(QPainter::Antialiasing,true);
    painter->fillRect(this->rect(), Qt::white);

    //Basic pen settings
    QPen pen;
    pen.setColor(QColor(0,0,255));
    painter->setPen(pen);

    Displayer::object3d(painter, *obj3D);
    delete painter;
}

void MainWindow::on_actionLeer_triggered()
{}

void MainWindow::on_actionGuardar_triggered()
{}

void MainWindow::on_actionNormal_triggered()
{
/*    setActualMode(Normal);
    tipoLineaSeleccionada = LineaNormal*/;
}

void MainWindow::on_actionInterlineado_triggered()
{
/*    setActualMode(Normal);
    tipoLineaSeleccionada = LineaInterlineada*/;
}

//Herramientas - Ninguno/Modo normal
void MainWindow::on_actionDibujar_triggered()
{
    //setActualMode(Normal);
}

void MainWindow::on_actionTrasladar_triggered()
{
/*    setActualMode(Trasladar);

    preview2D = objeto2D->copia();
    preview2D->updateLineStyleToAll(LineaInterlineada)*/;
}

void MainWindow::on_actionRotar_triggered() {
    setActualMode(Rotar);
}

void MainWindow::on_actionEscalar_triggered() {
    setActualMode(Escalar);
}

void MainWindow::on_actionEspejo_Reflejar_triggered() {
    setActualMode(Reflejar);
}

void MainWindow::on_actionEscalar_c_direccion_arbr_triggered() {
    setActualMode(EscalarArbitrario);
}
void MainWindow::on_btnVuelta_clicked()
{

}


void MainWindow::on_btnMarometa_clicked()
{

}


void MainWindow::on_btnGiro_clicked()
{

}

void MainWindow::setRotationAxisX() {
    currentAxis = X_AXIS;
}

void MainWindow::setRotationAxisY() {
    currentAxis = Y_AXIS;
}

void MainWindow::setRotationAxisZ() {
    currentAxis = Z_AXIS;
}
