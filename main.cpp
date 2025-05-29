#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <strings.h>

using namespace std;


struct Entry {
  char judul[250];
  int nominal;
};


#define T Entry
struct Node {
  T value;
  Node *prev;
  Node *next;
};

Node *node__tambah(T data, Node *prev, Node *next) {
  Node *node_baru = new Node;
  node_baru->value = data;
  node_baru->prev = prev;
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

  head = nullptr;
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
  head = node__tambah(data, nullptr, head);
}

void node__sisip_belakang(Node *&head, T data) {
  Node *new_node = node__tambah(data, new_node, nullptr);

  if (head == nullptr) {
    head = new_node;
    return;
  }

  Node *current = head;

  while (current != nullptr) {
    if (current->next == nullptr) {
      current->next = new_node;
      return;
    }

    current = current->next;
  }
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

  for (int i = 1; current != nullptr; i++) {
    cout << "=== " << i << "===" << endl;
    cout << "Judul: " << current->value.judul << endl;
    cout << "Nominal: " << current->value.nominal << endl << endl;
    current = current->next;
  } 
}

/**
 * mencari node berdasarkan judul
 * penggunaan:
* node__sisip_depan(n, {
  * .judul = "bakso"
  * .nominal = 10000
  * });
* node__sisip_depan(n, {
  * .judul = "mie ayam"
  * .nominal = 20000
  * });
 *
 * Node *node_mie_ayam = node_entry__cari_berdasarkan_judul(ENTRY_PENGELUARAN, "mie ayam");
 * cout << node_mie_ayam->nominal << endl; // 20000
 * 
 * */
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


/**
 * menjumlahkan semua nominal dalam linkedlist
 * penggunaan:
 *
* node__sisip_depan(n, {
  * .judul = "bakso"
  * .nominal = 10000
  * });
* node__sisip_depan(n, {
  * .judul = "mie ayam"
  * .nominal = 20000
  * });
 * int total_nominal = node_entry__sum_nominal(ENTRY_PENGELUARAN);
 *
 * cout << total_nominal << endl; // 30000
 * */
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

// baru
void halaman__set_budget_bulanan()
{
  int target_bulanan;
  cout << "=== Set Budget Bulanan ===" << endl;
  cout << "Masukkan target budget bulanan Anda: ";
  cin >> target_bulanan;

  if (target_bulanan < 0)
  {
    cout << "[ERROR] Nominal tidak boleh negatif!" << endl;
    return;
  }

  file__simpan_target_bulanan(&target_bulanan);
  cout << "Budget bulanan berhasil disimpan!" << endl
       << endl;
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
void file__baca_linkedlist_entry(Node *&head) {
  FILE *file_linkedlist = fopen("./store/linkedlist.bin", "rb");
  node__free(head);
  head = nullptr;

  while (true) {
    T value;
    if (fread(&value, sizeof(T), 1, file_linkedlist) != 1) break;
    node__sisip_belakang(head, value);
  }

  fclose(file_linkedlist);
}

void file__reset_linkedlist_entry() {
  FILE *file_linkedlist = fopen("./store/linkedlist.bin", "wb");

  fclose(file_linkedlist);
}

Node *ENTRY_PENGELUARAN = nullptr;
int BUDGET_PENGELUARAN;

void halaman__tambah_pengeluaran()
{
  system("clear");
  Entry data;
  cout << "=== Tambah Pengeluaran ===" << endl;
  cout << "Masukkan nama pengeluaran: ";
  cin.ignore();
  cin.getline(data.judul, 250);

  cout << "Masukkan nominal pengeluaran: ";
  cin >> data.nominal;

  if (data.nominal < 0)
  {
    cout << "[ERROR] Nominal tidak boleh negatif!" << endl;
    return;
  }

  node__sisip_depan(ENTRY_PENGELUARAN, data); 
  file__simpan_linkedlist_entry(ENTRY_PENGELUARAN);

  cout << "Pengeluaran berhasil ditambahkan!" << endl
       << endl;

  cout << "Tekan tombol sembarang untuk kembali..." << endl;
  getchar();
}

void halaman__lihat_sisa_budget()
{
  system("clear");
  int budget_bulanan;
  file__baca_target_bulanan(&budget_bulanan);

  file__baca_linkedlist_entry(ENTRY_PENGELUARAN);
  int total_pengeluaran = node_entry__sum_nominal(ENTRY_PENGELUARAN);

  int sisa_budget = budget_bulanan - total_pengeluaran;

  cout << "=== Sisa Budget Bulanan ===" << endl;
  cout << "Budget Bulanan     : " << budget_bulanan << endl;
  cout << "Total Pengeluaran  : " << total_pengeluaran << endl;
  cout << "Sisa Budget        : " << sisa_budget << endl
       << endl;


  cout << "Tekan tombol sembarang untuk kembali..." << endl;
  getchar();
}


void halaman__edit_pengeluaran() {
  system("clear");
  node_entry__print(ENTRY_PENGELUARAN);

  Node *entry_pilihan = nullptr;
  string error;

  do {
    if (error != "") {
      cout << error << endl;
    }

    int index_pilihan;
    cout << "masukkan indeks entry yang ingin diedit: ";
    cin >> index_pilihan;

    entry_pilihan = node__cari_berdasarkan_index(ENTRY_PENGELUARAN, index_pilihan);

    if (entry_pilihan == nullptr) {
      error = "Entry dengan index tersebut tidak ditemukkan!";
    }

  } while (entry_pilihan == nullptr);

  char judul_baru[250];
  int nominal_baru;

  cout << "Judul baru (tekan enter untuk melewati): ";
  cin.ignore();
  cin.getline(judul_baru, 250);

  cout << "Nominal baru (ketik 0 untuk melewati): ";
  cin >> nominal_baru;

  if (strcmp(judul_baru, "") != 0) strcpy(entry_pilihan->value.judul, judul_baru);
  if (nominal_baru) entry_pilihan->value.nominal = nominal_baru;

  file__simpan_linkedlist_entry(ENTRY_PENGELUARAN);

  cout << "Berhasil mengedit pengeluaran" << endl;
  cout << "Tekan tombol sembarang untuk kembali..." << endl;
  getchar();
}

void halaman__hapus_pengeluaran() {
  system("clear");
  node_entry__print(ENTRY_PENGELUARAN);

  Node *entry_pilihan = nullptr;
  string error;

  do {
    if (error != "") {
      cout << error << endl;
    }

    int index_pilihan;
    cout << "masukkan indeks entry yang ingin diedit: ";
    cin >> index_pilihan;

    entry_pilihan = node__cari_berdasarkan_index(ENTRY_PENGELUARAN, index_pilihan);

    if (entry_pilihan == nullptr) {
      error = "Entry dengan index tersebut tidak ditemukkan!";
    }

  } while (entry_pilihan == nullptr);

  node__hapus_berdasarkan_alamat(ENTRY_PENGELUARAN, entry_pilihan);
  file__simpan_linkedlist_entry(ENTRY_PENGELUARAN);

  cout << "Berhasil menghapus pengeluaran" << endl;
  cout << "Tekan tombol sembarang untuk kembali..." << endl;

  getchar();
}

int main() {
  file__baca_linkedlist_entry(ENTRY_PENGELUARAN);
  file__baca_target_bulanan(&BUDGET_PENGELUARAN);

  int pilihan;
  string error;

  while (true)
  {
    system("clear");

    cout << setw(27) << setfill('-') << "" << endl;
    cout << "Selamat datang di Budgetin!" << endl;
    cout << setw(27) << setfill('-') << "" << endl << endl;

    if (error != "") {
      cout << error << endl;
    }

    cout << "=== MENU ===" << endl;
    cout << "1. Lihat Pengeluaran" << endl;
    cout << "2. Tambah Pengeluaran" << endl;
    cout << "3. Set Budget Bulanan" << endl;
    cout << "4. Lihat Budget Bulanan" << endl;
    cout << "5. Total Pengeluaran Bulanan" << endl;
    cout << "6. Reset Data" << endl;
    cout << "7. Edit Pengeluaran" << endl;
    cout << "8. Hapus Pengeluaran" << endl;
    cout << "0. Keluar" << endl << endl;
    cout << "Pilihan: ";
    cin >> pilihan;
    cin.ignore();

    if (pilihan == 0)
    {
      node__free(ENTRY_PENGELUARAN);
      break;
    }

    if (pilihan == 1)
    {
      system("clear");
      node_entry__print(ENTRY_PENGELUARAN);
      cout << "Tekan tombol sembarang untuk kembali..." << endl;
      getchar();
    }
    else if (pilihan == 2)
    {
      halaman__tambah_pengeluaran();
    }
    else if (pilihan == 3)
    {
      system("clear");
      int budget;

      cout << "Masukkan Budget Bulanan: ";
      cin >> budget;
      cin.ignore();

      file__simpan_target_bulanan(&budget);
      BUDGET_PENGELUARAN = budget;

      cout << "Budget berhasil disimpan!" << endl;
      cout << "Tekan tombol sembarang untuk kembali..." << endl;
      getchar();
    }
    else if (pilihan == 4)
    {
      system("clear");
      cout << "Budget Bulanan Saat Ini: " << BUDGET_PENGELUARAN << endl;
      cout << "Tekan tombol sembarang untuk kembali..." << endl;
      getchar();
    }
    else if (pilihan == 5)
    {
      halaman__lihat_sisa_budget();
    }
    else if (pilihan == 6) 
    {
      system("clear");
      cout << "Apakah anda yakin ingin menghapus data? (y/n)" << endl;
      char pilihan;
      cout << "pilihan: ";
      cin >> pilihan;

      if (pilihan == 'y') {
        file__reset_target_bulanan();
        file__reset_linkedlist_entry();
        node__free(ENTRY_PENGELUARAN);
        ENTRY_PENGELUARAN = nullptr;
        
        cout << "Berhasil menghapus data!" << endl;
        cout << "Tekan tombol sembarang untuk kembali ke menu" << endl;
        getchar();
      } else {
        cout << "Berhasil batal menghapus data!" << endl;
        cout << "Tekan tombol sembarang untuk kembali ke menu" << endl;
        getchar();
      }
    }
    else if (pilihan == 7)
    {
      halaman__edit_pengeluaran();
    }
    else if (pilihan == 8)
    {
      halaman__hapus_pengeluaran();
    }
    else
    {
      error = "pilihan tidak valid!";
    }
  }
}
