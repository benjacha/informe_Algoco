#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <chrono> 
#include <ctime> 
#include <string>

using namespace std;

// Esta función elige un elemento al azar como pivote y reordena los elementos
// de tal forma que todos los menores al pivote queden a su izquierda y los mayores a su derecha
int particion(vector<int>& arr, int izq, int der) {
    int pi = izq + rand() % (der - izq + 1);
    int pivot = arr[pi];
    swap(arr[der], arr[pi]);
    int ent = izq; 
    vector<int>  D;
    for (int i = izq; i < der; i++) {
        if (arr[i] < pivot) {
            swap (arr[ent], arr[i]);
            ent++;
        }
    }
    swap(arr[der], arr[ent]);
    return ent;
}

// Implementa el algoritmo QuickSort de manera recursiva. 
// Divide el vector en dos subvectores utilizando el pivote y luego llama a sí misma para ordenar esas dos subpartes.
void quickSort(vector<int>& arr, int izq, int der) {
    if (izq < der) {
        int pi = particion(arr, izq, der);
        quickSort(arr, izq, pi - 1);  
        quickSort(arr, pi + 1, der); 
    }
}

//lee los archivos de prueba recibiendo el nombre de uno abriendolo y mostrando en pantalla el tiempo de ejecución
void procesarArchivo(string nomarchivo) {
    ifstream archivo(nomarchivo);  
    vector<int> arr;  
    int num;
    while (archivo >> num) {
        arr.push_back(num);
    }
    archivo.close(); 
    auto start = chrono::high_resolution_clock::now();
    srand(time(0));
    quickSort(arr, 0, arr.size() - 1);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start; 
    string salidaArchivo = nomarchivo.substr(0, nomarchivo.find_last_of('.')) + "_ordenado.txt";
    ofstream archivoSalida(salidaArchivo);
    for (int val : arr) {
        archivoSalida << val << " ";
    }
    archivoSalida.close();
    cout << "El algoritmo se demoró " << duration.count() << " ms en ordenar " << nomarchivo << "." << endl;
}
int main() {
    // Procesar los 4 archivos caso1.txt, caso2.txt, caso3.txt y caso4.txt
    procesarArchivo("caso1.txt");
    procesarArchivo("caso2.txt");
    procesarArchivo("caso3.txt");
    procesarArchivo("caso4.txt");
    procesarArchivo("numeros.txt");
    return 0;
}


