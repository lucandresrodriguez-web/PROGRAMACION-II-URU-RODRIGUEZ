#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <iomanip>

using namespace std;

struct Pokemon {
    int pokedex;
    string nombre;
    string tipo1;
    string tipo2;
    int total;
    int hp;
    int ataque;
    int defensa;
    int ataqueEsp;
    int defensaEsp;
    int velocidad;
    int generacion;
    bool legendario;
};

struct PokedexDinamica {
    Pokemon* datos;
    int cantidad;
    int capacidad;
};

string aMinusculas(string str) {
    transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {
        return tolower(c);
    });
    return str;
}

void inicializarPokedex(PokedexDinamica &pokedex, int capacidadInicial = 10) {
    pokedex.datos = new Pokemon[capacidadInicial];
    pokedex.cantidad = 0;
    pokedex.capacidad = capacidadInicial;
};

void redimensionarPokedex(PokedexDinamica &pokedex) {
    int nuevaCapacidad = pokedex.capacidad * 2;
    Pokemon* nuevosDatos = new Pokemon[nuevaCapacidad];

    for (int i = 0; i < pokedex.cantidad; i++) {
        nuevosDatos[i] = pokedex.datos[i];
    }

    delete[] pokedex.datos;
    pokedex.datos = nuevosDatos;
    pokedex.capacidad = nuevaCapacidad;
}

void agregarPokemon(PokedexDinamica &pokedex, const Pokemon &nuevoP) {
    if (pokedex.cantidad == pokedex.capacidad) {
        redimensionarPokedex(pokedex);
    }
    pokedex.datos[pokedex.cantidad] = nuevoP;
    pokedex.cantidad++;
}

void liberarPokedex(PokedexDinamica &pokedex) {
    if (pokedex.datos != nullptr) {
        delete[] pokedex.datos;
        pokedex.datos = nullptr;
        pokedex.cantidad = 0;
        pokedex.capacidad = 0;
    }
}

bool cargarCSV(PokedexDinamica &pokedex, const string &nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        return false;
    }

    string linea;
    getline(archivo, linea);

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        stringstream ss(linea);
        string item;
        Pokemon p;

        getline(ss, item, ','); p.pokedex = stoi(item);
        getline(ss, p.nombre, ',');
        getline(ss, p.tipo1, ',');
        getline(ss, p.tipo2, ',');
        getline(ss, item, ','); p.total = stoi(item);
        getline(ss, item, ','); p.hp = stoi(item);
        getline(ss, item, ','); p.ataque = stoi(item);
        getline(ss, item, ','); p.defensa = stoi(item);
        getline(ss, item, ','); p.ataqueEsp = stoi(item);
        getline(ss, item, ','); p.defensaEsp = stoi(item);
        getline(ss, item, ','); p.velocidad = stoi(item);
        getline(ss, item, ','); p.generacion = stoi(item);

        getline(ss, item, ',');
        string legMin = aMinusculas(item);
        p.legendario = (legMin == "true" || legMin == "1");

        agregarPokemon(pokedex, p);
    }

    archivo.close();
    return true;
}

void mostrarFicha(const Pokemon* p) {
    if (p == nullptr) return;

    cout << "\n----------------------------------------" << endl;
    cout << "Nº Pokedex:  " << p->pokedex << endl;
    cout << "Nombre:      " << p->nombre << endl;
    cout << "Tipo 1:      " << p->tipo1 << endl;
    cout << "Tipo 2:      " << (p->tipo2.empty() ? "Ninguno" : p->tipo2) << endl;
    cout << "Total Stats: " << p->total << endl;
    cout << "HP:          " << p->hp << endl;
    cout << "Ataque:      " << p->ataque << endl;
    cout << "Defensa:     " << p->defensa << endl;
    cout << "Ataque Esp.: " << p->ataqueEsp << endl;
    cout << "Defensa Esp.:" << p->defensaEsp << endl;
    cout << "Velocidad:   " << p->velocidad << endl;
    cout << "Generación:  " << p->generacion << endl;
    cout << "Legendario:  " << (p->legendario ? "Si" : "No") << endl;
    cout << "----------------------------------------" << endl;
}

void buscarPorNumero(const PokedexDinamica &pokedex, int num) {
    bool encontrado = false;
    for (int i = 0; i < pokedex.cantidad; i++) {
        if (pokedex.datos[i].pokedex == num) {
            mostrarFicha(&pokedex.datos[i]);
            encontrado = true;
            break;
        }
    }
    if (!encontrado) {
        cout << "No se ha encontrado ningun Pokemon con ese numero " << num << "." << endl;
    }
}

void buscarPorNombre(const PokedexDinamica &pokedex, const string &nombreBusq, bool exacto) {
    string busqMin = aMinusculas(nombreBusq);
    bool encontrado = false;

    for (int i = 0; i < pokedex.cantidad; i++) {
        string nomP = aMinusculas(pokedex.datos[i].nombre);
        if (exacto) {
            if (nomP == busqMin) {
                mostrarFicha(&pokedex.datos[i]);
                encontrado = true;
                break;
            }
        } else {
            if (nomP.find(busqMin) != string::npos) {
                mostrarFicha(&pokedex.datos[i]);
                encontrado = true;
            }
        }
    }

    if (!encontrado) {
        cout << "No se encontraron coincidencias para: \"" << nombreBusq << "\"." << endl;
    }
}

void buscarPorTipo(const PokedexDinamica &pokedex, const string &tipo) {
    string tipoMin = aMinusculas(tipo);
    int contador = 0;

    cout << "\n=== Pokemon de tipo: " << tipo << " ===" << endl;
    cout << left << setw(10) << "Nº" << setw(20) << "Nombre" << setw(12) << "Tipo 1" << setw(12) << "Tipo 2" << setw(8) << "Total" << endl;
    cout << string(62, '-') << endl;

    for (int i = 0; i < pokedex.cantidad; i++) {
        if (aMinusculas(pokedex.datos[i].tipo1) == tipoMin || aMinusculas(pokedex.datos[i].tipo2) == tipoMin) {
            cout << left << setw(10) << pokedex.datos[i].pokedex 
                 << setw(20) << pokedex.datos[i].nombre 
                 << setw(12) << pokedex.datos[i].tipo1 
                 << setw(12) << (pokedex.datos[i].tipo2.empty() ? "-" : pokedex.datos[i].tipo2) 
                 << setw(8) << pokedex.datos[i].total << endl;
            contador++;
        }
    }

    if (contador == 0) {
        cout << "No se encontraron Pokemon de tipo \"" << tipo << "\"." << endl;
    } else {
        cout << "\nTotal encontrados: " << contador << endl;
    }
}

void mostrarTopEstadisticas(const PokedexDinamica &pokedex) {
    if (pokedex.cantidad == 0) return;

    Pokemon* copia = new Pokemon[pokedex.cantidad];
    for (int i = 0; i < pokedex.cantidad; i++) {
        copia[i] = pokedex.datos[i];
    }

    for (int i = 0; i < pokedex.cantidad -1; i++) {
        for (int j = 0; j < pokedex.cantidad - i - 1; j++) {
            if (copia[j].total < copia[j + 1].total) {
                Pokemon temp = copia[j];
                copia[j] = copia[j + 1];
                copia[j + 1] = temp;
            }
        }
    }
    
    cout << "\n========================================" << endl;
    cout << "     TOP 3 POKEMON MAS FUERTES          " << endl;
    cout << "========================================" << endl;
    for (int i = 0; i < min(3, pokedex.cantidad); i++) {
        cout << "#" << (i + 1) << " " << copia[i].nombre << " (N " << copia[i].pokedex << ") - Total Stats: " << copia[i].total << endl;
    }

    cout << "\n========================================" << endl;
    cout << "     TOP 3 POKEMON MAS DEBILES          " << endl;
    cout << "========================================" << endl;
    for (int i = 0; i < min(3, pokedex.cantidad); i++) {
        int idx = pokedex.cantidad - 1 - i;
        cout << "#" << (i + 1) << " " << copia[idx].nombre << " (Nº " << copia[idx].pokedex << ") - Total Stats: " << copia[idx].total << endl;
    }
    cout << "========================================" << endl;

    delete[] copia;
}

int main() {
    string archivoCSV = "pokemon_150_registros.csv";
    PokedexDinamica pokedex;
    inicializarPokedex(pokedex, 10);

    if (!cargarCSV(pokedex, archivoCSV)) {
        cerr << "Error: No se pudo abrir el archivo '" << archivoCSV << "'. Verifique que esté en la misma carpeta." << endl;
        liberarPokedex(pokedex);
        return 1;
    }

    int opcion;
    do {
        cout << "\n===== MENU POKEDEX (MEMORIA DINAMICA Y FICHEROS) =====" << endl;
        cout << "1. Ver info de Pokemon por numero de Pokedex" << endl;
        cout << "2. Buscar Pokemon por nombre (parcial)" << endl;
        cout << "3. Ver info de Pokemon por nombre exacto" << endl;
        cout << "4. Ver Pokemon de un tipo" << endl;
        cout << "5. Ver Top 3 mas fuertes y Top 3 mas debiles" << endl;
        cout << "6. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                int num;
                cout << "\nIngrese el numero de Pokedex: ";
                cin >> num;
                buscarPorNumero(pokedex, num);
                break;
            }
            case 2: {
                string nombre;
                cout << "\nIngrese el nombre (o parte del nombre): ";
                cin.ignore();
                getline(cin, nombre);
                buscarPorNombre(pokedex, nombre, false);
                break;
            }
            case 3: {
                string nombre;
                cout << "\nIngrese el nombre exacto: ";
                cin.ignore();
                getline(cin, nombre);
                buscarPorNombre(pokedex, nombre, true);
                break;
            }
            case 4: {
                string tipo;
                cout << "\nIngrese el tipo de Pokemon: ";
                cin >> tipo;
                buscarPorTipo(pokedex, tipo);
                break;
            }
            case 5:
                mostrarTopEstadisticas(pokedex);
                break;
            case 6:
                cout << "¡Hasta luego!" << endl;
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo." << endl;
        }
    } while (opcion != 6);

    liberarPokedex(pokedex);

    return 0;
}