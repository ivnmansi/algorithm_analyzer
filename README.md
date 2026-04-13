# algoritmos_tarea1

Proyecto en C para generar datos de deportistas, ejecutar busquedas y ordenamientos sobre esos datos, y medir el tiempo de ejecucion de cada algoritmo mediante benchmarks.

## Funcionalidad

- Generacion de un CSV con deportistas aleatorios.
- Busqueda por ID con busqueda secuencial o binaria.
- Ordenamiento interactivo por ID, puntaje, competencias, nombre o equipo.
- Ranking de los mejores deportistas por puntaje.
- Benchmarks de busqueda y ordenamiento con exportacion a CSV.
- Generacion de graficos a partir de los resultados con `gnuplot`.

## Compilacion

```bash
make
```

El ejecutable queda en `build/tarea_1_algoritmos.out`.

## Uso

```bash
./build/tarea_1_algoritmos.out -h
./build/tarea_1_algoritmos.out -g 1000
./build/tarea_1_algoritmos.out -t
./build/tarea_1_algoritmos.out -i 42
./build/tarea_1_algoritmos.out -r 10
./build/tarea_1_algoritmos.out -b
./build/tarea_1_algoritmos.out -s
make plot
```

Tambien se mantiene el alias `-id [valor]` por compatibilidad con el flujo previo del proyecto.

## Estructura

- `src/`: implementaciones del programa, algoritmos y benchmarks.
- `include/`: cabeceras publicas, estructuras, enums y prototipos.
- `db/`: datos CSV de entrada y resultados de benchmarks.
- `plots/`: script de `gnuplot` y graficos generados.
- `docs/`: informe del proyecto en LaTeX.

## Criterios de codificacion aplicados

El codigo del repositorio fue alineado con las normas adjuntas:

- Variables en `camelCase`.
- Funciones en `snake_case`.
- Constantes y macros en `SCREAMING_SNAKE_CASE`.
- Llave de apertura de funciones en la linea inferior al prototipo.
- Llaves en bloques de control siempre presentes, incluso si hay una sola sentencia.
- Errores centralizados mediante `print_error(...)` y un conjunto documentado de codigos.
- Comentarios y textos del proyecto en ASCII para evitar problemas de compatibilidad por tildes o `enie`.

## Codigos de error

Los mensajes de error visibles para el usuario se centralizan en `print_error(...)` mediante el enum `ErrorCode`:

| Codigo | Significado |
| --- | --- |
| `ERROR_INVALID_DATA_AMOUNT` | La cantidad de datos solicitada esta fuera del rango permitido. |
| `ERROR_INVALID_RANKING_AMOUNT` | El ranking solicitado es menor o igual a cero. |
| `ERROR_NO_DATA_LOADED` | No se pudieron cargar deportistas desde el CSV principal. |
| `ERROR_FILE_CREATE_FAILED` | No se pudo crear un archivo de salida. |
| `ERROR_MEMORY_ALLOCATION_FAILED` | Fallo una reserva de memoria dinamica. |
| `ERROR_BENCHMARK_DATA_LOAD_FAILED` | No se pudieron cargar datos para ejecutar un benchmark. |
| `ERROR_UNKNOWN_OPTION` | Se recibio una opcion invalida por linea de comandos. |
| `ERROR_NOT_IMPLEMENTED` | Se intento usar una opcion no implementada. |
| `ERROR_DEPORTISTA_NOT_FOUND` | No existe un deportista para el ID solicitado. |

## Modulos principales

- `csv.c`: genera y carga archivos CSV de deportistas.
- `deportista.c`: administra la estructura `Deportista`.
- `generator.c`: produce nombres, equipos, puntajes y competencias aleatorias.
- `run_experiment.c`: contiene el flujo interactivo para ordenar, buscar y mostrar rankings.
- `benchmarks.c`: mide tiempos de ejecucion y exporta resultados.
- `sorting.c` y algoritmos asociados: encapsulan comparacion y ordenamiento.
- `sequential_search.c` y `binary_search.c`: implementan las busquedas por ID.

## Notas

- Los archivos del informe en LaTeX se conservan aparte del flujo principal del programa.
- Los CSV y PNG generados pueden cambiar al ejecutar benchmarks o generar nuevos datos.
