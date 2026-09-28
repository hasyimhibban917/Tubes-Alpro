#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define maksimallagu 100
#define maksimalhistori 100

struct Lagu {
    char id[20];
    char judul[100];
    char artis[100];
    int tahun;
    int durasi;
};

struct histori {
    char aktivitas[200];
    char waktu[30];
};

struct Lagu playlist[maksimallagu];
struct histori histori[maksimalhistori];
int jumlahLagu = 0;
int jumlahhistori = 0;

void getWaktu(char *output) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(output, "%02d-%02d-%04d %02d:%02d:%02d",
            tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,
            tm.tm_hour, tm.tm_min, tm.tm_sec);
}

void tambahhistori(char *aktivitas) {
    if (jumlahhistori >= maksimalhistori) {
        for (int i = 0; i < maksimalhistori - 1; i++) {
            histori[i] = histori[i + 1];
        }
        jumlahhistori--;
    }
    
    strcpy(histori[jumlahhistori].aktivitas, aktivitas);
    getWaktu(histori[jumlahhistori].waktu);
    jumlahhistori++;
}

void cetakjamwok() {
    char waktu[30];
    getWaktu(waktu);
    printf("\n[Waktu Selesai: %s]\n", waktu);
}

int cekIDSudahAda(char *id) {
    for (int i = 0; i < jumlahLagu; i++) {
        if (strcmp(playlist[i].id, id) == 0) {
            return 1;
        }
    }
    return 0;
}

int cariIndexBerdasarkanID(char *id) {
    for (int i = 0; i < jumlahLagu; i++) {
        if (strcmp(playlist[i].id, id) == 0) {
            return i;
        }
    }
    return -1;
}

void tambahLagu() {
    if (jumlahLagu >= maksimallagu) {
        printf("\nPlaylist penuh wok!\n");
        tambahhistori("Gagal nambahin lagu bjir - Playlist penuh");
        cetakjamwok();
        return;
    }
    
    struct Lagu lagubaru;
    
    printf("\n=== TAMBAH LAGU ===\n\n");
    
    while (1) {
        printf("ID Lagu: ");
        scanf(" %19[^\n]", lagubaru.id);
        
        if (cekIDSudahAda(lagubaru.id)) {
            printf("  >> ID '%s' sudah dipakai!\n\n", lagubaru.id);
        } else {
            printf("  >> ID '%s' tersedia!\n\n", lagubaru.id);
            break;
        }
    }
    
    printf("Judul: ");
    scanf(" %99[^\n]", lagubaru.judul);
    
    printf("Artis: ");
    scanf(" %99[^\n]", lagubaru.artis);
    
    printf("Tahun: ");
    scanf("%d", &lagubaru.tahun);
    
    printf("Durasi (detik): ");
    scanf("%d", &lagubaru.durasi);
    
    playlist[jumlahLagu] = lagubaru;
    jumlahLagu++;
    
    char log[200];
    sprintf(log, "Menambahkan lagu '%s' - %s (ID: %s)", 
            lagubaru.judul, lagubaru.artis, lagubaru.id);
    tambahhistori(log);
    
    printf("\nLagu berhasil ditambahkan dengan ID: %s\n", lagubaru.id);
    cetakjamwok();
}

void lihatLagu() {
    if (jumlahLagu == 0) {
        printf("\nPlaylist kosong tambahin dulu!\n");
        tambahhistori("Melihat playlist kosong tambahin dulu");
        cetakjamwok();
        return;
    }
    
    printf("\n=== DAFTAR SEMUA LAGU ===\n");
    printf("+------------+--------------------------------+----------------------+--------+----------+\n");
    printf("| %-10s | %-30s | %-20s | %-6s | %-8s |\n", 
           "ID", "Judul", "Artis", "Tahun", "Durasi");
    printf("+------------+--------------------------------+----------------------+--------+----------+\n");
    
    for (int i = 0; i < jumlahLagu; i++) {
        int menit = playlist[i].durasi / 60;
        int detik = playlist[i].durasi % 60;
        
        printf("| %-10s | %-30.30s | %-20.20s | %-6d | %02d:%02d    |\n",
            playlist[i].id,
            playlist[i].judul,
            playlist[i].artis,
            playlist[i].tahun,
            menit, detik);
    }
    
    printf("+------------+--------------------------------+----------------------+--------+----------+\n");
    printf("Total: %d lagu\n", jumlahLagu);
    
    char log[200];
    sprintf(log, "Melihat semua lagu (%d lagu)", jumlahLagu);
    tambahhistori(log);
    
    cetakjamwok();
}

void editLagu() {
    if (jumlahLagu == 0) {
        printf("\nTidak ada lagu!\n");
        tambahhistori("Gagal edit - Tidak ada lagu");
        cetakjamwok();
        return;
    }
    
    char id[20];
    printf("\nMasukkan ID lagu: ");
    scanf(" %19[^\n]", id);
    
    int index = cariIndexBerdasarkanID(id);
    
    if (index == -1) {
        printf("\nLagu dengan ID '%s' tidak ditemukan!\n", id);
        char log[200];
        sprintf(log, "Gagal edit - ID '%s' tidak ditemukan", id);
        tambahhistori(log);
        cetakjamwok();
        return;
    }
    
    printf("\n=== DATA LAGU SAAT INI ===\n");
    printf("Judul : %s\n", playlist[index].judul);
    printf("Artis : %s\n", playlist[index].artis);
    printf("Tahun : %d\n", playlist[index].tahun);
    printf("Durasi: %d detik\n", playlist[index].durasi);

    printf("\nPilih data yang ingin diedit:\n");
    printf("1. Judul\n");
    printf("2. Artis\n");
    printf("3. Tahun\n");
    printf("4. Durasi\n");
    printf("5. Edit Semua\n");
    printf("6. Batal\n");
    printf("Pilihan: ");

    int pilihan;
    scanf("%d", &pilihan);
    getchar();

    char log[200];

    switch (pilihan) {
        case 1:
            printf("Judul baru: ");
            scanf(" %99[^\n]", playlist[index].judul);
            sprintf(log, "Edit judul lagu ID '%s'", id);
            break;

        case 2:
            printf("Artis baru: ");
            scanf(" %99[^\n]", playlist[index].artis);
            sprintf(log, "Edit artis lagu ID '%s'", id);
            break;

        case 3:
            printf("Tahun baru: ");
            scanf("%d", &playlist[index].tahun);
            sprintf(log, "Edit tahun lagu ID '%s'", id);
            break;

        case 4:
            printf("Durasi baru (detik): ");
            scanf("%d", &playlist[index].durasi);
            sprintf(log, "Edit durasi lagu ID '%s'", id);
            break;

        case 5:
            printf("Judul baru: ");
            scanf(" %99[^\n]", playlist[index].judul);
            printf("Artis baru: ");
            scanf(" %99[^\n]", playlist[index].artis);
            printf("Tahun baru: ");
            scanf("%d", &playlist[index].tahun);
            printf("Durasi baru (detik): ");
            scanf("%d", &playlist[index].durasi);
            sprintf(log, "Edit semua data lagu ID '%s'", id);
            break;

        case 6:
            printf("\nEdit dibatalkan.\n");
            tambahhistori("Edit lagu dibatalkan");
            cetakjamwok();
            return;

        default:
            printf("\nPilihan tidak valid!\n");
            tambahhistori("Gagal edit - pilihan tidak valid");
            cetakjamwok();
            return;
    }

    tambahhistori(log);
    printf("\nData lagu berhasil diperbarui!\n");
    cetakjamwok();
}

void hapusLagu() {
    if (jumlahLagu == 0) {
        printf("\nTidak ada lagu!\n");
        tambahhistori("Gagal hapus - Tidak ada lagu");
        cetakjamwok();
        return;
    }
    
    char id[20];
    printf("\nMasukkan ID lagu: ");
    scanf(" %19[^\n]", id);
    
    int index = cariIndexBerdasarkanID(id);
    
    if (index == -1) {
        printf("\nLagu dengan ID '%s' tidak ditemukan!\n", id);
        char log[200];
        sprintf(log, "Gagal hapus - ID '%s' tidak ditemukan", id);
        tambahhistori(log);
        cetakjamwok();
        return;
    }
    
    printf("\n=== HAPUS LAGU ===\n");
    printf("ID    : %s\n", playlist[index].id);
    printf("Judul : %s\n", playlist[index].judul);
    printf("Artis: %s\n\n", playlist[index].artis);
    printf("Yakin hapus lagu ini? (y/n): ");
    
    char konfirmasi;
    scanf(" %c", &konfirmasi);
    
    if (konfirmasi == 'y' || konfirmasi == 'Y') {
        char log[200];
        sprintf(log, "Menghapus lagu ID '%s': '%s' - %s", 
                id, playlist[index].judul, playlist[index].artis);
        
        for (int i = index; i < jumlahLagu - 1; i++) {
            playlist[i] = playlist[i + 1];
        }
        jumlahLagu--;
        
        tambahhistori(log);
        printf("\nLagu berhasil dihapus!\n");
    } else {
        tambahhistori("Membatalkan penghapusan lagu");
        printf("\nPenghapusan dibatalkan.\n");
    }
    
    cetakjamwok();
}

void cariLagu() {
    if (jumlahLagu == 0) {
        printf("\nPlaylist kosong tambahin dulu!\n");
        tambahhistori("Gagal cari - Playlist kosong tambahin dulu");
        cetakjamwok();
        return;
    }
    
    char carijudul[100];
    printf("\nCari berdasarkan judul: ");
    scanf(" %99[^\n]", carijudul);
    
    for (int i = 0; carijudul[i]; i++) {
        carijudul[i] = tolower(carijudul[i]);
    }
    
    int ketemu = 0;
    
    printf("\n=== HASIL PENCARIAN ===\n");
    printf("+------------+--------------------------------+----------------------+--------+----------+\n");
    printf("| %-10s | %-30s | %-20s | %-6s | %-8s |\n", 
        "ID", "Judul", "Artis", "Tahun", "Durasi");
    printf("+------------+--------------------------------+----------------------+--------+----------+\n");
    
    for (int i = 0; i < jumlahLagu; i++) {
        char judulLower[100];
        strcpy(judulLower, playlist[i].judul);
        
        for (int j = 0; judulLower[j]; j++) {
            judulLower[j] = tolower(judulLower[j]);
        }
        
        if (strstr(judulLower, carijudul) != NULL) {
            int menit = playlist[i].durasi / 60;
            int detik = playlist[i].durasi % 60;
            
            printf("| %-10s | %-30.30s | %-20.20s | %-6d | %02d:%02d    |\n",
                playlist[i].id,
                playlist[i].judul,
                playlist[i].artis,
                playlist[i].tahun,
                menit, detik);
            ketemu++;
        }
    }
    
    printf("+------------+--------------------------------+----------------------+--------+----------+\n");
    
    char log[200];
    if (ketemu == 0) {
        printf("Tidak ada lagu yang ditemukan.\n");
        sprintf(log, "Mencari '%s' - Tidak ditemukan", carijudul);
    } else {
        printf("Ditemukan: %d lagu\n", ketemu);
        sprintf(log, "Mencari '%s' - Ditemukan %d lagu", carijudul, ketemu);
    }
    tambahhistori(log);
    
    cetakjamwok();
}

void urutkanLagu() {
    if (jumlahLagu == 0) {
        printf("\nPlaylist kosong tambahin dulu !\n");
        tambahhistori("Gagal urutkan - Playlist kosong tambahin dulu");
        cetakjamwok();
        return;
    }
    
    printf("\n=== URUTKAN LAGU BERDASARKAN ===\n");
    printf("1. ID\n");
    printf("2. Judul\n");
    printf("3. Artis\n");
    printf("4. Tahun\n");
    printf("Masukkan Pilihan: ");
    
    int pilihan;
    scanf("%d", &pilihan);
    
    char kriteria[20];
    
    for (int i = 0; i < jumlahLagu - 1; i++) {
        for (int j = 0; j < jumlahLagu - i - 1; j++) {
            int tukar = 0;
            
            if (pilihan == 1) {
                strcpy(kriteria, "ID");
                if (strcmp(playlist[j].id, playlist[j+1].id) > 0) {
                    tukar = 1;
                }
            } else if (pilihan == 2) {
                strcpy(kriteria, "Judul");
                if (strcmp(playlist[j].judul, playlist[j+1].judul) > 0) {
                    tukar = 1;
                }
            } else if (pilihan == 3) {
                strcpy(kriteria, "Artis");
                if (strcmp(playlist[j].artis, playlist[j+1].artis) > 0) {
                    tukar = 1;
                }
            } else if (pilihan == 4) {
                strcpy(kriteria, "Tahun");
                if (playlist[j].tahun > playlist[j+1].tahun) {
                    tukar = 1;
                }
            }
            
            if (tukar) {
                struct Lagu temp = playlist[j];
                playlist[j] = playlist[j+1];
                playlist[j+1] = temp;
            }
        }
    }
    
    char log[200];
    sprintf(log, "Mengurutkan lagu berdasarkan %s", kriteria);
    tambahhistori(log);
    
    printf("\nLagu berhasil diurutkan!\n");
    cetakjamwok();
    
    lihatLagu();
}

void lihathistori() {
    if (jumlahhistori == 0) {
        printf("\nbelom ngapa-ngapain lu wok!\n");
        cetakjamwok();
        return;
    }
    
    printf("\n=== HISTORI AKTIVITAS ===\n");
    printf("+-------+----------------------+---------------------------------------------------------+\n");
    printf("| %-5s | %-20s | %-55s |\n", "No", "Waktu", "Aktivitas");
    printf("+-------+----------------------+---------------------------------------------------------+\n");
    
    for (int i = jumlahhistori - 1; i >= 0; i--) {
        printf("| %-5d | %-20s | %-55.55s |\n",
            jumlahhistori - i,
            histori[i].waktu,
            histori[i].aktivitas);
    }
    
    printf("+-------+----------------------+---------------------------------------------------------+\n");
    printf("Total aktivitas: %d\n", jumlahhistori);
    cetakjamwok();
}

void hapushistori() {
    if (jumlahhistori == 0) {
        printf("\nTidak ada histori untuk dihapus.\n");
        cetakjamwok();
        return;
    }
    
    printf("\nYakin hapus semua histori? (y/n): ");
    char konfirmasi;
    scanf(" %c", &konfirmasi);
    
    if (konfirmasi == 'y' || konfirmasi == 'Y') {
        jumlahhistori = 0;
        printf("\nhistori berhasil dihapus!\n");
        tambahhistori("Menghapus semua histori");
    } else {
        printf("\nPenghapusan dibatalkan.\n");
        tambahhistori("Membatalkan penghapusan histori");
    }
    
    cetakjamwok();
}

int main() {
    int menuPilihan;
    
    tambahhistori("Program dimulai");
    
    while (1) {
        printf("\n");
        printf("================================\n");
        printf("   SISTEM MANAJEMEN LAGU\n");
        printf("================================\n");
        printf("1. Tambah Lagu\n");
        printf("2. Lihat Semua Lagu\n");
        printf("3. Cari Lagu\n");
        printf("4. Edit Lagu\n");
        printf("5. Hapus Lagu\n");
        printf("6. Urutkan Lagu\n");
        printf("7. Histori Aktivitas\n");
        printf("8. Hapus Histori\n");
        printf("9. Keluar\n");
        printf("================================\n");
        printf("Pilih menu: ");
        scanf("%d", &menuPilihan);
        
        if (menuPilihan == 1) {
            tambahLagu();
        } else if (menuPilihan == 2) {
            lihatLagu();
        } else if (menuPilihan == 3) {
            cariLagu();
        } else if (menuPilihan == 4) {
            editLagu();
        } else if (menuPilihan == 5) {
            hapusLagu();
        } else if (menuPilihan == 6) {
            urutkanLagu();
        } else if (menuPilihan == 7) {
            lihathistori();
        } else if (menuPilihan == 8) {
            hapushistori();
        } else if (menuPilihan == 9) {
            tambahhistori("Program ditutup");
            printf("\nTerima kasih!\n");
            cetakjamwok();
            break;
        } else {
            printf("\nPilihan tidak valid!\n");
            tambahhistori("Pilihan menu tidak valid");
            cetakjamwok();
        }
        
        printf("\nTekan Enter untuk kembali ke menu utama...");
        getchar();
        getchar();
    }
    
    return 0;
}   