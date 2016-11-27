void main(void)
{
  int x, y;
  float z;
  int *px;
  float *pz;

  px = &x;
  pz = &z;

  z+=x;
  z=z+z;

  x++;
  --y;

  return 0;
}
