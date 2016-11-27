void compare(int x, int y)
{
  print_int(x < y);
  print_int(x <= y);
  print_int(x > y);
  print_int(x >= y);
  print_int(x == y);
  print_int(x != y);
}

void main(void)
{
  compare(1, 1);
  compare(5, 6);
  compare(10, -20);

}
