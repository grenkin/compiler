int x[6];
int i;

void main(void)
{
  int y[6];  

  x[0] = 1;
  x[1] = 2;
  x[2] = 3;  
  y[3] = 4;
  y[4] = 5;
  y[5] = 6;

  y[0] = x[0];
  y[1] = x[1];
  y[2] = x[2];
  x[3] = y[3];
  x[4] = y[4];
  x[5] = y[5];

  for (i = 0; i < 6; ++i) {
    print_int(x[i]);
    print_int(y[i]);
  }
}
