/*  Ashwin Panditrao
 *  Jadhav
 *  ajadhav5
 */

#include <memory>
#include <algorithm>
#include <cuda_runtime_api.h>
#include <math.h>
#include <iostream>
#include <functional>

#ifndef A3_HPP
#define A3_HPP

using namespace std;

__global__ void compute_gaussian_kde(float *d_x , float *d_y , int n, float h);

void gaussian_kde(int n, float h, const std::vector<float>& x, std::vector<float>& y) {

    float *d_x;
    float *d_y;
    int size = n*sizeof(float);
    
    int numThreads = 1024;
    int numBlocks = (n + numThreads - 1) / numThreads;
    
    dim3 d_numThreads(numThreads);
    dim3 d_numBlocks(numBlocks);

    cudaMalloc(&d_x, size);
    cudaMalloc(&d_y, size);

    cudaMemcpy(d_x, x.data(), size, cudaMemcpyHostToDevice);
    
    compute_gaussian_kde<<<d_numBlocks , d_numThreads>>>(d_x, d_y, n, h);
    
    cudaMemcpy(y.data(), d_y, size, cudaMemcpyDeviceToHost);
    
    // testing for lower values data
    /*for(int i=0; i < n; i++){
        cout<<d_y<<" ";
    }*/
    
    cudaFree(d_x);
    cudaFree(d_y);
} // gaussian_kde

__global__ void compute_gaussian_kde(float *d_x , float *d_y , int n, float h)
{
    float sum=0;
    extern __shared__ float data[];
    float sqrt_pi = (1 / sqrt(2 * 3.14));

    int ind = threadIdx.x+blockIdx.x*blockDim.x;
    data[ind] = d_x[ind];
    
    __syncthreads();
    
    if(ind < n){
        for(int i = 0;i < n;i++){
            sum = sum + (((sqrt_pi)) * exp(-(((d_x[ind] - data[i])/h) * (d_x[ind] - data[i])/2)));
        }
        d_y[ind] = sum/(n * h);
    }
}
#endif // A3_HPP
