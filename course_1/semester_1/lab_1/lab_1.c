#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

void formula();
void cycle();
int get_multiplier(float start,float step,float end);
int count_decimals(float val);

int main(){
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
        if(b <= 0){
            fprintf(stderr, "there is an operation ln(b) in the formula, b must be greater than 0");
            exit(EXIT_FAILURE);
        }
    }


        x = pow(fabs(cos(fabs(a)) + cos(b)), (1 - 2*pow(sin(b), 2)));
        printf("x = %.4f\n", x);
        ///y = log(pow(b, -sqrt(fabs(a)))) * (a - b/2.0) -> y = -sqrt(fabs(a)) * log(b) * (a - b/2.0)
        y = -sqrt(fabs(a)) * log(b) * (a - b/2.0);
        printf("y = %.4f", y);
}




void cycle(){

    int mode = 0;
    printf("Type 1 to run the cycle on the initial values or type 2 to provide your own range of x, value of a, and step_x: ");
    scanf("%d", &mode);
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    float a, x, y, start, end, step;
    char left_b, right_b;
    int multiplier = 1;


    if(mode !=1 && mode !=2){
        fprintf(stderr, "Usage: type 1 to run the cycle on the initial values or type 2 to provide your own!");
        exit(EXIT_FAILURE);
    } 
    else if (mode == 1){
        a = 1.5;
        start = 0.1;
        end = 1;
        step = 0.1;
        multiplier = 10;
    }
    else if (mode == 2){
        char range_str[100];
        printf("Enter the range of x and step_x as '(a;b) c or [a;b] c' where a,b and c are float numbers (example: '(1.0;10.0) 3.0': ");
        if (fgets(range_str, sizeof(range_str), stdin) == NULL) {
        exit(EXIT_FAILURE);
        }   

        int parsed = sscanf(range_str, "%c%f;%f%c %f", &left_b, &start, &end, &right_b, &step);
        if (parsed != 5){
            fprintf(stderr, "Usage: enter the range of x and step_x as '(a;b) c or [a;b] c' where a,b and c are numbers (example: '(1;12.5) 3.25)'");
            exit(EXIT_FAILURE);
        }
        else if (end<=start){
            fprintf(stderr, "The end of the range must be greater than the start");
            exit(EXIT_FAILURE);
        }
        
        else if (left_b != '(' && left_b != '[' || right_b != ')' && right_b != ']'){
            fprintf(stderr, "Usage: use round or square brakets, example: '(1.5;10) 3' ");
            exit(EXIT_FAILURE);
        }

        if(left_b == '('){
            start += step;
        }
        else {
        }
        
        if(right_b == ')'){
            end -= step;
        }
        else {
        }
        multiplier = get_multiplier(start, step, end);
        
        printf("Enter the value of parameter a: ");
        if (scanf("%f", &a) != 1){
        fprintf(stderr, "Usage: enter a number\n");
        exit(EXIT_FAILURE);    
        }

    }

    int i_start = (int)roundf(start * multiplier);
    int i_end   = (int)roundf(end * multiplier);
    int i_step  = (int)roundf(step * multiplier);

    printf("+-----------------+-----------------+\n");
    printf("| %-15s | %-15s |\n", "ax", "y");
    printf("+-----------------+-----------------+\n");
    for(int i = i_start; i <= i_end; i += i_step){ ///ohh
        x = (float)i / multiplier;
        float ax = a*x;
        
        if(ax < 1){
            y = ax - log10f(ax); ///ax>0
            printf("|%15.4g  | %15.4g |\n", ax, y);
            printf("+-----------------+-----------------+\n");
        }
        else if (fabsf(ax - 1.0f) <= 1e-5f * fmaxf(fabsf(ax), 1.0f)){
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

int get_multiplier(float start,float step,float end){
    
    int d_start = count_decimals(start);
    int d_step  = count_decimals(step);
    int d_end   = count_decimals(end);

    int max_dec = d_start;
    if (d_step > max_dec) max_dec = d_step;
    if (d_end > max_dec)  max_dec = d_end;

    int multiplier = 1;
    for (int i = 0; i < max_dec; i++) {
        multiplier *= 10;
    }
    return multiplier;
}

int count_decimals(float val){
    char buf[64];

    snprintf(buf, sizeof(buf), "%.6f", val);

    int len = strlen(buf);
    while (len > 0 && buf[len - 1] == '0') {
        buf[--len] = '\0';
    }

    char *dot = strchr(buf, '.');
    
    if (dot == NULL) {
        return 0;
    }
    return strlen(dot + 1);
}