typedef struct PointTag
{
  float x[3];
  int y[3];
} T;

void f(T *p)
{
  int i;
  for (i = 0; i < 3; ++i) {
    print_float(p->x[i]);
    print_string(" ");
  }
  for (i = 0; i < 3; ++i) {
    print_int(p->y[i]);
    print_string(" ");
  }
}

void main(void) {
  T p;
  p.x[0] = 5;
  p.x[1] = 6;
  p.x[2] = 7;
  p.y[0] = 1;
  p.y[1] = 2;
  p.y[2] = 3;
  f(&p);
  print_float(1.5);
}
