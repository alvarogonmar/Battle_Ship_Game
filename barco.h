// Archivos de encabezado (.h): Aquí defines las clases, sus atributos y los métodos
// (pero solo las declaraciones, no las implementaciones).

#pragma once // Asegurar que el archivo solo se incluya una vez.

class Barco
{
public:
    int tamanio; // tamanio del barco
    int impacto; // contar los impactos recibidos

    Barco(int tamanio); // constructor del tamanio del barco
    bool hundido();     // Verificar si el barco esta hundido
};