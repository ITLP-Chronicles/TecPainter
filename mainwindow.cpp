#include <QtXml>
#include <qfiledialog.h>
#include <QMouseEvent>
#include <QPainter>
#include <QLabel>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "matrix.h"
#include "displayer.h"
#include "rotationutils.h"

using namespace std;

float ang = (1 * 3.14159) / 180.0;
Axis currentAxis = NO_AXIS;
bool rotatingY = false, rotatingX = false, rotatingZ = false;
Matrix transformacionAcumulada = Matrix::generateGraphicableSquareMatrix(4, {
                                                                           {1,0,0, 0},
                                                                           {0,1,0, 0},
                                                                           {0,0,1, 0}});
Matrix transformacionAcumuladaCabeza = Matrix::generateGraphicableSquareMatrix(4, {
                                                                             {1,0,0, 0},
                                                                             {0,1,0, 0},
                                                                             {0,0,1, 0}});

Vertex accumulatedAngles = Vertex(0, 0, 0);


Object3D* head = new Object3D();
Object3D* torso = new Object3D();
Object3D* limb1 = new Object3D();
Object3D* limb2 = new Object3D();
Object3D* limb3 = new Object3D();
Object3D* limb4 = new Object3D();

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

    Vertex angles(M_PI/4, M_PI/3, M_PI/6); // Your angles in radians

    Matrix R = RotationUtils::eulerAnglesToRotationMatrix(angles);
    auto debugR = Matrix::debug(R);

    Vertex resultAngles = RotationUtils::rotationMatrixToEulerAngles(R);


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

    head->addPrism(400,100,200,100,100,100, GreenBase);

    // Añadir las superficies de los ojos y la boca a la cabeza
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


    /// 250 x y 250 en y es el centro del creeper???, no es muy preciso...
    Vertex center = torso->calculateCentroid();
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


    // Realizar las operaciones de multiplicación y asignación correctamente
    transformacionAcumulada = transformacionAcumulada * (t3 * (t2 * t1));
    transformacionAcumuladaCabeza = transformacionAcumuladaCabeza * (t3 * (t2 * t1));
    head->transform(transformacionAcumuladaCabeza);
    head->transform(transformacionAcumulada);
    torso->transform(transformacionAcumulada);
    limb1->transform(transformacionAcumulada);
    limb2->transform(transformacionAcumulada);
    limb3->transform(transformacionAcumulada);
    limb4->transform(transformacionAcumulada);

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

Matrix getTranslationMatrix(double x, double y, double z) {
    return Matrix::generateGraphicableSquareMatrix(4, {
                                                       {1, 0, 0, x},
                                                       {0, 1, 0, y},
                                                       {0, 0, 1, z}});
}

void MainWindow::updateObj() {
    if (currentAxis == NO_AXIS) return;

    switch(currentAxis) {
    case X_AXIS:
        accumulatedAngles.x += ang;
        break;
    case Y_AXIS:
        accumulatedAngles.y += ang;
        break;
    case Z_AXIS:
        accumulatedAngles.z += ang;
        break;
    }

    ang = fmod(ang, M_PI*2); ///angle % 2pi
    if (ang < 0) ang += 360.0;


    // Get complete rotation matrix from accumulated angles


    Vertex center = torso->calculateCentroid();

    ///1. Go to origin
    Matrix translationToOrigin = getTranslationMatrix(-center.x, -center.y, -center.z);


    ///2. Cancel rotation
    Vertex negatedRotation = Vertex(-accumulatedAngles.x, -accumulatedAngles.y, -accumulatedAngles.z);
    Matrix negatedMatrixRotation = RotationUtils::eulerAnglesToRotationMatrix(negatedRotation);
    Matrix negatedMatrixRotationGraphicable = Matrix::generateGraphicableSquareMatrix(4, {
                                                                   {negatedMatrixRotation.data[0][0], negatedMatrixRotation.data[0][1], negatedMatrixRotation.data[0][2], 0},
                                                                   {negatedMatrixRotation.data[1][0], negatedMatrixRotation.data[1][1], negatedMatrixRotation.data[1][2], 0},
                                                                   {negatedMatrixRotation.data[2][0], negatedMatrixRotation.data[2][1], negatedMatrixRotation.data[2][2], 0}});

    ///3. Applicate new rotation
    Matrix rotation = RotationUtils::eulerAnglesToRotationMatrix(accumulatedAngles);
    Matrix rotationGraphicable = Matrix::generateGraphicableSquareMatrix(4, {
                                                                   {rotation.data[0][0], rotation.data[0][1], rotation.data[0][2], 0},
                                                                   {rotation.data[1][0], rotation.data[1][1], rotation.data[1][2], 0},
                                                                   {rotation.data[2][0], rotation.data[2][1], rotation.data[2][2], 0}});

    ///4. Put the obj back to its original pos
    Matrix translationBack = getTranslationMatrix(center.x, center.y, center.z);

    head->reset();
    torso->reset();
    limb1->reset();
    limb2->reset();
    limb3->reset();
    limb4->reset();

    transformacionAcumulada = transformacionAcumulada * (translationBack * (rotationGraphicable * (negatedMatrixRotationGraphicable * translationToOrigin)));

    head->transform(transformacionAcumulada);
    head->transform(transformacionAcumuladaCabeza);
    torso->transform(transformacionAcumulada);
    limb1->transform(transformacionAcumulada);
    limb2->transform(transformacionAcumulada);
    limb3->transform(transformacionAcumulada);
    limb4->transform(transformacionAcumulada);

    repaint();
}


Matrix getRotationMatrix(Axis axis, double desiredAngle){
    Vertex angles(0, 0, 0);

    switch (axis) {
    case X_AXIS:
        angles = Vertex(desiredAngle, 0, 0);  // Rotation around X
        break;
    case Y_AXIS:
        angles = Vertex(0, desiredAngle, 0);  // Rotation around Y
        break;
    case Z_AXIS:
        angles = Vertex(0, 0, desiredAngle);  // Rotation around Z
        break;
    case NO_AXIS:
        return Matrix::generateGraphicableSquareMatrix(4, {
                                                           {1, 0, 0, 0},
                                                           {0, 1, 0, 0},
                                                           {0, 0, 1, 0}});
    }

    // Get 3x3 rotation matrix
    Matrix R = RotationUtils::eulerAnglesToRotationMatrix(angles);

    // Convert to 4x4 matrix for your transformations
    return Matrix::generateGraphicableSquareMatrix(4, {
                                                       {R.data[0][0], R.data[0][1], R.data[0][2], 0},
                                                       {R.data[1][0], R.data[1][1], R.data[1][2], 0},
                                                       {R.data[2][0], R.data[2][1], R.data[2][2], 0}});
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
