
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

}
