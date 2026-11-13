## Nama / NIM: Raziqul Athar - 251401035

## Struktur Folder

struktur-data-tugas/
├── README.md

├── quiz_1.cpp

├── quiz_2.cpp

├── quiz_3.cpp

└── quiz_4.cpp

## Deskripsi Program

### 1. Sistem Pengelolaan Nilai Mahasiswa

**File:** `quiz_1.cpp`

Program untuk mengelola data mahasiswa (NIM, nama, nilai) dengan menu interaktif.

**Struktur data dan algoritma:**

| Komponen | Fungsi |
|---|---|
| Single Linked List (`DaftarMahasiswa`) | Menyimpan data mahasiswa: NIM, nama, dan nilai |
| Dynamic Array (`DynamicArray`) | Menyimpan kumpulan nilai. Kapasitas awal 2, lalu digandakan otomatis saat penuh |
| Insertion Sort | Mengurutkan array nilai dari terkecil ke terbesar |
| Linear Search | Mencari mahasiswa berdasarkan NIM pada linked list |
| Binary Search (iteratif) | Mencari nilai tertentu pada array nilai yang sudah terurut |

**Menu program:**

| Pilihan | Fitur |
|---|---|
| 1 | Tambah data mahasiswa (NIM yang sudah ada ditolak) |
| 2 | Tampilkan data mahasiswa dan kumpulan nilai |
| 3 | Urutkan nilai dengan Insertion Sort |
| 4 | Cari mahasiswa berdasarkan NIM (Linear Search) |
| 5 | Cari nilai (Binary Search) |
| 0 | Keluar |

**Catatan:**
- Binary Search hanya bisa dipakai setelah nilai diurutkan (menu 3). Setiap ada data baru, status "terurut" direset sehingga pengurutan harus diulang.
- Array nilai terpisah dari linked list, jadi urutan tampilan mahasiswa tetap sesuai urutan input.

---

### 2. Sistem Antrean dan Pengelolaan Buku Perpustakaan

**File:** `quiz_2.cpp`

Program untuk membantu peminjaman dan pengembalian buku di perpustakaan.

**Struktur data:**

| Komponen | Prinsip | Fungsi |
|---|---|---|
| Queue (`QueueMhs`, linked list) | FIFO | Antrean mahasiswa yang ingin meminjam buku |
| Stack (`StackRiwayat`, linked list) | LIFO | Riwayat pengembalian buku (yang terbaru tampil paling atas) |
| Binary Search Tree (`BSTBuku`) | - | Menyimpan buku berdasarkan ID, dengan pencarian dan traversal |

**Menu program:**

| Pilihan | Fitur |
|---|---|
| 1 | Tambah buku ke BST (ID yang sama ditolak) |
| 2 | Mahasiswa masuk antrean (Enqueue) |
| 3 | Layani peminjaman (Dequeue): mahasiswa terdepan meminjam buku berdasarkan ID |
| 4 | Kembalikan buku (Push ke stack riwayat) |
| 5 | Tampilkan antrean |
| 6 | Tampilkan riwayat pengembalian |
| 7 | Cari ID buku |
| 8 | Tampilkan isi BST: Pre-Order, In-Order, Post-Order, beserta status tiap buku |
| 0 | Keluar |

**Catatan:**
- Mahasiswa baru dikeluarkan dari antrean hanya jika peminjamannya berhasil. Kalau ID buku tidak ditemukan atau bukunya sedang dipinjam, mahasiswa tetap di antrean.
- Buku hanya bisa dikembalikan jika memang sedang dipinjam.
- Traversal In-Order selalu menghasilkan ID yang terurut dari kecil ke besar.

---

### 3. Sistem Pencarian Rute di Lingkungan Kampus

**File:** `quiz_3.cpp`

Program pencarian rute antarlokasi menggunakan graf tak berarah berbobot dengan 6 vertex (A sampai F), direpresentasikan dengan **Adjacency Matrix**.

**Data jarak antarlokasi:**

| Vertex 1 | Vertex 2 | Jarak |
|---|---|---|
| A | B | 4 |
| A | C | 2 |
| B | C | 1 |
| B | D | 5 |
| B | E | 3 |
| C | D | 8 |
| C | E | 6 |
| D | E | 2 |
| D | F | 4 |
| E | F | 3 |

**Algoritma:**

| Algoritma | Fungsi |
|---|---|
| BFS | Penelusuran graf level demi level memakai `queue` |
| DFS | Penelusuran graf sedalam mungkin memakai rekursi (`dfsUtil`) |
| Dijkstra | Mencari jarak terpendek dari vertex awal ke vertex tujuan, lalu menampilkan rute dan total jaraknya |

**Menu program:**

| Pilihan | Fitur |
|---|---|
| 1 | Tampilkan Adjacency Matrix |
| 2 | Penelusuran BFS (vertex awal dipilih pengguna) |
| 3 | Penelusuran DFS (vertex awal dipilih pengguna) |
| 4 | Rute terpendek dengan Dijkstra (vertex awal dan tujuan dipilih pengguna) |
| 0 | Keluar |

**Contoh hasil:** rute terpendek dari A ke F adalah `A -> C -> B -> E -> F` dengan total jarak **9**.

**Catatan:** input vertex tidak membedakan huruf besar dan kecil (`a` sama dengan `A`).

---

### 4. Sistem Pengelolaan Data Mahasiswa dengan Hash Table

**File:** `quiz_4.cpp`

Program yang menyimpan data mahasiswa dengan **NIM sebagai key** dan **nama sebagai value** pada hash table berukuran 20. Collision ditangani dengan **Double Hashing**.

**Fungsi hash:**

```
Hash1(key) = key % 20
Hash2(key) = 19 - (key % 19)
Posisi ke-i = (Hash1(key) + i * Hash2(key)) % 20
```

**Fitur:**

| Fitur | Keterangan |
|---|---|
| Insert | Menyimpan data. NIM duplikat ditolak, dan informasi collision ditampilkan |
| Search | Mencari nama berdasarkan NIM |
| Remove | Menghapus data dengan menandai slot `DIHAPUS` (bukan langsung dikosongkan) |
| Display | Menampilkan isi seluruh slot hash table |

**Status slot:** `KOSONG`, `TERISI`, dan `DIHAPUS`. Penanda `DIHAPUS` diperlukan supaya data yang sebelumnya melewati slot tersebut saat collision tetap bisa ditemukan. Slot `DIHAPUS` bisa dipakai lagi oleh data baru.

**Pengujian bawaan di `main()`:**
- 18 data mahasiswa, dengan 3 kejadian collision (NIM `251401021`, `251401039`, `251401043`)
- Insert NIM duplikat
- Search data tanpa collision, data hasil collision, dan data yang tidak ada
- Remove data yang ada dan yang tidak ada
- Search setelah remove (data hasil collision tetap harus ditemukan)
- Insert ulang yang memakai slot berstatus `DIHAPUS`

**Catatan:** ukuran tabel 20 bukan bilangan prima, sedangkan `Hash2` bisa bernilai 1 sampai 19. Kalau `Hash2` memiliki faktor persekutuan dengan 20 (misalnya 2, 4, 5, 10), penelusuran hanya menjangkau sebagian slot. Pada kasus seperti itu `insert` bisa gagal walaupun masih ada slot kosong, dan program mencetak pesan `tidak ada slot yang bisa dijangkau`. Rumus hash sengaja dibuat sesuai soal.

---

## Cara Menjalankan

| 1. Nilai Mahasiswa | Pilih menu angka. Mulai dari menu **1** untuk menambah data, lalu **3** untuk mengurutkan sebelum memakai menu **5** |

| 2. Perpustakaan | Tambah buku (menu **1**) dan mahasiswa ke antrean (menu **2**) dulu, baru layani peminjaman (menu **3**) |

| 3. Rute Kampus | Pilih menu angka, lalu ketik huruf vertex (A sampai F) saat diminta |

| 4. Hash Table | Tidak ada input. Seluruh pengujian berjalan otomatis dari `main()` dan hasilnya langsung tampil |

## LINK VIDEO
https://youtu.be/lCL4wXSndBE?si=DU14-FBaKWIcuMqz
