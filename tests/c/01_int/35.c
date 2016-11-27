void main(void)
{
  print_int(1 || 1);
  print_int(0 || 1);
  print_int(0 || 0);
  print_int(3 && 5);
  print_int(3 && 0);
  print_int(0 && 3);
  print_int(0 && 0);
  print_int(1 | 0);
  print_int(0 | 0);
  print_int(1 | 1);
  print_int(0 ^ 0);
  print_int(1 ^ 1);
  print_int(1 ^ 0);
  print_int(0 & 0);
  print_int(1 & 0);
  print_int(1 & 1);

}
