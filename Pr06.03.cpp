#include <iostream>
#include <random>
#include <omp.h>

int main() {
    int num_points = 10000000; 
    int num_inside_circle = 0;
    int num_threads = 4;

    double start_time = omp_get_wtime(); 

#pragma omp parallel num_threads(num_threads) reduction(+:num_inside_circle)
    {
        unsigned int seed = omp_get_thread_num();
        std::mt19937 rng(seed);
        std::uniform_real_distribution<double> dist(0, 1);

#pragma omp for
        for (int i = 0; i < num_points; i++) {
            double x = dist(rng);
            double y = dist(rng);
            if (x * x + y * y <= 1.0 * 1.0) {
                num_inside_circle++;
            }
        }
    }

    double end_time = omp_get_wtime(); 

    double pi = 4.0 * num_inside_circle / num_points;

    std::cout << "Threads = " << num_threads << std::endl;
    std::cout << "Points = " << num_points << std::endl;
    std::cout << "pi = " << pi << std::endl;
    std::cout << "Time taken: " << end_time - start_time << " seconds" << std::endl; 

    return 0;
}
