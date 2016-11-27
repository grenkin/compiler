void f(int x)
{
  print_int(x); print_string("\n");
  print_float(x); print_string("\n");
}

void g(float x)
{
  print_int(x); print_string("\n");
  print_float(x); print_string("\n");
}

void main(void)
{
  float x;
  int y;

  x = -3;
  y = -3.0;  

  f(x);
  g(y);
}