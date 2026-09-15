#include <stdio.h>
#include <math.h>

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



void formula() {
    
    int mode = 0;
    printf("Type 1 to run the formula on the initial values or type 2 to provide your own: ");
    scanf("%d", &mode);

    float a,b,x,y;
    


    if(mode == 1){
        a = -0.92;
        b = 0.58;  
    } 
    else if (mode == 2){
        printf("Enter a: ");
        scanf("%f", &a);
        printf("Enter b: ");
        scanf("%f", &b);
    }
    else{
        printf("Usage: type 1 to run the formula on the initial values or type 2 to provide your own!");
    }

    x = pow(fabs(cos(fabs(a)) + cos(b)), (1 - 2*pow(sin(b), 2)));
    printf("x = %.4f\n", x);
    if(b != 2){
        ///y = log(pow(b, -sqrt(fabs(a)))) * (a - b/2.0) -> y = -sqrt(fabs(a)) * log(b) * (a - b/2.0)
        y = -sqrt(fabs(a)) * log(b) * (a - b/2.0);
        printf("y = %.4f", y);
    }
    else{
        printf("ln(b), b cannot be equal to 2)");
    }

}




void cycle() {

    int mode = 0;
    printf("Type 1 to run the cycle on the initial values or type 2 to provide your own: ");
    scanf("%d", &mode);

    float a,x,y;

    if(mode == 1){
        a = 1.5;
    } 
    else if (mode == 2){
        printf("Enter a: ");
        scanf("%f", &a);
    }
    else{
        printf("Usage: type 1 to run the formula on the initial values or type 2 to provide your own!");
    }

    


}