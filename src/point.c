#include "../include/point.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Point point_random(Point min, Point max)
{
    Point p;

    p.x = min.x + rand() % (max.x-min.x);
    p.y = min.y + rand() % (max.y-min.y);
    p.z = min.z + rand() % (max.z-min.z);

    return p;
}

double point_distance(Point a, Point b)
{
    return sqrt((double)((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) + (a.z - b.z)*(a.z - b.z)));
}


Points points_alloc(size_t size)
{
    Points p;

    p.c = size;
    p.s = 0;
    p.e = (Point *) malloc(p.c * sizeof (Point));
    if (p.e == NULL) {
        fprintf(stderr, "ERROR: Failed to allocate memory for Points!\n");
        exit(EXIT_FAILURE);
    }
    memset(p.e, 0, p.c * sizeof (Point));

    return p;
}

void points_add(Points *p, Point s)
{
    p->s++;

    if (p->s > p->c) {
        p->c *= 2;
        p->e = (Point *) realloc(p->e, p->c * sizeof (Point));
        if (p->e == NULL) {
            fprintf(stderr, "ERROR: Failed to allocate memory for Points!\n");
            exit(EXIT_FAILURE);
        }
    }

    p->e[p->s-1] = s;
}

Point points_max(Points p)
{
    if (p.s == 0) return (Point){0};

    Point max = p.e[0];
    for (size_t i = 1; i < p.s; i++) {
        if (p.e[i].x > max.x) max.x = p.e[i].x;
        if (p.e[i].y > max.y) max.y = p.e[i].y;
        if (p.e[i].z > max.z) max.z = p.e[i].z;
    }

    return max;
}

Point points_min(Points p)
{
    if (p.s == 0) return (Point){0};

    Point min = p.e[0];
    for (size_t i = 1; i < p.s; i++) {
        if (p.e[i].x < min.x) min.x = p.e[i].x;
        if (p.e[i].y < min.y) min.y = p.e[i].y;
        if (p.e[i].z < min.z) min.z = p.e[i].z;
    }

    return min;
}

Points points_from_image(const char *filepath, int *w, int *h, int *comp)
{
    int x, y, c;
    unsigned char *img = stbi_load(filepath, &x, &y, &c, 3);
    if (img == NULL) {
        fprintf(stderr, "ERROR: Failed to read image %s!\n", filepath);
        exit(EXIT_FAILURE);
    }
    if (c < 3) {
        fprintf(stderr, "ERROR: Image must have three color channels! Image %s has %d channels\n", filepath, c);
        exit(EXIT_FAILURE);
    }

    Points p = points_alloc(x*y);
    for (size_t i = 0; i < (size_t)(x*y); i++) {
        Point s = {.x = img[i*3], .y = img[i*3 + 1], .z = img[i*3 + 2]};
        points_add(&p, s);
    }

    free(img);

    *w = x;
    *h = y;
    *comp = c;

    return p;
}

void points_free(Points p)
{
    free(p.e);
}