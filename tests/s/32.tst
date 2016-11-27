int main(void)
{
  struct a {
    int x;
    struct a {
      int y;
    };
  };
}