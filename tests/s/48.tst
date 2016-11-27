int main(void)
{
  typedef struct a { /* не ошибка */
    int x;
  };

  static struct b { /* не ошибка */
    int x;
  };

  struct a A;
  struct b B; /* не static */

}
