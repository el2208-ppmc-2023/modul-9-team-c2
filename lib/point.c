/*EL2208 Praktikum Pemecahan Masalah dengan C 2022/2023
    *Modul:9-TugasBesar
    *Kelompok:C2
    *HaridanTanggal:27 April 2023
    *Asisten(NIM):Muhammad Morteza Mudrick (13219061)
    *NamaFile:point.c
    *Deskripsi:File main untuk implementasi Convex Hull Algorithm yang di dalamnya terdapat directive file header stack dan point
    */

#include "point.h"

#define BUFFER_SIZE 100
#define PI 3.14159265358979323846
#define EARTH_RADIUS 6371 // dalam Kilometer


struct Point copyPoint(struct Point originalPoint) {
    // Alokasi memori untuk titik baru
    struct Point newPoint;

    // Mengcopy nilai dari titik awal ke titik baru
    strcpy(newPoint.name, originalPoint.name);
    newPoint.lat = originalPoint.lat;
    newPoint.lon = originalPoint.lon;

    return newPoint;
}


double haversine(struct Point a, struct Point b) {
    double dLat = (b.lat - a.lat) * PI / 180.0;
    double dLon = (b.lon - a.lon) * PI / 180.0;
    double x = pow(sin(dLat / 2), 2) + cos(a.lat * PI / 180.0) * cos(b.lat * PI / 180.0) * pow(sin(dLon / 2), 2);
    double c = 2 * atan2(sqrt(x), sqrt(1 - x));
    double distance = EARTH_RADIUS * c;
    return distance;
}

// Deklarasi fungsi orientation yang digunakan untuk menentukan arah putaran tiga titik pada bidang kartesius.
int orientation(struct Point a, struct Point b, struct Point c) {
    double val = (b.lon - a.lon) * (c.lat - b.lat) - (b.lat - a.lat) * (c.lon - b.lon);
    if (val == 0) {
        return 0; // colinear
    }
    if (val > 0) {
        return 1;
    }
    if (val < 0) {
        return 2;
    }
}

void swap(struct Point *p1, struct Point *p2) {
    struct Point temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}
