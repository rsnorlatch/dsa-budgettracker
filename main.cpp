#include <iostream>

using namespace std;

struct Entry {
  int id;
  string judul;
  int nominal;
};


#define T int
struct Node {
  T value;
  Node *next;
};

Node *node__add(T data, Node *next) {
  Node *new_node = new Node;
  new_node->value = data;
  new_node->next = next;

  return new_node;
}





void file__simpan_target_bulanan(int *target_bulanan) {
  FILE *file_target_bulanan = fopen("./store/target_bulanan.bin", "wb");

  fwrite(target_bulanan, sizeof(int), 1, file_target_bulanan);

  fclose(file_target_bulanan);
}

void file__baca_target_bulanan(int *target_bulanan) {
  FILE *file_target_bulanan = fopen("./store/target_bulanan.bin", "rb");
  fread(target_bulanan, sizeof(int), 1, file_target_bulanan);

  fclose(file_target_bulanan);
}

void file__reset_target_bulanan(int *target_bulanan) {
  FILE *file_target_bulanan = fopen("./store/target_bulanan.bin", "wb");
  int overwrite_value = 0;
  fwrite(&overwrite_value, sizeof(int), 1, file_target_bulanan);

  fclose(file_target_bulanan);
}

int main() {

}
