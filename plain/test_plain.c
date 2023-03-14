#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void matmul_plain(const float *p1, const float * p2, size_t nSize){
    float each[nSize*nSize];

    // memset(each,0,sizeof(each));
    for(size_t r_init=0;r_init<nSize;r_init++){
        for(size_t c_init=0;c_init<nSize;c_init++){ 
            // 初始化结果矩阵为全0          
            each[r_init*nSize+c_init]=0;
        }
    }

    for(size_t r=0;r<nSize;r++){
        for(size_t c=0;c<nSize;c++){
            for(size_t i=0;i<nSize;i++){
                //用一维数列表示矩阵乘法有点麻烦
                each[r*nSize+c]+=p1[r*nSize+i]*p2[c+i*nSize];    
            }
        }
    }

}


int main(int argc, char ** argv){ 
    //用命令行输入的方式确定矩阵的行列大小
    size_t nSize = atoi(argv[1]);
    size_t total_element=nSize*nSize;

    //用malloc分配两个矩阵内存
    float * p1;
    p1=(float*)malloc(total_element*sizeof(float));
    float * p2;
    p2=(float*)malloc(total_element*sizeof(float));

    for(int i=0;i<total_element;i++){
        //两个矩阵内所有元素均为0到1之间的随机数
        p1[i]=(double)rand()/RAND_MAX;
        p2[i]=(double)rand()/RAND_MAX;
	}

    clock_t start,end;
    start = clock();
    matmul_plain(p1, p2, nSize);
    end = clock();
    int time_ms=end-start;
    //如果时间较短，用ms作单位，否则用s
    if(time_ms<1000){
        printf("plain,%dms\n",time_ms);
    }else{
        int time_s=time_ms/CLOCKS_PER_SEC;
        printf("plain,%ds\n",time_s);
    }

    //释放内存
    free(p1);
    free(p2);

    return 0;
}