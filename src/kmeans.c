#include "../include/kmeans.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Points alloc_centroids(size_t k, Point min, Point max)
{
    Points p = points_alloc(k);

    for (size_t i = 0; i < k; i++) {
        points_add(&p, point_random(min, max));
    }

    return p;
}

Points kmeans(Points samples, size_t k, size_t max_iterations)
{
    if (k == 0) {
        fprintf(stderr, "ERROR: k cannot be 0!\n");
        exit(EXIT_FAILURE);
    }

    int converged;
    size_t iteration = 0;

    size_t n = samples.s;

    Points centroids = alloc_centroids(k, points_min(samples), points_max(samples));

    do {
        converged = 1;

        // assign points to centroids
        for (size_t i = 0; i < n; i++) {
            Point s = samples.e[i];
            Point c = centroids.e[0];
            double best_dst = point_distance(s, c);
            size_t class = 0;

            for (size_t j = 1; j < k; j++) {
                c = centroids.e[j];
                double dst = point_distance(s, c);

                if (dst < best_dst) {
                    best_dst = dst;
                    class    = j;
                }
            }

            // point was assigned to a new centroid
            if (s.c != class) converged = 0;

            samples.e[i].c = class;
        }

        // discard old centroids
        memset(centroids.e, 0, centroids.s * sizeof (Point));

        // calculate new centroids
        for (size_t i = 0; i < n; i++) {
            Point s  = samples.e[i];

            for (size_t j = 0; j < k; j++) {
                Point *c = &centroids.e[j];

                if (s.c == j) {
                    c->x += s.x;
                    c->y += s.y;
                    c->z += s.z;
                    c->c++;
                }
            }
        }

        for (size_t i = 0; i < k; i++) {
            Point *c = &centroids.e[i];
            
            if (c->c == 0) continue;
            c->x /= c->c;
            c->y /= c->c;
            c->z /= c->c;
        }

    } while (!converged && ++iteration < max_iterations);

    return centroids;
}