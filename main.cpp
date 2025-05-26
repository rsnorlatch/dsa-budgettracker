#include <cstring>
#include <iostream>

using namespace std;

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

// NOTE: WAJIB DIPANGGIL DIAKHIR PROGRAM
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
}

void node__sisip_depan(Node *&head, T data) {
  head = node__tambah(data, head);
}

void node__hapus_berdasarkan_alamat(Node *&head, Node *target) {
  if (target == nullptr) {
    cout << "[ERROR] anda mencoba menghapus nullpointer!!!" << endl;
    return;
  }

  Node *current = head;

  if (current == target) {
    head = current->next;
    delete current;
    return;
  }

  while (current != nullptr) {
    if (current->next != target) {
      current = current->next;
      continue;
    }

    current->next = current->next->next;
    delete target;
  }
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

void file__simpan_linkedlist(Node *&head) {
  FILE *file_linkedlist = fopen("./store/linkedlist.bin", "wb");

  Node *current = head;

  while (current != nullptr) {
    fwrite(&(current->value), sizeof(T), 1, file_linkedlist);
    current = current->next;
  }

  fclose(file_linkedlist);
}

void file__baca_linkedlist(Node *&head) {
  FILE *file_linkedlist = fopen("./store/linkedlist.bin", "rb");

  T value;

  while (fread(&value, sizeof(T), 1, file_linkedlist)) {
    node__sisip_depan(head, value);
  }

  fclose(file_linkedlist);
}

int main() {
  Node *n = nullptr;
  /*node__sisip_depan(n, 4);*/
  /*node__sisip_depan(n, 3);*/
  /*node__sisip_depan(n, 2);*/
  /*node__sisip_depan(n, 1);*/
  /**/
  /*file__simpan_linkedlist(n);*/

  file__baca_linkedlist(n);

  node__print_T(n);
  node__free(n);
}
