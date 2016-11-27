
int f(int* x)
{
    print_int(x[0]);
}

void main(void)
{
    int a[5];
    a[0] = 3;
    f(a);
}

