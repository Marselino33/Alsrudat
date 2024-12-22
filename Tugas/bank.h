/* *** Definisi ABSTRACT DATA TYPE Queue *** */
#ifndef QUEUE_H
#define QUEUE_H

#define MAX_QUEUE 100

/* *** Struktur Nasabah *** */
typedef struct _nasabah {
    int id_nasabah;
    char nama_nasabah[50];
    int nomor_antrian;
    char jenis_layanan[50];
    char waktu_kedatangan[10];
    char status[20]; /* Status: "antri", "dilayani", "selesai dilayani" */
} Nasabah;

/* *** Struktur Queue *** */
typedef struct _queue {
    Nasabah data[MAX_QUEUE];
    int front;
    int rear;
} Queue;

/* *** Konstruktor untuk membentuk Queue *** */
void initQueue(Queue *q);
/* Inisialisasi Queue (kosongkan queue) */

int isEmpty(Queue *q);
/* Mengecek apakah Queue kosong */

int isFull(Queue *q);
/* Mengecek apakah Queue penuh */

void addQueue(Queue *q, Nasabah n);
/* Menambahkan Nasabah ke antrian */

void delQueue(Queue *q);
/* Menghapus Nasabah dari antrian */

void peek(Queue *q);
/* Melihat Nasabah di depan antrian */

void peekAll(Queue *q, const char *jenis_layanan);
/* Melihat Nasabah dalam antrian berdasarkan jenis layanan */

void displayAll(Queue *q);
/* Menampilkan semua Nasabah dalam antrian */

#endif
