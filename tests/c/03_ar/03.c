typedef struct PointTag {
  float x;
  float y;
} PointT;

void f(PointT *p1, PointT *p2)
{
  print_float(p1->x);
  print_string("\n");
  print_float(p1->y);
  print_string("\n");
  print_float(p2->x);
  print_string("\n");
  print_float(p2->y);
  print_string("\n");
}

void main(void) {
  PointT p, q;
  p.x = 1.5;
  p.y = 2.7;
  q.x = -1.5;
  q.y = -2.7;
  f(&p, &q);
}
