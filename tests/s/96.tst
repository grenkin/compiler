struct {
  struct {
    struct {
      float d;
    } c;
  } b;
} a;

struct {
  struct {
    int t;
  } f;
} e;

struct {
  char b;
} *a1;

int main(void)
{
  a.b.c.d-e.f.t+a1->b;
}