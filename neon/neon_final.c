#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <arm_neon.h>
#define nSize 16


void matmul_neon(float *p1, float *p2){
    static float each[nSize*nSize];
    for(size_t r_init=0;r_init<nSize;r_init++){
        for(size_t c_init=0;c_init<nSize;c_init++){       
            each[r_init*nSize+c_init]=0;
        }
    }

    for(size_t r=0;r<nSize;r++){
        for(size_t c=0;c<nSize;c++){
            for(size_t i=0;i<nSize;i++){
                float32_t * A,*B,*C;
                static float32_t * A;
                A=(float32_t*)malloc(nSize*sizeof(float32_t));
                static float32_t * B;
                B=(float32_t*)malloc(nSize*sizeof(float32_t));
                static float32_t * C;
                C=(float32_t*)malloc(nSize*sizeof(float32_t));
                }  
            }
        }
    }
}


void matmul_neon_part(float32_t * A, float32_t * B, float32_t * C){
	float32x4_t A0,A1,A2,A3;	
	float32x4_t B0,B1,B2,B3;
	float32x4_t C0,C1,C2,C3;
	
	A0 = vld1q_f32(A);
	A1 = vld1q_f32(A+4);
	A2 = vld1q_f32(A+8);
	A3 = vld1q_f32(A+12);
	
	C0 = vmovq_n_f32(0);
	C1 = vmovq_n_f32(0);
	C2 = vmovq_n_f32(0);
	C3 = vmovq_n_f32(0);
	
	B0 = vld1q_f32(B);
	C0 = vfmaq_laneq_f32(C0, A0, B0, 0);
	C0 = vfmaq_laneq_f32(C0, A1, B0, 1);
	C0 = vfmaq_laneq_f32(C0, A2, B0, 2);
	C0 = vfmaq_laneq_f32(C0, A3, B0, 3);
	vst1q_f32(C, C0);
	
	B1 = vld1q_f32(B+4);
	C1 = vfmaq_laneq_f32(C1, A0, B1, 0);
	C1 = vfmaq_laneq_f32(C1, A1, B1, 1);
	C1 = vfmaq_laneq_f32(C1, A2, B1, 2);
	C1 = vfmaq_laneq_f32(C1, A3, B1, 3);
	vst1q_f32(C+4, C1);
	
	B2 = vld1q_f32(B+8);
	C2 = vfmaq_laneq_f32(C2, A0, B2, 0);
	C2 = vfmaq_laneq_f32(C2, A1, B2, 1);
	C2 = vfmaq_laneq_f32(C2, A2, B2, 2);
	C2 = vfmaq_laneq_f32(C2, A3, B2, 3);
	vst1q_f32(C+8, C2);
	
	B3 = vld1q_f32(B+12);
	C3 = vfmaq_laneq_f32(C3, A0, B3, 0);
	C3 = vfmaq_laneq_f32(C3, A1, B3, 1);
	C3 = vfmaq_laneq_f32(C3, A2, B3, 2);
	C3 = vfmaq_laneq_f32(C3, A3, B3, 3);
	vst1q_f32(C+12, C3);
}


void print_time(int time_ms){
    printf("neon,nSize=%d,time=",nSize);
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
    matmul_neon(p1, p2);
    end = clock();
    int time_ms=(int)(double)(end-start)/1000;
    print_time(time_ms);

    free(p1);
    free(p2);
    free(p3);

    return 0;
}