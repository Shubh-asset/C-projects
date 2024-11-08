#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void print_menu()
{
    printf("\n--------------------------\n");
    printf("Choose one of the following option:");

    printf("\n1. Add\n2. Subtract\n3. Divide\n4. Multiply\n5. Modulus\n6. Power\n7. Exit\n");
    printf("now, enter your choice: ");
}

double division(double a, double b)
{
    if(b==0)
    {
        fprintf(stderr, "invalid argument for division function");
        return NAN;
    }
    else{
        return a/b;
       //printf("the result is %.2lf", a/b);
    }
}

double modulus(int a, int b)
{
    if(b==0){
        fprintf(stderr, "invalid argument for Modulus");
        //return NAN;
    }
    else{
        return a%b;
    }
}

int main()
{
    int choice;
    double first, second, result;
    
        while(1)
        {
            print_menu();
            scanf("%d", &choice);

                if (choice == 7)
                {
                    break;
                }
                if (choice<1 || choice > 7) 
                {
                    /* code */
                    fprintf(stderr, "invalid input of choice");
                    continue;
                }
                
        

                    printf("please enter the first number: ");
                    scanf("%lf", &first);
                    printf("please enter the second number: ");
                    scanf("%lf", &second);

                        switch(choice)
                            {
                                case 1:
                                    result=first+second;
                                    printf("the result is: %0.2lf", result);
                                break;

                                case 2:
                                    result = first - second;
                                    printf("the result is %.2lf", result);
                                break;

                                case 3:
                                    result = division(first, second);
                                    if(result!=NAN)
                                    {
                                    printf("\nthe result is: %0.2lf", result);
                                    }
                                    
                                break;

                                case 4:
                                    result = first * second;
                                    printf("the result is: %0.2lf", result);
                                break;

                                case 5:
                                    //result = (int)first % (int)second;
                                    result = modulus( first,  second);
                                    printf("\nthe result is: %0.2lf", result);
                                break;

                                case 6:
                                    result = pow(first,second);
                                    printf("the result is %0.2lf", result);
                                break;

                                    if(result!=NAN){
                                        printf("the result is %.2lf", result);
                                    }
                                
                            }

        
        }; 

            

    return 0;
}


