#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <cmath>
#include <sys/wait.h>
#include <unistd.h>

void heavy_computation(int id, int iterations) {
    double result = 0.0;
    for (int i = 0; i < iterations; ++i) {
        result += std::sin(i) * std::cos(i); // Operasi berat
    }
    std::cout << "Task " << id << " selesai, hasil: " << result << std::endl;
}


void test_multithreading(int num_threads, int iterations) {
    std::vector<std::thread> threads;

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(heavy_computation, i, iterations);
    }

    for (auto& t : threads) {
        t.join();
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Multithreading selesai dalam "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;
}

void test_multiprocessing(int num_processes, int iterations) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < num_processes; ++i) {
        pid_t pid = fork();
        if (pid == 0) {
            // Proses anak
            heavy_computation(i, iterations);
            _exit(0); // Pastikan proses anak selesai
        }
    }

    for (int i = 0; i < num_processes; ++i) {
        wait(NULL); // Tunggu semua proses selesai
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Multiprocessing selesai dalam "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;
}

int main() {
    int num_tasks = 4;          // Jumlah thread/proses
    int iterations = 10000000; // Iterasi per tugas (beban kerja)

    std::cout << "=== Multithreading Test ===" << std::endl;
    test_multithreading(num_tasks, iterations);

    std::cout << "\n=== Multiprocessing Test ===" << std::endl;
    test_multiprocessing(num_tasks, iterations);

    return 0;
}

