#include <stdio.h>
#include <stdlib.h>

/*
 * Sistem Monitoring Stok dan Penjualan Kantin Kampus
 * Mata Kuliah : Algoritma dan Pemrograman Lanjutan
 * Bahasa      : C (console)
 *
 * Struktur data utama (array):
 *   char nama[MAKS_PRODUK][PANJANG_NAMA]  -> array karakter 2D (nama produk)
 *   int  harga[MAKS_PRODUK]               -> array 1D (harga satuan)
 *   int  stok[MAKS_PRODUK]                -> array 1D (stok tersedia)
 *   int  terjual[MAKS_PRODUK]             -> array 1D (jumlah terjual)
 *   int  jumlahProduk                     -> jumlah data aktif (indeks 0..jumlahProduk-1)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAKS_PRODUK   50
#define PANJANG_NAMA  30
#define BATAS_MENIPIS 5

/* ---------- Data global (disimpan selama program berjalan) ---------- */
char nama[MAKS_PRODUK][PANJANG_NAMA];
int  harga[MAKS_PRODUK];
int  stok[MAKS_PRODUK];
int  terjual[MAKS_PRODUK];
int  jumlahProduk = 0;

/* ---------- Fungsi bantu input ---------- */

/* Membaca satu baris string dari pengguna (tanpa newline). */
void bacaTeks(const char *prompt, char *hasil, int panjang) {
    printf("%s", prompt);
    if (fgets(hasil, panjang, stdin) == NULL) {
        hasil[0] = '\0';
        return;
    }
    size_t n = strlen(hasil);
    if (n > 0 && hasil[n - 1] == '\n') {
        hasil[n - 1] = '\0';
    } else {
        /* baris terlalu panjang: buang sisa input */
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
    }
}

/* Membaca bilangan bulat dengan validasi (menolak huruf/kosong). */
int bacaInt(const char *prompt) {
    char buf[64];
    char *akhir;
    long nilai;
    while (1) {
        bacaTeks(prompt, buf, sizeof(buf));
        if (buf[0] == '\0') {
            printf("  [!] Input tidak boleh kosong. Masukkan angka.\n");
            continue;
        }
        nilai = strtol(buf, &akhir, 10);
        if (*akhir != '\0') {
            printf("  [!] Input harus berupa angka bulat.\n");
            continue;
        }
        return (int)nilai;
    }
}

/* Membaca bilangan bulat >= 0 (untuk harga dan stok). */
int bacaIntNonNegatif(const char *prompt, const char *namaField) {
    int nilai;
    while (1) {
        nilai = bacaInt(prompt);
        if (nilai < 0) {
            printf("  [!] %s tidak boleh bernilai negatif.\n", namaField);
            continue;
        }
        return nilai;
    }
}

void tekanEnter(void) {
    char buf[8];
    bacaTeks("\nTekan ENTER untuk kembali ke menu...", buf, sizeof(buf));
}

/* ---------- Fungsi bantu umum ---------- */

void garis(void) {
    printf("--------------------------------------------------------------\n");
}

/* Salin teks menjadi huruf kecil (untuk pencarian tidak peka huruf besar/kecil). */
void keHurufKecil(const char *sumber, char *tujuan) {
    int i = 0;
    while (sumber[i] != '\0') {
        tujuan[i] = (char)tolower((unsigned char)sumber[i]);
        i++;
    }
    tujuan[i] = '\0';
}

/* Menambah produk ke array tanpa interaksi (dipakai untuk data awal). */
void masukkanProduk(const char *n, int h, int s) {
    if (jumlahProduk >= MAKS_PRODUK) return;
    strncpy(nama[jumlahProduk], n, PANJANG_NAMA - 1);
    nama[jumlahProduk][PANJANG_NAMA - 1] = '\0';
    harga[jumlahProduk]   = h;
    stok[jumlahProduk]    = s;
    terjual[jumlahProduk] = 0;
    jumlahProduk++;
}

void isiDataAwal(void) {
    masukkanProduk("Nasi Goreng",  15000, 20);
    masukkanProduk("Mie Ayam",     12000, 15);
    masukkanProduk("Es Teh",        3000, 30);
    masukkanProduk("Air Mineral",   4000,  3);
    masukkanProduk("Gorengan",      2000, 25);
    masukkanProduk("Kopi Susu",     8000,  4);
}

/* ---------- Fitur 1: Lihat daftar produk ---------- */
void tampilDaftar(void) {
    int i;
    printf("\n=== DAFTAR PRODUK (%d/%d) ===\n", jumlahProduk, MAKS_PRODUK);
    garis();
    printf("%-4s %-*s %10s %8s\n", "No", PANJANG_NAMA, "Nama Produk", "Harga", "Stok");
    garis();
    if (jumlahProduk == 0) {
        printf("(Belum ada produk)\n");
    }
    for (i = 0; i < jumlahProduk; i++) {
        printf("%-4d %-*s %10d %8d\n", i + 1, PANJANG_NAMA, nama[i], harga[i], stok[i]);
    }
    garis();
}

/* Meminta nomor produk; mengembalikan indeks array, atau -1 jika tidak valid. */
int pilihProduk(const char *prompt) {
    int no = bacaInt(prompt);
    if (no < 1 || no > jumlahProduk) {
        printf("  [!] Nomor produk %d tidak ditemukan.\n", no);
        return -1;
    }
    return no - 1;
}

/* ---------- Fitur 2: Tambah produk ---------- */
void tambahProduk(void) {
    char buf[PANJANG_NAMA];
    int h, s, i;

    printf("\n=== TAMBAH PRODUK ===\n");
    if (jumlahProduk >= MAKS_PRODUK) {
        printf("  [!] Kapasitas penuh (%d produk). Tidak dapat menambah produk.\n", MAKS_PRODUK);
        return;
    }

    while (1) {
        bacaTeks("Nama produk : ", buf, sizeof(buf));
        if (buf[0] == '\0') {
            printf("  [!] Nama produk tidak boleh kosong.\n");
            continue;
        }
        /* cegah nama ganda */
        int ganda = 0;
        for (i = 0; i < jumlahProduk; i++) {
            char a[PANJANG_NAMA], b[PANJANG_NAMA];
            keHurufKecil(nama[i], a);
            keHurufKecil(buf, b);
            if (strcmp(a, b) == 0) { ganda = 1; break; }
        }
        if (ganda) {
            printf("  [!] Produk dengan nama tersebut sudah ada.\n");
            continue;
        }
        break;
    }
    h = bacaIntNonNegatif("Harga (Rp)  : ", "Harga");
    s = bacaIntNonNegatif("Stok awal    : ", "Stok");

    masukkanProduk(buf, h, s);
    printf("  Produk \"%s\" berhasil ditambahkan.\n", buf);
}

/* ---------- Fitur 3: Ubah produk (harga dan stok) ---------- */
void ubahProduk(void) {
    int idx;
    printf("\n=== UBAH PRODUK ===\n");
    tampilDaftar();
    if (jumlahProduk == 0) return;

    idx = pilihProduk("Nomor produk yang diubah : ");
    if (idx < 0) return;

    printf("Produk terpilih: %s (Harga %d, Stok %d)\n", nama[idx], harga[idx], stok[idx]);
    harga[idx] = bacaIntNonNegatif("Harga baru (Rp) : ", "Harga");
    stok[idx]  = bacaIntNonNegatif("Stok baru       : ", "Stok");
    printf("  Data produk berhasil diubah.\n");
}

/* ---------- Fitur 4: Transaksi penjualan (beberapa produk) ---------- */
void transaksiPenjualan(void) {
    int beli[MAKS_PRODUK] = {0};   /* jumlah beli per produk dalam transaksi ini */
    int i, idx, qty, adaItem = 0;
    long subtotal, total = 0;
    char konfirmasi[8];

    printf("\n=== TRANSAKSI PENJUALAN ===\n");
    if (jumlahProduk == 0) {
        printf("  [!] Belum ada produk.\n");
        return;
    }
    tampilDaftar();
    printf("Masukkan nomor produk dan jumlah. Ketik 0 pada nomor produk untuk selesai.\n");

    while (1) {
        int no = bacaInt("\nNomor produk (0 = selesai) : ");
        if (no == 0) break;
        if (no < 1 || no > jumlahProduk) {
            printf("  [!] Nomor produk %d tidak ditemukan.\n", no);
            continue;
        }
        idx = no - 1;
        printf("  %s | Harga %d | Stok tersedia %d (sudah di keranjang: %d)\n",
               nama[idx], harga[idx], stok[idx], beli[idx]);

        qty = bacaInt("  Jumlah beli : ");
        if (qty <= 0) {
            printf("  [!] Jumlah pembelian harus lebih dari nol.\n");
            continue;
        }
        if (beli[idx] + qty > stok[idx]) {
            printf("  [!] Stok tidak cukup. Sisa stok yang bisa dibeli: %d. Item ditolak.\n",
                   stok[idx] - beli[idx]);
            continue;
        }
        beli[idx] += qty;
        adaItem = 1;
        printf("  OK: %d x %s ditambahkan ke keranjang.\n", qty, nama[idx]);
    }

    if (!adaItem) {
        printf("  Tidak ada item dibeli. Transaksi dibatalkan.\n");
        return;
    }

    /* Cetak struk */
    printf("\n=============== STRUK PEMBELIAN ===============\n");
    printf("%-*s %5s %9s %11s\n", PANJANG_NAMA, "Produk", "Qty", "Harga", "Subtotal");
    garis();
    for (i = 0; i < jumlahProduk; i++) {
        if (beli[i] > 0) {
            subtotal = (long)beli[i] * harga[i];
            total += subtotal;
            printf("%-*s %5d %9d %11ld\n", PANJANG_NAMA, nama[i], beli[i], harga[i], subtotal);
        }
    }
    garis();
    printf("TOTAL PEMBAYARAN : Rp %ld\n", total);

    bacaTeks("\nSelesaikan transaksi? (y/n) : ", konfirmasi, sizeof(konfirmasi));
    if (konfirmasi[0] == 'y' || konfirmasi[0] == 'Y') {
        for (i = 0; i < jumlahProduk; i++) {
            if (beli[i] > 0) {
                stok[i]    -= beli[i];
                terjual[i] += beli[i];
            }
        }
        printf("  Transaksi berhasil. Stok dan jumlah terjual telah diperbarui.\n");
    } else {
        printf("  Transaksi dibatalkan. Stok tidak berubah.\n");
    }
}

/* ---------- Fitur 5: Tambah stok ---------- */
void tambahStok(void) {
    int idx, tambah;
    printf("\n=== TAMBAH STOK ===\n");
    tampilDaftar();
    if (jumlahProduk == 0) return;

    idx = pilihProduk("Nomor produk : ");
    if (idx < 0) return;

    tambah = bacaInt("Jumlah stok yang ditambahkan : ");
    if (tambah <= 0) {
        printf("  [!] Jumlah tambahan stok harus lebih dari nol.\n");
        return;
    }
    stok[idx] += tambah;
    printf("  Stok %s sekarang: %d\n", nama[idx], stok[idx]);
}

/* ---------- Fitur 6: Cari produk berdasarkan nama ---------- */
void cariProduk(void) {
    char kunci[PANJANG_NAMA], kunciKecil[PANJANG_NAMA], namaKecil[PANJANG_NAMA];
    int i, ketemu = 0;

    printf("\n=== CARI PRODUK ===\n");
    bacaTeks("Masukkan nama (atau sebagian nama) : ", kunci, sizeof(kunci));
    if (kunci[0] == '\0') {
        printf("  [!] Kata kunci tidak boleh kosong.\n");
        return;
    }
    keHurufKecil(kunci, kunciKecil);

    garis();
    printf("%-4s %-*s %10s %8s\n", "No", PANJANG_NAMA, "Nama Produk", "Harga", "Stok");
    garis();
    for (i = 0; i < jumlahProduk; i++) {
        keHurufKecil(nama[i], namaKecil);
        if (strstr(namaKecil, kunciKecil) != NULL) {
            printf("%-4d %-*s %10d %8d\n", i + 1, PANJANG_NAMA, nama[i], harga[i], stok[i]);
            ketemu++;
        }
    }
    garis();
    if (ketemu == 0) printf("  Produk \"%s\" tidak ditemukan.\n", kunci);
    else             printf("  Ditemukan %d produk.\n", ketemu);
}

/* ---------- Fitur 7: Urutkan produk (bubble sort) ---------- */

/* Menukar seluruh data dua produk agar array tetap sinkron. */
void tukarProduk(int a, int b) {
    char tmpNama[PANJANG_NAMA];
    int tmp;

    strcpy(tmpNama, nama[a]); strcpy(nama[a], nama[b]); strcpy(nama[b], tmpNama);
    tmp = harga[a];   harga[a]   = harga[b];   harga[b]   = tmp;
    tmp = stok[a];    stok[a]    = stok[b];    stok[b]    = tmp;
    tmp = terjual[a]; terjual[a] = terjual[b]; terjual[b] = tmp;
}

/* Harga dari termurah (menaik). */
void urutHargaTermurah(void) {
    int i, j;
    for (i = 0; i < jumlahProduk - 1; i++)
        for (j = 0; j < jumlahProduk - i - 1; j++)
            if (harga[j] > harga[j + 1])
                tukarProduk(j, j + 1);
}

/* Jumlah terjual dari terbanyak (menurun). */
void urutTerjualTerbanyak(void) {
    int i, j;
    for (i = 0; i < jumlahProduk - 1; i++)
        for (j = 0; j < jumlahProduk - i - 1; j++)
            if (terjual[j] < terjual[j + 1])
                tukarProduk(j, j + 1);
}

void urutkanProduk(void) {
    int pilih, i;
    printf("\n=== URUTKAN PRODUK ===\n");
    if (jumlahProduk == 0) {
        printf("  [!] Belum ada produk.\n");
        return;
    }
    printf("1. Berdasarkan harga (termurah)\n");
    printf("2. Berdasarkan jumlah terjual (terbanyak)\n");
    pilih = bacaInt("Pilihan : ");

    if (pilih == 1) {
        urutHargaTermurah();
        printf("\nProduk diurutkan berdasarkan harga termurah:\n");
        garis();
        printf("%-4s %-*s %10s\n", "No", PANJANG_NAMA, "Nama Produk", "Harga");
        garis();
        for (i = 0; i < jumlahProduk; i++)
            printf("%-4d %-*s %10d\n", i + 1, PANJANG_NAMA, nama[i], harga[i]);
        garis();
    } else if (pilih == 2) {
        urutTerjualTerbanyak();
        printf("\nProduk diurutkan berdasarkan jumlah terjual terbanyak:\n");
        garis();
        printf("%-4s %-*s %10s\n", "No", PANJANG_NAMA, "Nama Produk", "Terjual");
        garis();
        for (i = 0; i < jumlahProduk; i++)
            printf("%-4d %-*s %10d\n", i + 1, PANJANG_NAMA, nama[i], terjual[i]);
        garis();
    } else {
        printf("  [!] Pilihan urutan tidak tersedia.\n");
    }
}

/* ---------- Fitur 8: Laporan penjualan ---------- */
void laporanPenjualan(void) {
    int i, terlaris = -1;
    long totalUnit = 0, totalPendapatan = 0;

    printf("\n=== LAPORAN PENJUALAN ===\n");
    garis();
    printf("%-4s %-*s %8s %12s\n", "No", PANJANG_NAMA, "Nama Produk", "Terjual", "Pendapatan");
    garis();
    for (i = 0; i < jumlahProduk; i++) {
        long pendapatan = (long)terjual[i] * harga[i];
        totalUnit       += terjual[i];
        totalPendapatan += pendapatan;
        printf("%-4d %-*s %8d %12ld\n", i + 1, PANJANG_NAMA, nama[i], terjual[i], pendapatan);

        if (terjual[i] > 0 && (terlaris == -1 || terjual[i] > terjual[terlaris]))
            terlaris = i;
    }
    garis();
    printf("Total unit terjual : %ld\n", totalUnit);
    printf("Total pendapatan   : Rp %ld\n", totalPendapatan);
    if (terlaris == -1)
        printf("Produk terlaris    : (belum ada penjualan)\n");
    else
        printf("Produk terlaris    : %s (%d unit)\n", nama[terlaris], terjual[terlaris]);
}

/* ---------- Fitur 9: Cek stok menipis (< 5) ---------- */
void cekStokMenipis(void) {
    int i, ada = 0;
    printf("\n=== STOK MENIPIS (kurang dari %d) ===\n", BATAS_MENIPIS);
    garis();
    for (i = 0; i < jumlahProduk; i++) {
        if (stok[i] < BATAS_MENIPIS) {
            printf("  [PERINGATAN] %-*s sisa stok: %d\n", PANJANG_NAMA, nama[i], stok[i]);
            ada = 1;
        }
    }
    if (!ada) printf("  Semua produk memiliki stok yang aman.\n");
    garis();
}

/* ---------- Menu utama ---------- */
void tampilMenu(void) {
    printf("\n==================================================\n");
    printf("   MONITORING STOK & PENJUALAN KANTIN KAMPUS\n");
    printf("==================================================\n");
    printf("1. Lihat Daftar Produk     6. Cari Produk\n");
    printf("2. Tambah Produk           7. Urutkan Produk\n");
    printf("3. Ubah Produk             8. Laporan Penjualan\n");
    printf("4. Transaksi Penjualan     9. Cek Stok Menipis\n");
    printf("5. Tambah Stok             0. Keluar\n");
    printf("--------------------------------------------------\n");
}

int main(void) {
    int pilihan;

    isiDataAwal();

    do {
        tampilMenu();
        pilihan = bacaInt("Pilih menu : ");

        switch (pilihan) {
            case 1: tampilDaftar();        break;
            case 2: tambahProduk();        break;
            case 3: ubahProduk();          break;
            case 4: transaksiPenjualan();  break;
            case 5: tambahStok();          break;
            case 6: cariProduk();          break;
            case 7: urutkanProduk();       break;
            case 8: laporanPenjualan();    break;
            case 9: cekStokMenipis();      break;
            case 0: printf("\nTerima kasih. Program selesai.\n"); break;
            default:
                printf("  [!] Pilihan menu %d tidak tersedia. Pilih 0-9.\n", pilihan);
        }
        if (pilihan != 0) tekanEnter();
    } while (pilihan != 0);

    return 0;
}
