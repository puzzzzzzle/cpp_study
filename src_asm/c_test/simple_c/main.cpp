int para_pass(int a, char b, double c, void * d)
{
  return a;
}
int main(int argc, char **argv) {
  para_pass(1,'x',3.14, nullptr);
  return 0;
}