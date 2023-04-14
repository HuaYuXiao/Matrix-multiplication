//预处理命令，基本的输入输出函数库
#include <stdio.h>
//随机函数rand()所在库
#include <stdlib.h>
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

void matmul_omp(const float *p1, const float * p2, size_t nSize){
    if(nSize % 4 != 0){
        printf("The size nSize must be a multiple of 4.");
        return;
    }

    float sum[4] = {0};
    float32x4_t a, b;
    float32x4_t c = vdupq_n_f32(0);

    #pragma omp parallel for
    for (size_t i = 0; i < nSize; i+=4)
    {
        a = vld1q_f32(p1 + i);
        b = vld1q_f32(p2 + i);
        c =  vaddq_f32(c, vmulq_f32(a, b));
    }
    vst1q_f32(sum, c);
    return;
}
