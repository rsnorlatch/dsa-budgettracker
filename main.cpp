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

void node__sisip_depan(Node *&head, T data) {
  head = node__tambah(data, head);
}

int main() {
  Node *n = node__tambah(1, node__tambah(2, nullptr));

  node__sisip_depan(n, 3);
  node__sisip_depan(n, 4);

  node__print_T(n);
}
