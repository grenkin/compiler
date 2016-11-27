void main(void)
{
  int x, y, z;
  x = 2;
  y = -5;
  print_int(x); print_string("\n");
  print_int(y); print_string("\n");
  z = x * y;
  print_int(z); print_string("\n");
  print_int(-z); print_string("\n");
  print_int(-z % 3); print_string("\n");
  print_int(x / -y); print_string("\n");
  x *= x;
  y *= y;
  print_int(x); print_string("\n");
  print_int(y); print_string("\n");
  x /= 2;
  y /= 5;
  print_int(x); print_string("\n");
  print_int(y); print_string("\n");
  print_int((-3)*(-5)); print_string("\n");
  print_int(3*(-5)); print_string("\n");
  print_int((-3)*5); print_string("\n");
}