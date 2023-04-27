#ifndef POINT_H
#define POINT_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct Point {
    char name[50];
    double lat;
    double lon;
};

int read_points_from_csv(const char* filename, struct Point* points);

struct Point copyPoint(struct Point originalPoint);

double haversine(struct Point a, struct Point b);

int orientation(struct Point a, struct Point b, struct Point c);

void swap(struct Point *p1, struct Point *p2);

#endif /* POINTS_H */
