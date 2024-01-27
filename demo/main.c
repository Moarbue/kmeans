#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/kmeans.h"
#include "../include/point.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int main(int argc, char **argv)
{
    const char *out_default = "out.png";
    char out_file[256];


    if (argc < 3) {
        fprintf(stderr, "Usage: %s <clusters> <input_image> <output_image (%s)>\n", argv[0], out_default);
        return 1;
    } else if (argc > 3) {
        strncpy((char *)out_file, argv[3], 256);
    } else {
        strncpy((char *)out_file, out_default, 256);
    }

    int x, y, comp;
    Points samples   = points_from_image(argv[2], &x, &y, &comp);
    Points centroids = kmeans(samples, atoi(argv[1]), 10000);

    unsigned char *img = (unsigned char *) malloc(samples.s * comp);
    if (img == NULL) {
        fprintf(stderr, "ERROR: Failed to allocate memory for image %s\n", out_file);
        return 1;
    }

    for (size_t i = 0; i < samples.s; i++) {
        Point s = samples.e[i];

        for (size_t j = 0; j < centroids.s; j++) {
            Point c = centroids.e[j];

            if (s.c == j) {
                img[i*comp + 0] = c.x;
                img[i*comp + 1] = c.y;
                img[i*comp + 2] = c.z;
                
                if (comp == 4)
                    img[i*comp + 3] = 255;
            }
        }
    }

    if (!stbi_write_png(out_file, x, y, comp, img, x*comp)) {
        fprintf(stderr, "ERROR: Failed to write image %s\n", out_file);
        return 1;
    }

    return 0;
}