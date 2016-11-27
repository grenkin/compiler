struct X { int a; float b; };

void main(void) {
  struct X x, y;
  y.a = 5;
  y.b = 7;
  x = y;
  print_int(x.a);
  print_string("\n");
  print_float(x.b);
}