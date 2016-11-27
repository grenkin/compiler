struct a {
  int x, y;
} t;

void main(void)
{
  t.x = 1;
  t.y = 2;

  print_int(t.x);
  print_int(t.y);
}