void main(void)
{
  int a[6];

  a[3] = 1;
  a[5] = a[3]+1;

  print_int(a[3]);
  print_int(a[5]);
}