int f(float);
int f(float);int f(float);int f(float);int f(float);int f(float);int f(float);
int f(float), f(float), f(float), f(float), f(float);

int f(float x)
{
  int x1;
}

void main(void)
{
  enum A {
    A1, A2, A3, A4, A5    
  } a;
  int x;
  float y;
  int *p;

  {
    int x; /* не ошибка */
  } 

  main();
  f(x+1.); f(y); f(a- -2.3); f(-1.9);
  p[2];

  p++; p--;
  x++; y++; x--; y--;
  a--;
  +a; -a; +x; -y; +y;
  ~a; ~x; !p; !a;


}