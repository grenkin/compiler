int x;

void main(void)
{
  struct {
    int x;
  } a;

  x = 2;
  a.x = 3;

  print_int(x);
  print_int(a.x);

  a.x += x;
  
  print_int(a.x);

  x = a.x+1;

  print_int(x);

}