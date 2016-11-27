void compare(int a, int b)
{
  print_int(a < b);  
  print_int(a <= b);
  print_int(a > b);
  print_int(a >= b);
  print_int(a == b);
  print_int(a != b);
  print_string("\n");
}

void main(void)
{
  compare(1, 1);
  compare(1, 2);
  compare(2, 1);
  compare(1, -1);
  compare(-1, 1);
  compare(-1, -1);
  compare(-1, -2);
  compare(-2, -1);
}
