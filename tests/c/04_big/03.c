void swap(int *a, int *b)
{
  int tmp;
  tmp = *a;
  *a = *b;
  *b = tmp;
}

void main(void)
{
  int a[10];
  int i, j;

  for (i = 0; i < 10; ++i)
    a[i] = 9-i;


  for (i = 0; i < 10; ++i) {
    for (j = i+1; j < 10; ++j) {
      if (a[i] > a[j])
        swap(&a[i], &a[j]);
    }
  }

  for (i = 0; i < 10; ++i) {
    print_int(a[i]);
    print_string(" ");
  }

}
