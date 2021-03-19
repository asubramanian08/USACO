//look at star league week 9 q3
int GCD(int num1, int num2)
{
    int temp;
    while (num2)
    {
        temp = num2;
        num2 = num1 % num2;
        num1 = temp;
    }
    return num1;
}
//if (GCD(x, y) <= 1) //has no in between latice points