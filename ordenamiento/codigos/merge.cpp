#include <iostream>
#include <vector>
#include <fstream>
#include <chrono> 

void merge(std::vector<int>& arr, int izq, int m, int der) {
    int n1 = m - izq + 1;
    int n2 = der - m;

    std::vector<int> I(n1), D(n2);

    for (int i = 0; i < n1; i++) {
        I[i] = arr[izq + i];
    }
    for (int j = 0; j < n2; j++) {
        D[j] = arr[m + 1 + j];
    }

    int i = 0, j = 0;

    int k = izq;

    while (i < n1 && j < n2) {
        if (I[i] <= D[j]) {
            arr[k] = I[i];
            i++;
        } else {
            arr[k] = D[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = I[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = D[j];
        j++;
        k++;
    }
}


void mergeSort(std::vector<int>& arr, int izq, int der) {
    if (izq < der) {
        int m = izq + (der - izq) / 2;

        mergeSort(arr, izq, m);

        mergeSort(arr, m + 1, der);

        merge(arr, izq, m, der);
    }
}

void printArray(const std::vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}


int main() {
    std::ifstream archivo("numeros.txt");  // Abrir el archivo en modo lectura

    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
        return 1;  // Salir si no se puede abrir el archivo
    }

    std::vector<int> arr;  // Vector para almacenar los números leídos
    int num;

    // Leer los números del archivo y almacenarlos en el vector
    while (archivo >> num) {
        arr.push_back(num);
    }

    archivo.close(); 
    std::cout << "Array original: ";
    // printArray(arr);

    auto start = std::chrono::high_resolution_clock::now();

    mergeSort(arr, 0, arr.size() - 1);

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Array ordenado: ";
    
    // printArray(arr);

    std::cout << std::endl;
    
    std::chrono::duration<double, std::milli> duration = end - start;
    // Imprimir el tiempo de ejecución
    std::cout << "El algoritmo se demoró " << duration.count() << " ms." << std::endl;
    return 0;
}
