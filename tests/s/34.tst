int main(void)
{
  struct a {
    int x;
    struct b {
      int y;
    } c;
  };

  struct b z;
  struct a t;
}