int main(void)
{
  struct a;

  struct a c;
  /* ошибка */

  {
    struct a {
      int x;
    };

    struct a b;
  }

}