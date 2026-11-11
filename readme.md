# Sistem Monitoring Stok dan Penjualan Kantin Kampus

## Identitas

| Keterangan | Isi |
|---|---|
| Nama Lengkap | Novriz Arizal |
| NIM | C2583207051 |
| Kelas | PTI3B |
| Mata Kuliah | Algoritma dan Pemrograman Lanjutan |
| Dosen Pengampu | Taofik Muhammad, M.Kom |
| Nama Proyek | Sistem Monitoring Stok dan Penjualan Kantin Kampus |

## Deskripsi Singkat

Aplikasi console berbahasa C untuk membantu pengelola kantin kampus mencatat produk, memantau stok, memproses transaksi penjualan, dan melihat laporan penjualan. Semua data disimpan dalam array selama program berjalan (tanpa database atau file eksternal). Kapasitas maksimal 50 produk, dengan 5 produk sebagai data awal.

## Daftar Fitur

| Menu | Fitur | Keterangan |
|---|---|---|
| 1 | Lihat Daftar Produk | Menampilkan nama, harga, dan stok seluruh produk |
| 2 | Tambah Produk | Menambah produk baru (ditolak jika kapasitas 50 penuh) |
| 3 | Ubah Produk | Mengubah harga dan stok produk |
| 4 | Transaksi Penjualan | Membeli beberapa jenis produk dalam satu transaksi, menghitung subtotal dan total pembayaran |
| 5 | Tambah Stok | Menambah stok produk yang sudah ada |
| 6 | Cari Produk | Mencari produk berdasarkan nama |
| 7 | Urutkan Produk | Mengurutkan berdasarkan harga (termurah) dan jumlah terjual (terbanyak) |
| 8 | Laporan Penjualan | Jumlah terjual per produk, total unit terjual, total pendapatan, produk terlaris |
| 9 | Cek Stok Menipis | Menampilkan produk dengan stok kurang dari 5 |
| 0 | Keluar | Mengakhiri program |

Validasi input yang ditangani: pilihan menu tidak tersedia, nomor produk tidak ditemukan, jumlah pembelian nol atau negatif, harga atau stok negatif, jumlah pembelian melebihi stok, dan kapasitas array penuh.

## Penjelasan Penggunaan Array

Seluruh data produk disimpan dalam array paralel. Indeks yang sama pada setiap array merujuk ke produk yang sama.

```c
#define MAKS_PRODUK 50
#define PANJANG_NAMA 30

char nama[MAKS_PRODUK][PANJANG_NAMA];   // array karakter 2 dimensi: nama produk
int  harga[MAKS_PRODUK];                // array 1 dimensi: harga
int  stok[MAKS_PRODUK];                 // array 1 dimensi: stok
int  terjual[MAKS_PRODUK];              // array 1 dimensi: jumlah terjual
int  jumlahProduk;                      // jumlah data aktif
```

- `nama` adalah array karakter dua dimensi: baris menunjukkan produk, kolom menyimpan karakter nama.
- `harga`, `stok`, dan `terjual` adalah array satu dimensi.
- `jumlahProduk` menyimpan jumlah data aktif. Indeks valid adalah `0` sampai `jumlahProduk - 1`, dan nilainya tidak boleh melebihi `MAKS_PRODUK` (50).
- Saat pengurutan, seluruh array paralel ditukar bersamaan agar data satu produk tetap konsisten.

> Sesuaikan bagian ini dengan kode yang benar-benar kamu tulis.



## Pengujian

### 1 Tambah Produk


- **Input/Tindakan:** Memasukkan produk baru lewat menu 2.
- **Hasil yang diharapkan:** Produk muncul dalam daftar.
- **Keterangan:** (tulis singkat input, proses, dan output yang terlihat)

<img width="333" height="181" alt="Screenshot 2026-11-11 141812" src="https://github.com/user-attachments/assets/132a454a-c68a-4b08-8dbb-35828a5afe89" />


### 2 Transaksi

- **Input/Tindakan:** Membeli beberapa produk lewat menu 4.
- **Hasil yang diharapkan:** Subtotal dan total benar.
- **Keterangan:** (tulis perhitungan manualmu sebagai pembanding)

<img width="533" height="448" alt="Screenshot 2026-11-11 142024" src="https://github.com/user-attachments/assets/c765f824-c31c-4a1a-82ae-d82a3d6f4b76" />


### 3 Pembaruan Stok

- **Input/Tindakan:** Menyelesaikan transaksi, lalu membuka daftar produk dan laporan.
- **Hasil yang diharapkan:** Stok dan jumlah terjual berubah.
- **Keterangan:** (bandingkan stok sebelum dan sesudah)

<img width="274" height="98" alt="Screenshot 2026-11-11 142112" src="https://github.com/user-attachments/assets/94501366-374d-4994-b24a-9ab83aac9763" />


### 4 Stok Tidak Cukup

- **Input/Tindakan:** Membeli melebihi stok.
- **Hasil yang diharapkan:** Transaksi ditolak; stok tetap.
- **Keterangan:** (tunjukkan pesan penolakan dan stok yang tidak berubah)

<img width="533" height="448" alt="Screenshot 2026-11-11 142024" src="https://github.com/user-attachments/assets/4592dd86-53a2-415b-9a0d-720b4c658365" />


### 5 Laporan

- **Input/Tindakan:** Menampilkan laporan lewat menu 8.
- **Hasil yang diharapkan:** Unit, pendapatan, dan produk terlaris benar.
- **Keterangan:** (cocokkan dengan transaksi yang sudah dilakukan)

<img width="460" height="230" alt="Screenshot 2026-11-11 142221" src="https://github.com/user-attachments/assets/bcd09b01-94a4-49a5-8bd0-c8dd17eb32b8" />


### 6 Pengurutan

- **Input/Tindakan:** Mengurutkan berdasarkan harga dan berdasarkan penjualan lewat menu 7.
- **Hasil yang diharapkan:** Urutan sesuai ketentuan (harga termurah, terjual terbanyak).
- **Keterangan:** (tampilkan hasil kedua jenis pengurutan)

<img width="448" height="279" alt="Screenshot 2026-11-11 142205" src="https://github.com/user-attachments/assets/e6f82bc8-61c6-4ca8-ba4a-227342ded650" />


### 7 Pencarian dan Stok

- **Input/Tindakan:** Mencari produk lewat menu 6 dan mengecek stok kurang dari 5 lewat menu 9.
- **Hasil yang diharapkan:** Hasil dan peringatan tepat.
- **Keterangan:** (tunjukkan produk yang ditemukan dan daftar stok menipis)

<img width="434" height="185" alt="Screenshot 2026-11-11 142142" src="https://github.com/user-attachments/assets/53e0e9a1-c682-4cdd-97a7-14e459fac4ad" />


## Struktur Repository

```
Proyek-Array-C-C2583207051/
├── main.c
├── README.md
└── screenshots/
    ├── 01-tambah-produk.png
    ├── 02-transaksi.png
    ├── 03-pembaruan-stok.png
    ├── 04-stok-tidak-cukup.png
    ├── 05-laporan.png
    ├── 06a-urut-harga.png
    ├── 06b-urut-terjual.png
    ├── 07a-pencarian.png
    └── 07b-stok-menipis.png
```
