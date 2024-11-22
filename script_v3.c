#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>


// Definir el tamaño de la cuadrícula y el número de pasos de simulación
#define SIZE 3000    // Tamaño de la cuadrícula (3000x3000)
#define STEPS 10000  // Número de iteraciones para la simulación

int main() {
    // Variables para medir tiempo
    double start, end, cpu_time_used;

    // Reservar memoria dinámica para la cuadrícula como un array unidimensional
    double *grid = malloc(SIZE * SIZE * sizeof(double));
    double *new_grid = malloc(SIZE * SIZE * sizeof(double));

    if (grid == NULL || new_grid == NULL) {
        // Verificar si la asignación de memoria falló
        fprintf(stderr, "Error: Unable to allocate memory for grid.\n");
        return EXIT_FAILURE;
    }

    start = omp_get_wtime(); // Comenzar medicion del tiempo

    int i, j, step; // Variables de control para los bucles

    // Inicializar toda la cuadrícula con valores de 0.0
    for (i = 0; i < SIZE * SIZE; i++) {
        grid[i] = 0.0;
        new_grid[i] = 0.0;
    }

    // Establecer un valor inicial alto en el centro de la cuadrícula
    grid[(SIZE / 2) * SIZE + (SIZE / 2)] = 10000.0;


    double tolerance = 1e-6; // Tolerancia para la convergencia
    int converged = 0; // Convergio o no (1 si, 0 no)

    // Inicio de la simulación de difusión
    for (step = 0; step < STEPS && !converged; step++) {
    converged = 1; // Supón que converge
    #pragma omp parallel for private(j) reduction(&& : converged)
    for (i = 1; i < SIZE - 1; i++) {
        for (j = 1; j < SIZE - 1; j++) {
            double newValue = 0.25 * (
                grid[(i - 1) * SIZE + j] +
                grid[(i + 1) * SIZE + j] +
                grid[i * SIZE + (j - 1)] +
                grid[i * SIZE + (j + 1)]
            );
            if (fabs(newValue - grid[i * SIZE + j]) > tolerance) {
                converged = 0; // Si hay un cambio significativo, no ha convergido
            }
            new_grid[i * SIZE + j] = newValue;
        }
        }
        double *temp = grid;
        grid = new_grid;
        new_grid = temp;
    }

    end = omp_get_wtime(); // Finalizar medicion del tiempo
    cpu_time_used = end - start;

    // Imprimir el valor final en el centro de la cuadrícula
    printf("Final grid center value: %f\n", grid[(SIZE / 2) * SIZE + (SIZE / 2)]);
    printf("Time: %f", cpu_time_used);

    // Liberar la memoria asignada para la cuadrícula
    free(grid);
    free(new_grid);

    return 0; // Terminar el programa con éxito
}
