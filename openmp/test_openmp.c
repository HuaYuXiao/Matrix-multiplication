#include <stdio.h> //预处理命令，基本的输入输出函数库
#include <stdlib.h>//随机函数rand()所在库
#include <time.h>


void matmul_openmp(const float *p1, const float * p2, size_t nSize){
    float each[nSize*nSize];
    for(size_t r_init=0;r_init<nSize;r_init++){
        for(size_t c_init=0;c_init<nSize;c_init++){           
            each[r_init*nSize+c_init]=0;
        }
    }

    for(size_t r=0;r<nSize;r++){
        for(size_t c=0;c<nSize;c++){
            for(size_t i=0;i<nSize;i++){
                each[r*nSize+c]+=p1[r*nSize+i]*p2[c+i*nSize];              
            }
        }
    }

}


int main(int argc, char ** argv){ 
    size_t nSize = atoi(argv[1]);
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
    start = clock();
    //openmp方法与plain方法的唯一区别在于这句话，启用了并行计算
    #pragma omp parallel for
    matmul_openmp(p1, p2, nSize);
    end = clock();
    int time_ms=end-start;
    if(time_ms<1000){
        printf("openmp,%dms\n",time_ms);
    }else{
        int time_s=time_ms/CLOCKS_PER_SEC;
        printf("openmp,%ds\n",time_s);
    }

    free(p1);
    free(p2);

    return 0;
}