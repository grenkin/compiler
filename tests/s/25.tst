struct tag;

struct tag {
  int x1, y1;
  char c;
  float z1;
  float a, b, c1, d;
};

struct tag t1;

struct tag *(*(**t2[5][4])(int))(void);