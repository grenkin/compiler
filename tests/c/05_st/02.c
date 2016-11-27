
  struct {
    int x;
  } a;

void main(void)
{

  struct {
    int x;
  } b;
 
  struct {
    int a;
    struct {
      int z;
    } b;
  } c;


  print_int(a.x = -1);

  print_int(b.x = -5+10);

  print_int(c.b.z = a.x*b.x);

}