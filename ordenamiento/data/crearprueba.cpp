#include <iostream>
#include <fstream>  // Para trabajar con archivos
#include <cstdlib>  // Para usar rand() y srand()
#include <ctime>    

int main() {
    std::ofstream archivo("numeros.txt");  // Crear o abrir el archivo
    int c;
    std::cin >> c;
    if (!archivo) {
        std::cerr << "No se pudo crear el archivo." << std::endl;
        return 1;  
    }

    srand(time(0));  

    for (int i = 0; i < c; ++i) {
        int num_aleatorio = rand() % 1000;  
        archivo << num_aleatorio << std::endl; 
    }

    archivo.close();  // Cerrar el archivo

    std::cout << "Archivo 'numeros.txt' creado con "<<  c <<" números aleatorios." << std::endl;

    return 0;
}
