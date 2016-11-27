
void main(void)
{
int x;
  struct {
    int x, y;
  } p;

  p.x = 1;
  p.y = 2;

  print_int(p.x);
  print_int(p.y);

  p.x = p.y;

  print_int(p.x);
  print_int(p.y);

  p.x = 3;

  print_int(p.x);
  print_int(p.y);

  p.y = p.x;

  print_int(p.x);
  print_int(p.y);

}
