#include <iostream>
#include <vector>
#include <algorithm>  // Necesario para funcion sort
#include <fstream>
#include <chrono> 
#include <ctime> 

void sorting(std::vector<int>& arr){
    std::sort(arr.begin(), arr.end());
    return;
}

int main() {
    std::ifstream archivo("numeros.txt");  // Abrir el archivo en modo lectura
    
    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
        return 1;  // Salir si no se puede abrir el archivo
    }
    std::vector<int> arr;  // Vector para almacenar los números leídos
    
    int num;
    while (archivo >> num) {
        arr.push_back(num);
    }
    archivo.close(); 
    
    auto start = std::chrono::high_resolution_clock::now();
    sorting(arr);
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