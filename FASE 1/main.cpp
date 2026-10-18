#include <iostream>
#include <cstring>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <limits>

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

    DetalleOrdenes* detalles;
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
    int siguienteIdOrdenes;
};

//SISTEMA GENERAL 
void inicializarSistema(SistemaTaller &s, Taller infoTaller) {

    s.tallerInfo = infoTaller;

    s.capacidadVehiculos = 4;
    s.capacidadRepuestos = 4;
    s.capacidadMecanicos = 4;
    s.capacidadOrdenes = 4;

    s.vehiculos = new Vehiculos[s.capacidadVehiculos];
    s.repuestos = new Repuestos[s.capacidadRepuestos];
    s.mecanicos = new Mecanicos[s.capacidadMecanicos];
    s.ordenes = new OrdenesServicio[s.capacidadOrdenes];

    s.numVehiculos = 0;
    s.numRepuestos = 0;
    s.numMecanicos = 0;
    s.numOrdenes = 0;

    s.siguienteIdMecanicos = 1;
    s.siguienteIdOrdenes = 1;
    s.siguienteIdRepuestos = 1;
    s.siguienteIdVehiculos = 1;
}

void liberarSistema(SistemaTaller &s, Taller infoTaller) {
    for (int i = 0; i < s.numOrdenes; i++) {
        delete[] s.ordenes[i].detalles;
    }
    
    delete[] s.vehiculos;
    delete[] s.repuestos;
    delete[] s.mecanicos;
    delete[] s.ordenes; 

} 

//SISTEMA DE VEHICULOS 
void redimensionarVehiculos(SistemaTaller* s) {
    s->capacidadVehiculos *= 2; 
    Vehiculo* nuevosVehiculos = new Vehiculo[s->capacidadVehiculos];

    for (int i = 0; i < s->numVehiculos; i++) {
        nuevosVehiculos[i] = s->vehiculos[i];
    }

    delete[] s->vehiculos;
    s->vehiculos = nuevosVehiculos;
}

Vehiculo* agregarVehiculo(SistemaTaller* s, Vehiculo datos) {
    if (s->numVehiculos >= s->capacidadVehiculos) {
        redimensionarVehiculos(s);
    }

    datos.id = s->siguienteIdVehiculos++;
    s->vehiculos[s->numVehiculos] = datos;
    s->numVehiculos++;

    return &(s->vehiculos[s->numVehiculos - 1]);
}

Vehiculo* buscarVehiculoPorID(SistemaTaller* s, int id) {
    for (int i = 0; i < s->numVehiculos; i++) {
        if (s->vehiculo[i].id == id) {
            return &(s->vehiculos[i]);
        }
    }
    return nullptr;
}

Vehiculo* buscarVehiculoPorPlaca(SistemaTaller* s, const char* placa){
    for (int i = 0; i < s->numVehiculos; i++) {
        if (strcmp(s->vehiculos[i],placa, placa) == 0) {
            return &(s->vehiculos[i]);
        }
    }
    return nullptr;
}

Vehiculo** buscarVehiculosPorPropietario(SistemaTaller* s, const char* subcadena, int* cantidad) {
    int encontrados = 0;
    for (int i = 0; i < s->numVehiculos; i++) {
        if (strstr(s->vehiculos[i].nombrePropietario, subcadena) != nullptr) {
            encontrados++;
        }
    }
    *cantidad = encontrados;
    if (encontrados == 0) return nullptr;

    Vehiculo** lista = new Vehiculo*[encontrados];
    int j = 0;
    for (int i = 0; i < s->numVehiculos; i++) {
        if (strstr(s->vehiculos[i].nombrePropietario, subcadena) != nullptr) {
            lista[j++] = &(s->vehiculos[i]);
        }
    }
    return lista;
}

Vehiculo** listarVehiculos(SistemaTaller* s, int* cantidad) {
    *cantidad = s->numVehiculos;
    if (s->numVehiculos == 0) return nullptr;

    Vehiculo** lista = new Vehiculo*[s->numVehiculos];
    for (int i = 0; i < s->nuevosVehiculos; i++) {
        lista[i] = &(s->vehiculos[i]);
    }
    return lista;
}

bool actualizarVehiculo(SistemaTaller* s, int id, Vehiculo datos) {
    Vehiculo* v = buscarVehiculoPorID(s, id);
    if (v == nullptr) return false;

    strcpy(v->placa, datos.placa);
    strcpy(v->marca, datos.marca);
    strcpy(v->modelo, datos.modelo);
    v->anio = datos.anio;
    v->kilometraje = datos.kilometraje;
    strcpy(v->nombrePropietario, datos.nombrePropietario);
    strcpy(v->cedulaPropietario, datos.cedulaPropietario);
    strcpy(v->telefonoPropietario, datos.telefonoPropietario);
    return true;
}

bool eliminarVehiculo(SistemaTaller* s, int id) {
    int pos = -1;
    for (int i = 0; i < s->numVehiculos; i++) {
        if (s->vehiculos[i].id == id) {
            pos = i;
            break;
        }
    }

    if (pos == -1) return false;

    for (int i = pos; i < s->numVehiculos - 1; i++) {
        s->vehiculos[i] = s->vehiculos[i + 1];
    }
    
    s->numVehiculos--;
    return true;
}

void menuRegistrarVehiculo(SistemaTaller* s) {
    if (vehiculo == nullptr) {
        cout << "[!] Vehiculo no encontrado." << endl;
        return;
    }
    cout << "----------------------------------------" << endl;
    cout << " ID: " << vehiculo->id << endl;
    cout << " Placa: " << vehiculo->placa << endl;
    cout << " Marca y Modelo: " << vehiculo->marca << " " << vehiculo->modelo << " (" << vehiculo->anio << ")" << endl;
    cout << " Kilometraje: " << vehiculo->kilometraje << " km" << endl;
    cout << " Propietario: " << vehiculo->nombrePropietario << " (CI: " << vehiculo->cedulaPropietario << ")" << endl;
    cout << " Telefono: " << vehiculo->telefonoPropietario << endl;
    cout << " Fecha Registro: " << vehiculo->fechaRegistro << endl;
    cout << "----------------------------------------" << endl;
}

void menuBuscarVehiculo(SistemaTaller* s) {
    if (vehiculos == nullptr || cantidad == 0) {
        cout << "\n[!] No hay vehiculos registrados para mostrar." << endl;
        return;
    }
    cout << "\n=== LISTA DE VEHICULOS (" << cantidad << ") ===" << endl;
    for (int i = 0; i < cantidad; i++) {
        mostrarVehiculo(vehiculos[i]);
    }
}

void menuActualizarVehiculo(SistemaTaller* s) {
    Vehiculo nuevoV;
    cout << "\n--- REGISTRAR NUEVO VEHICULO ---" << endl;
    cout << "Placa: ";
    cin >> nuevoV.placa;
    cout << "Marca: ";
    cin >> nuevoV.marca;
    cout << "Modelo: ";
    cin >> nuevoV.modelo;
    cout << "Anio: ";
    cin >> nuevoV.anio;
    cout << "Kilometraje: ";
    cin >> nuevoV.kilometraje;
    cout << "Nombre del Propietario: ";
    cin.ignore();
    cin.getline(nuevoV.nombrePropietario, 100);
    cout << "Cedula del Propietario: ";
    cin >> nuevoV.cedulaPropietario;
    cout << "Telefono del Propietario: ";
    cin >> nuevoV.telefonoPropietario;
    cout << "Fecha de Registro (DD/MM/AAAA): ";
    cin >> nuevoV.fechaRegistro;

    agregarVehiculo(s, nuevoV);
    cout << "\n[OK] Vehiculo registrado exitosamente con ID asignado." << endl;
}

void menuEliminarVehiculo(SistemaTaller* s) {
    int opc;
    cout << "\n--- BUSCAR VEHICULO ---" << endl;
    cout << "1. Buscar por ID" << endl;
    cout << "2. Buscar por Placa" << endl;
    cout << "3. Buscar por Propietario (parcial)" << endl;
    cout << "Seleccione una opcion: ";
    cin >> opc;

    if (opc == 1) {
        int id;
        cout << "Ingrese ID del vehiculo: ";
        cin >> id;
        Vehiculo* v = buscarVehiculoPorID(s, id);
        mostrarVehiculo(v);
    } else if (opc == 2) {
        char placa[10];
        cout << "Ingrese Placa: ";
        cin >> placa;
        Vehiculo* v = buscarVehiculoPorPlaca(s, placa);
        mostrarVehiculo(v);
    } else if (opc == 3) {
        char sub[100];
        cout << "Ingrese nombre o parte del propietario: ";
        cin.ignore();
        cin.getline(sub, 100);
        int cant = 0;
        Vehiculo** lista = buscarVehiculosPorPropietario(s, sub, &cant);
        mostrarListaVehiculos(lista, cant);
        delete[] lista;
    } else {
        cout << "[!] Opcion invalida." << endl;
    }
}

void menuListarVehiculos(SistemaTaller* s) {
    int id;
    cout << "\n--- ACTUALIZAR VEHICULO ---" << endl;
    cout << "Ingrese el ID del vehiculo a actualizar: ";
    cin >> id;

    Vehiculo* vExistente = buscarVehiculoPorID(s, id);
    if (vExistente == nullptr) {
        cout << "[!] No se encontro un vehiculo con el ID " << id << endl;
        return;
    }

    Vehiculo datosNuevos;
    cout << "Nueva Placa: ";
    cin >> datosNuevos.placa;
    cout << "Nueva Marca: ";
    cin >> datosNuevos.marca;
    cout << "Nuevo Modelo: ";
    cin >> datosNuevos.modelo;
    cout << "Nueva fecha: ";
    cin >> datosNuevos.anio;
    cout << "Nuevo Kilometraje: ";
    cin >> datosNuevos.kilometraje;
    cout << "Nuevo Propietario: ";
    cin.ignore();
    cin.getline(datosNuevos.nombrePropietario, 100);
    cout << "Nueva Cedula Propietario: ";
    cin >> datosNuevos.cedulaPropietario;
    cout << "Nuevo Telefono Propietario: ";
    cin >> datosNuevos.telefonoPropietario;

    if (actualizarVehiculo(s, id, datosNuevos)) {
        cout << "[OK] Vehiculo actualizado exitosamente." << endl;
    } else {
        cout << "[!] Error al actualizar." << endl;
    }
}

void mostrarVehiculo(Vehiculo* vehiculo) {
    int id;
    cout << "\n--- ELIMINAR VEHICULO ---" << endl;
    cout << "Ingrese el ID del vehiculo a eliminar: ";
    cin >> id;

    if (eliminarVehiculo(s, id)) {
        cout << "[OK] Vehiculo eliminado exitosamente." << endl;
    } else {
        cout << "[!] No se encontro el vehiculo con ese ID." << endl;
    }
}

void mostrarListaVehiculos(Vehiculo** vehiculos, int cantidad) {
    int cantidad = 0;
    Vehiculo** lista = listarVehiculos(s, &cantidad);
    mostrarListaVehiculos(lista, cantidad);
    delete[] lista;
}

// SISTEMA DE MECANICOS 
void redimensionarMecanicos(SistemaTaller* s) {
    s->capacidadMecanicos *= 2; 
    Mecanico* nuevosMecanicos = new Mecanicos[s->capacidadMecanicos];

    for (int i = 0; i < s->numMecanicos; i++) {
        nuevosMecanicos[i] = s->mecanicos[i];
    }

    delete[] s->mecanicos;
    s->mecanicos = nuevosMecanicos;
}

Mecanico* agregarMecanico(SistemaTaller* s, Mecanico datos) {
    if (s->numMecanicos >= s->capacidadMecanicos) {
        redimensionarMecanicos(s);
    }

    datos.id = s->siguienteIdMecanicos++;
    s->mecanicos[s->numMecanicos] = datos;
    s->numMecanicos++;

    return &(s->mecanicos[s->numMecanicos - 1]);
}

Mecanico* buscarMecanicoporID(SistemaTaller* s, int id) {
    for (int i = 0; i < s->numMecanicos; i++) {
        if (s->mecanicos[i].id == id) {
            return &(s->mecanicos[i]);
        }
    }
    return nullptr;
}

Mecanico* buscarMecanicoporCedula(SistemaTaller* s, const char* cedula) {
    for (int i = 0; i < ->numMecanicos; i++) {
        if (strcmp(s->mecanicos[i].cedula, cedula) == 0) {
            return &(s->mecanicos[i]);
        }
    }
    return nullptr;
}

Mecanico* listarMecanico(SistemaTaller* s, int* cantidad) {
    *cantidad = s->numMecanicos;
    if (s->numMecanicos == 0) return nullptr;
    return s->mecanicos;
}

int contarOrdenesAbiertasMecanico(SistemaTaller *s, int idMecanico) {
    int cont = 0;
    for (int i = 0; i < s->numOrdenes; i++) {
        if (s->ordenes[i].idMecanico == idMecanico) {
            if (strcmp(s->ordenes[i].estado, "Abierta") == 0 || strcmp(s->ordenes[i].estado, "ABIERTA") == 0) {
                cont++;
            }
        }
    }
    return cont;
}

void menuRegistrarMecanico(SistemaTaller* s) {
    Mecanico nuevoM;
    cout << "\n--- REGISTRAR NUEVO MECANICO ---" << endl;
    cout << "Nombre completo: ";
    cin.ignore();
    cin.getline(nuevoM.nombre, 100);
    cout << "Cedula: ";
    cin.nuevoM.cedula;
    cout << "Especialidad: ";
    cin >> nuevoM.especialidad;
    cout << "Fecha de Ingreso (DD/MM/AAAA): ";
    cin >> nuevoM.fechaIngreso;

    agregarMecanico(s, nuevoM);
    cout << "\n[OK] Mecanico registrado exitosamente." << endl;
}

void menuBuscarMecanico(SistemaTaller* s) {
    int opc;
    cout << "\n--- BUSCAR MECANICO ---" << endl;
    cout << "1. Buscar por ID" << endl;
    cout << "2. Buscar por cedula" << endl;
    cout << "Seleccione una opcion: ";
    cin >> opc;

    if (opc == 1) {
        int id;
        cout << "Ingrese ID del mecancio: ";
        cin >> id;
        Mecanico* m = buscarMecanicoporID(s, id);
        mostrarMecanicoUnico(m);
    } else if (opc == 2) {
        char ced[20];
        cout << "Ingrese Cedula: ";
        cin >> ced;
        Mecanico* m = buscarMecanicoporCedula(s, ced);
        mostrarMecanicoUnico(m);
    } else {
        cout << "[!] Opcion Invalida." << endl;
    }
}

void menuListarMecanico(SistemaTaller* s) {
    mostrarListaMecanico(s);
}

void mostrarMecanicoUnico(Mecancio *m) {
    if (m == nullptr) {
        cout << "[!] Mecanico no encontrado." << endl;
        return;
    }
    cout << "-------------------------------------------" << endl;
    cout << "ID: " << m->id << endl;
    cout << "Nombre: " << m->nombre << endl;
    cout << "Cedula: " << m->cedula << endl;
    cout << "Especialidad: " << m->especialidad << endl;
    cout << "Fecha Ingreso: " << m->fechaIngreso << endl;
    cout << "--------------------------------------------" << endl;
}

void mostrarMecanico(SistemaTaller* s) {
    int id;
    cout << "Ingrese el ID del mecanico a mostrar: ";
    cin >> id;
    Mecancio* m = buscarMecanicoporID(s, id);
    mostrarMecanicoUnico(m);
}

void mostrarListaMecanico(SistemaTaller* s) {
    int cantidad = 0;
    Mecancio* lista = listarMecanico(s, &cantidad);

    if (lista == nullptr || cantidad == 0) {
        cout << "\n[!] No hay mecanicos registrados para mostrar." << endl;
        return;
    }

    cout << "\n=== LISTA DE MECANCIOS (" << cantidad << ") ===" << endl;
    for (int i = 0; i < cantidad; i++) {
        mostrarMecanicoUnico(&lista[i]);
    }
}

//SISTEMA DE REPUESTOS
void redimensionarRepuestos(SistemaTaller* s) {
    s->capacidadRepuestos *= 2;
    Repuesto* nuevosRepuestos = new Repuesto[s->capacidadRepuestos];

    for (int i = 0; i < s->numRepuestos; i++) {
        nuevosRepuestos[i] = s->repuestos[i];
    }

    delete[] s->repuestos;
    s->repuestos = nuevosRepuestos;
}

Repuesto* agregarRepuesto(SistemaTaller* s, Repuesto datos) {
    if (s->numRepuestos >= s->capacidadRepuestos) {
        redimensionarRepuestos(s);
    }

    datos.id = s->siguienteIdRepuestos++;
    s->repuestos[s->numRepuestos] = datos;
    s->numRepuestos++;

    return &(s->repuestos[s->numRepuestos - 1]);
}

Repuesto* buscarRepuestoPorID(SistemaTaller* s, int id); {
    for (int i = 0; i < s->numRepuestos; i++) {
        if (s->repuestos[i].id == id) {
            return &(s->repuestos[i]);
        }
    }
    return nullptr;
}

Repuesto* buscarRepuestoPorCodigo(SistemaTaller* s, const char* codigo) {
    for (int i = 0; i < s->numRepuestos; i++) {
        if (strcmp(s->repuestos[i].codigo, codigo) == 0) {
            return &(s->repuestos[i]);
        }
    }
    return nullptr;
}

Repuesto* bucarRepuestoPorNombreParcial(SistemaTaller* s, const char* subcadena) {
    for (int i = 0; i < s->numRepuestos; i++) {
        if (strstr(s->repuestos[i].nombre, subcadena) != nullptr) {
            return &(s->repuestos[i]);
        }
    }
    return nullptr;
}

Repuesto* listarRepuesto(SistemaTaller* s, int* cantidad) {
     *cantidad = s->numRepuestos;
    if (s->numRepuestos == 0) return nullptr;
    return s->repuestos;
}

bool menuRegistrarEntradaMercancia(SistemaTaller* s, int idRepuesto, int CantidadAdicional) {
    Repuesto* r = buscarRepuestoPorID(s, idRepuesto);
    if (r == nullptr) return false;
    r->stock += CantidadAdicional;
    return true;
}

bool cambiarPrecioRepuesto(SistemaTaller* s, int idRepuesto, float nuevoPrecio) {
    Repuesto* r = buscarRepuestoPorID(s, idRepuesto);
    if (r == nullptr) return false;
    r->precio += nuevoPrecio;
    return true;
}

bool eliminarRepuesto(SistemaTaller* s, int id) {
    int pos = -1;
    for (int i = 0; i < s->numRepuestos; i++) {
        if (s->repuestos[i].id == id) {
            pos = i;
            break;
        }
    }

    if (pos == -1) return false;

    for (int i = pos; i < s->numRepuestos - 1; i++) {
        s->repuestos[i] = s->repuestos[i + 1];
    }
    
    s->numRepuestos--;
    return true;
}

void menuRegistrarRepuesto(SistemaTaller* s) {
    Repuesto nuevoR;
    cout << "\n--- REGISTRAR NUEVO REPUESTO ---" << endl;
    cout << "Codigo: ";
    cin >> nuevoR.codigo;
    cout << "Nombre: ";
    cin.ignore();
    cin.getline(nuevoR.nombre, 100);
    cout << "Precio unitario: ";
    cin >> nuevoR.precio;
    cout << "Stock inicial: ";
    cin >> nuevoR.stock;

    agregarRepuesto(s, nuevoR);
    cout << "\n[OK] Repuesto registrado exitosamente" << endl;
}

void menuBuscarRepuesto(SistemaTaller* s) {
    int opc;
    cout << "\n--- BUSCAR REPUESTO ---" << endl;
    cout << "1. Buscar por ID" << endl;
    cout << "2. Buscar por Codigo" << endl;
    cout << "3. Buscar por Nombre (parcial)" << endl;
    cout << "Seleccione una opcion: ";
    cin >> opc;

    if (opc == 1) {
        int id;
        cout << "Ingrese ID del repuesto: ";
        cin >> id;
        Repuesto* r = buscarRepuestoPorID(s, id);
        mostrarRepuesto(r);
    } else if (opc == 2) {
        char codigo[20];
        cout << "Ingrese Codigo: ";
        cin >> codigo;
        Repuesto* r = buscarRepuestoPorCodigo(s, codigo);
        mostrarRepuesto(r);
    } else if (opc == 3) {
        char sub[100];
        cout << "Ingrese el nombre o parte del mismo: ";
        cin.ignore();
        cin.getline(sub, 100);
        Repuesto* r = buscarRepuestoPorNombreParcial(s, sub);
        mostrarRepuesto(r);
    } else {
        cout << "[!] Opcion Invalida." << endl;
    }
}

void menuEntradaMercancia(SistemaTaller* s) {
    int id, cant;
    cout << "\n--- REGISTRAR ENTRADA DE MERCANCIA ---" << endl;
    cout << "Ingrese ID del repuesto: ";
    cin >> id;
    cout << "Ingrese la cantidad adicional a sumar al stock: ";
    cin >> cant;

    if (menuRegistrarEntradaMercancia(s, id, cant)) {
        cout << "[OK] Entrada de mercancia registrada con exito." << endl;
    } else {
        cout << "[!] No se encontro el repuesto con ese ID." << endl;
    }
}

void menuCambiarPrecio(SistemaTaller* s) {
    int id;
    float nuevoP;
    cout << "\n--- CAMBIAR PRECIO DE REPUESTO ---" << endl;
    cout << "Ingrese ID del repuesto: ";
    cin >> id;
    cout << "Ingrese el nuevo precio: ";
    cin >> nuevoP;

    if (cambiarPrecioRepuesto(s, id, nuevoP)) {
        cout << "[OK] Precio actualizado con exito." << endl;
    } else {
        cout << "[!] No se encontro el repuesto con ese ID." << endl;
    }
}

void menuEliminarRepuesto(SistemaTaller* s) {
    int id;
    cout << "\n--- ELIMINAR REPUESTO ---" << endl;
    cout << "Ingrese el ID del repuesto a eliminar: ";
    cin >> id;

    if (eliminarRepuesto(s, id)) {
        cout << "[OK] Repuesto eliminado exitosamente." << endl;
    } else {
        cout << "[!] No se encontro el repuesto con ese ID." << endl;
    }
}

void menuListarRepuestos(SistemaTaller* s) {
    int cantidad = 0;
    Repuesto* listaSimple = listarRepuesto(s, &cantidad);
    
    if (listaSimple == nullptr || cantidad == 0) {
        cout << "\n[!] No hay repuestos registrados para mostrar." << endl;
        return;
    }

    Repuesto** listaDoble = new Repuesto*[cantidad];
    for (int i = 0; i < cantidad; i++) {
        listaDoble[i] = &listaSimple[i];
    }

    mostrarListaRepuestos(listaDoble, cantidad);
    delete[] listaDoble;
}

void mostrarRepuesto(Repuesto* repuesto) {
    if (m == nullptr) {
        cout << "[!] Mecanico no encontrado." << endl;
        return;
    }
    cout << "-------------------------------------------" << endl;
    cout << "ID: " << m->id << endl;
    cout << "Nombre: " << m->nombre << endl;
    cout << "Codigo: " << m->cedula << endl;
    cout << "Precio $: " << m->especialidad << endl;
    cout << "Stock disponible: " << m->fechaIngreso << endl;
    cout << "--------------------------------------------" << endl;
}

void mostrarListaRepuestos(Repuesto** repuestos, int cantidad) {
    if (repuestos == nullptr || cantidad == 0) {
        cout << "\n[!] No hay repuestos registrados para mostrar." << endl;
        return;
    }

    cout << "\n=== LISTA DE REPUESTOS (" << cantidad << ") ===" << endl;
    for (int i = 0; i < cantidad; i++) {
        mostrarRepuesto(repuestos[i]);
    }
}

//SISTEMA DE ORDEN DE SERVICIO
void redimensionarOrdenes(SistemaTaller* s) {
    s->capacidadOrdenes *= 2;
    OrdenServicio* nuevasOrdenes = new OrdenServicio[s->capacidadOrdenes];

    for (int i = 0; i < s->numOrdenes; i++) {
        nuevasOrdenes[i] = s->ordenes[i];
    }

    delete[] s->ordenes;
    s->ordenes = nuevasOrdenes;
}

OrdenServicio* abrirOrden(SistemaTaller* s, int idVehiculo, int idMecanico, const char* descripcionFalla, int KilometrajeIngreso, const char* fechaActual) {
    if (s->numOrdenes >= s->capacidadOrdenes) {
        redimensionarOrdenes(s);
    }

    OrdenServicio nuevaO;
    nuevaO.id = s->siguienteIdOrdenes++;
    nuevaO.idVehiculo = idVehiculo;
    nuevaO.idMecanico = idMecanico;
    strcpy(nuevaO.descripcionFalla, descripcionFalla);
    nuevaO.kilometrajeIngreso = KilometrajeIngreso;
    strcpy(nuevaO.fechaIngreso, fechaActual);
    strcpy(nuevaO.fechaCierre, "Pendiente");
    strcpy(nuevaO.estado, "Abierta");
    nuevaO.manoObra = 0.0f;
    nuevaO.total = 0.0f;
    nuevaO.numRepuestosUsados = 0;

    s->ordenes[s->numOrdenes] = nuevaO;
    s->numOrdenes++;

    return &(s->ordenes[s->numOrdenes - 1]);
}

bool agregarRepuestoAOrden(SistemaTaller* s, int idOrden, int idRepuesto, int cantidad) {
    OrdenServicio* o = buscarOrdenPorID(s, idOrden);
    if (o == nullptr || strcmp(o->estado, "Abierta") !=0) return false;

    Repuesto* r = buscarRepuestoPorID(s, idRepuesto);
    if (r == nullptr || r->stock < cantidad) return false;

    r->stock -= cantidad;

    int idx = o->numRepuestosUsados;
    o->repuestosUsados[idx].idRepuesto = r->id;
    strcpy(o->repuestosUsados[idx].nombreRepuesto, r->nombre);
    o->repuestosUsados[idx].precioUnitario = r->precio;
    o->repuestosUsados[idx].cantidad = cantidad;
    o->numRepuestosUsados++;

    calcularTotalOrden(o);
    return true;
}

bool quitarRepuestoDeOrden(SistemaTaller* s, int idOrden, int idRepuesto) {
    OrdenServicio* o = buscarOrdenPorID(s, idOrden);
    if (o == nullptr || strcmp(o->estado, "Abierta") != 0) return false;

    int pos = -1;
    for (int i = 0; i < o->numRepuestosUsados; i++) {
        if (o->repuestosUsados[i].idRepuesto == idRepuesto) {
            pos = i;
            break;
        }
    }

    if (pos == -1) return false;

    Repuesto* r = buscarRepuestoPorID(s, idRepuesto);
    if (r != nullptr) {
        r->stock += o->repuestosUsados[pos].cantidad;
    }

    for (int i = pos; i < o->numRepuestosUsados - 1; i++) {
        o->repuestosUsados[i] = o->repuestosUsados[i + 1];
    }
    o->numRepuestosUsados--;

    calcularTotalOrden(o);
    return true;
}

bool cerrarOrden(SistemaTaller* s, int idOrden, float manoObra, const char* fechaActual) {
    OrdenServicio* o = buscarOrdenPorID(s, idOrden);
    if (o == nullptr || strcmp(o->estado, "Abierta") != 0) return false;

    o->manoObra = manoObra;
    strcpy(o->fechaCierre, fechaActual);
    strcpy(o->estado, "Cerrada");
    calcularTotalOrden(o);
    return true;
}

bool anularOrden(SistemaTaller* s, int idOrden) {
    OrdenServicio* o = buscarOrdenPorID(s, idOrden);
    if (o == nullptr || strcmp(o->estado, "Abierta") != 0) return false;

    for (int i = 0; i < o->numRepuestosUsados; i++) {
        Repuesto* r = buscarRepuestoPorID(s, o->repuestosUsados[i].idRepuesto);
        if (r != nullptr) {
            r->stock += o->repuestosUsados[i].cantidad;
        }
    }

    strcpy(o->estado, "Anulada");
    return true;
}

float calcularTotalOrden(OrdenServicio* Orden) {
    if (orden == nullptr) return 0.0f;

    float costoRepuestos = 0.0f;
    for (int i = 0; i < orden->numRepuestosUsados; i++) {
        costoRepuestos += (orden->repuestosUsados[i].precioUnitario * orden->repuestosUsados[i].cantidad);
    }

    orden->total = orden->manoObra + costoRepuestos;
    return orden->total;
}

OrdenServicio* buscarOrdenPorID(SistemaTaller* s, int id) {
    for (int i = 0; i < s->numOrdenes; i++) {
        if (s->ordenes[i].id == id) {
            return &(s->ordenes[i]);
        }
    }
    return nullptr;
}

OrdenServicio** listaOrdenesPorEstado(SistemaTaller* s, const char* estado, int* cantidad) {
    int encontrados = 0;
    for (int i = 0; i < s->numOrdenes; i++) {
        if (strcmp(s->ordenes[i].estado, estado) == 0) {
            encontrados++;
        }
    }
    *cantidad = encontrados;
    if (encontrados == 0) return nullptr;

    OrdenServicio** lista = new OrdenServicio*[encontrados];
    int j = 0;
    for (int i = 0; i < s->numOrdenes; i++) {
        if (strcmp(s->ordenes[i].estado, estado) == 0) {
            lista[j++] = &(s->ordenes[i]);
        }
    }
    return lista;
}

OrdenServicio** listaOrdenesPorVehiculo(SistemaTaller* s, int* vehiculo, int* cantidad) {
    int encontrados = 0;
    for (int i = 0; i < s->numOrdenes; i++) {
        if (s->ordenes[i].idVehiculo == idVehiculo) {
            encontrados++;
        }
    }
    *cantidad = encontrados;
    if (encontrados == 0) return nullptr;

    OrdenServicio** lista = new OrdenServicio*[encontrados];
    int j = 0;
    for (int i = 0; i < s->numOrdenes; i++) {
        if (s->ordenes[i].idVehiculo == idVehiculo) {
            lista[j++] = &(s->ordenes[i]);
        }
    }
    return lista;
}

OrdenServicio** listaTodasLasOrdenes(SistemaTaller* s, int* cantidad) {
    *cantidad = s->numOrdenes;
    if (s->numOrdenes == 0) return nullptr;

    OrdenServicio** lista = new OrdenServicio*[s->numOrdenes];
    for (int i = 0; i < s->numOrdenes; i++) {
        lista[i] = &(s->ordenes[i]);
    }
    return lista;
}

void menuAbrirOrden(SistemaTaller* s) {
    int idV, idM, km;
    char falla[200], fecha[15];

    cout << "\n--- ABRIR NUEVA ORDEN DE SERVICIO ---" << endl;
    cout << "Ingrese ID del Vehiculo: ";
    cin >> idV;
    if (buscarVehiculoPorID(s, idV) == nullptr) {
        cout << "[!] Error: El vehiculo no existe." << endl;
        return;
    }

    cout << "Ingrese ID del Mecanico: ";
    cin >> idM;
    if (buscarMecanicoporID(s, idM) == nullptr) {
        cout << "[!] Error: El mecanico no existe." << endl;
        return;
    }

    cout << "Descripcion de la falla: ";
    cin.ignore();
    cin.getline(falla, 200);
    cout << "Kilometraje de ingreso: ";
    cin >> km;
    cout << "Fecha actual (DD/MM/AAAA): ";
    cin >> fecha;

    abrirOrden(s, idV, idM, falla, km, fecha);
    cout << "\n[OK] Orden abierta exitosamente." << endl;
}

void menuAgregarRepuestoAOrden(SistemaTaller* s) {
    int idO, idR, cant;
    cout << "\n--- AGREGAR REPUESTO A ORDEN ---" << endl;
    cout << "Ingrese ID de la Orden: ";
    cin >> idO;
    cout << "Ingrese ID del Repuesto: ";
    cin >> idR;
    cout << "Cantidad: ";
    cin >> cant;

    if (agregarRepuestoAOrden(s, idO, idR, cant)) {
        cout << "[OK] Repuesto agregado a la orden con exito." << endl;
    } else {
        cout << "[!] Error al agregar repuesto (verifique que la orden este abierta, el repuesto exista y haya stock)." << endl;
    }
}

void menuQuitarRepuestoDeOrden(SistemaTaller* s) {
    int idO, idR;
    cout << "\n--- QUITAR REPUESTO DE ORDEN ---" << endl;
    cout << "Ingrese ID de la Orden: ";
    cin >> idO;
    cout << "Ingrese ID del Repuesto a retirar: ";
    cin >> idR;

    if (quitarRepuestoDeOrden(s, idO, idR)) {
        cout << "[OK] Repuesto retirado de la orden y devuelto al stock." << endl;
    } else {
        cout << "[!] Error al quitar el repuesto." << endl;
    }
}

void menuCerrarOrden(SistemaTaller* s) {
    int idO;
    float manoObra;
    char fecha[15];

    cout << "\n--- CERRAR ORDEN DE SERVICIO ---" << endl;
    cout << "Ingrese ID de la Orden a cerrar: ";
    cin >> idO;
    cout << "Costo de Mano de Obra: ";
    cin >> manoObra;
    cout << "Fecha de Cierre (DD/MM/AAAA): ";
    cin >> fecha;

    if (cerrarOrden(s, idO, manoObra, fecha)) {
        cout << "[OK] Orden cerrada exitosamente. Total calculado." << endl;
    } else {
        cout << "[!] Error al cerrar la orden (verifique que este abierta)." << endl;
    }
}

void menuAnularOrden(SistemaTaller* s) {
    int idO;
    cout << "\n--- ANULAR ORDEN DE SERVICIO ---" << endl;
    cout << "Ingrese ID de la Orden a anular: ";
    cin >> idO;

    if (anularOrden(s, idO)) {
        cout << "[OK] Orden anulada. Repuestos devueltos al inventario." << endl;
    } else {
        cout << "[!] Error al anular la orden." << endl;
    }
}

void menuVerDetalleOrden(SistemaTaller* s) {
    int idO;
    cout << "\n--- CONSULTAR DETALLE DE ORDEN ---" << endl;
    cout << "Ingrese ID de la Orden: ";
    cin >> idO;
    OrdenServicio* o = buscarOrdenPorID(s, idO);
    mostrarDetalleOrden(s, o);
}

void menuListarOrdenes(SistemaTaller* s) {
    int opc, cantidad = 0;
    cout << "\n--- LISTAR ORDENES ---" << endl;
    cout << "1. Listar todas" << endl;
    cout << "2. Listar por Estado (Abierta / Cerrada / Anulada)" << endl;
    cout << "3. Listar por Vehiculo (por ID)" << endl;
    cout << "Seleccione una opcion: ";
    cin >> opc;

    if (opc == 1) {
        OrdenServicio** lista = listaTodasLasOrdenes(s, &cantidad);
        mostrarListaOrdenes(s, lista, cantidad);
        delete[] lista;
    } else if (opc == 2) {
        char estado[20];
        cout << "Ingrese estado a buscar (Ej. Abierta): ";
        cin >> estado;
        OrdenServicio** lista = listaOrdenesPorEstado(s, estado, &cantidad);
        mostrarListaOrdenes(s, lista, cantidad);
        delete[] lista;
    } else if (opc == 3) {
        int idV;
        cout << "Ingrese ID del Vehiculo: ";
        cin >> idV;
        OrdenServicio** lista = listaOrdenesPorVehiculo(s, idV, &cantidad);
        mostrarListaOrdenes(s, lista, cantidad);
        delete[] lista;
    } else {
        cout << "[!] Opcion invalida." << endl;
    }
}

void mostrarDetalleOrden(SistemaTaller* s, OrdenServicio* orden) {
    if (orden == nullptr) {
        cout << "[!] Orden de servicio no encontrada." << endl;
        return;
    }

    Vehiculo* v = buscarVehiculoPorID(s, orden->idVehiculo);
    Mecanico* m = buscarMecanicoporID(s, orden->idMecanico);

    cout << "\n----------------------------------------" << endl;
    cout << " ORDEN DE SERVICIO # " << orden->id << endl;
    cout << " Estado: " << orden->estado << endl;
    cout << " Fecha Ingreso: " << orden->fechaIngreso << " | Cierre: " << orden->fechaCierre << endl;
    cout << " Kilometraje Ingreso: " << orden->kilometrajeIngreso << " km" << endl;
    cout << " Falla reportada: " << orden->descripcionFalla << endl;
    
    cout << " --- VEHICULO ASOCIADO ---" << endl;
    if (v != nullptr) {
        cout << " Placa: " << v->placa << " | " << v->marca << " " << v->modelo << " (" << v->anio << ")" << endl;
        cout << " Propietario: " << v->nombrePropietario << endl;
    } else {
        cout << " [!] Vehiculo con ID " << orden->idVehiculo << " no encontrado o eliminado." << endl;
    }

    cout << " --- MECANICO ASIGNADO ---" << endl;
    if (m != nullptr) {
        cout << " Nombre: " << m->nombre << " (Especialidad: " << m->especialidad << ")" << endl;
    } else {
        cout << " [!] Mecanico con ID " << orden->idMecanico << " no encontrado." << endl;
    }

    cout << " --- REPUESTOS UTILIZADOS (" << orden->numRepuestosUsados << ") ---" << endl;
    for (int i = 0; i < orden->numRepuestosUsados; i++) {
        cout << "  - " << orden->repuestosUsados[i].nombreRepuesto 
             << " x" << orden->repuestosUsados[i].cantidad 
             << " ($" << orden->repuestosUsados[i].precioUnitario << " c/u)" << endl;
    }

    calcularTotalOrden(orden);
    cout << " Mano de Obra: $" << orden->manoObra << endl;
    cout << " TOTAL A PAGAR: $" << orden->total << endl;
    cout << "----------------------------------------" << endl;
}

void mostrarListaOrdenes(SistemaTaller* s, OrdenServicio** ordenes, int cantidad) {
    if (ordenes == nullptr || cantidad == 0) {
        cout << "\n[!] No hay ordenes para mostrar." << endl;
        return;
    }
    cout << "\n=== LISTADO DE ORDENES (" << cantidad << ") ===" << endl;
    for (int i = 0; i < cantidad; i++) {
        cout << "[ID Orden: " << ordenes[i]->id << "] - Vehiculo ID: " << ordenes[i]->idVehiculo 
             << " - Estado: " << ordenes[i]->estado << " - Total: $" << ordenes[i]->total << endl;
    }
}