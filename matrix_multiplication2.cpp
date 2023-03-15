#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <pthread.h>

using namespace std;

const int N = 200;
const int NUM_THREADS = 4;

int A[N][N], B[N][N], C[N][N];

// struct to hold the arguments for each thread
struct ThreadArgs {
    int thread_id;
};

// generates a random N x N matrix and stores it in the provided array
void generate_random_matrix(int matrix[N][N])
{
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = rand() % 10;
        }
    }
}

// multiplies a portion of matrices A and B and stores the result in C
void* multiply_matrices(void* thread_args)
{
    ThreadArgs* args = (ThreadArgs*) thread_args;
    int thread_id = args->thread_id;
    int start_row = thread_id * N / NUM_THREADS;
    int end_row = (thread_id + 1) * N / NUM_THREADS;

    for (int i = start_row; i < end_row; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    pthread_exit(NULL);
    return(C);
}

// writes an N x N matrix to a file
void write_matrix_to_file(int matrix[N][N], string filename)
{
    ofstream output_file(filename);
    if (output_file.is_open()) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                output_file << matrix[i][j] << " ";
            }
            output_file << endl;
        }
        output_file.close();
    } else {
        cout << "Unable to open file: " << filename << endl;
    }
}

int main()
{
    pthread_t threads[NUM_THREADS];
    ThreadArgs thread_args[NUM_THREADS];

    generate_random_matrix(A);
    generate_random_matrix(B);

    clock_t start_time = clock();

    // create threads to perform matrix multiplication concurrently
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_args[i].thread_id = i;
        int rc = pthread_create(&threads[i], NULL, multiply_matrices, (void*) &thread_args[i]);
        if (rc) {
            cout << "Error creating thread: " << rc << endl;
            exit(-1);
        }
    }

    // wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    double time_taken = double(clock() - start_time) / double(CLOCKS_PER_SEC);

    write_matrix_to_file(A, "A.txt");
    write_matrix_to_file(B, "B.txt");
    write_matrix_to_file(C, "C.txt");

    cout << "Execution time: " << time_taken << " seconds" << endl;

    pthread_exit(NULL);
}
