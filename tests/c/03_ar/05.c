typedef struct PointTag
{
  float x[3];
  int y[3];
} T;

void main(void) {
  T p;
  p.x[0] = 5.0;
  p.y[0] = 1;
  print_float(p.x[0]);
  print_string("\n");
  print_int(p.y[0]);
}
