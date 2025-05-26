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

Node *node__tambah(T data, Node *next) {
  Node *node_baru = new Node;
  node_baru->value = data;
  node_baru->next = next;

  return node_baru;
}

void node__free(Node *head) {
  Node *current = head;

  while (current != nullptr) {
    Node *next = current->next;
    delete current;
    current = next;
  }
}

void node__print_T(Node *head) {
  if (head == nullptr) {
    cout << "NULL" << endl;
    return;
  }

  Node *current = head;

  while (current != nullptr) {
    cout << current->value << "->";
    current = current->next;
  } 

  cout << "NULL" << endl;
  node__free(head);
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
  Node *n = node__tambah(1, node__tambah(2, nullptr));

  node__print_T(n);
}
