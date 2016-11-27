int main(void)
{
  enum c {
    D
  };
  int x;
  enum c { /* ошибка */
    E
  };
}