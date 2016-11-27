int f(float x, int y) {
  f(x, y++);

}

int main(void)
{
  f(-1.e3, 1);
  f(1.1, 1);
}