#include <stdio.h> //预处理命令，基本的输入输出函数库
#include <stdlib.h>//随机函数rand()所在库
#include <time.h>
#include <arm_neon.h>


void matmul_neon(const float *p1, const float * p2, size_t nSize){
    float each[nSize*nSize];
    for(size_t r_init=0;r_init<nSize;r_init++){
        for(size_t c_init=0;c_init<nSize;c_init++){           
            each[r_init*nSize+c_init]=0;
        }
    }

    float32x4_t a, b;
    float32x4_t c = vdupq_n_f32(0);
    float sum[4] = {0};
    for(size_t r=0;r<nSize;r++){
        for(size_t c=0;c<nSize;c++){
            for(size_t i=0;i<nSize;i+=4){
                a = vld1q_f32(p1 + r*nSize+i);
                b = vld1q_f32(p2 + c+i*nSize);
                c = vaddq_f32(c, vmulq_f32(a, b));
            }
            vst1q_f32(sum, c);
            each[r*nSize+c]+=(sum[0]+sum[1]+sum[2]+sum[3]);
        }
    }
}


int main(int argc, char ** argv){   
    size_t nSize = argc;
    size_t total_element=nSize*nSize;

    float * p1;
    p1=(float*)malloc(total_element*sizeof(float));
    float * p2;
    p2=(float*)malloc(total_element*sizeof(float));

    for(int i=0;i<total_element;i++){
        p1[i]=1;
        p2[i]=1;
	}

    clock_t start,end;
    double time_db;
    int time_int;

    start = clock();
    matmul_neon(p1, p2, nSize);
    end = clock();
    // time_db=(double)(end-start)/CLOCKS_PER_SEC;
    time_db=(double)(end-start)/1000;
    time_int=(int)time_db;
    printf("neon,\ttime=%dms\n",time_int);

    free(p1);
    free(p2);

    return 0;
}