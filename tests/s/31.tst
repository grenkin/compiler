int main(void)
{
  enum a {
    A, B, C
  };

  {
    enum a { /* �� ������ */
      Z
    };
  }
}
