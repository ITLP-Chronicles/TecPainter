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

float ang = (2 * 3.14159) / 180.0;
Axis currentAxis = NO_AXIS;
bool rotatingHead = false, walking = false;
Matrix transformacionAcumulada = Matrix::generateGraphicableSquareMatrix(4, {
                                                                           {1,0,0, 0},
                                                                           {0,1,0, 0},
                                                                           {0,0,1, 0}});
Matrix transformacionAcumuladaCabeza = Matrix::generateGraphicableSquareMatrix(4, {
                                                                             {1,0,0, 0},
                                                                             {0,1,0, 0},
                                                                             {0,0,1, 0}});
Matrix transformacionAcumuladaPierna1 = Matrix::generateGraphicableSquareMatrix(4, {
                                                                                   {1,0,0, 0},
                                                                                   {0,1,0, 0},
                                                                                   {0,0,1, 0}});
Matrix transformacionAcumuladaPierna2 = Matrix::generateGraphicableSquareMatrix(4, {
                                                                                    {1,0,0, 0},
                                                                                    {0,1,0, 0},
                                                                                    {0,0,1, 0}});
Matrix transformacionAcumuladaPierna3 = Matrix::generateGraphicableSquareMatrix(4, {
                                                                                    {1,0,0, 0},
                                                                                    {0,1,0, 0},
                                                                                    {0,0,1, 0}});
Matrix transformacionAcumuladaPierna4 = Matrix::generateGraphicableSquareMatrix(4, {
                                                                                    {1,0,0, 0},
                                                                                    {0,1,0, 0},
                                                                                    {0,0,1, 0}});


Object3D* head = new Object3D();
Object3D* torso = new Object3D();
Object3D* limb1 = new Object3D();
Object3D* limb2 = new Object3D();
Object3D* limb3 = new Object3D();
Object3D* limb4 = new Object3D();

Object3D* head2 = new Object3D();
Object3D* torso2 = new Object3D();
Object3D* limb12 = new Object3D();
Object3D* limb22 = new Object3D();
Object3D* limb32 = new Object3D();
Object3D* limb42 = new Object3D();

Object3D* head3 = new Object3D();
Object3D* torso3 = new Object3D();
Object3D* limb13 = new Object3D();
Object3D* limb23 = new Object3D();
Object3D* limb33 = new Object3D();
Object3D* limb43 = new Object3D();

Object3D* head4 = new Object3D();
Object3D* torso4 = new Object3D();
Object3D* limb14 = new Object3D();
Object3D* limb24 = new Object3D();
Object3D* limb34 = new Object3D();
Object3D* limb44 = new Object3D();

Vertex center;

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
    center = torso->calculateCentroid();
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
    this->timer->start(60);

    connect(ui->btnVuelta, &QPushButton::clicked, this, &MainWindow::toggleRotationY);
    connect(ui->btnMarometa, &QPushButton::clicked, this, &MainWindow::toggleRotationX);
    connect(ui->btnGiro, &QPushButton::clicked, this, &MainWindow::toggleRotationZ);

    delete ojo1;
    delete ojo2;
    delete boca1;
    delete boca2;
    delete boca3;
}

// Variables de control para la rotación de las piernas
float angleLimb = 0.0f;         // Ángulo actual de las piernas
float angleIncrement = ang;    // Incremento de ángulo para cada actualización
bool increasingAngle = true;    // Dirección de rotación: true si aumenta, false si disminuye
// Cambia el parámetro de angulación para cada pierna

void MainWindow::updateObj() {
    center = torso->calculateCentroid();

    if (rotatingHead) {
        independantRotation(head, Y_AXIS, transformacionAcumuladaCabeza, center, ang); // Usar 'ang' para la cabeza
    }

    if (walking) {
        if (increasingAngle) {
            angleLimb += angleIncrement;
            if (angleLimb >= 6 * M_PI / 180) increasingAngle = false;
        } else {
            angleLimb -= angleIncrement;
            if (angleLimb <= -6 * M_PI / 180) increasingAngle = true;
        }

        Vertex intersection1(limb1->x, limb1->y, limb1->z - limb1->sizez);
        independantRotation(limb1, X_AXIS, transformacionAcumuladaPierna1, intersection1, angleLimb);

        Vertex intersection2(limb2->x, limb2->y, limb2->z - limb2->sizez);
        independantRotation(limb2, X_AXIS, transformacionAcumuladaPierna2, intersection2, -angleLimb);

        Vertex intersection3(limb3->x, limb3->y, limb3->z);
        independantRotation(limb3, X_AXIS, transformacionAcumuladaPierna3, intersection3, angleLimb);

        Vertex intersection4(limb4->x, limb4->y, limb4->z);
        independantRotation(limb4, X_AXIS, transformacionAcumuladaPierna4, intersection4, -angleLimb);
    }

    // Generar las matrices de transformación para el torso
    Matrix translationToOrigin = Matrix::generateGraphicableSquareMatrix(4, {
                                                                             {1, 0, 0, -center.x},
                                                                             {0, 1, 0, -center.y},
                                                                             {0, 0, 1, -center.z}});
    Matrix rotate = getRotationMatrix(currentAxis, ang);
    Matrix translationBack = Matrix::generateGraphicableSquareMatrix(4, {
                                                                         {1, 0, 0, center.x},
                                                                         {0, 1, 0, center.y},
                                                                         {0, 0, 1, center.z}});

    head->reset();
    torso->reset();
    limb1->reset();
    limb2->reset();
    limb3->reset();
    limb4->reset();

    transformacionAcumulada = transformacionAcumulada * (translationBack * (rotate * translationToOrigin));

    head->transform(transformacionAcumuladaCabeza);
    head->transform(transformacionAcumulada);
    torso->transform(transformacionAcumulada);
    limb1->transform(transformacionAcumuladaPierna1);
    limb1->transform(transformacionAcumulada);
    limb2->transform(transformacionAcumuladaPierna2);
    limb2->transform(transformacionAcumulada);
    limb3->transform(transformacionAcumuladaPierna3);
    limb3->transform(transformacionAcumulada);
    limb4->transform(transformacionAcumuladaPierna4);
    limb4->transform(transformacionAcumulada);

    rotate = getRotationMatrix(X_AXIS, -M_PI/2);
    Matrix rotation = (translationBack * (rotate * translationToOrigin));
    Matrix traslate1 = Matrix::generateGraphicableSquareMatrix(4, {
                                                                   {0.35, 0, 0, 450},
                                                                   {0, 0.35, 0, -70},
                                                                   {0, 0, 0.35, 0}});
    Matrix previewTransformation = (translationBack * (traslate1 * translationToOrigin));

    head2 = head->copy();
    torso2 = torso->copy();

    limb12 = limb1->copy();
    limb22 = limb2->copy();
    limb32 = limb3->copy();
    limb42 = limb4->copy();

    head2->transform(rotation);
    torso2->transform(rotation);
    limb12->transform(rotation);
    limb22->transform(rotation);
    limb32->transform(rotation);
    limb42->transform(rotation);

    head2->transform(previewTransformation);
    torso2->transform(previewTransformation);
    limb12->transform(previewTransformation);
    limb22->transform(previewTransformation);
    limb32->transform(previewTransformation);
    limb42->transform(previewTransformation);

    rotate = getRotationMatrix(Y_AXIS, M_PI/2);
    rotation = (translationBack * (rotate * translationToOrigin));
    traslate1 = Matrix::generateGraphicableSquareMatrix(4, {
                                                                   {0.35, 0, 0, 450},
                                                                   {0, 0.35, 0, 120},
                                                                   {0, 0, 0.35, 0}});
    previewTransformation = (translationBack * (traslate1 * translationToOrigin));

    head3 = head->copy();
    torso3 = torso->copy();

    limb13 = limb1->copy();
    limb23 = limb2->copy();
    limb33 = limb3->copy();
    limb43 = limb4->copy();

    head3->transform(rotation);
    torso3->transform(rotation);
    limb13->transform(rotation);
    limb23->transform(rotation);
    limb33->transform(rotation);
    limb43->transform(rotation);

    head3->transform(previewTransformation);
    torso3->transform(previewTransformation);
    limb13->transform(previewTransformation);
    limb23->transform(previewTransformation);
    limb33->transform(previewTransformation);
    limb43->transform(previewTransformation);

    rotate = getRotationMatrix(X_AXIS, M_PI/2);
    rotation = (translationBack * (rotate * translationToOrigin));
    traslate1 = Matrix::generateGraphicableSquareMatrix(4, {
                                                                   {0.35, 0, 0, 450},
                                                                   {0, 0.35, 0, 300},
                                                                   {0, 0, 0.35, 0}});
    previewTransformation = (translationBack * (traslate1 * translationToOrigin));

    head4 = head->copy();
    torso4 = torso->copy();
    limb14 = limb1->copy();
    limb24 = limb2->copy();
    limb34 = limb3->copy();
    limb44 = limb4->copy();

    head4->transform(rotation);
    torso4->transform(rotation);
    limb14->transform(rotation);
    limb24->transform(rotation);
    limb34->transform(rotation);
    limb44->transform(rotation);

    head4->transform(previewTransformation);
    torso4->transform(previewTransformation);
    limb14->transform(previewTransformation);
    limb24->transform(previewTransformation);
    limb34->transform(previewTransformation);
    limb44->transform(previewTransformation);

    repaint();
}

void MainWindow::independantRotation(Object3D* objeto, Axis eje, Matrix& transformacionAcumuladaObjeto, Vertex centro, float anguloPersonalizado) {
    Matrix translationToOrigin = Matrix::generateGraphicableSquareMatrix(4, {{1, 0, 0, -centro.x}, {0, 1, 0, -centro.y}, {0, 0, 1, -centro.z}});
    Matrix rotate = getRotationMatrix(eje, anguloPersonalizado); // Se usa el ángulo personalizado
    Matrix translationBack = Matrix::generateGraphicableSquareMatrix(4, {{1, 0, 0, centro.x}, {0, 1, 0, centro.y}, {0, 0, 1, centro.z}});

    objeto->reset();
    transformacionAcumuladaObjeto = transformacionAcumuladaObjeto * (translationBack * (rotate * translationToOrigin));
    objeto->transform(transformacionAcumuladaObjeto); // Aplica transformación local
    objeto->transform(transformacionAcumulada);       // Aplica transformación global
}

Matrix MainWindow::getRotationMatrix(Axis axis, float angle) {
    switch (axis) {
    case X_AXIS:
        return Matrix::generateGraphicableSquareMatrix(4, {{1, 0, 0, 0}, {0, cos(angle), -sin(angle), 0}, {0, sin(angle), cos(angle), 0}});
    case Y_AXIS:
        return Matrix::generateGraphicableSquareMatrix(4, {{cos(angle), 0, sin(angle), 0}, {0, 1, 0, 0}, {-sin(angle), 0, cos(angle), 0}});
    case Z_AXIS:
        return Matrix::generateGraphicableSquareMatrix(4, {{cos(angle), -sin(angle), 0, 0}, {sin(angle), cos(angle), 0, 0}, {0, 0, 1, 0}});
    default:
        return Matrix::generateGraphicableSquareMatrix(4, {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}});
    }
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
    Displayer::object3d(painter, *head2);
    Displayer::object3d(painter, *torso2);
    Displayer::object3d(painter, *limb12);
    Displayer::object3d(painter, *limb22);
    Displayer::object3d(painter, *limb32);
    Displayer::object3d(painter, *limb42);
    Displayer::object3d(painter, *head3);
    Displayer::object3d(painter, *torso3);
    Displayer::object3d(painter, *limb13);
    Displayer::object3d(painter, *limb23);
    Displayer::object3d(painter, *limb33);
    Displayer::object3d(painter, *limb43);
    Displayer::object3d(painter, *head4);
    Displayer::object3d(painter, *torso4);
    Displayer::object3d(painter, *limb14);
    Displayer::object3d(painter, *limb24);
    Displayer::object3d(painter, *limb34);
    Displayer::object3d(painter, *limb44);
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
    if (currentAxis == Y_AXIS){
        currentAxis = NO_AXIS;
    } else {
        currentAxis = Y_AXIS;
    }
}

void MainWindow::toggleRotationX() {
    if (currentAxis == X_AXIS){
        currentAxis = NO_AXIS;
    } else {
        currentAxis = X_AXIS;
    }
}

void MainWindow::toggleRotationZ() {
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

void MainWindow::on_btnGiroCabeza_clicked()
{
    rotatingHead = !rotatingHead;
}


void MainWindow::on_btnCaminar_clicked()
{
    walking = !walking;
}


void MainWindow::on_btnUpView_clicked()
{
    // Generar las matrices de transformación para el torso
    Matrix translationToOrigin = Matrix::generateGraphicableSquareMatrix(4, {
                                                                             {1, 0, 0, -center.x},
                                                                             {0, 1, 0, -center.y},
                                                                             {0, 0, 1, -center.z}});
    Matrix rotate = getRotationMatrix(X_AXIS, -M_PI/2);
    Matrix translationBack = Matrix::generateGraphicableSquareMatrix(4, {
                                                                         {1, 0, 0, center.x},
                                                                         {0, 1, 0, center.y},
                                                                         {0, 0, 1, center.z}});

    transformacionAcumulada = transformacionAcumulada * (translationBack * (rotate * translationToOrigin));
    Matrix rotation = (translationBack * (rotate * translationToOrigin));

    head->transform(rotation);
    torso->transform(rotation);

    limb1->transform(rotation);
    limb2->transform(rotation);
    limb3->transform(rotation);
    limb4->transform(rotation);

    repaint();
}


void MainWindow::on_btnSideView_clicked()
{
    // Generar las matrices de transformación para el torso
    Matrix translationToOrigin = Matrix::generateGraphicableSquareMatrix(4, {
                                                                             {1, 0, 0, -center.x},
                                                                             {0, 1, 0, -center.y},
                                                                             {0, 0, 1, -center.z}});
    Matrix rotate = getRotationMatrix(Y_AXIS, M_PI/2);
    Matrix translationBack = Matrix::generateGraphicableSquareMatrix(4, {
                                                                         {1, 0, 0, center.x},
                                                                         {0, 1, 0, center.y},
                                                                         {0, 0, 1, center.z}});

    transformacionAcumulada = transformacionAcumulada * (translationBack * (rotate * translationToOrigin));

    Matrix rotation = (translationBack * (rotate * translationToOrigin));

    head->transform(rotation);
    torso->transform(rotation);

    limb1->transform(rotation);
    limb2->transform(rotation);
    limb3->transform(rotation);
    limb4->transform(rotation);

    repaint();
}


void MainWindow::on_btnBottomView_clicked()
{
    // Generar las matrices de transformación para el torso
    Matrix translationToOrigin = Matrix::generateGraphicableSquareMatrix(4, {
                                                                             {1, 0, 0, -center.x},
                                                                             {0, 1, 0, -center.y},
                                                                             {0, 0, 1, -center.z}});
    Matrix rotate = getRotationMatrix(X_AXIS, M_PI/2);
    Matrix translationBack = Matrix::generateGraphicableSquareMatrix(4, {
                                                                         {1, 0, 0, center.x},
                                                                         {0, 1, 0, center.y},
                                                                         {0, 0, 1, center.z}});

    transformacionAcumulada = transformacionAcumulada * (translationBack * (rotate * translationToOrigin));

    Matrix rotation = (translationBack * (rotate * translationToOrigin));

    head->transform(rotation);
    torso->transform(rotation);

    limb1->transform(rotation);
    limb2->transform(rotation);
    limb3->transform(rotation);
    limb4->transform(rotation);

    repaint();
}

