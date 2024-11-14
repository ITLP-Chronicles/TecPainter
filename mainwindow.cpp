#include <QtXml>
#include <qfiledialog.h>
#include <QMouseEvent>
#include <QPainter>
#include <QLabel>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "matrix.h"
#include "displayer.h"
#include "math.h"

using namespace std;

float ang = M_PI / 180.0;
Axis currentAxis = NO_AXIS;
bool rotatingY = false, rotatingX = false, rotatingZ = false;

Matrix transformacionAcumulada = Matrix::generateIdentityMatrix(4);
Matrix transformacionAcumuladaCabeza = Matrix::generateIdentityMatrix(4);

Object3D* head = new Object3D();
Object3D* torso = new Object3D();
Object3D* limb1 = new Object3D();
Object3D* limb2 = new Object3D();
Object3D* limb3 = new Object3D();
Object3D* limb4 = new Object3D();

Object3D* headOriginal = nullptr;
Object3D* torsoOriginal = nullptr;
Object3D* limb1Original = nullptr;
Object3D* limb2Original = nullptr;
Object3D* limb3Original = nullptr;
Object3D* limb4Original = nullptr;

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

    // ------------- Obj3D creation ----------------
    QColor GreenBase = QColor::fromRgb(58, 140, 55);
    QColor DarkGreen = QColor::fromRgb(30, 90, 29);
    QColor LightGreen= QColor::fromRgb(113, 192, 101);//sin usar de momento, falta dibujar la carita del creeper, centrarlo y hacerlo más grande.// Define el color negro para la cara
    QColor BlackColor = QColor::fromRgb(0, 0, 0);

    // Crear superficies para los ojos
    Surface* ojo1 = new Surface(BlackColor);
    Surface* ojo2 = new Surface(BlackColor);
    Surface* boca1 = new Surface(BlackColor);
    Surface* boca2 = new Surface(BlackColor);
    Surface* boca3 = new Surface(BlackColor);

    // Coordenadas de los ojos
    ojo1->addRectangleOnXY(410,120,201,20,20);
    ojo2->addRectangleOnXY(470,120,201,20,20);

    // Coordenadas de la boca (tres partes)
    boca1->addRectangleOnXY(420,170,201,15,30);
    boca2->addRectangleOnXY(435,155,201,30,30);
    boca3->addRectangleOnXY(465,170,201,15,30);

    // Añadir las superficies de los ojos y la boca a la cabeza
    head->addPrism(400,100,200,100,100,100, GreenBase);
    head->addSurface(*ojo1);
    head->addSurface(*ojo2);
    head->addSurface(*boca1);
    head->addSurface(*boca2);
    head->addSurface(*boca3);

    torso->addPrism(415,200,185,70,200,70, GreenBase);
    limb1->addPrism(395,400,205,20,40,20, DarkGreen);
    limb2->addPrism(485,400,205,20,40,20, DarkGreen);
    limb3->addPrism(395,400,115,20,40,20, DarkGreen);
    limb4->addPrism(485,400,115,20,40,20, DarkGreen);

    Vertex center = torso->calculateCentroid();
    head->rotate(ang,currentAxis,center);
    torso->rotate(ang,currentAxis,center);
    limb1->rotate(ang,currentAxis,center);
    limb2->rotate(ang,currentAxis,center);
    limb3->rotate(ang,currentAxis,center);
    limb4->rotate(ang,currentAxis,center);

    this->timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateObj()));
    this->timer->start(30);

    connect(ui->btnVuelta, &QPushButton::clicked, this, &MainWindow::toggleRotationY);
    connect(ui->btnMarometa, &QPushButton::clicked, this, &MainWindow::toggleRotationX);
    connect(ui->btnGiro, &QPushButton::clicked, this, &MainWindow::toggleRotationZ);

    delete ojo1;
    delete ojo2;
    delete boca1;
    delete boca2;
    delete boca3;
}

void MainWindow::updateObj() {

    Vertex center = torso->calculateCentroid();
    head->rotate(ang,currentAxis,center);
    torso->rotate(ang,currentAxis,center);
    limb1->rotate(ang,currentAxis,center);
    limb2->rotate(ang,currentAxis,center);
    limb3->rotate(ang,currentAxis,center);
    limb4->rotate(ang,currentAxis,center);

    repaint();
}

void MainWindow::mouseMoveEvent(QMouseEvent* _) {}
void MainWindow::mouseReleaseEvent(QMouseEvent* _) {}
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

    Displayer::object3d(painter, *head);
    Displayer::object3d(painter, *torso);
    Displayer::object3d(painter, *limb1);
    Displayer::object3d(painter, *limb2);
    Displayer::object3d(painter, *limb3);
    Displayer::object3d(painter, *limb4);
    delete painter;
}

MainWindow::~MainWindow(){
    delete head;
    delete torso;
    delete limb1;
    delete limb2;
    delete limb3;
    delete limb4;
    delete headOriginal;
    delete torsoOriginal;
    delete limb1Original;
    delete limb2Original;
    delete limb3Original;
    delete limb4Original;
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *e) {
    QMainWindow::mousePressEvent(e);
}

void MainWindow::setRotationAxisX() {
    if (currentAxis == X_AXIS){
        currentAxis = NO_AXIS;
    } else {
        currentAxis = X_AXIS;
    }
}

void MainWindow::setRotationAxisY() {
    if (currentAxis == Y_AXIS){
        currentAxis = NO_AXIS;
    } else {
        currentAxis = Y_AXIS;
    }
}

void MainWindow::setRotationAxisZ() {
    if (currentAxis == Z_AXIS){
        currentAxis = NO_AXIS;
    } else {
        currentAxis = Z_AXIS;
    }
}

// -------------------- Stuff ------------------------
void MainWindow::on_actionLeer_triggered(){}
void MainWindow::on_actionGuardar_triggered(){}
void MainWindow::on_actionNormal_triggered(){}
void MainWindow::on_actionInterlineado_triggered(){}
void MainWindow::on_actionDibujar_triggered(){}
void MainWindow::on_actionTrasladar_triggered(){}
void MainWindow::on_actionRotar_triggered(){}
void MainWindow::on_actionEscalar_triggered(){}
void MainWindow::on_actionEspejo_Reflejar_triggered() {}
void MainWindow::on_actionEscalar_c_direccion_arbr_triggered() {}
void MainWindow::on_btnVuelta_clicked(){}
void MainWindow::on_btnMarometa_clicked(){}
void MainWindow::on_btnGiro_clicked(){}


void MainWindow::toggleRotationY() {
    rotatingY = !rotatingY;
    if (currentAxis == Y_AXIS){
        currentAxis = NO_AXIS;
    } else {
        currentAxis = Y_AXIS;
    }
}

void MainWindow::toggleRotationX() {
    rotatingX = !rotatingX;
    if (currentAxis == X_AXIS){
        currentAxis = NO_AXIS;
    } else {
        currentAxis = X_AXIS;
    }
}

void MainWindow::toggleRotationZ() {
    rotatingZ = !rotatingZ;
    if (currentAxis == Z_AXIS){
        currentAxis = NO_AXIS;
    } else {
        currentAxis = Z_AXIS;
    }
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
