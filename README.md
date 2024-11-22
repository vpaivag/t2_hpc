# Simulación de Difusión 2D Paralelizada

Este repositorio contiene tres implementaciones distintas de un simulador de difusión en 2D, cada una con diferentes técnicas de paralelización para mejorar el rendimiento.

## Descripción de los Archivos

### 1. **`parallel_double_grid.c`**

Este script utiliza:

- **OpenMP para paralelizar los cálculos**:
  Se aplica `#pragma omp parallel for private(j)` para paralelizar el bucle exterior que recorre las filas de la cuadrícula.
  
- **Doble cuadrícula (Double Grid)**:
  Una segunda cuadrícula (`new_grid`) almacena los valores actualizados en cada paso de simulación para evitar dependencias de datos y conflictos entre los hilos.

**Ventajas**:
- Evita problemas de acceso simultáneo a datos.
- Simple de implementar y escalable para sistemas con múltiples núcleos.

### 2. **`parallel_blocking.c`**

Este script utiliza:

- **División en bloques (Blocking)**:
  Divide la cuadrícula en subregiones más pequeñas (bloques) de tamaño `BLOCK_SIZE` para optimizar la localización de datos en la caché.

- **OpenMP con `collapse(2)`**:
  Se paralelizan ambos bucles (`i` y `j`) que recorren las filas y columnas, respectivamente, lo que aprovecha mejor los recursos del sistema.

**Ventajas**:
- Mejor uso de la jerarquía de memoria del procesador.
- Muy eficiente en sistemas con grandes cachés.

### 3. **`parallel_convergence.c`**

Este script utiliza:

- **Convergencia temprana**:
  La simulación se detiene antes de alcanzar el número máximo de pasos (`STEPS`) si los valores de la cuadrícula han convergido a un estado estable (basado en una tolerancia definida).

- **OpenMP para paralelizar**:
  Usa `#pragma omp parallel for` para acelerar los cálculos en cada iteración.

**Ventajas**:
- Ahorra tiempo al no realizar iteraciones innecesarias.
- Útil para simulaciones donde el tiempo de ejecución es crítico y el estado estable puede alcanzarse rápidamente.

## Compilación y Ejecución

Para correr los scripts se tienen dos archivos `bash`. El primero `slurm_base.sh` manda el script base a ejecutarse en el cluster. El archivo `slurm.sh` manda a ejecutar las tres versiones comentadas anteriormente. 

```bash
sbatch slurm_base.sh # Ejecuta solo el script base
sbatch slurm.sh # Ejecuta las 3 versiones paralelizadas





