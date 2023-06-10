#ifndef __LISTA_ENLAZADA_H__
#define __LISTA_ENLAZADA_H__

class ListaEnlazada {

    public:
    ListaEnlazada();
    ~ListaEnlazada();

    int longitud();

    void agregarAtras(const int elemento);
    
    int iesimo(const int posicion);
    
    int suma();

    void borrarUltimo();

    void borrarIesimo(const int posicion);


    // iteración
    int actual();

    void avanzar();
    
    void retroceder();
   
    private:
        struct nodo {
            int elemento;
            nodo* anterior; // Agregado.
            nodo* siguiente;
        };
        nodo* _primero;
        int _longitud;
        nodo* _actual;
        nodo* _ultimo; // Agregado.
};

#endif
