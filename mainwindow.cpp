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
bool rotatingY = false, rotatingX = false, rotatingZ = false;

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
    obj3D = new Object3D();

    obj3D->addPrism(400,100,200,100,100,100, GreenBase);
    obj3D->addPrism(415,200,185,70,200,70, GreenBase);
    obj3D->addPrism(395,400,205,20,40,20, DarkGreen);
    obj3D->addPrism(485,400,205,20,40,20, DarkGreen);
    obj3D->addPrism(395,400,115,20,40,20, DarkGreen);
    obj3D->addPrism(485,400,115,20,40,20, DarkGreen);

    // Crear superficies para los ojos
    Surface* ojo1 = new Surface(BlackColor);
    Surface* ojo2 = new Surface(BlackColor);
    Surface* boca1 = new Surface(BlackColor);
    Surface* boca2 = new Surface(BlackColor);
    Surface* boca3 = new Surface(BlackColor);


    // Coordenadas de los ojos
    ojo1->addVertex(Vertex(410, 140, 201));  // Inferior izquierdo
    ojo1->addVertex(Vertex(410, 120, 201));  // Superior izquierdo
    ojo1->addVertex(Vertex(430, 120, 201));  // Superior derecho
    ojo1->addVertex(Vertex(430, 140, 201));  // Inferior derecho

    ojo2->addVertex(Vertex(470, 140, 201));  // Inferior izquierdo
    ojo2->addVertex(Vertex(470, 120, 201));  // Superior izquierdo
    ojo2->addVertex(Vertex(490, 120, 201));  // Superior derecho
    ojo2->addVertex(Vertex(490, 140, 201));  // Inferior derecho

    // Coordenadas de la boca (tres partes)
    boca1->addVertex(Vertex(420, 200, 201));  // Inferior izquierdo
    boca1->addVertex(Vertex(420, 170, 201));  // Superior izquierdo
    boca1->addVertex(Vertex(435, 170, 201));  // Superior derecho
    boca1->addVertex(Vertex(435, 200, 201));  // Inferior derecho

    boca2->addVertex(Vertex(435, 185, 201));  // Inferior izquierdo
    boca2->addVertex(Vertex(435, 155, 201));  // Superior izquierdo
    boca2->addVertex(Vertex(465, 155, 201));  // Superior derecho
    boca2->addVertex(Vertex(465, 185, 201));  // Inferior derecho

    boca3->addVertex(Vertex(465, 200, 201));  // Inferior izquierdo
    boca3->addVertex(Vertex(465, 170, 201));  // Superior izquierdo
    boca3->addVertex(Vertex(480, 170, 201));  // Superior derecho
    boca3->addVertex(Vertex(480, 200, 201));  // Inferior derecho


    // Asignar color negro a las superficies y añadirlas al objeto

    obj3D->addSurface(*ojo1);
    obj3D->addSurface(*ojo2);
    obj3D->addSurface(*boca1);
    obj3D->addSurface(*boca2);
    obj3D->addSurface(*boca3);


    /// 250 x y 250 en y es el centro del creeper???, no es muy preciso...
    Vertex center = obj3D->calculateCentroid();
    Matrix t1 = Matrix::generateGraphicableSquareMatrix(4, {
                                                            {1,0,0, -center.x},
                                                            {0,1,0, -center.y},
                                                            {0,0,1, -center.z}});
    Matrix t2 = Matrix::generateGraphicableSquareMatrix(4, {
                                                            {1, 0,        0,          0},
                                                            {0, cos(ang), -sin(ang),  0},
                                                            {0, sin(ang), cos(ang),   0}});
    Matrix t3 = Matrix::generateGraphicableSquareMatrix(4, {
                                                            {1,0,0, center.x},
                                                            {0,1,0, center.y},
                                                            {0,0,1, center.z}});

    obj3D->transform(t3 * (t2 * t1));

    this->timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateObj()));
    this->timer->start(30);

    connect(ui->btnVuelta, &QPushButton::clicked, this, &MainWindow::toggleRotationY);
    connect(ui->btnMarometa, &QPushButton::clicked, this, &MainWindow::toggleRotationX);
    connect(ui->btnGiro, &QPushButton::clicked, this, &MainWindow::toggleRotationZ);
}

void MainWindow::updateObj() {
    Vertex center = obj3D->calculateCentroid();
    Matrix traslateToOrigin = Matrix::generateGraphicableSquareMatrix(4, {
                                                                             {1, 0, 0, -center.x},
                                                                             {0, 1, 0, -center.y},
                                                                             {0, 0, 1, -center.z}
                                                                         });

    Matrix rotate = getRotationMatrix(currentAxis); // Usa el eje seleccionado

    Matrix traslateBackToOrigin = Matrix::generateGraphicableSquareMatrix(4, {
                                                                                 {1, 0, 0, center.x},
                                                                                 {0, 1, 0, center.y},
                                                                                 {0, 0, 1, center.z}
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

    Displayer::object3d(painter, *obj3D);
    delete painter;
}

MainWindow::~MainWindow(){
    delete obj3D;
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *e) {
    QMainWindow::mousePressEvent(e);
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
    currentAxis = Y_AXIS;
}

void MainWindow::toggleRotationX() {
    rotatingX = !rotatingX;
    currentAxis = X_AXIS;
}

void MainWindow::toggleRotationZ() {
    rotatingZ = !rotatingZ;
    currentAxis = Z_AXIS;
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

