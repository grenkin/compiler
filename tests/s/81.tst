struct T {
    int A;
};

int f(void)
{
    struct T z;
    z.A;
}

/* не ошибка */