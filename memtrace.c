// SPDX-License-Identifier: Apache-2.0

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <pthread.h>

static size_t malloc_sizes[1000] = {0};  // Array to store size counts
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

typedef void* (*malloc_t)(size_t);
typedef void* (*calloc_t)(size_t, size_t);

void* malloc(size_t size) {
    static malloc_t real_malloc = NULL;
    if (!real_malloc) {
        real_malloc = (malloc_t) dlsym(RTLD_NEXT, "malloc");
    }

    pthread_mutex_lock(&lock);
    if (size < 1000) {
        malloc_sizes[size]++;
    }
    pthread_mutex_unlock(&lock);

    return real_malloc(size);
}

void* calloc(size_t nmemb, size_t size) {
    static calloc_t real_calloc = NULL;
    if (!real_calloc) {
        real_calloc = (calloc_t) dlsym(RTLD_NEXT, "calloc");
    }

    pthread_mutex_lock(&lock);
    size_t total_size = nmemb * size;
    if (total_size < 1000) {
        malloc_sizes[total_size]++;
    }
    pthread_mutex_unlock(&lock);

    return real_calloc(nmemb, size);
}

// Print the histogram at the end of program execution
__attribute__((destructor)) void print_histogram() {
    printf("Allocation Size Histogram:\n");
    for (size_t i = 0; i < 1000; i++) {
        if (malloc_sizes[i] > 0) {
            printf("%zu bytes: %zu allocations\n", i, malloc_sizes[i]);
        }
    }
    // Also dump it to file.
    FILE *f = fopen("alloc_histogram.txt", "w");
    if (f == NULL) {
        perror("Error opening file");
        return;
    }
    for (size_t i = 0; i < 1000; i++) {
        if (malloc_sizes[i] > 0) {
            fprintf(f, "%zu %zu\n", i, malloc_sizes[i]);
        }
    }
    fclose(f);
}

