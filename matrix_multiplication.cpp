#include <iostream>
#include <fstream>  // for file I/O
#include <cstdlib>  // for rand() and srand()
#include <ctime>    // for time()

using namespace std;

const int N = 50; // size of the matrices

// generates a random N x N matrix and stores it in the provided array
void generate_random_matrix(int matrix[N][N])
{
    srand(time(NULL)); // initialize random seed

    // iterate over each element in the matrix
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // generate a random number between 0 and 9 and store it in the matrix
            matrix[i][j] = rand() % 10;
        }
    }
}

// multiplies two N x N matrices A and B and stores the result in C
void multiply_matrices(int A[N][N], int B[N][N], int C[N][N])
{
    // iterate over each row in A and each column in B
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0; // initialize the current element in C to 0
            // iterate over each element in the current row of A and current column of B
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j]; // calculate the dot product and add it to the current element in C
            }
        }
    }
}

// writes an N x N matrix to a file
void write_matrix_to_file(int matrix[N][N], string filename)
{
    ofstream output_file(filename); // open the file for writing
    if (output_file.is_open()) {
        // iterate over each element in the matrix and write it to the file
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                output_file << matrix[i][j] << " ";
            }
            output_file << endl; // move to the next row in the file
        }
        output_file.close(); // close the file when we're done writing
    } else {
        cout << "Unable to open file: " << filename << endl;
    }
}

int main()
{
    int A[N][N], B[N][N], C[N][N];

    generate_random_matrix(A); // generate random matrix A
    generate_random_matrix(B); // generate random matrix B

    multiply_matrices(A, B, C); // multiply matrices A and B and store the result in C

    // write each matrix to a separate file
    write_matrix_to_file(A, "A.txt");
    write_matrix_to_file(B, "B.txt");
    write_matrix_to_file(C, "C.txt");

    return 0;
}
