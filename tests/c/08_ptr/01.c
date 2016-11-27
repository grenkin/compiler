void swap(int* a, int* b)
{
  int tmp;
  tmp = *a;
  *a = *b;
  *b = tmp;
}

void main(void)
{
  int x, y;

  x = 1; y = 2;
  swap(&x, &y);

  print_int(x);
  print_int(y);

}
