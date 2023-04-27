#include "point.h"

#define BUFFER_SIZE 100
#define PI 3.14159265358979323846
#define EARTH_RADIUS 6371 // in km

int read_points_from_csv(const char* filename, struct Point* points) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: could not open file %s\n", filename);
        return -1;
    }

    char buffer[BUFFER_SIZE];
    if (fgets(buffer, BUFFER_SIZE, file) == NULL) {
        printf("Error: empty file\n");
        fclose(file);
        return -1;
    }

    int num_points = 0;
    while (fgets(buffer, BUFFER_SIZE, file)) {
        if (buffer[0] == '\n') {
            continue; // Skip empty lines
        }

        struct Point p;

        // Read name
        char* pos = strchr(buffer, ',');
        *pos = '\0';
        strcpy(p.name, buffer);
        buffer[strlen(buffer)] = ',';

        // Read latitude
        buffer[strlen(buffer) - 1] = '\0'; // Remove comma from end of name
        pos = strchr(buffer, ',');
        p.lat = atof(buffer + strlen(p.name) + 1);
        buffer[strlen(p.name) + strlen(pos)] = ',';

        // Read longitude
        p.lon = atof(pos + 1);

        points[num_points++] = p;
    }

    fclose(file);

    return num_points;
}

struct Point copyPoint(struct Point originalPoint) {
    // Allocate memory for the new point
    struct Point newPoint;

    // Copy the values from the original point to the new point
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
