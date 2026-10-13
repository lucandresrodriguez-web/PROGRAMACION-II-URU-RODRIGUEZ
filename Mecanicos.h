#ifndef MECANICO_H
#define MECANICO_H

#include "Estructuras_taller.h"
#include <string>

Mecanico* agregarMecanico(SistemaTaller* s, Mecanico datos);
Mecanico* buscarMecanicoporID(SistemaTaller* s, int id);
Mecanico* buscarMecanicoporCedula(SistemaTaller* s, const char* cedula);
Mecanico* listarMecanico(SistemaTaller* s, int* cantidad);

int contarOrdenesAbiertasMecanico(SistemaTaller *s, int idMecanico);

void menuRegistrarMecanico(SistemaTaller* s);
void menuBuscarMecanico(SistemaTaller* s);
void menuListarMecanico(SistemaTaller* s);
void mostrarMecanico(SistemaTaller* s);
void mostrarListaMecanico(SistemaTaller* s);

#endif