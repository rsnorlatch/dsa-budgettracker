#include <cassert>
#include <cstring>
#include <iostream>

using namespace std;


struct Entry {
  char judul[250];
  int nominal;
};


#define T Entry
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


/**
*  menyisipkan nilai didepan linkedlist
*  contoh :
*
* Node *n = nullptr;
* node__sisip_depan(n, {
  * .judul = "bakso"
  * .nominal = 10000
  * });
* node__sisip_depan(n, {
  * .judul = "mie ayam"
  * .nominal = 10000
  * });
* node_entry__print(n); 
* node__free(n);
* // output : mieayam->bakso->nullptr
*/


void node__sisip_depan(Node *&head, T data) {
  head = node__tambah(data, head);
}

/**
 * menghapus nilai dalam linkedlist berdasarkan alamat dalam memory
 * penggunaan:
 *
 * Node *n = nullptr;
 *
 * node__sisip
* node__sisip_depan(n, {
  * .judul = "bakso"
  * .nominal = 10000
  * });
* node__sisip_depan(n, {
  * .judul = "mie ayam"
  * .nominal = 10000
  * });
  *
  * node_entry__print(n); // mieayam->bakso->nullptr
  *
  * node__hapus_berdasarkan_alamat(n, n->next);
 *
  * node_entry__print(n); // mieayam->nullptr
  * node__free(n);
  *
  * penjelasan:
  * misal linkedlist berikut
  * n = a->b->c->nullptr
  *
  * misal b memiliki alamat 0x7FFDE13A9C40
  *
  * node__hapus_berdasarkan_alamat(n, 0x7FFDE13A9C40)
  * maka n = a->c->nullptr
 */

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

/**
 * mencetak seluruh entry yang tersimpan dalam linkedlist
 * */
void node_entry__print(Node *head) {
  if (head == nullptr) {
    cout << "entry kosong." << endl << endl;
    return;
  }

  Node *current = head;

  while (current != nullptr) {
    cout << "===" << endl;
    cout << "Judul: " << current->value.judul << endl;
    cout << "Nominal: " << current->value.nominal << endl << endl;
    current = current->next;
  } 
}

Node *node_entry__cari_berdasarkan_judul(Node *head, string target) {
  if (head == nullptr) {
    return nullptr;
  }

  Node *current = head;

  while (current != nullptr) {
    if (current->value.judul == target) {
      return current;
    }

    current = current->next;
  }

  return nullptr;
}

int node_entry__sum_nominal(Node *head) {
  if (head == nullptr) {
    return 0;
  }

  Node *current = head;
  int accumulator = 0;

  while (current != nullptr) {
    accumulator += current->value.nominal;

    current = current->next;
  }

  return accumulator;
}

/**
 * menyimpan target bulanan dalam file
 * penggunaan:
 *
 * int target_bulanan = 20000;
 *
 * file__simpan_target_bulanan(&target_bulanan);
 * */
void file__simpan_target_bulanan(int *target_bulanan) {
  FILE *file_target_bulanan = fopen("./store/target_bulanan.bin", "wb");

  fwrite(target_bulanan, sizeof(int), 1, file_target_bulanan);

  fclose(file_target_bulanan);
}


/**
 * membaca target bulanan dari file
 * penggunaan:
 *
 * int target_bulanan;
 *
 * file__baca_target_bulanan(&target_bulanan);
 * */
void file__baca_target_bulanan(int *target_bulanan) {
  FILE *file_target_bulanan = fopen("./store/target_bulanan.bin", "rb");
  fread(target_bulanan, sizeof(int), 1, file_target_bulanan);

  fclose(file_target_bulanan);
}

/**
* mereset data yang tersimpan dalam file target bulanan
* */
void file__reset_target_bulanan() {
  FILE *file_target_bulanan = fopen("./store/target_bulanan.bin", "wb");
  int overwrite_value = 0;
  fwrite(&overwrite_value, sizeof(int), 1, file_target_bulanan);

  fclose(file_target_bulanan);
}

/**
 * simpan linkedlist berisi entry ke dalam file
 * penggunaan:
 *
 * Node *n = nullptr;
 * node__sisip_depan(n, 3);
 * node__sisip_depan(n, 2);
 * node__sisip_depan(n, 1);
 *
 * file__simpan_linkedlist_entry(n);
 * node__free(n);
 * */

void file__simpan_linkedlist_entry(Node *&head) {
  FILE *file_linkedlist = fopen("./store/linkedlist.bin", "wb");

  Node *current = head;

  while (current != nullptr) {
    fwrite(&current->value, sizeof(T), 1, file_linkedlist);

    current = current->next;
  }

  fclose(file_linkedlist);
}

/**
 * membaca linkedlist berisi entry dari file
 * penggunaan:
 *
 * Node *n = nullptr;
 *
 * file__baca_linkedlist_entry(n);
 *
 * node__free(n);
 * */
// WARNING: pembacaan file membuat linkedlist menjadi terbalik
// TODO: tambahkan sisip belakang
void file__baca_linkedlist_entry(Node *&head) {
  FILE *file_linkedlist = fopen("./store/linkedlist.bin", "rb");

  while (true) {
    T value;
    if (fread(&value, sizeof(T), 1, file_linkedlist) != 1) break;
    node__sisip_depan(head, value);
  }

  fclose(file_linkedlist);
}

Node *ENTRY_PENGELUARAN = nullptr;

int main() {
  node__free(ENTRY_PENGELUARAN);
}
