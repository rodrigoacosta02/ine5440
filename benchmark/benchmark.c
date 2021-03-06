#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "mytime.h"

int main(){
    double inicio, fim, tempo;

    uint32_t sizes[] = {1024*32, 1024*64, 1024*128, 1024*256, 1024*512, 1*1024*1024};
    uint32_t nSizes = sizeof(sizes)/sizeof(uint32_t);
    uint32_t strides[] = {1, 4, 16, 1024, 2046, 64*1024, 128*1024};
    uint32_t nStrides = sizeof(strides)/sizeof(uint32_t);
    uint32_t nRun = 30;

    uint32_t *a, *b;
    uint32_t size, stride;

    for(uint32_t s1 = 0; s1<nSizes; s1++){
        size = sizes[s1];
        a = malloc(sizeof(uint32_t)*size);
        memset(a, 1, size*sizeof(uint32_t));
        b = malloc(sizeof(uint32_t)*size);
        memset(b, 1, size*sizeof(uint32_t));

        for(uint32_t s2 = 0; s2<nStrides; s2++){
            stride = strides[s2];
            tempo = 0;
            for(uint32_t i = 0; i<nRun; i++){
                mytime(&inicio);
                for(uint32_t j = 0; j < size; j++)
                    a[i] = b[(j*stride)%size];
                mytime(&fim);
                tempo += (fim-inicio);
            }
            printf("size[%4.dKB], stride[%6.d]: %.15fs.\n", size/1024, stride, (tempo/nRun)/size);
        }
        free(a);
        free(b);
        printf("\n");
    }
    return 0;
}