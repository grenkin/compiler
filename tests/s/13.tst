struct A {
  int x, y, z;
  float t;
} a, b;

typedef struct A *(***P[3])(int);

int main(void)
{
  struct A a;
  P p1, p2, p3;  
}