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

void node__sisip_belakang(Node *&head, T data) {
  if (head == nullptr) {
    head = node__tambah(data, nullptr);
    return;
  }

  Node *current = head;

  while (current != nullptr) {
    if (current->next == nullptr) {
      current->next = node__tambah(data, nullptr);
      return;
    }

    current = current->next;
  }
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
  }
}

Node *node__cari_berdasarkan_index(Node *&head, int target_index) {
  Node *current = head;
  
  for (int i = 1; current != nullptr; i++) {
    if (i == target_index) {
      return current;
    }

    current = current->next;
  }

  return nullptr;
}

int main() {
  Node *n = nullptr;

  node__sisip_depan(n, 1);
  node__sisip_depan(n, 2);
  node__sisip_depan(n, 3);
  node__sisip_depan(n, 4);

  node__print_T(n);

  Node *empat = node__cari_berdasarkan_index(n, 2);
  cout << empat->value << endl;

  node__free(n);
}
