#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtXml>
#include <qfiledialog.h>
#include <QMouseEvent>
#include "objeto2d.h"
#include <iostream>
#include <tuple>
using namespace std;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    actualLine=nullptr;
    lastLine=nullptr;
    pointToMove=nullptr;
    objeto2D=new Objeto2D();
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
        //If theres a selected line, is Edit Mode, otherwise Normal Mode
        if (actualLine != nullptr) actualMode = Edit; else actualMode = Normal;
    } else if (e->button() == Qt::LeftButton) {
        actualMode = Normal;
        actualLine = new Linea(click.x, click.y, click.x, click.y);
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
        objeto2D->agregar(actualLine);
        goto UpdateLastLine;
    }
    if (actualMode == Edit) goto UpdateLastLine;

    UpdateLastLine:
        lastLine = actualLine;
        actualLine = nullptr;
}

void MainWindow::keyPressEvent(QKeyEvent *e){
    if(!objeto2D->HayLineas())return;

    if (e->key() == Qt::Key_Z && e->modifiers() & Qt::ControlModifier) {
        objeto2D->eliminar(lastLine);
        lastLine = objeto2D->final;
        actualMode = Normal;
        repaint();
    } else {
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

    objeto2D = new Objeto2D();
    while (!lineaXML.isNull()) {
        Linea* linea = new Linea();

        QDomElement puntoXML = lineaXML.firstChildElement();
        if (!puntoXML.isNull()) {
            float x = puntoXML.attribute("X").toFloat();
            float y = puntoXML.attribute("Y").toFloat();
            linea->p1 = new Punto(x, y);
            std::cout << "Punto X=" << x << " Y=" << y << std::endl;

            puntoXML = puntoXML.nextSiblingElement();
            if (!puntoXML.isNull()) {
                x = puntoXML.attribute("X").toFloat();
                y = puntoXML.attribute("Y").toFloat();
                linea->p2 = new Punto(x, y);
                std::cout << "Punto X=" << x << " Y=" << y << std::endl;
            }
        }
        objeto2D->agregar(linea);
        lineaXML = lineaXML.nextSiblingElement();
    }
    repaint();
}

void MainWindow::on_actionGuardar_2_triggered()
{
    QString file= QFileDialog::getSaveFileName
        (this,"Guardar Dibujo","*.xml");
    QDomDocument document;

    QDomElement objeto2DXML=document.createElement("Objeto2D");
    document.appendChild(objeto2DXML);

    Linea* pointer = objeto2D->inicio;
    while (pointer != nullptr)
    {
        QDomElement linea=document.createElement("Linea");
        objeto2DXML.appendChild(linea);

        QDomElement punto=document.createElement("Punto");
        punto.setAttribute("X",pointer->p1->x);
        punto.setAttribute("Y",pointer->p1->y);
        linea.appendChild(punto);

        punto=document.createElement("Punto");
        punto.setAttribute("X",pointer->p2->x);
        punto.setAttribute("Y",pointer->p2->y);
        linea.appendChild(punto);

        pointer = pointer->sig;
    }
    pointer = nullptr;

    QFile sFile(file);
    sFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream archivo(&sFile);
    archivo<<document.toString();
    sFile.close();
}

void MainWindow::on_actionGuardar_triggered()
{

}

