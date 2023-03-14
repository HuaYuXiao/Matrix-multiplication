#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <arm_neon.h>
#include <omp.h>
#define nSize 8000


void matmul_openmp(const float *p1, const float * p2){
    static float each[nSize*nSize];
    for(size_t r=0;r<nSize;r++){
        for(size_t c=0;c<nSize;c++){
            each[r*nSize+c]=0;
            for(size_t i=0;i<nSize;i++){
                each[r*nSize+c]+=p1[r*nSize+i]*p2[c+i*nSize];              
            }
        }
    }
}


void print_time(int time_ms){
    printf("openmp,nSize=%d,time=",nSize);
    int time_s=time_ms/1000;
    if(time_ms<1000){
        printf("%dms\n",time_ms);
    }else if(time_s<60){
        printf("%ds\n",time_s);
    }else{
        int time_m_part=time_s/60;
        int time_s_part=time_s%60;
        printf("%dm%ds\n",time_m_part,time_s_part);
    }
}


int main(int argc, char ** argv){ 
    size_t total_element=nSize*nSize;

    static float * p1;
    p1=(float*)malloc(total_element*sizeof(float));
    static float * p2;
    p2=(float*)malloc(total_element*sizeof(float));

    for(int i=0;i<total_element;i++){
        p1[i]=(double)rand()/RAND_MAX;
        p2[i]=(double)rand()/RAND_MAX;
	}

    clock_t start,end;
    start = clock();
    #pragma omp parallel for
    matmul_openmp(p1, p2);
    end = clock();
    int time_ms=(int)(double)(end-start)/1000;
    print_time(time_ms);

    free(p1);
    free(p2);

    return 0;
}