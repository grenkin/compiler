int fact(int n)
{
  if (n == 0)
    return 1;
  else
    return n*fact(n-1);
}

void main(void)
{
  print_int(fact(5));

}
