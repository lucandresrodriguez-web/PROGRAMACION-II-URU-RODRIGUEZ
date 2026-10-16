#include <iostream>
#include <cstring>
#include <iomanip>
#include <cstdlib>
#include <cct


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

//SISTEMA DE VEHICULOS 
Vehiculo* agregarVehiculo(SistemaTaller* s, Vehiculo datos);
Vehiculo* buscarVehiculoPorID(SistemaTaller* s, int id);
Vehiculo* buscarVehiculoPorPlaca(SistemaTaller* s, const char* placa);
Vehiculo** buscarVehiculosPorPropietario(SistemaTaller* s, const char* subcadena, int* cantidad);
Vehiculo** listarVehiculos(SistemaTaller* s, int* cantidad);

bool actualizarVehiculo(SistemaTaller* s, int id, Vehiculo datos);
bool eliminarVehiculo(SistemaTaller* s, int id);


void menuRegistrarVehiculo(SistemaTaller* s);
void menuBuscarVehiculo(SistemaTaller* s);
void menuActualizarVehiculo(SistemaTaller* s);
void menuEliminarVehiculo(SistemaTaller* s);
void menuListarVehiculos(SistemaTaller* s);
void mostrarVehiculo(Vehiculo* vehiculo);
void mostrarListaVehiculos(Vehiculo** vehiculos, int cantidad);

// SISTEMA DE MECANICOS 
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

//SISTEMA DE REPUESTOS
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

//SISTEMA DE ORDEN DE SERVICIO
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