#include <iostream>
#include <vector>
#include <fstream>
#include <chrono> 

using namespace std;

// Este algoritmo encuentra el elemento más pequeño en el vector no ordenado y 
// lo intercambia con el primer elemento del vector no ordenado.
void selectionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        std::swap(arr[i], arr[min]);
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
    selectionSort(arr);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;

    std::cout << "El algoritmo se demoró " << duration.count() << " ms en ordenar " << archivo << "." << std::endl;
}
int main() {
    procesarArchivo("caso1.txt");
    procesarArchivo("caso2.txt");
    procesarArchivo("caso3.txt");
    procesarArchivo("caso4.txt");
    procesarArchivo("numeros.txt");
    return 0;
}

