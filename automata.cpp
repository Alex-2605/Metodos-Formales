#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <string.h>

using namespace std;

int AFD = 0, ingresadas = 0, validas = 0, invalidas = 0, traducidas = 0;
const int longitudMaxima = 15, inicio = 80 - 47, cadenaMax = 256;
string palabra[cadenaMax], palabraTraducida[cadenaMax];

// lista encadenada para alfabetos
struct simboloEntrada
{
    string letra;
    struct simboloEntrada *siguiente;
};

struct simboloSalida
{
    string letra;
    struct simboloSalida *siguiente;
};

simboloEntrada *pointerPalabra = NULL;
simboloEntrada *inicioPosicionPalabra = NULL;
simboloEntrada *ultimaPosicionPalabra = NULL;
simboloEntrada *nuevaPalabra = NULL;
simboloSalida *pointerPalabraSalida = NULL;
simboloSalida *inicioPosicionPalabraSalida = NULL;
simboloSalida *ultimaPosicionPalabraSalida = NULL;
simboloSalida *nuevaPalabraSalida = NULL;

//lista encadenada para conjuntos
struct conjuntoEstados
{
    string palabra;
    struct conjuntoEstados *siguienteEstado;
};
conjuntoEstados *pointerEstadosPosibles = NULL;
conjuntoEstados *inicioPosicionEstados = NULL;
conjuntoEstados *ultimaPosicionEstados = NULL;
conjuntoEstados *nuevoEstado = NULL;

// Lista encadenada para los nodos del grafo
struct nodoGrafo
{
    char nodo[longitudMaxima];
    struct nodo *siguienteNodo;
    struct arista *aristaAdyacente;
};
typedef struct nodo *nodoTraduccion;
nodoTraduccion grafo = NULL;

// Lista encadenada para las aristas de los nodos
struct aristasGrafo
{
    char numeroArista;
    char traduccion;
    struct arista *siguienteArista;
    struct nodo *nodoAdyacente;
};
typedef struct arista *Tarista;

void Ayuda(),
    Traduccion(),
    AlfabetoSalida(),
    ConjuntoEstados(),
    EstadoInicial(),
    mostrar(),
    Validacion(),
    Estadisticas(),
    Validar();

int main()
{
    int opcion;
    bool ingresa = false;
    do
    {
        cout << "Menu: \n"
             << endl;
        cout << "1. Ayuda\n";
        cout << "2. AFD Traduccion\n";
        cout << "3. AFD Validacion\n";
        cout << "4. Estadisticas\n";
        cout << "5. Validar letra alfabeto general\n";
        cout << "6. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            Ayuda();
            break;
        case 2:
            Traduccion();
            cout << endl;
            break;
        case 3:
            Validacion();
            cout << endl;
            break;
        case 4:
            Estadisticas();
            cout << endl;
            break;
        case 5:
            Validar();
            cout << endl;
            break;
        case 6:
            cout << "Cerrando sistema\n";
            break;
        default:
            cout << "Opcion invalida\n";
        }
    } while (opcion != 6);

    return 0;
}

void Ayuda()
{
    cout << endl
         << "Un AFD de traduccion recibe siete parametros y el AFD de validacion cinco" << endl;
    cout << "Los parametros posibles son:" << endl;
    cout << "ΣE = Alfabeto de entrada." << endl;
    cout << "ΣS = Alfabeto de saluda." << endl;
    cout << "Q = Conjunto de estados posibles." << endl;
    cout << "q0 = Estado incial." << endl;
    cout << "A = Conjunto de estados de aceptacion." << endl;
    cout << "F = Funcion de transcicion." << endl;
    cout << "G = Funcion de traduccion." << endl;
    cout << "EL AFD de traduccion recibe: ΣE, ΣS, Q, q0, A, F y G." << endl;
    cout << "El AFD de validacion recibe: ΣE, Q, q0, A y F." << endl
         << endl;
}

void Traduccion()
{
    string letraEntrada, letraSalida;
    char opcion;
    bool aceptado = true;

    while (true)
    {
        do
        {
            do
            {
                aceptado = true;
                cout << endl << "Indique el alfabeto de entrada: ";
                cin >> letraEntrada;

                for (string::size_type i = 0; i < letraEntrada.size(); ++i)
                {
                    if (!isdigit(letraEntrada[i]) && !isalpha(letraEntrada[i]))
                    {
                        aceptado = false;
                        cout << "El caracter: " << (letraEntrada[i]) << " en la palabra, " << letraEntrada << " no puede ser aceptado, ya que no es alfanumerico, intenta de nuevo." << endl
                             << endl;
                    }
                }

            } while (aceptado == false);

            nuevaPalabra = new (simboloEntrada);
            nuevaPalabra->letra = letraEntrada;
            nuevaPalabra->siguiente = NULL;
            if (inicioPosicionPalabra == NULL)
            {
                inicioPosicionPalabra = nuevaPalabra;
                if (ultimaPosicionPalabra == NULL)
                    ultimaPosicionPalabra = nuevaPalabra;
            }
            else
            {
                ultimaPosicionPalabra->siguiente = nuevaPalabra;
                ultimaPosicionPalabra = nuevaPalabra;
            }

            cout << endl << "Desea ingresar un nuevo simbolo? (s/n): ";
            cin >> opcion;
            if (opcion == 'n')
            {
                AlfabetoSalida();
            }
        } while (opcion == 's');
        break;
    }
}

void AlfabetoSalida()
{
    string letraSalida;
    char opcion;
    bool aceptado = true;

    while (true)
    {
        do
        {
            do
            {
                aceptado = true;
                cout << endl
                     << "Indique el alfabeto de salida: ";
                cin >> letraSalida;

                for (string::size_type i = 0; i < letraSalida.size(); ++i)
                {
                    if (!isdigit(letraSalida[i]) && !isalpha(letraSalida[i]))
                    {
                        aceptado = false;
                        cout << "El caracter: " << (letraSalida[i]) << " en la palabra, " << letraSalida << " no puede ser aceptado, ya que no es alfanumerico, intenta de nuevo." << endl
                             << endl;
                    }
                }

            } while (aceptado == false);

            nuevaPalabraSalida = new (simboloSalida);
            nuevaPalabraSalida->letra = letraSalida;
            nuevaPalabraSalida->siguiente = NULL;
            if (inicioPosicionPalabraSalida == NULL)
            {
                inicioPosicionPalabraSalida = nuevaPalabraSalida;
                if (ultimaPosicionPalabraSalida == NULL)
                    ultimaPosicionPalabraSalida = nuevaPalabraSalida;
            }
            else
            {
                ultimaPosicionPalabraSalida->siguiente = nuevaPalabraSalida;
                ultimaPosicionPalabraSalida = nuevaPalabraSalida;
            }

            cout << endl
                 << "Desea ingresar un nuevo simbolo? (s/n): ";
            cin >> opcion;
            if (opcion == 'n')
            {
                ConjuntoEstados();
            }
        } while (opcion == 's');
        break;
    }
}

void ConjuntoEstados()
{
    string estados;
    char opcion;
    bool aceptado = true;

    while (true)
    {
        do
        {
            do
            {
                aceptado = true;
                cout << endl << "Indique el conjunto de estados: ";
                cin >> estados;

                for (string::size_type i = 0; i < estados.size(); ++i)
                {
                    if (!isdigit(estados[i]) && !isalpha(estados[i]))
                    {
                        aceptado = false;
                        cout << "El caracter: " << (estados[i]) << " en la palabra, " << estados << " no puede ser aceptado, ya que no es alfanumerico, intenta de nuevo." << endl
                             << endl;
                    }
                }

            } while (aceptado == false);

            nuevoEstado = new (conjuntoEstados);
            nuevoEstado->palabra = estados;
            nuevoEstado->siguienteEstado = NULL;
            if (inicioPosicionEstados == NULL)
            {
                inicioPosicionEstados = nuevoEstado;
                if (ultimaPosicionEstados == NULL)
                    ultimaPosicionEstados = nuevoEstado;
            }
            else
            {
                ultimaPosicionEstados->siguienteEstado = nuevoEstado;
                ultimaPosicionEstados = nuevoEstado;
            }

            cout << endl << "Desea ingresar un nuevo simbolo? (s/n): ";
            cin >> opcion;
            if (opcion == 'n')
            {
                mostrar();
            }
        } while (opcion == 's');
        break;
    }
}

void EstadoInicial()
{

}

void mostrar()
{
    cout << endl
         << "ΣE: ";
    pointerPalabra = inicioPosicionPalabra;
    cout << "{ ";

    while (true)
    {
        cout << pointerPalabra->letra;
        if (pointerPalabra->siguiente == NULL)
        {
            cout << " }";
            break;
        }
        else
        {
            pointerPalabra = pointerPalabra->siguiente;
            cout << ", ";
        }
    }

    cout << endl
         << "ΣS: ";
    pointerPalabraSalida = inicioPosicionPalabraSalida;
    cout << "{ ";

    while (true)
    {
        cout << pointerPalabraSalida->letra;
        if (pointerPalabraSalida->siguiente == NULL)
        {
            cout << " }";
            break;
        }
        else
        {
            pointerPalabraSalida = pointerPalabraSalida->siguiente;
            cout << ", ";
        }
    }

    cout << endl
         << "Q: ";
    pointerEstadosPosibles = inicioPosicionEstados;
    cout << "{ ";

    while (true)
    {
        cout << pointerEstadosPosibles->palabra;
        if (pointerEstadosPosibles->siguienteEstado == NULL)
        {
            cout << " }";
            break;
        }
        else
        {
            pointerEstadosPosibles = pointerEstadosPosibles->siguienteEstado;
            cout << ", ";
        }
    }
}

void Validacion()
{

}

void Estadisticas()
{

}

void Validar()
{

}