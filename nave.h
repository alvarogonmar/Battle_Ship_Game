// Archivos de encabezado (.h): Aquí defines las clases, sus atributos y los métodos
// (pero solo las declaraciones, no las implementaciones).

#pragma once // Asegurar que el archivo solo se incluya una vez.

class Nave
{
public:
    int tamanio; // tamanio del barco
    int impacto; // contar los impactos recibidos
    int posicion_x, posicion_y;

    Nave(int tamanio, int x, int y); // constructor del tamanio del barco
    void impacto();
    bool hundido(); // Verificar si el barco esta hundido
};