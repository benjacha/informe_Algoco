#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include <string>

using type = int;
using Matrix = type**;
using size = std::size_t;

// Función para crear una matriz de tamaño N x N e inicializarla con ceros
Matrix createMatrix(size N) {
    Matrix newMatrix = new type*[N];
    for (unsigned int i = 0; i < N; i++) {
        newMatrix[i] = new type[N];
        for (unsigned int j = 0; j < N; j++) {
            newMatrix[i][j] = 0;  // Inicializamos con ceros
        }
    }
    return newMatrix;
}

// Función para liberar la memoria dinámica de una matriz
void freeMatrix(Matrix matrix, size N) {
    for (unsigned int i = 0; i < N; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

// Función para sumar dos matrices
Matrix add(Matrix A, Matrix B, size N) {
    Matrix C = createMatrix(N);
    for (unsigned int i = 0; i < N; i++) {
        for (unsigned int j = 0; j < N; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

// Función para restar dos matrices
Matrix subtract(Matrix A, Matrix B, size N) {
    Matrix C = createMatrix(N);
    for (unsigned int i = 0; i < N; i++) {
        for (unsigned int j = 0; j < N; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

// Función de multiplicación de matrices (clásica) para el caso base
Matrix sq_matrix_multiply(Matrix A, Matrix B, size N) {
    Matrix C = createMatrix(N);
    type sum = 0;

    for (unsigned int i = 0; i < N; i++) {
        for (unsigned int j = 0; j < N; j++) {
            for (size k = 0; k < N; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
            sum = 0;
        }
    }
    return C;
}

// Algoritmo de Strassen para multiplicar matrices
Matrix strassen(Matrix A, Matrix B, size N) {
    if (N == 1) {
        Matrix C = createMatrix(1);
        C[0][0] = A[0][0] * B[0][0];  // Caso base para 1x1
        return C;
    }

    Matrix C = createMatrix(N);
    size K = N / 2;

    // Crear submatrices
    Matrix A11 = createMatrix(K), A12 = createMatrix(K), A21 = createMatrix(K), A22 = createMatrix(K);
    Matrix B11 = createMatrix(K), B12 = createMatrix(K), B21 = createMatrix(K), B22 = createMatrix(K);

    // Llenar las submatrices
    for (unsigned int i = 0; i < K; i++) {
        for (unsigned int j = 0; j < K; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][K + j];
            A21[i][j] = A[K + i][j];
            A22[i][j] = A[K + i][K + j];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][K + j];
            B21[i][j] = B[K + i][j];
            B22[i][j] = B[K + i][K + j];
        }
    }

    // Calcular las matrices S
    Matrix S1 = subtract(B12, B22, K);
    Matrix S2 = add(A11, A12, K);
    Matrix S3 = add(A21, A22, K);
    Matrix S4 = subtract(B21, B11, K);
    Matrix S5 = add(A11, A22, K);
    Matrix S6 = add(B11, B22, K);
    Matrix S7 = subtract(A12, A22, K);
    Matrix S8 = add(B21, B22, K);
    Matrix S9 = subtract(A11, A21, K);
    Matrix S10 = add(B11, B12, K);

    // Calcular las matrices P
    Matrix P1 = strassen(A11, S1, K);
    Matrix P2 = strassen(S2, B22, K);
    Matrix P3 = strassen(S3, B11, K);
    Matrix P4 = strassen(A22, S4, K);
    Matrix P5 = strassen(S5, S6, K);
    Matrix P6 = strassen(S7, S8, K);
    Matrix P7 = strassen(S9, S10, K);

    // Combinar los resultados en la matriz C
    Matrix C11 = subtract(add(add(P5, P4, K), P6, K), P2, K);
    Matrix C12 = add(P1, P2, K);
    Matrix C21 = add(P3, P4, K);
    Matrix C22 = subtract(subtract(add(P5, P1, K), P3, K), P7, K);

    for (unsigned int i = 0; i < K; i++) {
        for (unsigned int j = 0; j < K; j++) {
            C[i][j] = C11[i][j];
            C[i][j + K] = C12[i][j];
            C[K + i][j] = C21[i][j];
            C[K + i][K + j] = C22[i][j];
        }
    }

    // Liberar memoria de las matrices intermedias
    freeMatrix(A11, K); freeMatrix(A12, K); freeMatrix(A21, K); freeMatrix(A22, K);
    freeMatrix(B11, K); freeMatrix(B12, K); freeMatrix(B21, K); freeMatrix(B22, K);
    freeMatrix(S1, K); freeMatrix(S2, K); freeMatrix(S3, K); freeMatrix(S4, K); freeMatrix(S5, K);
    freeMatrix(S6, K); freeMatrix(S7, K); freeMatrix(S8, K); freeMatrix(S9, K); freeMatrix(S10, K);
    freeMatrix(P1, K); freeMatrix(P2, K); freeMatrix(P3, K); freeMatrix(P4, K); freeMatrix(P5, K);
    freeMatrix(P6, K); freeMatrix(P7, K);

    return C;
}

// Función para encontrar la siguiente potencia de 2
unsigned int siguientePotenciaDeDos(unsigned int n) {
    if (n == 0) return 1;
    if ((n & (n - 1)) == 0) return n;
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    return n + 1;
}

// Función para escribir la matriz resultante en un archivo
void escribirMatrizEnArchivo(Matrix matriz, size fila, size columnas, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo para escribir.\n";
        return;
    }
    for (size i = 0; i < fila; ++i) {
        for (size j = 0; j < columnas; ++j) {
            file << matriz[i][j] << " ";
        }
        file << "\n";
    }
    file.close();
    std::cout << "Matriz escrita en el archivo: " << filename << std::endl;
}

int main() {
    std::ifstream fileA("matrizAcaso1.txt");
    if (!fileA.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo.\n";
        return {};
    }

    int filaA, columnasA;
    fileA >> filaA >> columnasA;

    std::ifstream fileB("matrizBcaso1.txt");
    if (!fileB.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo.\n";
        return {};
    }

    int filaB, columnasB;
    fileB >> filaB >> columnasB;

    if (columnasA != filaB) {
        std::cerr << "Error: Las dimensiones de las matrices no son compatibles para la multiplicación.\n";
        return {};
    }

    int N = std::max(filaA, std::max( columnasA, filaB));
    N = siguientePotenciaDeDos(N);

    Matrix matrizA = createMatrix(N);
    Matrix matrizB = createMatrix(N);

    // Leer los valores de las matrices
    for (int i = 0; i < filaA; ++i) {
        for (int j = 0; j < columnasA; ++j) {
            fileA >> matrizA[i][j];
        }
    }
    fileA.close();

    for (int i = 0; i < filaB; ++i) {
        for (int j = 0; j < columnasB; ++j) {
            fileB >> matrizB[i][j];
        }
    }
    fileB.close();
    
   auto start = std::chrono::high_resolution_clock::now();

    // Llamar a la multiplicación de Strassen
    Matrix matrizResultado = strassen(matrizA, matrizB, N);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start; 

    // Imprimir el tiempo que tomó la multiplicación
    std::cout << "El algoritmo de multiplicación de Strassen se demoró " << duration.count() << " ms." << std::endl;

    // Escribir la matriz resultante en un archivo
    escribirMatrizEnArchivo(matrizResultado, filaA, columnasB, "resultado.txt");

    // Liberar la memoria de las matrices
    freeMatrix(matrizA, N);
    freeMatrix(matrizB, N);
    freeMatrix(matrizResultado, N);

    return 0;
}

