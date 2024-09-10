#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <chrono> 
#include <ctime> 

// Esta función elige un elemento al azar como pivote y reordena los elementos
// de tal forma que todos los menores al pivote queden a su izquierda y los mayores a su derecha
int particion(std::vector<int>& arr, int izq, int der) {
    int pi = izq + rand() % (der - izq + 1);
    int pivot = arr[pi];
    std::swap(arr[der], arr[pi]);
    int ent = 0; 
    std::vector<int>  D;
    for (int i = izq; i < der; i++) {
        if (arr[i] < pivot) {
            arr[izq+ent]= arr[i];
            ent++;
        }
        else{
            D.push_back(arr[i]);
        }
    }
    arr[izq+ent]=pivot;
    for (int j = 0; j < D.size(); j++){
        arr[izq+ent+1+j] = D[j];
    }
    return izq+ent;
}

// Implementa el algoritmo QuickSort de manera recursiva. 
// Divide el vector en dos subvectores utilizando el pivote y luego llama a sí misma para ordenar esas dos subpartes.
void quickSort(std::vector<int>& arr, int izq, int der) {
    if (izq < der) {
        int pi = particion(arr, izq, der);
        quickSort(arr, izq, pi - 1);  
        quickSort(arr, pi + 1, der); 
    }
}

//lee los archivos de prueba recibiendo el nombre de uno abriendolo y mostrando en pantalla el tiempo de ejecución
void procesarArchivo(const std::string& archivo) {
    std::ifstream archivo(archivo);  
    std::vector<int> arr;  

    int num;
    while (archivo >> num) {
        arr.push_back(num);
    }
    
    archivo.close(); 

    auto start = std::chrono::high_resolution_clock::now();
    quickSort(arr, 0, arr.size() - 1);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;

    std::cout << "El algoritmo se demoró " << duration.count() << " ms en ordenar " << archivo << "." << std::endl;
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
