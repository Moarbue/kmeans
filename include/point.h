#include <stddef.h>

#ifndef _POINT_H_
#define _POINT_H_

typedef struct {
    size_t x;   // x-coordiante
    size_t y;   // y-coordinate
    size_t z;   // z-coordinate
    size_t c;   // class
} Point;

Point  point_random(Point min, Point max);
double point_distance(Point a, Point b);

typedef struct {
    size_t c;   // capacity
    size_t s;   // size
    Point *e;   // elements
} Points;

Points points_alloc(size_t size);
void   points_add(Points *p, Point s);
Point  points_max(Points p);
Point  points_min(Points p);
Points points_from_image(const char *filepath, int *w, int *h, int *comp);
void   points_free(Points p);

#endif // _POINT_H_