
#ifndef __GREYSCALE_H__
#define __GREYSCALE_H__

#include "Color.h"

__global__
void greyscale(size_t width, size_t height, Color* color, Byte* greyscale) {

    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    if (x >= width || y >= height) return;

    int index = x + width * y;

    Color& c = color[index];
    greyscale[index] = 0.299 * c.r + 0.587 * c.g + 0.114 * c.b;

    __syncthreads();
}

#endif // __GREYSCALE_H__