/*  Ashwin
 *  Jadhav
 *  ajadhav5/50405435
 */

#ifndef A0_HPP
#define A0_HPP

#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <random>
#include <vector>
#include <omp.h>

using namespace std;

float mat_mul(float Sub[], std::vector<float> Kernel);

void filter_2d(int n, int m, const std::vector<float>& Kernel, std::vector<float>& A) {

  std::vector<float> Z((n * m),0);


  size_t i = m+1;
  #pragma omp parallel shared(A) private(i)
  {
    #pragma omp for nowait
    {
      for (i = (m+1); i < (A.size()-m-1); i++){
        int c = 0;
        if ((i % m != 0) && ((i+1) % m != 0)){
          float *Sub = new float[9]();
          int count = 0;
          for (size_t j = (i-m-1); j < (i+m+2); j++){
            if (count == 3){
              j += (m-3-1);
              count = 0;
              continue;
            }
            Sub[c++] = A[j];
            count++;
          }
          Z[i] = mat_mul(Sub, Kernel);
        }
      }
    }
  }

  //Resultant Matrix Z
  for(size_t i = m+1; i <= (A.size()-m-1); i++){
    if((i % m != 0) && (i % m != 1)) {
      A[i-1] = Z[i];
    }
  }

}

 // filter_2d

float mat_mul(float Sub[], std::vector<float> Kernel){

std::vector<float> S((9),0.0);

float sum = 0.0;

#pragma omp parallel shared(sum)
{
  #pragma omp for nowait //reduction(+ \: sum)
  {
    for (int i = 0; i < 9; i+=3){
      for (int j = 0; j < 3; j++){
        int mul = j;
        for (int k = i; k < i + 3; k++){
          sum += Sub[k] * Kernel[mul];
          mul += 3;
        }
      }
    }
  }
}

//cout<<sum<<endl;
return sum;
}


#endif // A0_HPP
