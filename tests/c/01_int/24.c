void f(void)
{
  return 1;
}

void main(void)
{

  print_int((f(), f(), f(), f(), f(), 10));

}