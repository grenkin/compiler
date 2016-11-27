void main(void)
{
  struct S {
    int p;
    int q;
  } *ps; 

  ps->p = ps->q;

  ps,ps,ps;

  return 0;
}
