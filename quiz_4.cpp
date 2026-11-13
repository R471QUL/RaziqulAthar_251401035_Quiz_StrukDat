#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int TABLE_SIZE = 20;

// Status tiap slot pada hash table
enum Status { KOSONG, TERISI, DIHAPUS };

struct Slot {
    long long nim;   // key
    string nama;     // value
    Status status;
};

class HashTable {
private:
    vector<Slot> table;

    // Hash1(key) = key % 20
    int hash1(long long key) {
        return key % TABLE_SIZE;
    }

    // Hash2(key) = 19 - (key % 19)
    int hash2(long long key) {
        return 19 - (key % 19);
    }

    // Mencari indeks slot milik key, -1 jika tidak ada
    int cari(long long key) {
        int h1 = hash1(key);
        int h2 = hash2(key);

        for (int i = 0; i < TABLE_SIZE; i++) {
            int index = (h1 + i * h2) % TABLE_SIZE;

            if (table[index].status == KOSONG) {
                return -1; // slot kosong asli: key pasti tidak ada
            }
            if (table[index].status == TERISI && table[index].nim == key) {
                return index;
            }
            // DIHAPUS atau terisi key lain: lanjut ke langkah berikutnya
        }
        return -1;
    }

public:
    HashTable() {
        table.resize(TABLE_SIZE);
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i].nim = 0;
            table[i].nama = "";
            table[i].status = KOSONG;
        }
    }

    void insert(long long nim, string nama) {
        if (cari(nim) != -1) {
            cout << "Insert " << nim << " gagal: NIM sudah ada." << endl;
            return;
        }

        int h1 = hash1(nim);
        int h2 = hash2(nim);

        // Double hashing: index = (h1 + i * h2) % TABLE_SIZE
        for (int i = 0; i < TABLE_SIZE; i++) {
            int index = (h1 + i * h2) % TABLE_SIZE;

            if (table[index].status != TERISI) {
                table[index].nim = nim;
                table[index].nama = nama;
                table[index].status = TERISI;

                cout << "Insert " << nim << " (" << nama << ") -> slot " << index;
                if (i > 0) {
                    cout << "  [collision, h1=" << h1 << ", h2=" << h2
                         << ", percobaan ke-" << i + 1 << "]";
                }
                cout << endl;
                return;
            }
        }

        cout << "Insert " << nim << " gagal: tidak ada slot yang bisa dijangkau." << endl;
    }

    void search(long long nim) {
        int index = cari(nim);

        if (index == -1) {
            cout << "Search " << nim << " -> tidak ditemukan." << endl;
        } else {
            cout << "Search " << nim << " -> ditemukan di slot " << index
                 << ", nama: " << table[index].nama << endl;
        }
    }

    void remove(long long nim) {
        int index = cari(nim);

        if (index == -1) {
            cout << "Remove " << nim << " -> gagal, data tidak ditemukan." << endl;
        } else {
            cout << "Remove " << nim << " (" << table[index].nama
                 << ") -> slot " << index << " dihapus." << endl;
            table[index].status = DIHAPUS;
        }
    }

    void display() {
        cout << "Slot | NIM       | Nama" << endl;
        cout << "---------------------------------" << endl;
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (i < 10) cout << " ";
            cout << i << "  | ";
            if (table[i].status == TERISI) {
                cout << table[i].nim << " | " << table[i].nama << endl;
            } else if (table[i].status == DIHAPUS) {
                cout << "(dihapus)" << endl;
            } else {
                cout << "(kosong)" << endl;
            }
        }
    }
};

int main() {
    HashTable ht;

    cout << "=== INSERT 18 DATA ===" << endl;
    ht.insert(251401001, "Andi");
    ht.insert(251401002, "Budi");
    ht.insert(251401003, "Citra");
    ht.insert(251401004, "Dina");
    ht.insert(251401005, "Eka");
    ht.insert(251401006, "Farhan");
    ht.insert(251401007, "Gita");
    ht.insert(251401008, "Hadi");
    ht.insert(251401009, "Indah");
    ht.insert(251401010, "Joko");
    ht.insert(251401011, "Kiki");
    ht.insert(251401012, "Lala");
    ht.insert(251401013, "Maya");
    ht.insert(251401014, "Nando");
    ht.insert(251401015, "Olivia");
    ht.insert(251401021, "Putra");   // collision dengan Andi
    ht.insert(251401039, "Qori");    // collision dengan Putra
    ht.insert(251401043, "Rani");    // collision berulang

    cout << "\n=== INSERT NIM DUPLIKAT ===" << endl;
    ht.insert(251401005, "Eka Duplikat");

    cout << "\n=== DISPLAY SEBELUM REMOVE ===" << endl;
    ht.display();

    cout << "\n=== SEARCH ===" << endl;
    ht.search(251401011);   // tanpa collision
    ht.search(251401039);   // hasil collision
    ht.search(251401099);   // tidak ada

    cout << "\n=== REMOVE ===" << endl;
    ht.remove(251401001);   // Andi, slot 1
    ht.remove(251401021);   // Putra, slot 19 (dilewati saat mencari Qori)
    ht.remove(251401099);   // tidak ada

    cout << "\n=== SEARCH SETELAH REMOVE ===" << endl;
    ht.search(251401001);   // sudah dihapus
    ht.search(251401021);   // sudah dihapus
    ht.search(251401039);   // masih harus ditemukan

    cout << "\n=== INSERT ULANG (memakai slot dihapus) ===" << endl;
    ht.insert(251401061, "Sinta");

    cout << "\n=== DISPLAY SETELAH SELURUH OPERASI ===" << endl;
    ht.display();

    return 0;
}