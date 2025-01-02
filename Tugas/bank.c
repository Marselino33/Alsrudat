#include <stdio.h>
#include <string.h>
#include "bank.h"

void initQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

int isEmpty(Queue *q) {
    return q->front == -1;
}

int isFull(Queue *q) {
    return (q->rear + 1) % MAX_QUEUE == q->front;
}


void addQueue(Queue *q, Nasabah n)
{
    if (isFull(q))
    {
        printf("Error: Antrian penuh! Tidak dapat menambahkan nasabah '%s'.\n", n.nama_nasabah);
        return;
    }

    // Validasi jenis layanan
    while (strcmp(n.jenis_layanan, "setoran") != 0 && strcmp(n.jenis_layanan, "penarikan") != 0)
    {
        printf("Jenis layanan salah! Masukkan hanya 'setoran' atau 'penarikan': ");
        scanf("%s", n.jenis_layanan);
    }

    if (isEmpty(q))
    {
        q->front = 0;
        q->rear = 0;
    }
    else
    {
        q->rear = (q->rear + 1) % MAX_QUEUE;
    }
    q->data[q->rear] = n;
    printf("Nasabah '%s' berhasil ditambahkan ke antrian dengan nomor %d.\n", n.nama_nasabah, n.nomor_antrian);
}


void delQueue(Queue *q) {
    if (isEmpty(q)) {
        printf("Antrian kosong! Tidak ada nasabah yang dapat dihapus.\n");
        return;
    }
    if (strcmp(q->data[q->front].status, "dilayani") == 0 || strcmp(q->data[q->front].status, "selesai dilayani") == 0) {
        printf("Nasabah '%s' dengan nomor antrian %d sedang dilayani atau selesai dilayani dan dapat dihapus.\n", q->data[q->front].nama_nasabah, q->data[q->front].nomor_antrian);
        if (q->front == q->rear) {
            initQueue(q);
        } else {
            q->front = (q->front + 1) % MAX_QUEUE;
        }
    } else {
        printf("Nasabah '%s' dengan nomor antrian %d belum dilayani, tidak bisa dihapus.\n", q->data[q->front].nama_nasabah, q->data[q->front].nomor_antrian);
    }
}

void peek(Queue *q) {
    if (isEmpty(q)) {
        printf("Antrian kosong! Tidak ada nasabah yang dapat dilihat.\n");
        return;
    }
    Nasabah n = q->data[q->front];
    printf("Nasabah di depan antrian:\n");
    printf("ID: %d, Nama: %s, Nomor Antrian: %d, Jenis Layanan: %s, Waktu Kedatangan: %s, Status: %s\n",
           n.id_nasabah, n.nama_nasabah, n.nomor_antrian, n.jenis_layanan, n.waktu_kedatangan, n.status);
}

void peekAll(Queue *q, const char *jenis_layanan) {
    if (isEmpty(q)) {
        printf("Antrian kosong! Tidak ada nasabah yang dapat dilihat.\n");
        return;
    }
    printf("Daftar nasabah dengan jenis layanan '%s':\n", jenis_layanan);
    int i = q->front;
    do {
        if (strcmp(q->data[i].jenis_layanan, jenis_layanan) == 0) {
            Nasabah n = q->data[i];
            printf("ID: %d, Nama: %s, Nomor Antrian: %d, Waktu Kedatangan: %s, Status: %s\n",
                   n.id_nasabah, n.nama_nasabah, n.nomor_antrian, n.waktu_kedatangan, n.status);
        }
        i = (i + 1) % MAX_QUEUE;
    } while (i != (q->rear + 1) % MAX_QUEUE);
}

void displayAll(Queue *q) {
    if (isEmpty(q)) {
        printf("Antrian kosong! Tidak ada nasabah dalam antrian.\n");
        return;
    }
    printf("Daftar semua nasabah dalam antrian:\n");
    int i = q->front;
    do {
        Nasabah n = q->data[i];
        printf("ID: %d, Nama: %s, Nomor Antrian: %d, Jenis Layanan: %s, Waktu Kedatangan: %s, Status: %s\n",
               n.id_nasabah, n.nama_nasabah, n.nomor_antrian, n.jenis_layanan, n.waktu_kedatangan, n.status);
        i = (i + 1) % MAX_QUEUE;
    } while (i != (q->rear + 1) % MAX_QUEUE);
}
