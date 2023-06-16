#include "Editor.h"
#include "iostream"
using std::string;


Editor::Editor(const set<string> & conectivos) {
    this->_editor = {};
    this->_conectivos = conectivos;
    this->_vocabulario = {};
    this -> _apariciones = {};
    this->_conteo_palabras = 0; 
}

bool Editor::es_conectivo(string palabra){
    bool res = false;
    if(this->_conectivos.find(palabra) != this->_conectivos.end()){
        res = true;
    }
    return res;
}

string Editor::texto() const {
    string res = "";
    for (int i = 0; i < this->_editor.size(); i++){
        if(i < _editor.size()-1){
        res.append(this->_editor[i]);
        res.append(" ");}
        else{
            res.append(this->_editor[i]);
        }
    }
    return res;
}

const set<string>& Editor::vocabulario() const {
    return _vocabulario;
}

const set<string>& Editor::conectivos() const {
    return _conectivos;
}

int Editor::conteo_palabras() const { 
	return _conteo_palabras; 
}

int Editor::longitud() const { 
	return _editor.size();
}

void Editor::agregar_atras(const string& oracion) {
    string temporal = "";
    for(int i = 0; i < oracion.size(); i++){
        if(oracion[i] == ' '){
             if(!(es_conectivo(temporal))){
                this->_conteo_palabras++;
                this->_vocabulario.insert(temporal);
                this->_apariciones[temporal].insert(_editor.size());
            } 
            this->_editor.push_back(temporal);
            temporal = "";
        }
        else{
            temporal.push_back(oracion[i]);
        }
    }
    if(!(es_conectivo(temporal))){
                this->_conteo_palabras++;
                this->_vocabulario.insert(temporal);
                this->_apariciones[temporal].insert(_editor.size());
            }
            this->_editor.push_back(temporal); 
}

const set<int> & Editor::buscar_palabra(const string& palabra) const {
    return this->_apariciones.find(palabra)->second;
}

void Editor::insertar_palabras(const string& oracion, int pos) {
    //Dividir la oracion e insertarlas guardando su posicion. Además modifica las variables internas
    string temporal = "";
    int cant_palabras = 0;
    auto it = this->_editor.begin() + pos;
    int i;
    for(int i = 0; i < oracion.size(); i++){
        if(oracion[i] == ' '){
             if(!(es_conectivo(temporal))){
                this->_conteo_palabras++;
                this->_vocabulario.insert(temporal);
                this->_apariciones[temporal].insert(pos);
            } 
            this->_editor.insert(it,temporal);
            temporal = "";
            it++;
            pos++;
        }
        else{
            temporal.push_back(oracion[i]);
            cant_palabras++;
        }
    }
    if(!(es_conectivo(temporal))){
                this->_conteo_palabras++;
                this->_vocabulario.insert(temporal);
                this->_apariciones[temporal].insert(pos);
            }
            this->_editor.insert(it,temporal);
            cant_palabras++;

    //Modificar las posiciones de las palabras subsecuentes
    

    set<int> set_temporal;
    auto it2 = this->_apariciones.find(this->_editor[pos]);

    while(pos < this->_editor.size()){
        set_temporal = it2->second;
        for (auto iterator = set_temporal.begin(); set_temporal.size(); iterator++){
        }
    }
    
}

void Editor::borrar_posicion(int pos) {
    // Pre: 0 ≤ posicion ≤ longitud()-1
    // Post: Se elimina la palabra ubicada en esa posición del texto.
    string palabra = _editor[pos];

    if (!es_conectivo(palabra)){
        _conteo_palabras--;
        _vocabulario.erase(palabra);
    }  // Eliminar la palabra del conjunto de vocabulario si no es conectiva.

    _editor.erase(next(_editor.begin(), pos));  // Eliminar la palabra en la posición indicada

    auto it = _apariciones.find(palabra); // Busca la palabra especificada
    if (it != _apariciones.end()) {
        it->second.erase(pos);  // Eliminar la posición de la palabra en el mapa de apariciones
        if (it->second.empty())
            _apariciones.erase(it);  // Si no quedan más apariciones de la palabra, eliminarla del mapa
    }

    // Actualizar las posiciones de las palabras siguientes en el mapa de apariciones
    for (auto& pair : _apariciones) { // Itera sobre cada par clave-valor en _apariciones
        auto& posiciones = pair.second; // Valor.
        for (auto it = posiciones.begin(); it != posiciones.end(); ++it) { // Itera sobre cada posición en el conjunto posiciones
            if (*it > pos)
                (*it)--;  // Decrementar las posiciones mayores a la posición eliminada
            if (*it == pos)
                it = posiciones.erase(it);  // Eliminar la posición si coincide con la eliminada
        }
    }
}

int Editor::borrar_palabra(const string& palabra) {
    // Pre: El string palabra no tiene espacios ni signos de puntuación.
    // Post: Se elimina la palabra indicada de todo el texto, y se devuelve la cantidad de palabras eliminadas.
    set<int> posiciones = buscar_palabra(palabra); // Obtener las posiciones de la palabra

    int cantidadBorrada = 0; // Inicializar la cantidad borrada

    while (!posiciones.empty()) {
        int pos = *posiciones.begin();

        borrar_posicion(pos); // Utilizar la función borrar_posicion() para eliminar la palabra del texto
        cantidadBorrada += 1; // Incrementar la cantidad borrada

        posiciones.erase(pos); // Eliminar la posición actual del conjunto de posiciones
    }

    return cantidadBorrada; // Devolver la cantidad de palabras borradas
}

void Editor::reemplazar_palabra(const string& palabra1, const string& palabra2) {
    /* Completar */}


/*int main() {
    //set<std::string> conectivos = { "y", "o", "pero" };
    Editor editor({"y", "o", "pero"});

    editor.agregar_atras("Este es un ejemplo de texto para pruebas");
    editor.borrar_posicion(2);
    // El texto resultante debe ser: "Este es ejemplo de texto para pruebas"
    cout << editor.texto() << endl;

    return 0;
}*/
