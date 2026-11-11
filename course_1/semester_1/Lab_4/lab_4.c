/* We need to:
1. Get the values
2. Process them:
    a) Devide them into massives for negative and positive values and get 0 out of account
    b) Create variables for sums and amounts
3. Find z, running the formula on the given data */

#include <stdio.h>
#include <stdlib.h>

void get_values(float *S1, float *S2, int *K1, int *K2);
void formula(float *S1, float *S2, int *K1, int *K2, float *Z);

int main(void) {
    int k1 = 0, k2 = 0;
    float s1 = 0, s2 = 0, z = 0;

    get_values(&s1, &s2, &k1, &k2);

    if (k1 + k2 == 0) {
        fprintf(stderr, "No nonzero values, cannot divide by zero\n");
        return EXIT_FAILURE;
    }

    formula(&s1, &s2, &k1, &k2, &z);
    printf("z = (S1 + S2)/(K1 + K2) = (%g + %g)/(%d + %d) = %g/%d = %g\n",
           s1, s2, k1, k2, s1 + s2, k1 + k2, z);
    return 0;
}

void get_values(float *S1, float *S2, int *K1, int *K2) {
    int nn = 0, np = 0;
    float x;

    printf("Enter the numbers one by one, enter 'd' to stop:\n");

    while (1) {
        int r = scanf("%f", &x);
        if (r == 1) {
            if (x > 0) {
                *S1 += x;
                (*K1)++;
                
            } 
            else if (x < 0) {
                *S2 += x;
                (*K2)++;
            }
        }
        else if (r == EOF) {
            break;
        } 
        else {
            char c;
            scanf(" %c", &c);
            if (c == 'd' || c == 'D')
                break;
            printf("Not a number, try again\n");
            while (getchar() != '\n');
        }
    }
}

void formula(float *S1, float *S2, int *K1, int *K2, float *Z) {
    *Z = (*S1 + *S2) / (*K1 + *K2);
}