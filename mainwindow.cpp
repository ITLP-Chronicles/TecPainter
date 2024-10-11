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

    if (e->button() == Qt::RightButton) {
        if (!objeto2D->HayLineas())return;
        auto line_ClosestPoint = objeto2D->seleccionada(click.x, click.y);
        actualLine = std::get<0>(line_ClosestPoint);
        pointToMove = std::get<1>(line_ClosestPoint);
        if (std::get<1>(line_ClosestPoint)) objectStack.push(objeto2D->copia());

        //If theres a selected line, is Edit Mode, otherwise Normal Mode
        if (actualLine != nullptr) actualMode = Edit; else actualMode = Normal;

    } else if (e->button() == Qt::LeftButton) {
        deletedObjectStack = *new std::stack<Objeto2D*>();

        if (actualMode == Normal) goto StoreActualLine;
        else if (actualMode == Trasladar){
            preview2D = objeto2D->copia();
            preview2D->updateLineStyleToAll(LineaInterlineada);
            goto StoreActualLine;
        }
        else if (actualMode == Rotar){
            preview2D = objeto2D->copia();
            preview2D->updateLineStyleToAll(LineaInterlineada);
            goto StoreActualLine;
        }
        else if (actualMode == Escalar){
            preview2D = objeto2D->copia();
            preview2D->updateLineStyleToAll(LineaInterlineada);
            goto StoreActualLine;
        }
        else if (actualMode == Edit){
            actualMode = Normal;
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
    if(objeto2D->HayLineas()){
        if(actualMode == Trasladar){
            // Calculate the translation delta
            int deltaX = e->position().x() - actualLine->p2->x;
            int deltaY = e->position().y() - actualLine->p2->y;

            // Apply the translation to preview2D
            preview2D->trasladar(deltaX, deltaY);

            // Update lastMousePos for the next move event
        }
        if (actualMode == Rotar) {
            Punto *centro = objeto2D->centro();
            //int delta1X = actualLine->p2->x - centro->x;
            //int delta1Y = actualLine->p2->y - centro->y;
            int delta2X = actualLine->p1->x - centro->x;
            int delta2Y = actualLine->p1->y - centro->y;
            int delta1X = actualLine->p2->x - actualLine->p1->x;
            int delta1Y = actualLine->p2->y - actualLine->p1->y;
            float angle = atan2(delta1Y, delta1X) - atan2(delta2Y, delta2X);
            //float angle = atan2(delta1Y, delta1X);

            preview2D = objeto2D->copia();
            preview2D->updateLineStyleToAll(LineaInterlineada);
            preview2D->rotar(actualLine->p1->x, actualLine->p1->y, angle);
            delete centro;
        }
        if (actualMode == Escalar) {
            Punto *centro = objeto2D->centro();

            int deltaX = actualLine->p2->x - actualLine->p1->x;
            int deltaY = actualLine->p2->y - actualLine->p1->y;

            float distanciaInicialX = actualLine->p1->x - centro->x;
            float distanciaInicialY = actualLine->p1->y - centro->y;

            if (distanciaInicialX == 0 || distanciaInicialY == 0) {
                delete centro;
                return;
            }

            float factorX = 1 + ((float) deltaX / distanciaInicialX);
            float factorY = 1 + ((float) deltaY / distanciaInicialY);

            preview2D = objeto2D->copia();
            preview2D->updateLineStyleToAll(LineaInterlineada);
            preview2D->escalar(factorX, factorY, actualLine->p1->x, actualLine->p1->y);

            delete centro;
        }
    }

    DisplayChangingLine:
        actualLine->p2->x=e->position().x();
        actualLine->p2->y=e->position().y();
    repaint();
}
void MainWindow::mouseReleaseEvent(QMouseEvent* _) {
    if (!actualLine) return;

    if (actualMode != Edit) objectStack.push(objeto2D->copia());
    if (actualMode == Normal) {
        objeto2D->agregar(actualLine);
        goto UpdateLastLine;
    }

    if(objeto2D->HayLineas()){
        if (actualMode == Trasladar){
            int deltaX = actualLine->p2->x - actualLine->p1->x;
            int deltaY = actualLine->p2->y - actualLine->p1->y;
            objeto2D->trasladar(deltaX, deltaY);
            delete preview2D;
            preview2D = nullptr;
        }

        if (actualMode == Rotar) {
            Punto *centro = objeto2D->centro();
            //int delta1X = actualLine->p2->x - centro->x;
            //int delta1Y = actualLine->p2->y - centro->y;
            int delta1X = actualLine->p2->x - actualLine->p1->x;
            int delta1Y = actualLine->p2->y - actualLine->p1->y;
            int delta2X = actualLine->p1->x - centro->x;
            int delta2Y = actualLine->p1->y - centro->y;
            float angle = atan2(delta1Y, delta1X) - atan2(delta2Y, delta2X);
            //float angle = atan2(delta1Y, delta1X);

            objeto2D->rotar(actualLine->p1->x, actualLine->p1->y, angle);
            delete centro;
        }
        if (actualMode == Escalar) {
            Punto *centro = objeto2D->centro();

            int deltaX = actualLine->p2->x - actualLine->p1->x;
            int deltaY = actualLine->p2->y - actualLine->p1->y;

            float distanciaInicialX = actualLine->p1->x - centro->x;
            float distanciaInicialY = actualLine->p1->y - centro->y;

            if (distanciaInicialX == 0 || distanciaInicialY == 0) {
                delete centro;
                return;
            }

            float factorX = 1 + ((float) deltaX / distanciaInicialX);
            float factorY = 1 + ((float) deltaY / distanciaInicialY);

            objeto2D->escalar(factorX, factorY, actualLine->p1->x, actualLine->p1->y);

            delete centro;
            if (preview2D) {
                delete preview2D;
                preview2D = nullptr;
            }
        }
    }
    if (actualMode == Edit) goto UpdateLastLine;

    UpdateLastLine:
        lastLine = actualLine;
        actualLine = nullptr;

    preview2D = new Objeto2D;
    repaint();
}

void MainWindow::keyPressEvent(QKeyEvent *e){
    if (e->key() == Qt::Key_A) actualMode = Normal;
    if (e->key() == Qt::Key_E) actualMode = Escalar;
    if (e->key() == Qt::Key_R) actualMode = Rotar;
    if (e->key() == Qt::Key_T) actualMode = Trasladar;


    if (e->key() == Qt::Key_Z && e->modifiers() & Qt::ControlModifier && objeto2D->HayLineas()) {
        deletedObjectStack.push(objeto2D->copia());
        delete objeto2D;
        objeto2D = objectStack.top()->copia();
        objectStack.pop();
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

    if (actualMode == Rotar){
        if (preview2D!=nullptr)
            preview2D->desplegar(painter);
    }

    if (actualMode == Escalar){
        if (preview2D!=nullptr)
            preview2D->desplegar(painter);
    }
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

    objectStack = *new std::stack<Objeto2D*>();
    deletedObjectStack = *new std::stack<Objeto2D*>();
    objectStack.push(new Objeto2D);

    preview2D = new Objeto2D;
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
