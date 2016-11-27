void f(int* a)
{
  print_int(*a);
  *a = 1;
  print_int(*a);
}

void main(void)
{
  int x;

  x = 3;
  f(&x);

  print_int(x);

}
