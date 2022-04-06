#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "cuda.h"
#include <cuda_runtime_api.h>

#include<stdio.h>
#include <cmath>
#include<stdlib.h>
#include<iostream>
#include <iomanip>

#include <stdio.h>

using namespace std;
typedef unsigned int uint;



static const int wholeArraySize = 4;
static const int blockSize = 1024;
static const int gridSize = 2;

__device__ bool lastBlock(int* counter) {
    __threadfence(); //ensure that partial result is visible by all blocks
    int last = 0;
    if (threadIdx.x == 0)
        last = atomicAdd(counter, 1);
    return __syncthreads_or(last == gridDim.x - 1);
}

__global__ void sumCommMultiBlock(
    int start, 
    int end, 
    int target, 
    int* gOut, 
    int* lastBlockCounter){

    int thIdx = threadIdx.x;
    int gthIdx = thIdx + blockIdx.x * blockSize;
    const int gridSize = blockSize * gridDim.x;

    int sum = 0;
    for (int i = gthIdx; i < end; i += gridSize)

        if (i = target) 
            sum += target;



    __shared__ int shArr[blockSize];
    shArr[thIdx] = sum;
    __syncthreads();
    for (int size = blockSize / 2; size > 0; size /= 2) { //uniform
        if (thIdx < size)
            shArr[thIdx] += shArr[thIdx + size];
        __syncthreads();
    }
    if (thIdx == 0)
        gOut[blockIdx.x] = shArr[0];
    if (lastBlock(lastBlockCounter)) {
        shArr[thIdx] = thIdx < gridSize ? gOut[thIdx] : 0;
        __syncthreads();
        for (int size = blockSize / 2; size > 0; size /= 2) { //uniform
            if (thIdx < size)
                shArr[thIdx] += shArr[thIdx + size];
            __syncthreads();
        }
        if (thIdx == 0)
            gOut[0] = shArr[0];
    }
}

int sumArray(int* arr) {
    int* dev_arr;

    //cout << "start alloc" << endl;
    cudaMalloc((void**)&dev_arr, wholeArraySize * sizeof(int));
    cudaMemcpy(dev_arr, arr, wholeArraySize * sizeof(int), cudaMemcpyHostToDevice);

    int target;
    //cudaMalloc((void**)&target, sizeof(int));
    //cudaMemcpy(target, 10, sizeof(int), cudaMemcpyHostToDevice);

    int out;
    int* dev_out;
    cudaMalloc((void**)&dev_out, sizeof(int) * gridSize);

    int* dev_lastBlockCounter;
    cudaMalloc((void**)&dev_lastBlockCounter, sizeof(int));
    cudaMemset(dev_lastBlockCounter, 0, sizeof(int));

    sumCommMultiBlock << <gridSize, blockSize >> > (0, 2048, 10, dev_out, dev_lastBlockCounter);
    cudaDeviceSynchronize();

    cudaMemcpy(&out, dev_out, sizeof(int), cudaMemcpyDeviceToHost);
    cudaFree(dev_arr);
    cudaFree(dev_out);

    return out;
}


int main() {

    const int arraySize = 4;
    int a[arraySize] = { 1,  2,  3,  4 };


    cout << sumArray(a) << endl;
}

