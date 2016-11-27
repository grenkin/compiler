void main(void)
{
  print_int(9 & 7); /* 1 */                    print_string("\n");
  print_int(90 & 87); /* 82 */                 print_string("\n");
  print_int(+3); /* 3 */                       print_string("\n");
  print_int(-3); /* -3 */                      print_string("\n");
  print_int(- -3); /* 3 */                     print_string("\n");
  print_int(- +3); /* -3 */                    print_string("\n");
  print_int(~~5);  /* 5 */                     print_string("\n");
}
