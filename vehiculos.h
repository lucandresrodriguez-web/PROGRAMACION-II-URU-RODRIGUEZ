#ifndef Vehiculo_H
#define Vehiculo_H

#include "Estructuras_taller.h"

//Capa de Logica 
Vehiculo* agregarVehiculo(SistemaTaller* s, Vehiculo datos);
Vehiculo* buscarVehiculoPorID(SistemaTaller* s, int id);
Vehiculo* buscarVehiculoPorPlaca(SistemaTaller* s, const char* placa);
Vehiculo** buscarVehiculosPorPropietario(SistemaTaller* s, const char* subcadena, int* cantidad);
Vehiculo** listarVehiculos(SistemaTaller* s, int* cantidad);
bool actualizarVehiculo(SistemaTaller* s, int id, Vehiculo datos);
bool eliminarVehiculo(SistemaTaller* s, int id);

//Capa de presentacion 
void menuRegistrarVehiculo(SistemaTaller* s);
void menuBuscarVehiculo(SistemaTaller* s);
void menuActualizarVehiculo(SistemaTaller* s);
void menuEliminarVehiculo(SistemaTaller* s);
void menuListarVehiculos(SistemaTaller* s);
void mostrarVehiculo(Vehiculo* vehiculo);
void mostrarListaVehiculos(Vehiculo** vehiculos, int cantidad);