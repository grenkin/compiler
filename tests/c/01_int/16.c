void main(void)
{
  print_int(0&0);
  print_int(0&1);
  print_int(1&0);
  print_int(1&1);
  print_string("\n");

  print_int(0|0);
  print_int(0|1);
  print_int(1|0);
  print_int(1|1);
  print_string("\n");

  print_int(0^0);
  print_int(0^1);
  print_int(1^0);
  print_int(1^1);
  print_string("\n");
}