void f(int a[])
{
  a[0] = 5;

}

void main(void) {
  int a[3];
  f(a);

  print_int(a[0]);
}
