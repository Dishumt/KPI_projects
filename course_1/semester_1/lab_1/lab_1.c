#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void formula();
void cycle();

int main()
{
    int mode = 0;
    printf("Type 1 to enter the formula mode, 2 to enter the cycle mode: ");
    scanf("%d", &mode);

    if(mode == 1){
        formula();
    } 
    else if (mode == 2){
        cycle();
    }
    else{
        printf("Usage: type 1 to enter the formula mode or 2 to enter the cycle mode!");
    }

    return 0;
}



void formula(){
    
    int mode = 0;
    printf("Type 1 to run the formula on the initial values or type 2 to provide your own: ");
    scanf("%d", &mode);

    float a,b,x,y;
    


    if(mode !=1 && mode !=2){
        fprintf(stderr, "Usage: type 1 to run the formula on the initial values or type 2 to provide your own!");
        exit(EXIT_FAILURE);
    } 
    else if (mode == 1){
        a = -0.92;
        b = 0.58;  
    }
    
    else if (mode == 2){
        printf("Enter a: ");
        scanf("%f", &a);
        printf("Enter b: ");
        scanf("%f", &b);
    }


        x = pow(fabs(cos(fabs(a)) + cos(b)), (1 - 2*pow(sin(b), 2)));
        printf("x = %.4f\n", x);

        if(b > 0){
            ///y = log(pow(b, -sqrt(fabs(a)))) * (a - b/2.0) -> y = -sqrt(fabs(a)) * log(b) * (a - b/2.0)
            y = -sqrt(fabs(a)) * log(b) * (a - b/2.0);
            printf("y = %.4f", y);
        }
        else{
            printf("there is an operation ln(b) in the formula, b cannot be equal to 0)");
        }
}




void cycle(){

    int mode = 0;
    printf("Type 1 to run the cycle on the initial values or type 2 to provide your own range of x, value of a, and step ∆x: ");
    scanf("%d", &mode);

    float a,x,y;


    if(mode !=1 && mode !=2){
        fprintf(stderr, "Usage: type 1 to run the cycle on the initial values or type 2 to provide your own!");
        exit(EXIT_FAILURE);
    } 
    else if (mode == 1){
        a = 1.5;
    }
    
    else if (mode == 2){
        printf("Enter a: ");
        if (scanf("%f", &a) != 1){
        fprintf(stderr, "Usage: enter a number\n");
        exit(EXIT_FAILURE);    
        }
        printf("Enter the start of the range as '(x' where x is a number: ");
        printf("Enter ∆x: ");
    }
    printf("+-----------------+-----------------+\n");
    printf("| %-15s | %-15s |\n", "x", "y");
    printf("+-----------------+-----------------+\n");
    for(int i = 1; i <= 10; i++){ ///ohh
        x = i/10.0f;
        float ax = a*x;
        
        if(ax < 1){
            y = ax - log10f(ax);
            printf("|%15.4g  | %15.4g |\n", ax, y );
            printf("+-----------------+-----------------+\n");
        }
        else if (ax == 1){
            y = 1;
            printf("|%15.4g  | %15.4g |\n", ax, y );
            printf("+-----------------+-----------------+\n");
        }
        else if(ax > 1){
            y = ax + log10f(ax);
            printf("|%15.4g  | %15.4g |\n", ax, y );
            printf("+-----------------+-----------------+\n");
        }
        
      
    }
}