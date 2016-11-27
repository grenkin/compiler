void main(void)
{
  int x, y;
  x = 0;
  x = 0 || x;
  print_int(x);
  y = 0 || !x;
  print_int(y);
}
