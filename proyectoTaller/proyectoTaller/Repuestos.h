#ifndef REPUESTO_H
#define REPUESTO_H

#include "Estructura_taller.h"
#include <string>

Repuesto* agregarRepuesto(SistemaTaller* s, Repuesto datos);
Repuesto* buscarRepuestoPorID(SistemaTaller* s, int id);
Repuesto* buscarRepuestoPorCodigo(SistemaTaller* s, const char* codigo);
Repuesto* bucarRepuestoPorNombreParcial(SistemaTaller* s, const char* subcadena);
Repuesto* listarRepuesto(SistemaTaller* s, int* cantidad);

bool menuRegistrarEntradaMercancia(SistemaTaller* s, int idRepuesto, int CantidadAdicional);
bool cambiarPrecioRepuesto(SistemaTaller* s, int idRepuesto, float nuevoPrecio);
bool eliminarRepuesto(SistemaTaller* s, int id);

void menuRegistrarRepuesto(SistemaTaller* s);
void menuBuscarRepuesto(SistemaTaller* s);
void menuEntradaMercancia(SistemaTaller* s);
void menuCambiarPrecio(SistemaTaller* s);
void menuEliminarRepuesto(SistemaTaller* s);
void menuListarRepuestos(SistemaTaller* s);
void mostrarRepuesto(Repuesto* repuesto);
void mostrarListaRepuestos(Repuesto** repuestos, int cantidad);

#endif