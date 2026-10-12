#include <iostream>
#include "sistema_general.h"

using namespace std;

void inicializarSistema(SistemaTaller &s, Taller infoTaller) {

    s.tallerInfo = infoTaller;

    s.capacidadVehiculos = 4;
    s.capacidadRepuestos = 4;
    s.capacidadMecanicos = 4;
    s.capacidadOrden = 4;

    s.vehiculos = new Vehiculos[s.capacidadVehiculos];
    s.repuestos = new Repuestos[s.capacidadRepuestos];
    s.mecanicos = new Mecanicos[s.capacidadMecanicos];
    s.orden = new OrdenServicio[s.capacidadOrden];

    s.numVehiculos = 0;
    s.numRepuestos = 0;
    s.numMecanicos = 0;
    s.numOrden = 0;

    s.siguienteIdMecanicos = 1;
    s.siguienteIdOrden = 1;
    s.siguienteIdRepuestos = 1;
    s.siguienteIdVehiculos = 1;
}