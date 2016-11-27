int main(void)
{
  struct a {
    int y;
  };

  struct a c;

  {
    struct a {
      int x;
    };

    struct a b;
  }

}