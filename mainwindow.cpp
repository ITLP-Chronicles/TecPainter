#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtXml>
#include <qfiledialog.h>
#include <QMouseEvent>
#include "objeto2d.h"
#include <stack>

using namespace std;
TipoLinea tipoLineaSeleccionada = LineaNormal;
Objeto2D *preview2D = nullptr;
QPoint lastMousePos;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    actualLine=nullptr;
    lastLine=nullptr;
    pointToMove=nullptr;
    objeto2D=new Objeto2D();
    preview2D = new Objeto2D();
    actualMode = Normal;

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
    delete preview2D;
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    Punto click(e->position().x(), e->position().y());
    lastMousePos = e->pos();

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

        if (actualMode == Normal) goto StoreActualLine;
        else if (actualMode == Trasladar){
            preview2D = objeto2D->copia();
            preview2D->updateLineStyleToAll(LineaInterlineada);
            goto StoreActualLine;
        }

        StoreActualLine:
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
    if(actualMode == Trasladar){
        // Calculate the translation delta
        int deltaX = e->position().x() - lastMousePos.x();
        int deltaY = e->position().y() - lastMousePos.y();

        // Apply the translation to preview2D
        preview2D->trasladar(deltaX, deltaY);

        // Update lastMousePos for the next move event
        lastMousePos = e->pos();
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

    if (actualMode == Trasladar){
        int deltaX = lastMousePos.x() - actualLine->p1->x;
        int deltaY = lastMousePos.y() - actualLine->p1->y;
        objeto2D->trasladar(deltaX, deltaY);
        delete preview2D;
        preview2D = nullptr;
    }

    if (actualMode == Edit) goto UpdateLastLine;

    UpdateLastLine:
        lastLine = actualLine;
        actualLine = nullptr;

    repaint();
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
    //Basic window rendering settings
    QPainter *painter=new QPainter(this);
    painter->setRenderHint(QPainter::Antialiasing,true);
    painter->fillRect(this->rect(), Qt::white);

    //Basic pen settings
    QPen pen;
    pen.setColor(QColor(0,0,255));
    painter->setPen(pen);

    if (actualMode == Normal){
        if (actualLine!=nullptr)
            actualLine->desplegar(painter);
    }

    objeto2D->desplegar(painter);

    if (actualMode == Trasladar){
        if (preview2D!=nullptr)
            preview2D->desplegar(painter);
    }
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
    actualMode = Normal;
    tipoLineaSeleccionada = LineaNormal;
}

void MainWindow::on_actionInterlineado_triggered()
{
    actualMode = Normal;
    tipoLineaSeleccionada = LineaInterlineada;
}

//Herramientas - Ninguno/Modo normal
void MainWindow::on_actionDibujar_triggered()
{
    actualMode = Edit;
}

void MainWindow::on_actionTrasladar_triggered()
{
    actualMode = Trasladar;

    preview2D = objeto2D->copia();
    preview2D->updateLineStyleToAll(LineaInterlineada);
}

void MainWindow::on_actionRotar_triggered()
{
    actualMode = Rotar;
}

void MainWindow::on_actionEscalar_triggered()
{
    actualMode = Escalar;
}
