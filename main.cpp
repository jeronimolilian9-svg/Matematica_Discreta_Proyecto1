#include <iostream>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

long long factorial(int n){
    int i;
    long long factorial = 1;
     if (n < 0) {
        cout<< "Error: El factorial de un número negativo no existe." <<endl;
     }else {
        for (i = 1; i <= n; ++i ){
            factorial *= i; //factorial = factorial * i
        }
    }
    return factorial;
} 

void PermutacionConRepeticion(){
    cout<<"Ingrese 2 numeros para la permutacion con repeticion"<<endl;
    //Inicializamos las variables para calcular la permutacion n1,a,b
    int n1;    
    int k;
    //Le pedimos al usuario que ingrese los valores numericos
    cin >> n1;
    cin >> k;
    //declaramos la variable p de permutacion
    long long p;
    //Aqui ejecutamos la funcion de permutacion apoyandonos de la funcion auxiliar factorial
    //la variable p, recibe los resultados de la funcion factorial y los opera.
    p = (factorial (n1))/(factorial (n1-k));
    cout<<"El valor de la permutacion con repeticion es: "<< p <<" Regresando al menu principal"<<endl;
}

void CombinacionConRepeticion(){
    cout << "ingrese dos numeros para la combinacion con Repeticion" << endl;
    int r1;
    int c;
    cin >> r1;
    cin >> c;
    long long l;
    l = (factorial (r1))/((factorial (r1-c)* factorial(c)));
    cout<<"El valor de la combinacion con Repeticion es: "<< l <<" Regresando al menu principal"<<endl;

}


void CombinacionSinRepeticion(){
    cout << "ingrese dos numeros para la combinacion sin Repeticion" << endl;
    int p;
    int b1;
    cin >> p;
    cin >> b1;
    long long f;
    f = (factorial (p+b1-1))/((factorial (b1)* factorial(p-1)));
    cout<<"El valor de la combinacion sin Repeticion es: "<< f <<" Regresando al menu principal"<<endl;


}


struct Nodo;

struct Arista {
    Nodo* destino;
    double peso;
};

struct Nodo {
    int dato;
    vector<Arista> salientes;

    Nodo(int valor) : dato(valor) {}
};

vector<Nodo*> nodosGrafo;

Nodo* buscarNodo(int valor) {
    for (Nodo* nodo : nodosGrafo) {
        if (nodo->dato == valor) {
            return nodo;
        }
    }
    return nullptr;
}

Nodo* insertar(Nodo* raiz, int valor) {
    if (buscarNodo(valor) != nullptr) {
        cout << "Ya existe un nodo con ese valor." << endl;
        return raiz;
    }

    Nodo* nuevoNodo = new Nodo(valor);
    nodosGrafo.push_back(nuevoNodo);
    if (raiz == nullptr) {
        cout << "El primer nodo sera la raiz del grafo." << endl;
        return nuevoNodo;
    }
    return raiz;
}

void agregarArista() {
    int valorOrigen;
    int valorDestino;
    double peso;

    cout << "Ingrese el valor del nodo de origen: ";
    cin >> valorOrigen;
    Nodo* origen = buscarNodo(valorOrigen);
    if (origen == nullptr) {
        cout << "No existe el nodo de origen." << endl;
        return;
    }

    cout << "Ingrese el valor del nodo de destino: ";
    cin >> valorDestino;
    Nodo* destino = buscarNodo(valorDestino);
    if (destino == nullptr) {
        cout << "No existe el nodo de destino." << endl;
        return;
    }

    for (const Arista& arista : origen->salientes) {
        if (arista.destino == destino) {
            cout << "Esa arista dirigida ya existe." << endl;
            return;
        }
    }

    cout << "Ingrese el peso de la arista (no negativo): ";
    cin >> peso;
    if (peso < 0) {
        cout << "Dijkstra requiere pesos no negativos." << endl;
        return;
    }

    origen->salientes.push_back({destino, peso});
    cout << "Arista dirigida agregada." << endl;
}


void imprimirRuta(const vector<Nodo*>& ruta, double pesoTotal) {
    cout << "Ruta: ";
    for (size_t i = 0; i < ruta.size(); ++i) {
        if (i > 0) {
            cout << " -> ";
        }
        cout << ruta[i]->dato;
    }
    cout << "\nPeso total: " << pesoTotal << endl;
}

void grafoRutaCorta(Nodo* raiz, int valor) {
    if (raiz == nullptr) {
        cout << "No hay nodos en el grafo." << endl;
        return;
    }

    Nodo* destino = buscarNodo(valor);
    if (destino == nullptr) {
        cout << "No existe un nodo con ese valor." << endl;
        return;
    }

    unordered_map<Nodo*, double> distancias;
    unordered_map<Nodo*, Nodo*> anteriores;
    auto comparar = [](const pair<double, Nodo*>& primero, const pair<double, Nodo*>& segundo) {
        return primero.first > segundo.first;
    };
    priority_queue<pair<double, Nodo*>, vector<pair<double, Nodo*>>, decltype(comparar)> pendientes(comparar);

    distancias[raiz] = 0;
    pendientes.push({0, raiz});

    while (!pendientes.empty()) {
        Nodo* actual = pendientes.top().second;
        double distanciaActual = pendientes.top().first;
        pendientes.pop();

        if (distancias.find(actual) == distancias.end() || distanciaActual > distancias[actual]) {
            continue;
        }
        if (actual == destino) {
            break;
        }

        for (const Arista& arista : actual->salientes) {
            double nuevaDistancia = distanciaActual + arista.peso;
            if (distancias.find(arista.destino) == distancias.end() || nuevaDistancia < distancias[arista.destino]) {
                distancias[arista.destino] = nuevaDistancia;
                anteriores[arista.destino] = actual;
                pendientes.push({nuevaDistancia, arista.destino});
            }
        }
    }

    if (distancias.find(destino) == distancias.end()) {
        cout << "No existe una ruta dirigida desde la raiz hasta ese nodo." << endl;
        return;
    }

    vector<Nodo*> ruta;
    for (Nodo* actual = destino; actual != nullptr;) {
        ruta.push_back(actual);
        if (actual == raiz) {
            break;
        }
        auto anterior = anteriores.find(actual);
        if (anterior == anteriores.end()) {
            cout << "No se pudo reconstruir la ruta." << endl;
            return;
        }
        actual = anterior->second;
    }
    reverse(ruta.begin(), ruta.end());
    imprimirRuta(ruta, distancias[destino]);
}

void explorarRutasLargas(Nodo* actual, Nodo* destino, double pesoActual,
                         unordered_set<Nodo*>& visitados, vector<Nodo*>& rutaActual,
                         vector<Nodo*>& mejorRuta, double& mejorPeso, bool& encontrada) {
    if (actual == destino) {
        if (!encontrada || pesoActual > mejorPeso) {
            mejorPeso = pesoActual;
            mejorRuta = rutaActual;
            encontrada = true;
        }
        return;
    }

    for (const Arista& arista : actual->salientes) {
        if (visitados.find(arista.destino) == visitados.end()) {
            visitados.insert(arista.destino);
            rutaActual.push_back(arista.destino);
            explorarRutasLargas(arista.destino, destino, pesoActual + arista.peso,
                                visitados, rutaActual, mejorRuta, mejorPeso, encontrada);
            rutaActual.pop_back();
            visitados.erase(arista.destino);
        }
    }
}

void grafoRutaLarga(Nodo* raiz, int valor) {
    if (raiz == nullptr) {
        cout << "No hay nodos en el grafo." << endl;
        return;
    }

    Nodo* destino = buscarNodo(valor);
    if (destino == nullptr) {
        cout << "No existe un nodo con ese valor." << endl;
        return;
    }

    unordered_set<Nodo*> visitados = {raiz};
    vector<Nodo*> rutaActual = {raiz};
    vector<Nodo*> mejorRuta;
    double mejorPeso = 0;
    bool encontrada = false;
    explorarRutasLargas(raiz, destino, 0, visitados, rutaActual, mejorRuta, mejorPeso, encontrada);

    if (!encontrada) {
        cout << "No existe una ruta dirigida desde la raiz hasta ese nodo." << endl;
        return;
    }
    imprimirRuta(mejorRuta, mejorPeso);
}


int main(){
    Nodo* raizGrafo = nullptr;
    while (true) {
        //El programa inicia mostrando el menu y las opciones
        cout << "Seleccione una opcion: 1. Permutaciones con repeticion  2. Permutacion sin repeticion  3. Combinacion con repeticion  4. Combinacion sin repeticion  5. Grafos  6. Salir" << endl;
        //inicializamos la variable opcion para que el usuario nos de la opcion que desee 
        string opcion;
        cin >> opcion;
        //Iniciamos el bucle para ejecutar las opciones
        while (true) {
            if (opcion == "1") { 
                //Le mostramos al usuario la opcion que escogio
                cout << "Permutaciones con repeticion" << endl;
                //llamamos a la funcion que ejecuta los calculos
                PermutacionConRepeticion();
                break;
            }else if (opcion == "2") {
                cout << "Permutaciones sin repeticion" << endl;
                cout << "ingrese un numero"<< endl; 
                int n;
                cin >> n;
                if ( n < 0 ){
                    cout<< "Error: La Permutacion sin repeticion de un número negativo no existe." <<endl;
                }else {
                //la variable p, recibe los resultados de la funcion factorial
                long long p = factorial(n);
                cout << "La permutacion es "<< p << endl;
                }
                
                break;
            }else if (opcion == "3") {
                cout << "Combinacion con repeticion" << endl;
                CombinacionConRepeticion();
                break;
            }else if (opcion == "4") {
                cout << "Combinacion sin repeticion" << endl;
                CombinacionSinRepeticion();
                break;
            }else if (opcion == "5") {
                while (true) {
                    cout << "\nMenu de grafos: 1. Insertar nodo  2. Agregar arista dirigida  3. Ruta mas corta  4. Ruta mas larga  5. Regresar al menu principal" << endl;
                    string opcionGrafo;
                    cin >> opcionGrafo;

                    if (opcionGrafo == "1") {
                        int valor;
                        cout << "Ingrese el valor del nuevo nodo: ";
                        cin >> valor;
                        raizGrafo = insertar(raizGrafo, valor);
                    } else if (opcionGrafo == "2") {
                        agregarArista();
                    } else if (opcionGrafo == "3") {
                        int valorDestino;
                        cout << "Ingrese el valor del nodo destino: ";
                        cin >> valorDestino;
                        grafoRutaCorta(raizGrafo, valorDestino);
                    } else if (opcionGrafo == "4") {
                        int valorDestino;
                        cout << "Ingrese el valor del nodo destino: ";
                        cin >> valorDestino;
                        grafoRutaLarga(raizGrafo, valorDestino);
                    } else if (opcionGrafo == "5") {
                        break;
                    } else {
                        cout << "Opcion invalida. Seleccione una opcion del submenu." << endl;
                    }
                }
                break;
            }else if (opcion == "6") {
                cout << "Saliendo del Programa..." << endl;
                return 0; // salir del programa
            }else {
                cout << "opcion invalida. por favor, seleccione una opcion valida: ";
                cin >> opcion; // solicita nuevamente la opcion
            }              
        }
    }
    
}