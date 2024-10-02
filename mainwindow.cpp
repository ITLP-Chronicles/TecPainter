#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtXml>
#include <qfiledialog.h>
#include <QMouseEvent>
#include "objeto2d.h"
#include <stack>

using namespace std;
TipoLinea tipoLineaSeleccionada = LineaNormal;
Objeto2D *previewDraw = nullptr;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    actualLine=nullptr;
    lastLine=nullptr;
    pointToMove=nullptr;
    objeto2D=new Objeto2D();
    //copia2D = new Objeto2D();

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
}



MainWindow::~MainWindow()
{
    while (!objectStack.empty()) {
        delete &objectStack.top();
        objectStack.pop();
    }
    resetDeletedObjectStack();
    delete objeto2D;
    if(actualLine)delete actualLine;
    if(lastLine)delete lastLine;
    if(pointToMove)delete pointToMove;
    actualLine = nullptr;
    lastLine = nullptr;
    pointToMove = nullptr;
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    Punto click(e->position().x(), e->position().y());
    if (e->button() == Qt::RightButton) {
        if (!objeto2D->HayLineas())return;
        auto line_ClosestPoint = objeto2D->seleccionada(click.x, click.y);
        actualLine = std::get<0>(line_ClosestPoint);
        pointToMove = std::get<1>(line_ClosestPoint);
        if (std::get<1>(line_ClosestPoint)) objectStack.push(objeto2D->copia());
        //If theres a selected line, is Edit Mode, otherwise Normal Mode
        if (actualLine != nullptr) actualMode = Edit; else actualMode = Normal;
    } else if (e->button() == Qt::LeftButton) {
        resetDeletedObjectStack();
        actualMode = Normal;
        actualLine = new Linea(click.x, click.y, click.x, click.y);
        actualLine->tipoLinea = tipoLineaSeleccionada;
    }
    repaint();
    //Call original parent event
    QMainWindow::mousePressEvent(e);
}

void MainWindow::mouseMoveEvent(QMouseEvent *e) {
    if (!actualLine)return;

    if(actualMode == Normal) goto DisplayChangingLine;
    if(actualMode == Edit){
        if (pointToMove == actualLine->p1){
            actualLine->p1 = actualLine->p2;
            actualLine->p2 = pointToMove;
        }
        goto DisplayChangingLine;
    }

    DisplayChangingLine:
        actualLine->p2->x=e->position().x();
        actualLine->p2->y=e->position().y();

    repaint();
}

void MainWindow::mouseReleaseEvent(QMouseEvent* _) {
    if (!actualLine) return;

    if (actualMode == Normal) {
        objectStack.push(objeto2D->copia());
        objeto2D->agregar(actualLine);
        //copia2D->agregar(actualLine->copia());
        goto UpdateLastLine;
    }

    if (actualMode == Edit) goto UpdateLastLine;

    UpdateLastLine:
        lastLine = actualLine;
        actualLine = nullptr;
}

void MainWindow::keyPressEvent(QKeyEvent *e){

    if (e->key() == Qt::Key_Z && e->modifiers() & Qt::ControlModifier && objeto2D->HayLineas()) {
        deletedObjectStack.push(objeto2D->copia());
        delete objeto2D;
        objeto2D = objectStack.top()->copia();
        objectStack.pop();
        actualMode = Normal;
        repaint();
    } else if (e->key() == Qt::Key_Y && e->modifiers() & Qt::ControlModifier){
        if (!deletedObjectStack.empty()){
            objectStack.push(objeto2D->copia());
            delete objeto2D;
            objeto2D = deletedObjectStack.top()->copia();
            deletedObjectStack.pop();
        }
        repaint();
    }
    else {
        QMainWindow::keyPressEvent(e);
    }
};

void MainWindow::paintEvent(QPaintEvent *) {
    QPainter *painter=new QPainter(this);
    painter->setRenderHint(QPainter::Antialiasing,true);
    painter->fillRect(this->rect(), Qt::white);

    QPen pen;
    pen.setColor(QColor(0,0,255));
    painter->setPen(pen);
    if (actualLine!=nullptr)
        actualLine->desplegar(painter);
    objeto2D->desplegar(painter);

    //copia2D->trasladar(150,150);
    //pen.setColor(QColor(255,0,0));
    //painter->setPen(pen);
    //copia2D->desplegar(painter);

    delete painter;
}

void MainWindow::on_actionLeer_triggered()
{
    QDomDocument document;
    QString sFile= QFileDialog::getOpenFileName(this,"Abrir Dibujo");

    QFile file(sFile);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    document.setContent(&file);

    QDomElement objeto2DXML = document.firstChildElement();
    QDomElement lineaXML = objeto2DXML.firstChildElement();
    QDomElement puntoXML=lineaXML.firstChildElement();

    objeto2D = new Objeto2D;
    objeto2D->leer(lineaXML,puntoXML);
    repaint();
}

void MainWindow::on_actionGuardar_triggered()
{
    QString file= QFileDialog::getSaveFileName
        (this,"Guardar Dibujo","*.xml");
    QDomDocument document;

    QDomElement objeto2DXML=document.createElement("Objeto2D");
    document.appendChild(objeto2DXML);

    objeto2D->guardar(document,objeto2DXML);

    QFile sFile(file);
    sFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream archivo(&sFile);
    archivo<<document.toString();
    sFile.close();
}

void MainWindow::resetDeletedObjectStack(){
    while (!deletedObjectStack.empty()) {
        delete deletedObjectStack.top();
        deletedObjectStack.pop();
    }
}

void MainWindow::on_actionNormal_triggered()
{
    tipoLineaSeleccionada = LineaNormal;
}

void MainWindow::on_actionInterlineado_triggered()
{
    tipoLineaSeleccionada = LineaInterlineada;
}

void MainWindow::on_actionDibujar_triggered()
{
    actualMode = Edit;
}

