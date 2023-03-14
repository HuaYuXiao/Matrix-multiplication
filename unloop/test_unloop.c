#include <stdio.h> //预处理命令，基本的输入输出函数库
#include <stdlib.h>//随机函数rand()所在库
#include <time.h>


void matmul_unloop(const float *p1, const float * p2, size_t nSize){
    //必须确保矩阵的行列大小为8的倍数，这里我注释掉了
    // if(nSize % 8 != 0){
    //     std::cerr << "The size n must be a multiple of 8." <<std::endl;
    //     return;
    // }
    float each[nSize*nSize];
    for(size_t r_init=0;r_init<nSize;r_init++){
        for(size_t c_init=0;c_init<nSize;c_init++){           
            each[r_init*nSize+c_init]=0;
        }
    }

    for(size_t r=0;r<nSize;r++){
        for(size_t c=0;c<nSize;c++){
            for(size_t i=0;i<nSize;i+=8){
                //一次性计算8次乘法运算，然后再加起来
                each[r*nSize+c]+=p1[r*nSize+i]*p2[c+i*nSize];
                each[r*nSize+c]+=p1[r*nSize+i+1]*p2[c+(i+1)*nSize];
                each[r*nSize+c]+=p1[r*nSize+i+2]*p2[c+(i+2)*nSize];
                each[r*nSize+c]+=p1[r*nSize+i+3]*p2[c+(i+3)*nSize];
                each[r*nSize+c]+=p1[r*nSize+i+4]*p2[c+(i+4)*nSize];
                each[r*nSize+c]+=p1[r*nSize+i+5]*p2[c+(i+5)*nSize];
                each[r*nSize+c]+=p1[r*nSize+i+6]*p2[c+(i+6)*nSize];
                each[r*nSize+c]+=p1[r*nSize+i+7]*p2[c+(i+7)*nSize];
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
        p1[i]=(double)rand()/RAND_MAX;
        p2[i]=(double)rand()/RAND_MAX;
	}

    clock_t start,end;
    start = clock();
    matmul_unloop(p1, p2, nSize);
    end = clock();
    int time_ms=end-start;
    if(time_ms<1000){
        printf("unloop,%dms\n",time_ms);
    }else{
        int time_s=time_ms/CLOCKS_PER_SEC;
        printf("unloop,%ds\n",time_s);
    }

    free(p1);
    free(p2);

    return 0;
}