#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Estudiante {
    char nombre[50];
    int codigo;
    float nota;
    struct Estudiante* siguiente;
} Estudiante;

Estudiante* crearEstudiante(char* nombre, int codigo, float nota) {
    Estudiante* nuevoEstudiante = (Estudiante*)malloc(sizeof(Estudiante));
    strcpy(nuevoEstudiante->nombre, nombre);
    nuevoEstudiante->codigo = codigo;
    nuevoEstudiante->nota = nota;
    nuevoEstudiante->siguiente = NULL;
    return nuevoEstudiante;
}

void agregarEstudiante(Estudiante** cabeza, char* nombre, int codigo, float nota) {
    Estudiante* nuevoEstudiante = crearEstudiante(nombre, codigo, nota);
    nuevoEstudiante->siguiente = *cabeza;
    *cabeza = nuevoEstudiante;
}

void ordenarPorCodigo(Estudiante* cabeza) {
    if (cabeza == NULL) return;
    Estudiante* i;
    Estudiante* j;
    int tempCodigo;
    float tempNota;
    char tempNombre[50];

    for (i = cabeza; i != NULL; i = i->siguiente) {
        for (j = cabeza; j->siguiente != NULL; j = j->siguiente) {
            if (j->codigo > j->siguiente->codigo) {
                // Intercambio
                tempCodigo = j->codigo;
                j->codigo = j->siguiente->codigo;
                j->siguiente->codigo = tempCodigo;

                tempNota = j->nota;
                j->nota = j->siguiente->nota;
                j->siguiente->nota = tempNota;

                strcpy(tempNombre, j->nombre);
                strcpy(j->nombre, j->siguiente->nombre);
                strcpy(j->siguiente->nombre, tempNombre);
            }
        }
    }
}

void ordenarPorNota(Estudiante* cabeza) {
    if (cabeza == NULL) return;
    Estudiante* i;
    Estudiante* j;
    int tempCodigo;
    float tempNota;
    char tempNombre[50];

    for (i = cabeza; i != NULL; i = i->siguiente) {
        for (j = cabeza; j->siguiente != NULL; j = j->siguiente) {
            if (j->nota < j->siguiente->nota) {
                // Intercambio
                tempCodigo = j->codigo;
                j->codigo = j->siguiente->codigo;
                j->siguiente->codigo = tempCodigo;

                tempNota = j->nota;
                j->nota = j->siguiente->nota;
                j->siguiente->nota = tempNota;

                strcpy(tempNombre, j->nombre);
                strcpy(j->nombre, j->siguiente->nombre);
                strcpy(j->siguiente->nombre, tempNombre);
            }
        }
    }
}

void mostrarEstudiantes(Estudiante* cabeza) {
    Estudiante* actual = cabeza;
    printf("\nLista de Estudiantes:\n");
    while (actual != NULL) {
        printf("Nombre: %s, Codigo: %d, Nota: %.2f\n", actual->nombre, actual->codigo, actual->nota);
        actual = actual->siguiente;
    }
}

void mayorNota(Estudiante* cabeza) {
    Estudiante* actual = cabeza;
    Estudiante* mejorEstudiante = NULL;
    float mayor = -1;

    while (actual != NULL) {
        if (actual->nota > mayor) {
            mayor = actual->nota;
            mejorEstudiante = actual;
        }
        actual = actual->siguiente;
    }

    if (mejorEstudiante) {
        printf("Mayor Nota: %s con %.2f\n", mejorEstudiante->nombre, mejorEstudiante->nota);
    }
}

void menorNota(Estudiante* cabeza) {
    Estudiante* actual = cabeza;
    Estudiante* peorEstudiante = NULL;
    float menor = 101; // Suponiendo que la nota máxima es 100

    while (actual != NULL) {
        if (actual->nota < menor) {
            menor = actual->nota;
            peorEstudiante = actual;
        }
        actual = actual->siguiente;
    }

    if (peorEstudiante) {
        printf("Menor Nota: %s con %.2f\n", peorEstudiante->nombre, peorEstudiante->nota);
    }
}

void promedioNotas(Estudiante* cabeza) {
    Estudiante* actual = cabeza;
    float suma = 0;
    int contador = 0;

    while (actual != NULL) {
        suma += actual->nota;
        contador++;
        actual = actual->siguiente;
    }

    if (contador > 0) {
        printf("Promedio de Notas: %.2f\n", suma / contador);
    } else {
        printf("No hay estudiantes.\n");
    }
}

int main() {
    Estudiante* listaEstudiantes = NULL;
    int opcion;
    char nombre[50];
    int codigo;
    float nota;

    do {
        printf("\nMenu:\n");
        printf("1. Ingresar datos de estudiantes\n");
        printf("2. Ordenar y mostrar la lista de estudiantes\n");
        printf("3. Mostrar mayor, menor y promedio de notas\n");
        printf("4. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Ingrese el nombre del estudiante: ");
                scanf("%s", nombre);
                printf("Ingrese el codigo del estudiante: ");
                scanf("%d", &codigo);
                printf("Ingrese la nota del estudiante: ");
                scanf("%f", &nota);
                agregarEstudiante(&listaEstudiantes, nombre, codigo, nota);
                break;
            case 2:
                printf("Seleccione el criterio de ordenamiento:\n");
                printf("1. Por Codigo Estudiantil\n");
                printf("2. Por Nota\n");
                int criterio;
                scanf("%d", &criterio);
                if (criterio == 1) {
                    ordenarPorCodigo(listaEstudiantes);
                } else if (criterio == 2) {
                    ordenarPorNota(listaEstudiantes);
                } else {
                    printf("Opcion invalida.\n");
                    break;
                }
                mostrarEstudiantes(listaEstudiantes);
                break;
            case 3:
                mayorNota(listaEstudiantes);
                menorNota(listaEstudiantes);
                promedioNotas(listaEstudiantes);
                break;
            case 4:
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opcion invalida. Intente de nuevo.\n");
        }
    } while (opcion != 4);

    // Liberar memoria
    Estudiante* actual = listaEstudiantes;
    while (actual != NULL) {
        Estudiante* siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }

    return 0;
}
