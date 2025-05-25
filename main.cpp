#include <iostream>

using namespace std;

int main() {
  int *p = (int *)malloc(sizeof(int));

  free(p);

  cout << *p << endl;
}
