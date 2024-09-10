#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <chrono> 
#include <string>

using namespace std;

//utiliza el sort implementado en la biblioteca <algorithm>
void sorting(vector<int>& arr){
    sort(arr.begin(), arr.end());
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
    sorting(arr);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start; 
    string salidaArchivo = nomarchivo.substr(0, nomarchivo.find_last_of('.')) + "_ordenado.txt";
    ofstream archivoSalida(salidaArchivo);
    for (int val : arr) {
        archivoSalida << val << " ";
    }
    archivoSalida.close();
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
