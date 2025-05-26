#include <iostream>

using namespace std;

int main() {
  int *p = (int *)malloc(sizeof(int));
  *p = 10;

  cout << *p << endl;
}
