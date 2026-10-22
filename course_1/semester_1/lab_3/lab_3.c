#include <stdio.h> 
#include <stdlib.h> 

int main(){ 
float n;
int M; // Число рядків 
int N; // Число стовпців 
int i,j; // Індекси для циклу for 
float **a; // Двовимірний масив 
printf("\nEnter M: "); scanf("%d",&M); 
printf("\nEnter N: "); scanf("%d",&N); 
a=(float**) malloc(sizeof(float*)*M); 

for (i=0; i<M; i++) 
    *(a+i)=(float*)malloc(sizeof(float)*N); 
for (i=0; i<M; i++){ 
    for (j=0; j<N; j++){
        printf("Enter the element of %d row and %d column: ", i,j);
        scanf("%f", &a[i][j]);
        }
    } 
for (i=0; i<M; i++){ 
    for (j=0; j<N; j++) printf("%8.2g",a[i][j]); 
    printf("\n"); 
}

// Спочатку звільняємо пам'ять кожного рядка
for (i = 0; i < M; i++) {
    free(a[i]);
}
// Потім звільняємо масив вказівників
free(a);
}