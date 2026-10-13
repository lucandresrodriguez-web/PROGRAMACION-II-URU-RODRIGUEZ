#ifndef ORDEN_SERVICIO_H
#define ORDEN_SERVICIO_H

#include "Estructuras_taller.h"
#include <string>

OrdenServicio* abrirOrden(SistemaTaller* s, int idVehiculo, int idMecanico, const char* descripcionFalla, int KilometrajeIngreso, const char* fechaActual);

bool agregarRepuestoAOrden(SistemaTaller* s, int idOrden, int idRepuesto, int cantidad);
bool quitarRepuestoDeOrden(SistemaTaller* s, int idOrden, int idRepuesto);
bool cerrarOrden(SistemaTaller* s, int idOrden, float manoObra, const char* fechaActual);
bool anularOrden(SistemaTaller* s, int idOrden);

float calcularTotalOrden(OrdenServicio* Orden);

OrdenServicio* buscarOrdenPorID(SistemaTaller* s, int id);

OrdenServicio** listaOrdenesPorEstado(SistemaTaller* s, const char* estado, int* cantidad);
OrdenServicio** listaOrdenesPorVehiculo(SistemaTaller* s, int* vehiculo, int* cantidad);
OrdenServicio** listaTodasLasOrdenes(SistemaTaller* s, int* cantidad);

void menuAbrirOrden(SistemaTaller* s);
void menuAgregarRepuestoAOrden(SistemaTaller* s);
void menuQuitarRepuestoDeOrden(SistemaTaller* s);
void menuCerrarOrden(SistemaTaller* s);
void menuAnularOrden(SistemaTaller* s);
void menuVerDetalleOrden(SistemaTaller* s);
void menuListarOrdenes(SistemaTaller* s);
void mostrarDetalleOrden(SistemaTaller* s, OrdenServicio* orden);
void mostrarListaOrdenes(SistemaTaller* s, OrdenServicio** ordenes, int cantidad);

#endif