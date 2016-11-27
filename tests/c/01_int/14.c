void main(void)
{
  print_int(1<<0); print_string("\n");
  print_int(1<<1); print_string("\n");
  print_int(1<<2); print_string("\n");
  print_int(1<<3); print_string("\n");
  print_int(1<<4); print_string("\n");
  print_int(1<<5); print_string("\n");
  print_int(1<<6); print_string("\n");

  print_int(1<<6>>6); print_string("\n");
  print_int(1<<6>>5); print_string("\n");
  print_int(1<<6>>4); print_string("\n");
  print_int(1<<6>>3); print_string("\n");
  print_int(1<<6>>2); print_string("\n");
  print_int(1<<6>>1); print_string("\n");
  print_int(1<<6>>0); print_string("\n");
}