#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//宏定义数组大小
#define nSize 1000


void matmul_plain(const float * p1, const float * p2){
    static float each[nSize*nSize];
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
            //这段话是为了观察计算进度
            // float sequence=(float)r*nSize+c;
            // float total=(float)nSize*nSize;
            // float percent=sequence/total*100;
            // printf("%luth,%.2f%c\n",r*nSize+c,percent,'%');
        }
    }
}


void print_time(int time_ms){
    //如果时间较短，用毫秒作单位，否则用秒,超过60秒改用分钟
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


int main(){ 
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
    matmul_plain(p1, p2);
    end = clock();
    int time_ms=(int)(end-start)/1000;

    print_time(time_ms);

    free(p1);
    free(p2);

    return 0;
}