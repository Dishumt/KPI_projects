#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define REPS 100000

int  fill_array(float **A, int *N);
void print_array(const float *A, int N);
void process_iter(const float *A, int N, float *S1, float *S2, int *K1, int *K2);
void process_rec(const float *A, int N, float *S1, float *S2, int *K1, int *K2);
int  formula(float S1, float S2, int K1, int K2, float *Z);

int main(void) {
    float *A = NULL;
    int N = 0;
    int k1, k2, rk1, rk2;
    float s1, s2, rs1, rs2, z;
    clock_t start;
    double t_iter, t_rec; 

    if (fill_array(&A, &N) != EXIT_SUCCESS)
        return EXIT_FAILURE;

    print_array(A, N);

    start = clock();
    for (int i = 0; i < REPS; i++)
        process_iter(A, N, &s1, &s2, &k1, &k2);
    t_iter = (double)(clock() - start) / CLOCKS_PER_SEC * 1e6 / REPS;

    start = clock();
    for (int i = 0; i < REPS; i++)
        process_rec(A, N, &rs1, &rs2, &rk1, &rk2);
     t_rec = (double)(clock() - start) / CLOCKS_PER_SEC * 1e6 / REPS;

    printf("Iterative: S1=%g K1=%d S2=%g K2=%d\n", s1, k1, s2, k2);
    printf("Run for: %g us \n", t_iter);
    printf("Recursive: S1=%g K1=%d S2=%g K2=%d\n", rs1, rk1, rs2, rk2);
    printf("Run for: %g us \n", t_rec);
    printf("Results match: %s\n",
           (s1 == rs1 && s2 == rs2 && k1 == rk1 && k2 == rk2) ? "yes" : "no");

    if (formula(s1, s2, k1, k2, &z) != EXIT_SUCCESS) {
        fprintf(stderr, "No nonzero values, cannot divide by zero\n");
        free(A);
        return EXIT_FAILURE;
    }
    printf("z = (S1 + S2)/(K1 + K2) = (%g + %g)/(%d + %d) = %g\n",
           s1, s2, k1, k2, z);

    free(A);
    return EXIT_SUCCESS;
}

int fill_array(float **A, int *N) {
    int cap = 4, n = 0;
    float x;

    float *arr = malloc(cap * sizeof(*arr));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Enter the numbers one by one, enter 'd' to stop:\n");

    while (1) {
        int r = scanf("%f", &x);
        if (r == 1) {
            if (n == cap) {
                cap *= 2;
                float *tmp = realloc(arr, cap * sizeof(*tmp));
                if (tmp == NULL) {
                    fprintf(stderr, "Memory allocation failed\n");
                    free(arr);
                    return EXIT_FAILURE;
                }
                arr = tmp;
            }
            arr[n++] = x;
        } else if (r == EOF) {
            break;
        } else {
            char c;
            scanf(" %c", &c);
            if (c == 'd' || c == 'D')
                break;
            printf("Not a number, try again\n");
            while (getchar() != '\n');
        }
    }

    *A = arr;
    *N = n;
    return EXIT_SUCCESS;
}

void print_array(const float *A, int N) {
    printf("Array (%d elements): ", N);
    for (int i = 0; i < N; i++)
        printf("%g ", A[i]);
    printf("\n");
}

void process_iter(const float *A, int N, float *S1, float *S2, int *K1, int *K2) {
    *S1 = *S2 = 0;
    *K1 = *K2 = 0;

    for (int i = 0; i < N; i++) {
        if (A[i] > 0) {
            *S1 += A[i];
            (*K1)++;
        } else if (A[i] < 0) {
            *S2 += A[i];
            (*K2)++;
        }
    }
}

void process_rec(const float *A, int N, float *S1, float *S2, int *K1, int *K2) {
    if (N == 0) {                       
        *S1 = *S2 = 0;
        *K1 = *K2 = 0;
        return;
    }
    process_rec(A, N - 1, S1, S2, K1, K2);   

    if (A[N - 1] > 0) {
        *S1 += A[N - 1];
        (*K1)++;
    } else if (A[N - 1] < 0) {
        *S2 += A[N - 1];
        (*K2)++;
    }
}

int formula(float S1, float S2, int K1, int K2, float *Z) {
    if (K1 + K2 == 0)
        return EXIT_FAILURE;
    *Z = (S1 + S2) / (K1 + K2);
    return EXIT_SUCCESS;
}