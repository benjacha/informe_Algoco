#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

vector<vector<int>> generarMatriz(int filas, int columnas) {
    vector<vector<int>> matriz(filas, vector<int>(columnas));
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            matriz[i][j] = rand() % 10;  
        }
    }
    return matriz;
}

void guardarMatrizEnArchivo(vector<vector<int>> matriz, string nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        int filas = matriz.size();
        int columnas = matriz[0].size();
        archivo << filas << " " << columnas << endl;  
        for (int i = 0; i < filas; ++i) {
            for (int j = 0; j < columnas; ++j) {
                archivo << matriz[i][j] << " ";
            }
            archivo << endl;
        }
        archivo.close();
        cout << "Matriz guardada en el archivo " << nombreArchivo << endl;
    } else {
        cout << "No se pudo abrir el archivo " << nombreArchivo << endl;
    }
}

int main() {
    srand(time(0));  
    int filasA = 200;  
    int columnasA = 400;  
    int filasB = columnasA;  
    int columnasB = 500;  

    vector<vector<int>> matrizA = generarMatriz(filasA, columnasA);
    vector<vector<int>> matrizB = generarMatriz(filasB, columnasB);

    guardarMatrizEnArchivo(matrizA, "matrizA.txt");
    guardarMatrizEnArchivo(matrizB, "matrizB.txt");

    return 0;
}
