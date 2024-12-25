# kmeans
Simple C library which performs [kmeans-clustering](https://en.wikipedia.org/wiki/K-means_clustering) on for example the pixels of an image.
The library exposes a single structure to the user: `Points` which is an array of points.
The kmeans-algorithmn uses those points to create centroids (which are also just points) and assigns each input point to one of the centroids.

# Installation
Currently only static library building is supported.
To build the library simply run
```sh
$ make
```
inside a terminal. Obviously you need to have `make` installed for this to work.

# Example usage
```c

// Sample points can be really anything, in this example they are the colors of each pixel of an image
Points samples   = points_from_image(image_path, &x, &y, &comp);
// Perform kmeans on the sample, this changes the samples, as it assign the 'sample.c' attribute to a centroid
Points centroids = kmeans(samples, cluster_count, iterations);

// for each sample
for (size_t i = 0; i < samples.s; i++) {
        Point s = samples.e[i];

        // iterate over each centroid
        for (size_t j = 0; j < centroids.s; j++) {
            Point c = centroids.e[j];

            // if the sample class index is the current centroid
            // that means the kmeans algorithmn assigned the current sample to this centroid
            if (s.c == j) {
                // do some stuff
            }
        }
}

```
A more complete example can be found inside the [demo](demo) directory.
