#ifndef OBJETO2D_H
#define OBJETO2D_H

#include "linea.h"
#include "bezier.h"
#include <tuple>
#include <QtXml>

//Dependencias
//- Línea
//- Qt

//Objeto2D | Lista enlazada con nodos
//Almacena todos los detalles del dibujo completo (Toda la pantalla, la lógica está mezclada con
//la lógica que tendría una lista enlazada con nodos. Siendo los nodos líneas también a su vez.
class Objeto2D
{
public:
    //Campos de la clase

    //(Nodo) Indica la primera línea de la lista interna de nodos de líneas.
    //Por defecto es nullptr. (No se inicializa)
    Linea *inicio;

    //(Nodeo) Indica la última línea de la lista interna de nodos de líneas.
    //Por defecto es nullptr. (No se inicializa)
    Linea *final;

    //Indica el estilo de línea por defecto que se configurará cada línea agregada nueva.
    TipoLinea defaultLineStyle;

    //Indica la lista de curvaInicio de bezier
    //TODO: Por qué hay 2 y no solo una? --------------------------------
    std::vector<Bezier*>* listaDeBezieres;

    //Constructor por defecto. Inicializa todas las variables en sus configuraciones por defecto
    Objeto2D();

    //Clona el objeto2D y regresa un nuevo objeto2D alojado en el heap. (Puntero)
    Objeto2D *copia();

    //Destructor.
    ~Objeto2D();

    void agregarLinea(Linea *);
    void eliminar(Linea *);
    void eliminarTodasLineas();
    bool HayLineas();
    //Establece un estilo de línea para cada una de las líneas ya existentes de la lista interna de este objeto.
    //No tiene relación alguna con el estilo de línea por defecto en 'defaultLineStyle'
    void updateLineStyleToAll(TipoLinea newStyle);

    void agregarCurva(Bezier *);
    void eliminarCurva(Bezier*);
    bool HayCurvas();
    void desplegar(QPainter *);


    //Obten el centro de este objeto2D de forma dinámica tomando en cuenta las líneas internas de este obj.
    Punto *centro();

    // Verifica si el click hecho en clickX y en clickY concuerda con la
    // ubicación de cualquier línea dibujada interna de este objeto.
    //
    // Regresa:
    // -------------------
    // 		Regresa una tupla con la siguiente información en caso de éxito:
    // 			1. La línea en el que se realizó el click
    // 			2. El p1 ó p2 más cercano de la línea con respecto a las coordenadas del clickX y clickY
    // 		De lo contrario:
    // 			1. La línea es nullptr
    // 			2. El punto es nullptr
    // 		Pero siempre regresa una tupla
    std::tuple<Linea*, Punto*> seleccionada(int clickX, int clickY);

    // --------------------- Graficación 2D SIN MATRICES -----------------------

    void trasladar(float newX, float newY);
    void rotar(float xr, float yr, float ang);
    void escalar(float factorX, float factorY, float centerX, float centerY);



    // --------------------- Graficación 2D CON MATRICES -----------------------

    void transformar(Matriz2D*);

    void trasladar(Linea* inputLinea);
    void rotar(Linea * lineaInput);
    void escalar(Linea * lineaInput);
    void reflejar(Linea * lineaInput);
    void escalarArbitrario(Linea * lineaInput);


    //----------- Guardado de archivos (Funcionalidad especial externa) --------------

    void leer(QDomElement, QDomElement);
    void guardar(QDomDocument,QDomElement);

private:
    // Dada una función (anónima|normal), recorre todas las líneas internas de este objeto
    // 2D y ejecuta la función sobre esa línea. Método de utilidad meramente.
    void ForEachLine(std::function<void(Linea*)> callBack);
};

#endif // OBJETO2D_H
