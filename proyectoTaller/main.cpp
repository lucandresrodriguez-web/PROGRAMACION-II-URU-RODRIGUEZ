#include <iostream>
#include <cstring>

using namespace std;

//ESTRUCTURAS DE DATOS
struct Taller {
    char nombre[100]; 
    char rif[20];
    char direccion[200];
    char telefono[20];
};

//Estructura Vehiculo
struct Vehiculo {
    int id;
    char placa[10];
    char marca [50];
    char modelo[50];
    int anio;
    int kilometraje;
    char nombrePropietario[100];
    char cedulaPropietario[20];
    char telefonoPropietario[20];
    char fechaRegistro[11];
};

//Estructura Mecanico
struct Mecanico {
    int id;
    char nombre[100];
    char cedula[20];
    char especialidad[20];

    char fechaIngreso[11];
};

//Estructura Repuesto
struct Repuesto {
    int id;
    char codigo[20];
    char nombre[100];
    char marca[50];
    float precio;
    int stock;
    int stockMinimo;
    char fechaRegistro[11];
};

//Estructuras DetalleOrden y OrdenServicio
struct DetalleOrden {
    int idRepuesto;
    int cantidad;
    float precioUnitario;
};

struct OrdenServicio {
    int id;
    int idVehiculo;
    int idMecanico;
    char fechaApertura[11];
    char fechaCierre[11];
    char estado[12];
    char descripcionFalla[200];
    int kilometrajeIngreso;
    float manoObra;

    DetalleOrden* detalles;
    int           numDetalles;
    int           capacidadDetalles;
};

//Estructura Principal: SistemaTaller
struct SistemaTaller {
    Taller taller;

    Vehiculo*      vehiculos; int numVehiculos; int capacidadVehiculos;
    Mecanico*      mecanicos; int numMecanicos; int capacidadMecanicos;
    Repuesto*      repuestos; int numRepuestos; int capacidadRepuestos;
    OrdenServicio* ordenes;   int numOrdenes;   int capacidadOrdenes;

    int siguienteIdVehiculos;
    int siguienteIdMecanicos;
    int siguienteIdRepuestos;
    int siguienteIdOrden;
};

//SISTEMA GENERAL 
void inicializarSistema(SistemaTaller &s, Taller infoTaller);
void liberarSistema(SistemaTaller &s);

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

void liberarSistema(SistemaTaller &s, Taller infoTaller) {
    for (int i = 0; i < s.numOrden; i++) {
        delete[] s.orden[i].detalles;
    }
    
    delete[] s.vehiculos;
    delete[] s.repuestos;
    delete[] s.mecanicos;
    delete[] s.orden;

}