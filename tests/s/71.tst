int f(float x, int y) {
  f(y+1.0, y);
  f(x+1, y);
  f(x-2, y+1);
}