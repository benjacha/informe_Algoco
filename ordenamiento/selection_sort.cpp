#include <iostream>
#include <vector>
#include <fstream>
#include <chrono> 

using namespace std;

void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        swap(arr[i], arr[min]);
    }
}



int main() {
    ifstream archivo("numeros.txt");  

    if (!archivo) {
        cerr << "No se pudo abrir el archivo." << endl;
        return 1; 
    }

    vector<int> arr;  
    int num;

    while (archivo >> num) {
        arr.push_back(num);
    }
    archivo.close(); 

    auto start = chrono::high_resolution_clock::now();
    selectionSort(arr);
    auto end = chrono::high_resolution_clock::now();

    // std::cout << "Array ordenado: ";
    
    // for (int i : arr) {
    //     std::cout << i << " ";
    // }
    
    std::cout << std::endl;

    chrono::duration<double, std::milli> duration = end - start;
    // Imprimir el tiempo de ejecución
    std::cout << "El algoritmo se demoró " << duration.count() << " ms." << std::endl;
    return 0;
}
