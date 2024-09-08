#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <chrono> 
#include <ctime> 

int partition(std::vector<int>& arr, int izq, int der) {
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


void quickSort(std::vector<int>& arr, int izq, int der) {
    if (izq < der) {
        int pi = partition(arr, izq, der);

        quickSort(arr, izq, pi - 1);  
        quickSort(arr, pi + 1, der); 
    }
}


int main() {
    std::ifstream archivo("numeros.txt");  

    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
        return 1; 
    }

    std::vector<int> arr;  
    int num;

    while (archivo >> num) {
        arr.push_back(num);
    }
    archivo.close(); 
    srand(time(0));
    auto start = std::chrono::high_resolution_clock::now();
    quickSort(arr, 0, arr.size() - 1);
    auto end = std::chrono::high_resolution_clock::now();

    // std::cout << "Array ordenado: ";
    
    // for (int i : arr) {
    //     std::cout << i << " ";
    // }

    std::cout << std::endl;
    
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "El algoritmo se demoró " << duration.count() << " ms." << std::endl;

    return 0;
}
