void main(void)
{
  int x, y;
  float z;
  int *px;
  float *pz;

  px = &x;
  pz = &z;

  z+=x-0.0;
  z=z+z;

  return 0;
}
