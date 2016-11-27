struct {
  int X, Y;
} A[3][5];

void main(void)
{
  A[0][0].X = 1;
  A[0][0].Y = 2;
  A[0][1].X = 3;
  A[0][1].Y = 4;
  print_int(A[0][0].X);
  print_int(A[0][0].Y);
  print_int(A[0][1].X);
  print_int(A[0][1].Y);
}