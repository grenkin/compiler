void main(void) {
  int a[3];
  int *p;
  int i;
  
  for (i = 0; i < 3; ++i)
    a[i] = i;

  p = &a[0];
  print_int(*p);
  p = &a[1];
  print_int(*p);
  p = &a[2];
  print_int(*p);
}
