#include <iostream>
#include <vector>
#include <fstream>
#include <chrono> 

using namespace std;

vector<vector<int>> mulMatriz(vector<vector<int>> A, vector<vector<int>> B) {
    int ac = A.size();
    int bf = B[0].size();
    int af = A[0].size();

    vector<vector<int>> C(ac, vector<int>(bf, 0));
    
    for (int i = 0; i < ac; ++i) {
        for (int j = 0; j < bf; ++j) {
            for (int k = 0; k < af; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}

vector<vector<int>> leerArchivo(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir el archivo.\n";
        return {};
    }
    int fila, columnas;
    file >> fila >> columnas;

    vector<vector<int>> matriz(fila, vector<int>(columnas));

    for (int i = 0; i < fila; ++i) {
        for (int j = 0; j < columnas; ++j) {
            file >> matriz[i][j];
        }
    }

    file.close();
    return matriz;
}

void guardarMatriz(vector<vector<int>> matriz, string nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        int filas = matriz.size();
        int columnas = matriz[0].size();
        archivo << filas << " " << columnas << endl;  // Guardar el tamaño de la matriz
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

    vector<vector<int>> A = leerArchivo("matrizA.txt");
    vector<vector<int>> B = leerArchivo("matrizB.txt");

    auto start = chrono::high_resolution_clock::now();
    
    vector<vector<int>> C = mulMatriz(A, B);
    
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start; 
    cout << "El algoritmo se demoró " << duration.count() << " ms en ordenar." << endl;
    guardarMatriz(C, "matrizC.txt");
    return 0;
}