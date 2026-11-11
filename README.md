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

## Petunjuk Kompilasi dan Menjalankan

Prasyarat: compiler GCC terpasang.

**Kompilasi**

```bash
gcc main.c -o kantin
```

**Menjalankan**

- Linux / macOS:
  ```bash
  ./kantin
  ```
- Windows:
  ```cmd
  kantin.exe
  ```

## Pengujian

### Skenario 1: Tambah Produk

- **Input/Tindakan:** Memasukkan produk baru lewat menu 2.
- **Hasil yang diharapkan:** Produk muncul dalam daftar.
- **Keterangan:** (tulis singkat input, proses, dan output yang terlihat)

![Skenario 1](screenshots/01-tambah-produk.png)

### Skenario 2: Transaksi

- **Input/Tindakan:** Membeli beberapa produk lewat menu 4.
- **Hasil yang diharapkan:** Subtotal dan total benar.
- **Keterangan:** (tulis perhitungan manualmu sebagai pembanding)

![Skenario 2](screenshots/02-transaksi.png)

### Skenario 3: Pembaruan Stok

- **Input/Tindakan:** Menyelesaikan transaksi, lalu membuka daftar produk dan laporan.
- **Hasil yang diharapkan:** Stok dan jumlah terjual berubah.
- **Keterangan:** (bandingkan stok sebelum dan sesudah)

![Skenario 3](screenshots/03-pembaruan-stok.png)

### Skenario 4: Stok Tidak Cukup

- **Input/Tindakan:** Membeli melebihi stok.
- **Hasil yang diharapkan:** Transaksi ditolak; stok tetap.
- **Keterangan:** (tunjukkan pesan penolakan dan stok yang tidak berubah)

![Skenario 4](screenshots/04-stok-tidak-cukup.png)

### Skenario 5: Laporan

- **Input/Tindakan:** Menampilkan laporan lewat menu 8.
- **Hasil yang diharapkan:** Unit, pendapatan, dan produk terlaris benar.
- **Keterangan:** (cocokkan dengan transaksi yang sudah dilakukan)

![Skenario 5](screenshots/05-laporan.png)

### Skenario 6: Pengurutan

- **Input/Tindakan:** Mengurutkan berdasarkan harga dan berdasarkan penjualan lewat menu 7.
- **Hasil yang diharapkan:** Urutan sesuai ketentuan (harga termurah, terjual terbanyak).
- **Keterangan:** (tampilkan hasil kedua jenis pengurutan)

![Skenario 6a - Urut harga](screenshots/06a-urut-harga.png)
![Skenario 6b - Urut terjual](screenshots/06b-urut-terjual.png)

### Skenario 7: Pencarian dan Stok

- **Input/Tindakan:** Mencari produk lewat menu 6 dan mengecek stok kurang dari 5 lewat menu 9.
- **Hasil yang diharapkan:** Hasil dan peringatan tepat.
- **Keterangan:** (tunjukkan produk yang ditemukan dan daftar stok menipis)

![Skenario 7a - Pencarian](screenshots/07a-pencarian.png)
![Skenario 7b - Stok menipis](screenshots/07b-stok-menipis.png)

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
