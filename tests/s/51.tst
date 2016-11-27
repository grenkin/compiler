int A;

int main(int argc, char* argv[])
{
  int a;

  a = A;
   
  return 0;
}

char* f(char c)
{
  float b;
  b++;
}

typedef struct PointTag {
  int x;
  int y;
} PointT;

float sqr_distance(float x1, float y1, float x2, float y2)
{
  return (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1);
}

float sqr_distance1(struct PointTag p1, PointT p2)
{
  return (p2.x-p1.x)*(p2.x-p1.x) + (p2.y-p1.y)*(p2.y-p1.y);
}
