int f(int, int b);

int f(int a, int b);

int a, b, c, d;

int f(int c, int d)
{
  c = d;
}

void main(void)
{
	f(a=b,c=d);
}
