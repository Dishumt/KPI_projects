#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>

float get_random_float(float min, float max);
int get_random_int(int min, int max);
float get_random_float_int(float min, float max);

void free_matrix(float **a, int rows) {
    if (!a) return;
    for (int i = 0; i < rows; i++) {
        free(a[i]);
    }
    free(a);
}

int main(void) { 
    srand((unsigned int)time(NULL));

    int M, N;
    int i, j;
    int mode;
    float **a = NULL;
    float min, max;

    printf("Enter M: ");
    if (scanf("%d", &M) != 1 || M <= 0) {
        fprintf(stderr, "Invalid M size\n");
        return EXIT_FAILURE;
    }

    printf("Enter N: "); 
    if (scanf("%d", &N) != 1 || N <= 0) {
        fprintf(stderr, "Invalid N size\n");
        return EXIT_FAILURE;
    }

    a = (float**) malloc(sizeof(float*) * M);
    if (!a) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < M; i++) {
        *(a + i) = (float*) malloc(sizeof(float) * N); 
        if (!*(a + i)) {
            fprintf(stderr, "Memory allocation failed\n");
            free_matrix(a, i);
            return EXIT_FAILURE;
        }
    }

    printf("\nEnter 1 to enter the values or 2 to get random ones: "); 
    if (scanf("%d", &mode) != 1) {
        fprintf(stderr, "Enter a number\n");
        free_matrix(a, M);
        return EXIT_FAILURE;
    }

    switch (mode) {
    case 1:
        for (i = 0; i < M; i++) { 
            for (j = 0; j < N; j++) {
                printf("Enter the element of row %d, column %d: ", i + 1, j + 1);
                if (scanf("%f", &a[i][j]) != 1) {
                    fprintf(stderr, "Invalid number entered\n");
                    free_matrix(a, M);
                    return EXIT_FAILURE;
                }
            }
        } 
        break;

    case 2:
        printf("Enter a choice for random matrix generation:\n");
        printf("1 - with integers\n2 - with floats\n3 - with random mix of integers and floats\nChoice: ");
        if (scanf("%d", &mode) != 1) {
            fprintf(stderr, "Invalid mode input\n");
            free_matrix(a, M);
            return EXIT_FAILURE;
        }

        printf("Enter min random value: ");
        if (scanf("%f", &min) != 1) {
            fprintf(stderr, "Invalid min value\n");
            free_matrix(a, M);
            return EXIT_FAILURE;
        }
        printf("Enter max random value: ");
        if (scanf("%f", &max) != 1) {
            fprintf(stderr, "Invalid max value\n");
            free_matrix(a, M);
            return EXIT_FAILURE;
        }

        if (min > max) {
            float temp = min;
            min = max;
            max = temp;
        }

        if (mode == 1) {
            for (i = 0; i < M; i++) { 
                for (j = 0; j < N; j++) {
                    a[i][j] = (float)get_random_int((int)min, (int)max);
                }
            }
        }
        else if (mode == 2) {
            for (i = 0; i < M; i++) { 
                for (j = 0; j < N; j++) {
                    a[i][j] = get_random_float(min, max);
                }
            }
        }
        else if (mode == 3) {
            for (i = 0; i < M; i++) { 
                for (j = 0; j < N; j++) {
                    a[i][j] = get_random_float_int(min, max);
                }
            }
        }
        else {
            fprintf(stderr, "Invalid selection mode\n");
            free_matrix(a, M);
            return EXIT_FAILURE;
        }
        break;

    default:
        fprintf(stderr, "Invalid choice. Select 1 or 2\n");
        free_matrix(a, M);
        return EXIT_FAILURE;
    }

    printf("\nGiven matrix:\n");
    for (i = 0; i < M; i++) { 
        for (j = 0; j < N; j++) {
            printf("%8.2f", a[i][j]); 
        }
        printf("\n"); 
    }

    max = a[0][0];
    min = a[0][0];
    int max_row = 0, min_row = 0;

    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            if (a[i][j] > max) {
                max = a[i][j];
                max_row = i; 
            }
            if (a[i][j] < min) {
                min = a[i][j];
                min_row = i; 
            }
        }
    }

    if (max_row != min_row) {
        float *temp = a[max_row];
        a[max_row] = a[min_row];
        a[min_row] = temp;
        
        printf("\nSwapped row %d with row %d\n", max_row + 1, min_row + 1);
        printf("The matrix after swapping rows with min and max values:\n");
        for (i = 0; i < M; i++) { 
            for (j = 0; j < N; j++) {
                printf("%8.2f", a[i][j]); 
            }
            printf("\n"); 
        }
    }
    else {
        printf("\nMin and Max are in the same row (%d). No swap needed.\n", max_row + 1);
    }

    free_matrix(a, M);
    return 0;
}
    
float get_random_float(float min, float max) {
    float scale = (float)rand() / (float)RAND_MAX;
    return min + scale * (max - min);
}

int get_random_int(int min, int max) {
    return min + rand() % (max - min + 1);
}

float get_random_float_int(float min, float max) {
    int choice = 1 + rand() % 2;
    if (choice == 1) {
        return get_random_float(min, max);
    } else {
        return (float)get_random_int((int)min, (int)max);
    }
}