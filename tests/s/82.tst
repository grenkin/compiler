struct T {
    int A;
};

int f(void)
{
    struct T;
    struct T z;
    z.A;
}

/* ошибка */