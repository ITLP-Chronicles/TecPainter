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
QLabel *label_CommandsCheatSheet = nullptr;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    actualMode = Normal;

    //Matrix thisToMatrix(1,3, {{23, 3, 23}});
    //auto cut = Matrix::debug(thisToMatrix);

    obj3D = new Object3D();
    Surface *s = new Surface();
    s->addVertex(Vertex(200,200,200));
    s->addVertex(Vertex(300,200,200));
    s->addVertex(Vertex(300,300,200));
    s->addVertex(Vertex(200,300,200));
    obj3D->addSurface(*s);

    double ang = (10 * 3.14159) / 180.0;
    Matrix t1 = Matrix::generateGraphicableSquareMatrix(4, {{1,0,0,-250}, {0,1,0,-250}, {0,0,1, -150}});
    auto aaaaa = Matrix::debug(t1);
    Matrix t2 = Matrix::generateGraphicableSquareMatrix(4, {{1,0,0,0}, {0, cos(ang), -sin(ang), 0}, {0, sin(ang), cos(ang)}});
    auto aaa = Matrix::debug(t2);
    Matrix t3 = Matrix::generateGraphicableSquareMatrix(4, {{1,0,0,250}, {0,1,0, 250}, {0,0,1, 150}});
    auto aaaa =  Matrix::debug(t3);

    obj3D->transform(t3 *(t2 * t1));


    //Testing -------------------------------
    // Matrix m(3,3 ,{{1,0,0}, {0,1,0}, {0,0,1}});
    // auto z = Matrix::debug(m);

    // Matrix m2(3,3, {{1,2,3}, {4,5,6}, {7,8,9}});
    // auto zz = Matrix::debug(m2);

    // Matrix algo = m * m2;
    // auto zzz = Matrix::debug(algo);
    // /// 1, 2 , 3
    // /// 4, 5 , 6
    // /// 7, 8 , 9

    // ///El 3 es para indicar el tamaño cuadratico (filas y columnas)
    // Matrix aa = Matrix::generateGraphicableSquareMatrix(3,{{1,2,3}, {1,2,3}});
    // auto zzzz = Matrix::debug(aa);
    // /// 1, 2, 3
    /// 1, 2, 3
    /// 0, 0, 1


    // Setting colors ------------------------------
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

    label_CommandsCheatSheet = new QLabel(
    R"(
Comandos Modos:
- Normal: A
- Editar: E
- Trasladar: T ó V
- Rotar: R
- Borrar Dibujo: D
- Reflejar: W
    )"
    , this);
    label_CommandsCheatSheet->setGeometry(660,360, 300,300);
    label_CommandsCheatSheet->show();

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
    // while (!objectStack.empty()) {
    //     delete objectStack.top();
    //     objectStack.pop();
    // }
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    //Point click(e->position().x(), e->position().y());

    // if (e->button() == Qt::RightButton) {
    //     //Reset selection
    //     actualLine = nullptr;
    //     pointToMove = nullptr;
    //     curva = nullptr;
    //     curvaControlPointSelected = nullptr;

    //     //FIRST: Try to see if a line was selected first (avoid calculate at first if bezier curves were selectedj as well)

    //     //A line was selected?
    //     auto [line, closestPoint] = objeto2D->seleccionada(click.x, click.y);
    //     actualLine = line;
    //     pointToMove = closestPoint;

    //     //A Line was selected! //Note: both are nullptr or none of them. Thats how  "seleccionada(x,y)" works
    //     if (actualLine && pointToMove){
    //         objectStack.push(objeto2D->copia());
    //         setActualMode(Edit);
    //     }
    //     //A line wasn't selected...
    //     else{
    //         //Now, a curve bezier was selected instead?
    //         auto [curve, pointSelected] = objeto2D->seleccionadaCurva(click.x, click.y);
    //         curva = curve;
    //         curvaControlPointSelected = pointSelected;
    //         setActualMode(Curvas);

    //         //A curve was selected! //Note: both are nullptr or none of them. Thats how  "seleccionadaCurva(x,y)" works
    //         if (curva && curvaControlPointSelected){
    //             //You can do some logic here. Right now it isn't neccesary Atte: Kris
    //         } else {
    //             //Neither a line nor a curve was selected... (click on blank space) so, create a new bezier curve right there
    //             //and set it as our actual "this.curva" but "this.curvaControlPointSelected" will be nullptr. Its just creating it
    //             //not selecting any point yet.
    //             addBezier(&click);
    //         }
    //     }
    // } else if (e->button() == Qt::LeftButton) {
    //     deletedObjectStack = *new std::stack<Objeto2D*>();//Reset stack

    //     if (actualMode == Normal) goto StoreActualLine;
    //     else if (actualMode == Trasladar){
    //         preview2D = objeto2D->copia();
    //         preview2D->updateLineStyleToAll(LineaInterlineada);
    //         goto StoreActualLine;
    //     }
    //     else if (actualMode == Rotar){
    //         preview2D = objeto2D->copia();
    //         preview2D->updateLineStyleToAll(LineaInterlineada);
    //         goto StoreActualLine;
    //     }
    //     else if (actualMode == Escalar || actualMode == EscalarArbitrario){
    //         preview2D = objeto2D->copia();
    //         preview2D->updateLineStyleToAll(LineaInterlineada);
    //         goto StoreActualLine;
    //     }
    //     else if (actualMode == Edit || actualMode == Curvas){
    //         setActualMode(Normal);
    //         goto StoreActualLine;
    //     }
    //     else if (actualMode == Trasladar){
    //         tipoLineaSeleccionada = LineaInterlineada;
    //     }
    //     else if (actualMode == Reflejar){
    //         tipoLineaSeleccionada = LineaInterlineada;
    //         goto StoreActualLine;
    //     }

    //     StoreActualLine:
    //         actualLine = new Linea(click.x, click.y, click.x, click.y);
    //         actualLine->tipoLinea = tipoLineaSeleccionada;
    // }

    // repaint();

    //Call original parent event
    QMainWindow::mousePressEvent(e);
}


void MainWindow::mouseMoveEvent(QMouseEvent *e) {

    //Do line logic if theres a line selected
    // if (actualLine){
    //     if(actualMode == Normal) goto DisplayChangingLine;
    //     if(actualMode == Edit){
    //         if (pointToMove == actualLine->p1){
    //             actualLine->p1 = actualLine->p2;
    //             actualLine->p2 = pointToMove;
    //         }
    //         goto DisplayChangingLine;
    //     }
    //     if(objeto2D->HayLineas() || objeto2D->HayCurvas()){
    //         if(actualMode == Trasladar){
    //             preview2D = objeto2D->copia();
    //             preview2D->updateLineStyleToAll(LineaInterlineada);
    //             preview2D->trasladar(actualLine);
    //         }
    //         if (actualMode == Rotar) {
    //             preview2D = objeto2D->copia();
    //             preview2D->updateLineStyleToAll(LineaInterlineada);
    //             preview2D->rotar(actualLine);
    //         }
    //         if (actualMode == Escalar) {

    //             preview2D = objeto2D->copia();
    //             preview2D->updateLineStyleToAll(LineaInterlineada);
    //             preview2D->escalar(actualLine);
    //         }

    //         if (actualMode == Reflejar){
    //             preview2D = objeto2D->copia();
    //             preview2D->updateLineStyleToAll(LineaInterlineada);
    //             preview2D->reflejar(actualLine);
    //         }

    //         if (actualMode == EscalarArbitrario){
    //             preview2D = objeto2D->copia();
    //             preview2D->updateLineStyleToAll(LineaInterlineada);
    //             preview2D->escalarArbitrario(actualLine);
    //         }

    //     }

    //     DisplayChangingLine:
    //         actualLine->p2->x=e->position().x();
    //         actualLine->p2->y=e->position().y();
    // }

    // //Do curve logic if one is selected
    // if(curva && curvaControlPointSelected){
    //     curvaControlPointSelected->x = e->position().x();
    //     curvaControlPointSelected->y = e->position().y();
    //     curva->RecalculateSelf();
    // }
    repaint();
}

void MainWindow::mouseReleaseEvent(QMouseEvent* _) {


    // if (curva && curvaControlPointSelected){
    //     curva = nullptr;
    //     curvaControlPointSelected = nullptr;
    //     objectStack.push(objeto2D->copia());
    //     setActualMode(Normal);
    // }
    // if (actualLine){
    //     if (actualMode != Edit) objectStack.push(objeto2D->copia());
    //     if (actualMode == Normal) {
    //         objeto2D->agregarLinea(actualLine);
    //         goto UpdateLastLine;
    //     }

    //     if (actualMode == Reflejar){
    //         tipoLineaSeleccionada = LineaNormal;
    //         objeto2D->reflejar(actualLine);
    //         repaint();
    //         goto ReflejarCase;
    //     }

    //     if(objeto2D->HayLineas() || objeto2D->HayCurvas()){
    //         if (actualMode == Trasladar){
    //             objeto2D->trasladar(actualLine);
    //             if (preview2D) {
    //                 delete preview2D;
    //                 preview2D = nullptr;
    //             }
    //         }

    //         if (actualMode == Rotar) {
    //             objeto2D->rotar(actualLine);
    //             if (preview2D) {
    //                 delete preview2D;
    //                 preview2D = nullptr;
    //             }
    //         }
    //         if (actualMode == Escalar) {
    //             objeto2D->escalar(actualLine);

    //             if (preview2D) {
    //                 delete preview2D;
    //                 preview2D = nullptr;
    //             }
    //         }

    //         if (actualMode == EscalarArbitrario) {
    //             objeto2D->escalarArbitrario(actualLine);

    //             if (preview2D) {
    //                 delete preview2D;
    //                 preview2D = nullptr;
    //             }
    //         }
    //     }

    //     if (actualMode == Edit) goto UpdateLastLine;

    //     UpdateLastLine:
    //         lastLine = actualLine;
    //         actualLine = nullptr;


    //     ReflejarCase:
    //         actualLine = nullptr;
    //         preview2D = new Objeto2D;

    // }

    repaint();
}

void MainWindow::keyPressEvent(QKeyEvent *e){
    if (e->key() == Qt::Key_A) setActualMode(Normal);
    if (e->key() == Qt::Key_E) setActualMode(Escalar);
    if (e->key() == Qt::Key_R) setActualMode(Rotar);
    if (e->key() == Qt::Key_T) setActualMode(Trasladar);
    if (e->key() == Qt::Key_V) setActualMode(Trasladar);
    if (e->key() == Qt::Key_W) setActualMode(Reflejar);
    if (e->key() == Qt::Key_Q) setActualMode(EscalarArbitrario);
    if (e->key() == Qt::Key_D){
        //delete objeto2D;
        //objeto2D = new Objeto2D();
        repaint();
    }

    // if (e->key() == Qt::Key_Z && e->modifiers() & Qt::ControlModifier && (objeto2D->HayLineas() || objeto2D->HayCurvas())) {
    //     deletedObjectStack.push(objeto2D->copia());
    //     delete objeto2D;
    //     objeto2D = objectStack.top()->copia();
    //     objectStack.pop(); repaint(); } else if (e->key() == Qt::Key_Y && e->modifiers() & Qt::ControlModifier){
    //     if (!deletedObjectStack.empty()){
    //         objectStack.push(objeto2D->copia());
    //         delete objeto2D;
    //         objeto2D = deletedObjectStack.top()->copia();
    //         deletedObjectStack.pop();
    //     }
    //     repaint();
    // }
    // else {
    //     QMainWindow::keyPressEvent(e);
    // }
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


    // if (actualMode == Normal){
    //     if (actualLine!=nullptr)
    //         actualLine->desplegar(painter);
    // }

    // else if (actualMode == Reflejar){
    //     if (actualLine != nullptr)
    //         actualLine->desplegar(painter);

    //     if (preview2D != nullptr)
    //         preview2D->desplegar(painter);
    // }
    // else if (actualMode != Edit){
    //     if (preview2D!= nullptr)
    //         preview2D->desplegar(painter);

    // }

    // objeto2D->desplegar(painter);
    delete painter;
}

void MainWindow::on_actionLeer_triggered()
{
    // QDomDocument document;
    // QString sFile= QFileDialog::getOpenFileName(this,"Abrir Dibujo");

    // QFile file(sFile);
    // file.open(QIODevice::ReadOnly | QIODevice::Text);
    // document.setContent(&file);

    // QDomElement objeto2DXML = document.firstChildElement();

    // objeto2D = new Objeto2D;
    // objeto2D->leer(objeto2DXML);

    // objectStack = *new std::stack<Objeto2D*>();
    // deletedObjectStack = *new std::stack<Objeto2D*>();
    // objectStack.push(new Objeto2D);

    // preview2D = new Objeto2D;
    // repaint();
}

void MainWindow::on_actionGuardar_triggered()
{
    // QString file= QFileDialog::getSaveFileName
    //     (this,"Guardar Dibujo","*.xml");
    // QDomDocument document;

    // QDomElement objeto2DXML=document.createElement("Objeto2D");
    // document.appendChild(objeto2DXML);

    // objeto2D->guardar(document,objeto2DXML);

    // QFile sFile(file);
    // sFile.open(QIODevice::WriteOnly | QIODevice::Text);
    // QTextStream archivo(&sFile);
    // archivo<<document.toString();
    // sFile.close();
}

//void MainWindow::addBezier(Point* click){
    // objectStack.push(objeto2D->copia());

    // //Curva bezier por defecto
    // auto help = new std::vector<Point*>();
    // help->push_back(new Point(click->x - 150, click->y));
    // help->push_back(new Point(click->x - 50, click->y - 200));
    // help->push_back(new Point(click->x + 50, click->y + 200));
    // help->push_back(new Point(click->x + 150, click->y));

    // curva = new Bezier(help, 500); //500 points to draw // Set as actual curva
    // curva->tipoLineasBezier = tipoLineaSeleccionada;
    // objeto2D->agregarCurva(curva); //Store it in objeto2D
//}

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
