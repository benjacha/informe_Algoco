#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <chrono> 

//utiliza el sort implementado en la biblioteca <algorithm>
void sorting(std::vector<int>& arr){
    std::sort(arr.begin(), arr.end());
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
    sorting(arr);
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
