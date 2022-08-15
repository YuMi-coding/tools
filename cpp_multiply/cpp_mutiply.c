#include <stdio.h>

int multiply(int para1, int para2)
{
    if(para2 == 1)
        return para1;
    else
    {
        return multiply(para1, para2 - 1) + multiply(para1, 1);
        // if(para2 % 2 == 0)
        //     return multiply(2 * para1, para2/2);
        // else
        //     return multiply(2 * para1, para2/2) + multiply(para1, 1);
    }
}

int main()
{
    int para1, para2;
    int is_negative=1;
    int result = 0;
    printf("Input the two numbers you want to multiply: ");
    scanf("%d%d", &para1, &para2);

    if(para1 < 0)
    {
        is_negative *= -1;
        para1 = -para1;
    }
    if(para2 < 0)
    {
        is_negative *= -1;
        para2 = -para2;
    }

    printf("The result is %d.\n", is_negative *multiply(para1, para2));
    return 0;

}
