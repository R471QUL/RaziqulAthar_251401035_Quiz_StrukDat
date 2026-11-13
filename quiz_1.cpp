#include <iostream>
#include <string>
using namespace std;

// ================= SINGLE LINKED LIST: data mahasiswa =================
struct Mahasiswa {
    string nim;
    string nama;
    int nilai;
    Mahasiswa* next;
};

class DaftarMahasiswa {
private:
    Mahasiswa* head;
    Mahasiswa* tail;

public:
    DaftarMahasiswa() {
        head = nullptr;
        tail = nullptr;
    }

    ~DaftarMahasiswa() {
        while (head != nullptr) {
            Mahasiswa* hapus = head;
            head = head->next;
            delete hapus;
        }
    }

    // Linear search berdasarkan NIM, mengembalikan node atau nullptr
    Mahasiswa* linearSearchNIM(string nim) {
        Mahasiswa* temp = head;
        while (temp != nullptr) {
            if (temp->nim == nim) {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }

    // Menambah mahasiswa di belakang list
    bool tambah(string nim, string nama, int nilai) {
        if (linearSearchNIM(nim) != nullptr) {
            return false; // NIM sudah ada
        }

        Mahasiswa* baru = new Mahasiswa();
        baru->nim = nim;
        baru->nama = nama;
        baru->nilai = nilai;
        baru->next = nullptr;

        if (head == nullptr) {
            head = baru;
            tail = baru;
        } else {
            tail->next = baru;
            tail = baru;
        }
        return true;
    }

    void tampilkan() {
        if (head == nullptr) {
            cout << "Belum ada data mahasiswa." << endl;
            return;
        }

        cout << "No | NIM         | Nama            | Nilai" << endl;
        cout << "-----------------------------------------" << endl;

        int no = 1;
        Mahasiswa* temp = head;
        while (temp != nullptr) {
            cout << no++ << "  | " << temp->nim << " | " << temp->nama
                 << " | " << temp->nilai << endl;
            temp = temp->next;
        }
    }

    // Menampilkan semua mahasiswa yang memiliki nilai tertentu
    void tampilkanByNilai(int nilai) {
        Mahasiswa* temp = head;
        while (temp != nullptr) {
            if (temp->nilai == nilai) {
                cout << "  - " << temp->nim << " | " << temp->nama << endl;
            }
            temp = temp->next;
        }
    }
};

// ================= DYNAMIC ARRAY: kumpulan nilai =================
class DynamicArray {
private:
    int* data;
    int jumlah;
    int kapasitas;

    // Memperbesar kapasitas dua kali lipat saat array penuh
    void perbesar() {
        kapasitas *= 2;
        int* baru = new int[kapasitas];
        for (int i = 0; i < jumlah; i++) {
            baru[i] = data[i];
        }
        delete[] data;
        data = baru;
    }

public:
    DynamicArray() {
        kapasitas = 2;
        jumlah = 0;
        data = new int[kapasitas];
    }

    ~DynamicArray() {
        delete[] data;
    }

    void tambah(int nilai) {
        if (jumlah == kapasitas) {
            perbesar();
        }
        data[jumlah++] = nilai;
    }

    int ukuran() {
        return jumlah;
    }

    // Insertion sort: ascending (kecil ke besar)
    void insertionSort() {
        for (int i = 1; i < jumlah; i++) {
            int key = data[i];
            int j = i - 1;

            while (j >= 0 && data[j] > key) {
                data[j + 1] = data[j];
                j--;
            }
            data[j + 1] = key;
        }
    }

    // Binary search iteratif (array harus sudah terurut)
    int binarySearch(int target) {
        int left = 0;
        int right = jumlah - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (data[mid] == target) {
                return mid;
            } else if (target < data[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return -1;
    }

    void tampilkan() {
        for (int i = 0; i < jumlah; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

// ================= PROGRAM UTAMA =================
int main() {
    DaftarMahasiswa daftar;
    DynamicArray nilaiArray;
    bool terurut = false;
    int pilihan;

    do {
        cout << "\n===== SISTEM PENGELOLAAN NILAI MAHASISWA =====" << endl;
        cout << "1. Tambah data mahasiswa" << endl;
        cout << "2. Tampilkan data mahasiswa" << endl;
        cout << "3. Urutkan nilai (Insertion Sort)" << endl;
        cout << "4. Cari mahasiswa berdasarkan NIM (Linear Search)" << endl;
        cout << "5. Cari nilai (Binary Search)" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        if (pilihan == 1) {
            string nim, nama;
            int nilai;

            cout << "NIM   : ";
            cin >> nim;
            cin.ignore();
            cout << "Nama  : ";
            getline(cin, nama);
            cout << "Nilai : ";
            cin >> nilai;

            if (daftar.tambah(nim, nama, nilai)) {
                nilaiArray.tambah(nilai);
                terurut = false; // data baru, urutan harus dibuat ulang
                cout << "Data berhasil ditambahkan." << endl;
            } else {
                cout << "Gagal: NIM " << nim << " sudah terdaftar." << endl;
            }

        } else if (pilihan == 2) {
            cout << "\nData mahasiswa:" << endl;
            daftar.tampilkan();

            if (nilaiArray.ukuran() > 0) {
                cout << "\nKumpulan nilai (array): ";
                nilaiArray.tampilkan();
            }

        } else if (pilihan == 3) {
            if (nilaiArray.ukuran() == 0) {
                cout << "Belum ada data nilai." << endl;
            } else {
                cout << "Nilai sebelum diurutkan: ";
                nilaiArray.tampilkan();

                nilaiArray.insertionSort();
                terurut = true;

                cout << "Nilai setelah diurutkan: ";
                nilaiArray.tampilkan();
            }

        } else if (pilihan == 4) {
            string nim;
            cout << "Masukkan NIM yang dicari: ";
            cin >> nim;

            Mahasiswa* hasil = daftar.linearSearchNIM(nim);
            if (hasil != nullptr) {
                cout << "Data ditemukan -> NIM: " << hasil->nim
                     << ", Nama: " << hasil->nama
                     << ", Nilai: " << hasil->nilai << endl;
            } else {
                cout << "Mahasiswa dengan NIM " << nim << " tidak ditemukan." << endl;
            }

        } else if (pilihan == 5) {
            if (!terurut) {
                cout << "Urutkan nilai dulu (menu 3) sebelum memakai Binary Search." << endl;
            } else {
                int target;
                cout << "Masukkan nilai yang dicari: ";
                cin >> target;

                int index = nilaiArray.binarySearch(target);
                if (index != -1) {
                    cout << "Nilai " << target << " ditemukan pada indeks: " << index << endl;
                    cout << "Mahasiswa dengan nilai tersebut:" << endl;
                    daftar.tampilkanByNilai(target);
                } else {
                    cout << "Nilai " << target << " tidak ditemukan." << endl;
                }
            }

        } else if (pilihan != 0) {
            cout << "Pilihan tidak valid!" << endl;
        }

    } while (pilihan != 0);

    cout << "Program selesai." << endl;
    return 0;
}