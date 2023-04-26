    /*EL2208 Praktikum Pemecahan Masalah dengan C 2022/2023
    *Modul:9-TugasBesar
    *Kelompok:C2
    *HaridanTanggal:27 April 2023
    *Asisten(NIM):Muhammad Morteza Mudrick (13219061)
    *NamaFile:main.c
    *Deskripsi:File main untuk implementasi Convex Hull Algorithm yang di dalamnya terdapat directive file header stack dan point
    */
    
    #include <stdio.h>
    #include "lib/stack.h"
    #include "lib/point.h"

    // variabel global p0
    struct Point p0;
    // Deklarasi variabel p0 sebagai titik paling bawah kiri yang akan digunakan sebagai titik awal untuk membentuk hull.

    // Deklarasi fungsi compare yang digunakan sebagai parameter fungsi qsort untuk mengurutkan titik-titik berdasarkan sudut yang dibentuk dengan titik awal p0.
    int compare(const void *p1, const void *p2) {
        struct Point *a = (struct Point *)p1;
        struct Point *b = (struct Point *)p2;

        int o = orientation(p0, *a, *b); //fungsi orientation  digunakan untuk menentukan arah putaran tiga titik pada bidang kartesius.
        if (o == 0) {
            (haversine(p0, *a) >= haversine(p0, *b))? -1 : 1;
        } 
    
        return (o == 2)? -1: 1;
    }



    int main() {
        int n = 0;
        double perimeter = 0;
        struct Point points[100], ineffective [100];
        char fname[100], path[106];

        // input filename
        printf("\nMasukkan file markas: ");
        scanf("%s", fname);
        snprintf(path, sizeof(path), "test/%s", fname);

        FILE *file = fopen(path, "r");
        if (file == NULL) {
            printf("Tidak dapat membuka file.\n");
            return 1;
        }

        // input titik dari file
        char line[1024];
        while (fgets(line, sizeof(line), file)) {
            char name[50];
            double latitude, longitude;
            if (sscanf(line, "%[^,],%lf,%lf", name, &latitude, &longitude) == 3) {
                n++;
                strcpy(points[n-1].name, name);
                points[n-1].lat = latitude;
                points[n-1].lon = longitude;
            }
        }

        // close file
        fclose(file);

        // menentukan titik paling bawah kiri
        int ymin = points[0].lat, min = 0;
        for (int i = 1; i < n; i++)
        {
            int y = points[i].lat;
            if ((y < ymin) || (ymin == y && points[i].lon < points[min].lon)) {
                ymin = points[i].lat, min = i;
            }   
        }

        // meletakkan titik bawah kiri sebagai p0
        swap(&points[0], &points[min]);
        p0 = points[0];
        
        // sort titik berdasarkan sudut polar terhadap p0
        qsort(&points[1], n-1, sizeof(struct Point), compare);

        

        // menghapus titik yang sudut polarnya sama
        int m = 1; 
        for (int i=1; i<n; i++)
        {
            while (i < n-1 && orientation(points[0], points[i], points[i+1]) == 0) {
                i++;
            }
            points[m] = points[i];
            m++; 
        }
        n = m;

        // initialize stack
        struct Stack stack;
        stack.top = -1;
        
        

        // tidak dapat membentuk convex hull jika titik < 3
        if (n < 3) {
            printf("Tidak dapat membentuk perbatasan\n");
        }
        else {

            // melakukan loop hingga titik dapat kembali ke titik awal
            while (1) {
                // push 3 titik pertama
                push(&stack, points[0]);
                push(&stack, points[1]);
                push(&stack, points[2]);

                m = 0;


                for (int i = 3; i < n; i++) {
                    struct Stack temp = copyStack(stack);
                    
                    // lakukan pop terhadap stack jika jarak 2 titik baru > 2500 atau arah 2 titik baru berlawanan arah jarum jam
                    while (stack.top >= 1 && (orientation(nextToTop(&stack), top(stack), points[i]) != 2 || haversine(top(stack), points[i]) > 2500)) {
                        struct Point dump = pop(&stack);
                    }

                    // jika ukuran stack kurang dari 1 maka titik terakhir tidak efektif
                    if (stack.top < 1) {
                        stack = copyStack(temp);
                        m++;
                        ineffective[m-1] = copyPoint(points[i]);
                    } else {
                        push(&stack, points[i]);
                    }

                }

                // break while loop jika convex hull terbentuk
                if (haversine(p0, top(stack)) <= 2500) {
                    push(&stack, p0);
                    break;
                }
            }


            

            // print result dan hitung keliling
            printf("\nPerbatasan Efektif Negara Api:\n");
            for (int i = 0; i <= stack.top; i++) {
                if (i < stack.top) {
                    perimeter += haversine(stack.points[i], stack.points[i+1]);
                }
                printf("%d. %s (%.4f, %.4f)\n", i+1, stack.points[i].name, stack.points[i].lat, stack.points[i].lon);
            }

            printf("\nPanjang Perbatasan Efektif Negara Api: %.4f km\n", perimeter);

            printf("\nMarkas di Luar Perbatasan Efektif: (%d)\n", m);
            for (int i = 0; i < m; i++) {
                printf("%s (%.4f, %.4f)\n", ineffective[i].name, ineffective[i].lat, ineffective[i].lon);
            }
        }
        
        return 0;
    }
