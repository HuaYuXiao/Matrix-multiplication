#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include 'cblas.h'
#define nSize 16


static void matmul_openblas(const float * p1, const float * p2, const float * p3) {
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, nSize, nSize, nSize, 1.0f, *p1, nSize, *p2, nSize, 1.0f, *p3, nSize);
}


void print_time(int time_ms){
    printf("plain,nSize=%d,time=",nSize);
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


int main(int argc, const char * argv[]) {
    size_t total=nSize*nSize;

    static float * p1;
    p1=(float*)malloc(total*sizeof(float));
    static float * p2;
    p2=(float*)malloc(total*sizeof(float));
    static float * p3;
    p3=(float*)malloc(total*sizeof(float));

    for(int i=0;i<total;i++){
        p1[i]=(double)rand()/RAND_MAX;
        p2[i]=(double)rand()/RAND_MAX;
        p3[i]=0;
	}

    clock_t start,end;
    start = clock();
    matmul_openblas(p1, p2, p3);
    end = clock();
    int time_ms=(int)(end-start)/1000;

    print_time(time_ms);

    free(p1);
    free(p2);
    free(p3);

    return 0;
}