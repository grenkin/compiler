int main(void)
{
  typedef struct a { /* �� ������ */
    int x;
  };

  static struct b { /* �� ������ */
    int x;
  };

  struct a A;
  struct b B; /* �� static */

}
