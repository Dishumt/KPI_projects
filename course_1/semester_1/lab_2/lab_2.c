#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void calculate_sum(float x, float eps);

int main() {
    float x, eps;
    
    printf("Enter the value of x (|x| <= 1): ");
    do {
        scanf("%f", &x);
        if (x < -1 || x > 1) {
            fprintf(stderr, "Try again with (|x| <= 1): ");
        }
    } while (x < -1 || x > 1);
    
    printf("Enter the value of epsilon (epsilon > 0): ");
    do {
        scanf("%f", &eps);
        if (eps <= 0) {
            printf("Epsilon must be greater than 0, try again: ");
        }
    } while (eps <= 0);

    calculate_sum(x, eps);

    return 0;
} 

void calculate_sum(float x, float eps) {
    int n = 1;
    float a = -(x * x) / 2.0f;
    float sum = a;             


    while (fabs(a) >= eps) {
        n++;
        //рекурсивний множник q = -x^2* (n - 1) / n
        a = a * (-(x * x) * (n - 1) / (float)n);

        sum += a;
    }

    //обчислення контрольного значення f(x)= -0.5 * ln(1 + x^2)
    float f = -0.5f * log(1.0f + x * x);

    printf("\n--- Results ---\n");
    printf("Calculated Sum (S): %f\n", sum);
    printf("Number of iterations (n): %d\n", n);
    printf("Exact Value f(x): %f\n", f);
    printf("Absolute Difference: %f\n", fabs(sum - f));
}