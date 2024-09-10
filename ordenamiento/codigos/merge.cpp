#include <iostream>
#include <vector>
#include <fstream>
#include <chrono> 

using namespace std;

// Esta función toma dos vectores ya ordenados 
// el vector izquierdo que va desde el inicio(izq) hasta el medio(m),
// y el vector derecho que va desde el (m) hasta el final (der). los fusiona en uno solo ordenado. 
// Utiliza dos vectores auxiliares, I (para el vector izquierdo) 
// y D (para el vector derecho), y después los combina en el vector original arr
void merge(vector<int>& arr, int izq, int m, int der) {
    int n1 = m - izq + 1;
    int n2 = der - m;

    vector<int> I(n1), D(n2);

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

// Esta función divide el vector en dos mitades recursivamente hasta que solo quedan vectores de un solo elemento. 
// Luego, usa la función merge para fusionar las mitades de vuelta en un vector completamente ordenado.
void mergeSort(vector<int>& arr, int izq, int der) {
    if (izq < der) {
        int m = izq + (der - izq) / 2;
        mergeSort(arr, izq, m);
        mergeSort(arr, m + 1, der);
        merge(arr, izq, m, der);
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
    mergeSort(arr, 0, arr.size() - 1);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;

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


