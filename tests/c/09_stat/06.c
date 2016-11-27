void main(void)
{
  int i;

  i = 0;
  do {
    ++i;
    if (i%2 == 0)
      continue;
    print_int(i);
    if (i > 7)
      break;
  } while (1);

}
