//预处理命令，基本的输入输出函数库
#include <stdio.h>
//随机函数rand()所在库
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <arm_neon.h>

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

    start = clock();
    matmul_unloop(p1, p2, nSize);
    end = clock();
    printf("unloop,time=%f\n",(double)end-start/CLOCKS_PER_SEC);

    start = clock();
    matmul_neon(p1, p2, nSize);
    end = clock();
    printf("SIMD,time=%f\n",(double)end-start/CLOCKS_PER_SEC);

    start = clock();
    matmul_omp(p1, p2, nSize);
    end = clock();
    printf("OpenMP,time=%f\n",(double)end-start/CLOCKS_PER_SEC);

    free(p1);
    free(p2);

    return 0;
}
