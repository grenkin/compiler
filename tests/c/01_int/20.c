void main(void) {
  int x; 
  int y;

  x = 3;
  y = 5;

  print_int(x == 3 || y == 5);
  print_int(x == 3 && y == 5);

  print_int(x == 3 || y == 4);
  print_int(x == 3 && y == 4);

  print_int(x == 4 || y == 5);
  print_int(x == 4 && y == 5);

  print_int(x == 4 || y == 4);
  print_int(x == 4 && y == 4);

  print_string("\n");

  print_int(3 && 5);
  print_int(0 && 3);
  print_int(3 && 0);
  print_int(0 && 0);

  print_string("\n");

  print_int(3 || 5);
  print_int(0 || 3);
  print_int(3 || 0);
  print_int(0 || 0);
}