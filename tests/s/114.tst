void main(void)
{
  int x, y;
  float z;
  int *px;
  float *pz;

  px = &x;
  pz = &z;
  pz = px;

  return 0;
}
