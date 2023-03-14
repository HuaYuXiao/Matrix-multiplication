#include <stdio.h> //预处理命令，基本的输入输出函数库
#include <stdlib.h>//随机函数rand()所在库
#include <time.h>
#include <stdio.h>
#include <arm_neon.h>


void matmul_plain(const float *p1, const float * p2, size_t nSize){
    float each[nSize*nSize];
    for(size_t i=0;i<nSize*nSize;i++){
        each[i]=0.f;
    }
}


void matmul_unloop(const float *p1, const float * p2, size_t nSize){
    float sum = 0.0f;
    for (size_t i = 0; i < nSize; i+=8){
        sum += (p1[i] * p2[i]);
        sum += (p1[i+1] * p2[i+1]);
        sum += (p1[i+2] * p2[i+2]);
        sum += (p1[i+3] * p2[i+3]);
        sum += (p1[i+4] * p2[i+4]);
        sum += (p1[i+5] * p2[i+5]);
        sum += (p1[i+6] * p2[i+6]);
        sum += (p1[i+7] * p2[i+7]);
    }

}


void matmul_neon(const float *p1, const float * p2, size_t nSize){
    float sum[4] = {0};
    float32x4_t a, b;
    float32x4_t c = vdupq_n_f32(0);

    for (size_t i = 0; i < nSize; i+=4){
        a = vld1q_f32(p1 + i);
        b = vld1q_f32(p2 + i);
        c =  vaddq_f32(c, vmulq_f32(a, b));
    }
    vst1q_f32(sum, c);
    return;
}


// void matmul_omp(const float *p1, const float * p2, size_t nSize){
//     if(nSize % 4 != 0){
//         printf("The size nSize must be a multiple of 4.");
//         return;
//     }

//     float sum[4] = {0};
//     float32x4_t a, b;
//     float32x4_t c = vdupq_n_f32(0);

//     #pragma omp parallel for
//     for (size_t i = 0; i < nSize; i+=4)
//     {
//         a = vld1q_f32(p1 + i);
//         b = vld1q_f32(p2 + i);
//         c =  vaddq_f32(c, vmulq_f32(a, b));
//     }
//     vst1q_f32(sum, c);
//     return;
// }


int main(int argc, char ** argv){   

    size_t nSize = argc;
    size_t total_element=nSize*nSize;

    float * p1;
    p1=(float*)malloc(total_element*sizeof(float));
    float * p2;
    p2=(float*)malloc(total_element*sizeof(float));

    for(int i=0;i<total_element;i++){
		p1[i]=(double)rand()/RAND_MAX;
        p2[i]=(double)rand()/RAND_MAX;
	}

    clock_t start,end;

    start = clock();
    matmul_plain(p1, p2, nSize);
    end = clock();
    printf("plain,time=%f\n",(double)end-start/CLOCKS_PER_SEC);

    // start = clock();
    // matmul_unloop(p1, p2, nSize);
    // end = clock();
    // printf("unloop,time=%f\n",(double)end-start/CLOCKS_PER_SEC);

    // start = clock();
    // matmul_neon(p1, p2, nSize);
    // end = clock();
    // printf("SIMD,time=%f\n",(double)end-start/CLOCKS_PER_SEC);

    // start = clock();
    // matmul_omp(p1, p2, nSize);
    // end = clock();
    // printf("OpenMP,time=%f\n",(double)end-start/CLOCKS_PER_SEC);

    free(p1);
    free(p2);

    return 0;
}