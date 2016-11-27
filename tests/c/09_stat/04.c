void main(void)
{
  int i;

  i = 0;
  while (1) {
    ++i;
    if (i == 3)
      continue;
    print_int(i);
    if (i == 6)
      break;
  }

}
