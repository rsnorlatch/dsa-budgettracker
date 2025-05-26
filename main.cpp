#include <iostream>

using namespace std;

struct Entry {
  int id;
  string judul;
  int nominal;
};


int main() {
  int *p = (int *)malloc(sizeof(int));
  *p = 10;

  cout << *p << endl;
}
