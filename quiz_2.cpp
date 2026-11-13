#include <iostream>
#include <string>
using namespace std;

// ================= QUEUE (linked list): antrean peminjaman =================
struct Antrean {
    string nim;
    string nama;
    Antrean* next;
};

class QueueMhs {
private:
    Antrean* front;
    Antrean* rear;

public:
    QueueMhs() {
        front = nullptr;
        rear = nullptr;
    }

    ~QueueMhs() {
        while (front != nullptr) {
            Antrean* hapus = front;
            front = front->next;
            delete hapus;
        }
    }

    bool kosong() {
        return front == nullptr;
    }

    // Enqueue: masuk dari belakang
    void enqueue(string nim, string nama) {
        Antrean* baru = new Antrean();
        baru->nim = nim;
        baru->nama = nama;
        baru->next = nullptr;

        if (rear == nullptr) {
            front = baru;
            rear = baru;
        } else {
            rear->next = baru;
            rear = baru;
        }
    }

    // Melihat mahasiswa paling depan tanpa mengeluarkannya
    Antrean* depan() {
        return front;
    }

    // Dequeue: keluar dari depan (FIFO)
    void dequeue() {
        if (front == nullptr) return;

        Antrean* hapus = front;
        front = front->next;
        if (front == nullptr) rear = nullptr;
        delete hapus;
    }

    void tampilkan() {
        if (front == nullptr) {
            cout << "Antrean kosong." << endl;
            return;
        }

        cout << "Antrean (depan -> belakang):" << endl;
        int no = 1;
        Antrean* temp = front;
        while (temp != nullptr) {
            cout << "  " << no++ << ". " << temp->nama << " (" << temp->nim << ")";
            if (temp == front) cout << "  <- giliran berikutnya";
            cout << endl;
            temp = temp->next;
        }
    }
};

// ================= STACK (linked list): riwayat pengembalian =================
struct Riwayat {
    int idBuku;
    string judul;
    string peminjam;
    Riwayat* next;
};

class StackRiwayat {
private:
    Riwayat* top;

public:
    StackRiwayat() {
        top = nullptr;
    }

    ~StackRiwayat() {
        while (top != nullptr) {
            Riwayat* hapus = top;
            top = top->next;
            delete hapus;
        }
    }

    // Push: pengembalian terbaru ditaruh paling atas
    void push(int idBuku, string judul, string peminjam) {
        Riwayat* baru = new Riwayat();
        baru->idBuku = idBuku;
        baru->judul = judul;
        baru->peminjam = peminjam;
        baru->next = top;
        top = baru;
    }

    void tampilkan() {
        if (top == nullptr) {
            cout << "Belum ada riwayat pengembalian." << endl;
            return;
        }

        cout << "Riwayat pengembalian (terbaru di atas, LIFO):" << endl;
        int no = 1;
        Riwayat* temp = top;
        while (temp != nullptr) {
            cout << "  " << no++ << ". [" << temp->idBuku << "] " << temp->judul
                 << " - dikembalikan oleh " << temp->peminjam << endl;
            temp = temp->next;
        }
    }
};

// ================= BST: data buku berdasarkan ID =================
struct Buku {
    int id;
    string judul;
    bool dipinjam;
    string peminjam;
    Buku* kiri;
    Buku* kanan;
};

class BSTBuku {
private:
    Buku* root;

    Buku* sisipkan(Buku* akar, int id, string judul, bool& berhasil) {
        if (akar == nullptr) {
            Buku* baru = new Buku();
            baru->id = id;
            baru->judul = judul;
            baru->dipinjam = false;
            baru->peminjam = "";
            baru->kiri = nullptr;
            baru->kanan = nullptr;
            berhasil = true;
            return baru;
        }

        if (id < akar->id) {
            akar->kiri = sisipkan(akar->kiri, id, judul, berhasil);
        } else if (id > akar->id) {
            akar->kanan = sisipkan(akar->kanan, id, judul, berhasil);
        } else {
            berhasil = false; // ID sama, ditolak
        }
        return akar;
    }

    void preOrder(Buku* akar) {
        if (akar == nullptr) return;
        cout << akar->id << " ";
        preOrder(akar->kiri);
        preOrder(akar->kanan);
    }

    void inOrder(Buku* akar) {
        if (akar == nullptr) return;
        inOrder(akar->kiri);
        cout << akar->id << " ";
        inOrder(akar->kanan);
    }

    void postOrder(Buku* akar) {
        if (akar == nullptr) return;
        postOrder(akar->kiri);
        postOrder(akar->kanan);
        cout << akar->id << " ";
    }

    // In-order dengan detail buku (terurut berdasarkan ID)
    void detail(Buku* akar) {
        if (akar == nullptr) return;
        detail(akar->kiri);
        cout << "  [" << akar->id << "] " << akar->judul << " - ";
        if (akar->dipinjam) {
            cout << "dipinjam oleh " << akar->peminjam;
        } else {
            cout << "tersedia";
        }
        cout << endl;
        detail(akar->kanan);
    }

    void hapusSemua(Buku* akar) {
        if (akar == nullptr) return;
        hapusSemua(akar->kiri);
        hapusSemua(akar->kanan);
        delete akar;
    }

public:
    BSTBuku() {
        root = nullptr;
    }

    ~BSTBuku() {
        hapusSemua(root);
    }

    bool tambah(int id, string judul) {
        bool berhasil = false;
        root = sisipkan(root, id, judul, berhasil);
        return berhasil;
    }

    // Pencarian ID buku (iteratif mengikuti aturan BST)
    Buku* cari(int id) {
        Buku* temp = root;
        while (temp != nullptr) {
            if (id == temp->id) return temp;
            if (id < temp->id) temp = temp->kiri;
            else temp = temp->kanan;
        }
        return nullptr;
    }

    void tampilkan() {
        if (root == nullptr) {
            cout << "Belum ada data buku." << endl;
            return;
        }

        cout << "Pre-Order  : ";
        preOrder(root);
        cout << endl;

        cout << "In-Order   : ";
        inOrder(root);
        cout << endl;

        cout << "Post-Order : ";
        postOrder(root);
        cout << endl;

        cout << "\nDaftar buku (urut ID):" << endl;
        detail(root);
    }
};

// ================= PROGRAM UTAMA =================
int main() {
    QueueMhs antrean;
    StackRiwayat riwayat;
    BSTBuku daftarBuku;
    int pilihan;

    do {
        cout << "\n===== SISTEM PERPUSTAKAAN =====" << endl;
        cout << "1. Tambah buku (BST)" << endl;
        cout << "2. Mahasiswa masuk antrean (Queue)" << endl;
        cout << "3. Layani peminjaman (Dequeue)" << endl;
        cout << "4. Kembalikan buku (Stack)" << endl;
        cout << "5. Tampilkan antrean" << endl;
        cout << "6. Tampilkan riwayat pengembalian" << endl;
        cout << "7. Cari ID buku" << endl;
        cout << "8. Tampilkan isi BST (Pre/In/Post-Order)" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        if (pilihan == 1) {
            int id;
            string judul;
            cout << "ID buku    : ";
            cin >> id;
            cin.ignore();
            cout << "Judul buku : ";
            getline(cin, judul);

            if (daftarBuku.tambah(id, judul)) {
                cout << "Buku [" << id << "] " << judul << " ditambahkan." << endl;
            } else {
                cout << "Gagal: ID " << id << " sudah ada." << endl;
            }

        } else if (pilihan == 2) {
            string nim, nama;
            cout << "NIM  : ";
            cin >> nim;
            cin.ignore();
            cout << "Nama : ";
            getline(cin, nama);

            antrean.enqueue(nim, nama);
            cout << nama << " masuk antrean." << endl;

        } else if (pilihan == 3) {
            if (antrean.kosong()) {
                cout << "Tidak ada mahasiswa dalam antrean." << endl;
            } else {
                Antrean* giliran = antrean.depan();
                cout << "Giliran: " << giliran->nama << " (" << giliran->nim << ")" << endl;

                int id;
                cout << "ID buku yang dipinjam: ";
                cin >> id;

                Buku* buku = daftarBuku.cari(id);
                if (buku == nullptr) {
                    cout << "Buku dengan ID " << id << " tidak ditemukan. Mahasiswa tetap di antrean." << endl;
                } else if (buku->dipinjam) {
                    cout << "Buku \"" << buku->judul << "\" sedang dipinjam oleh "
                         << buku->peminjam << ". Mahasiswa tetap di antrean." << endl;
                } else {
                    buku->dipinjam = true;
                    buku->peminjam = giliran->nama;
                    cout << giliran->nama << " berhasil meminjam \"" << buku->judul << "\"." << endl;
                    antrean.dequeue();
                }
            }

        } else if (pilihan == 4) {
            int id;
            cout << "ID buku yang dikembalikan: ";
            cin >> id;

            Buku* buku = daftarBuku.cari(id);
            if (buku == nullptr) {
                cout << "Buku dengan ID " << id << " tidak ditemukan." << endl;
            } else if (!buku->dipinjam) {
                cout << "Buku \"" << buku->judul << "\" tidak sedang dipinjam." << endl;
            } else {
                riwayat.push(buku->id, buku->judul, buku->peminjam);
                cout << "Buku \"" << buku->judul << "\" dikembalikan oleh "
                     << buku->peminjam << "." << endl;
                buku->dipinjam = false;
                buku->peminjam = "";
            }

        } else if (pilihan == 5) {
            antrean.tampilkan();

        } else if (pilihan == 6) {
            riwayat.tampilkan();

        } else if (pilihan == 7) {
            int id;
            cout << "Masukkan ID buku: ";
            cin >> id;

            Buku* buku = daftarBuku.cari(id);
            if (buku == nullptr) {
                cout << "ID " << id << " tidak ditemukan." << endl;
            } else {
                cout << "Ditemukan -> [" << buku->id << "] " << buku->judul << " - ";
                if (buku->dipinjam) cout << "dipinjam oleh " << buku->peminjam << endl;
                else cout << "tersedia" << endl;
            }

        } else if (pilihan == 8) {
            daftarBuku.tampilkan();

        } else if (pilihan != 0) {
            cout << "Pilihan tidak valid!" << endl;
        }

    } while (pilihan != 0);

    cout << "Program selesai." << endl;
    return 0;
}