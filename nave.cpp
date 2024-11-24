// Archivos de implementación (.cpp): Aquí implementas los métodos definidos en los encabezados.

#include "nave.h"

Nave::Nave(int tamanio, int x, int y)
{
    this->tamanio = tamanio;
    this->impacto = 0; // iniciar impactos en contador 0
    this->posicion_x = x;
    this->posicion_y = y;
}

void Nave::impacto_recibido()
{
    impacto++;
}
bool Nave::hundido()
{
    return impacto >= tamanio;
}