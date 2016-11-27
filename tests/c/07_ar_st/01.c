
void main(void)
{
int x;
  struct {
    int x, y;
  } p[2];

  p[0].x = 1;
  p[1].y = 2;

  print_int(p[0].x);
  print_int(p[1].y);

  p[0].y = p[0].x;
  p[1].x = p[1].y;

  print_int(p[0].y);
  print_int(p[1].x);

                     
}
