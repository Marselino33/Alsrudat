#include <stdio.h>
#include <string.h>
#include "bank.h"

Queue q;

void tellerMenu() {
    int choice;
    Nasabah n;
    char jenis_layanan[50];

    do {
        printf("\n=== Sistem Teller Bank ===\n");
        printf("1. Tambah Nasabah ke Antrian\n");
        printf("2. Hapus Nasabah dari Antrian\n");
        printf("3. Lihat Nasabah di Depan Antrian\n");
        printf("4. Lihat Semua Nasabah Berdasarkan Jenis Layanan\n");
        printf("5. Lihat Semua Nasabah dalam Antrian\n");
        printf("6. Layani Nasabah di Depan Antrian\n");
        printf("7. Ubah Status Nasabah Menjadi Selesai Dilayani\n");
        printf("8. Kembali ke Menu Utama\n");
        printf("Pilih opsi: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (isFull(&q)) {
                    printf("Antrian penuh! Tidak dapat menambahkan nasabah baru.\n");
                } else {
                    printf("Masukkan ID Nasabah: ");
                    scanf("%d", &n.id_nasabah);
                    getchar(); // Menghilangkan newline dari buffer

                    printf("Masukkan Nama Nasabah: ");
                    fgets(n.nama_nasabah, 50, stdin);
                    n.nama_nasabah[strcspn(n.nama_nasabah, "\n")] = 0; // Menghapus newline

                    printf("Masukkan Jenis Layanan: ");
                    fgets(n.jenis_layanan, 50, stdin);
                    n.jenis_layanan[strcspn(n.jenis_layanan, "\n")] = 0;

                    printf("Masukkan Waktu Kedatangan (HH:MM): ");
                    scanf("%s", n.waktu_kedatangan);

                    printf("Masukkan Status (antri/dilayani/selesai dilayani): ");
                    scanf("%s", n.status);

                    n.nomor_antrian = q.rear + 2; // Nomor antrian dimulai dari 1
                    addQueue(&q, n);
                }
                break;

            case 2:
                delQueue(&q);
                break;

            case 3:
                peek(&q);
                break;

            case 4:
                printf("Masukkan jenis layanan untuk ditampilkan: ");
                getchar(); // Menghilangkan newline dari buffer
                fgets(jenis_layanan, 50, stdin);
                jenis_layanan[strcspn(jenis_layanan, "\n")] = 0; // Menghapus newline
                peekAll(&q, jenis_layanan);
                break;

            case 5:
                displayAll(&q);
                break;

            case 6:
                if (isEmpty(&q)) {
                    printf("Antrian kosong! Tidak ada nasabah untuk dilayani.\n");
                } else {
                    printf("Nasabah '%s' dengan nomor antrian %d sedang dilayani.\n", q.data[q.front].nama_nasabah, q.data[q.front].nomor_antrian);
                    strcpy(q.data[q.front].status, "dilayani");
                }
                break;

            case 7:
                if (isEmpty(&q)) {
                    printf("Antrian kosong! Tidak ada nasabah untuk diperbarui statusnya.\n");
                } else {
                    if (strcmp(q.data[q.front].status, "dilayani") == 0) {
                        printf("Nasabah '%s' dengan nomor antrian %d statusnya diubah menjadi 'selesai dilayani'.\n", q.data[q.front].nama_nasabah, q.data[q.front].nomor_antrian);
                        strcpy(q.data[q.front].status, "selesai dilayani");
                        delQueue(&q); // Menghapus nasabah yang selesai dilayani
                    } else {
                        printf("Nasabah di depan antrian belum dalam status 'dilayani'.\n");
                    }
                }
                break;

            case 8:
                printf("Kembali ke menu utama.\n");
                break;

            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    } while (choice != 8);
}

void nasabahMenu() {
    Nasabah n;
    printf("=== Pendaftaran Antrian Nasabah ===\n");

    if (isFull(&q)) {
        printf("Antrian penuh! Tidak dapat mendaftar.\n");
    } else {
        printf("Masukkan ID Nasabah: ");
        scanf("%d", &n.id_nasabah);
        getchar(); // Menghilangkan newline dari buffer

        printf("Masukkan Nama Nasabah: ");
        fgets(n.nama_nasabah, 50, stdin);
        n.nama_nasabah[strcspn(n.nama_nasabah, "\n")] = 0; // Menghapus newline

        printf("Masukkan Jenis Layanan: ");
        fgets(n.jenis_layanan, 50, stdin);
        n.jenis_layanan[strcspn(n.jenis_layanan, "\n")] = 0;

        printf("Masukkan Waktu Kedatangan (HH:MM): ");
        scanf("%s", n.waktu_kedatangan);

        strcpy(n.status, "antri");

        n.nomor_antrian = q.rear + 2; // Nomor antrian dimulai dari 1
        addQueue(&q, n);
        printf("Pendaftaran berhasil. Nomor antrian Anda adalah %d.\n", n.nomor_antrian);
    }
}

int main() {
    initQueue(&q);
    int actor_choice;

    do {
        printf("\n=== Sistem Antrian Bank ===\n");
        printf("1. Teller\n");
        printf("2. Nasabah\n");
        printf("3. Keluar\n");
        printf("Pilih aktor: ");
        scanf("%d", &actor_choice);

        switch (actor_choice) {
            case 1:
                tellerMenu();
                break;
            case 2:
                nasabahMenu();
                break;
            case 3:
                printf("Keluar dari program. Terima kasih!\n");
                break;
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    } while (actor_choice != 3);

    return 0;
}
