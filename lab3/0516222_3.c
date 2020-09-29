/*
Student No.: 0516222
Student Name: Fang Yu Syu
Email: becca211137@gmail.com
SE tag: xnxcxtxuxoxsx
Statement: I am fully aware that this program is not supposed to be posted to a public server, such as a public GitHub repository or a public web page. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>
#include <math.h>

int total, data[1000010],ans[1000010];
int pivot_index[8];
int first[20], last[20];
sem_t mul_thread[16],bubble_thread[16],mul_finish,mul_merge[16];
int array1[1000010];

void *step1(void *temp);

void merge(int temp){
    int id = temp;
    int array[1000010];
    int i = first[id*2];
    int j = first[id*2+1];

    for(int t = first[id*2]; t<=last[id*2+1];t++){
        if(i>last[id*2]){
            for(int t1 = j;t1<=last[id*2+1];t++,t1++)
                ans[t] = array1[t1];
            break;
        }
        if(j>last[id*2+1]){
            for(int t2 = i; t2<=last[id*2];t++,t2++)
                ans[t] = array1[t2];
            break;
        }
        if(i<=last[id*2]&&array1[i]<=array1[j]){
            ans[t] = array1[i];
            i++;
        }
        else{
            ans[t] = array1[j];
            j++;
        }
    }
    for(int t = first[id*2]; t<=last[id*2+1];t++)
            array1[t] = ans[t];


}

void divide(int temp){
    int id = temp;
    if(id==1)
        return;
    if(id%2 == 1){
        id--;
        last[id+1] = last[id/2];
        first[id+1] = last[id/2] - ceil((last[id/2]-first[id/2])/2+1)+1;
    }
    else{
        first[id] = first[id/2];
        last[id] = first[id/2]+floor((last[id/2] - first[id/2]+1)/2)-1;
    }
}


void bubble_sort(int id, int left, int right){
    int i = left;
    int j = right;
    int length = right - left + 1;
    if(i <= j){
        for(int x = 0; x<length;x++){
            for(int y=left; y<right-x; y++){
                if(array1[y] > array1[y+1]){
                    int temp = array1[y];
                    array1[y] = array1[y+1];
                    array1[y+1] = temp;
                }
            }
        }
    }
    else
        return;

}


void *step1(void *temp){
    int id =  (long)temp;
    if( id == 1){
        sem_wait(&mul_thread[id]);
        divide(id);
        sem_post(&mul_thread[id * 2]);
        sem_post(&mul_thread[id * 2 + 1]);
        sem_wait(&mul_merge[id * 2]); 
        sem_wait(&mul_merge[id * 2+1]);   
        merge(id);
        sem_post(&mul_finish);

    }
    else if(id<=7){
        sem_wait(&mul_thread[id]);
        divide(id);
        sem_post(&mul_thread[id * 2]);
        sem_post(&mul_thread[id * 2 + 1]);
        sem_wait(&mul_merge[id * 2]); 
        sem_wait(&mul_merge[id * 2+1]); 
        merge(id);
        sem_post(&mul_merge[id]);
    }
    else{
        sem_wait(&mul_thread[id]);
        divide(id);
        bubble_sort(id, first[id], last[id]);
        sem_post(&mul_merge[id]);
    }

}

int main(){
    FILE *fp;
	char filename[200];	
	printf("input filename please : ");
	scanf("%s", filename);

	fp = fopen(filename, "r");
	fscanf(fp, "%d", &total);
	for(int i=0; i < total; i++) {
		fscanf(fp, "%d", &data[i]);
	}
	fclose(fp);

   first[1] = 0;
   last[1] = total-1;


    struct timeval start, end;

//multi
    
    
    pthread_t thread_id[16];
    sem_init(&mul_finish, 0, 0);
    int temp[16];
    for(int i=0;i<16;i++)
        temp[i] = i;
   for(int i = 0; i < total; i++)
       array1[i] = data[i];

    for(int i = 0; i <= 15; i++)
        sem_init(&mul_thread[i], 0, 0);

    for(int i = 0; i <= 15; i++)
        sem_init(&mul_merge[i], 0, 0);

    for(int i = 1; i <= 15; i++){
        if(pthread_create(&thread_id[i], NULL, step1, (void*)i)!=0)
            printf("error\n");
    }

    gettimeofday(&start, 0);
    sem_post(&mul_thread[1]);
    sem_wait(&mul_finish);
    gettimeofday(&end, 0);
    double sec = end.tv_sec - start.tv_sec;
	double usec = end.tv_usec - start.tv_usec;
    printf("MT sorting time : %lf\n",sec+(usec/100000.0));
    fp = fopen("output1.txt", "w");
	for(int i=0; i<total; i++) {
		fprintf(fp, "%d ", array1[i]);
        
	}
    fclose(fp);

 //single
    gettimeofday(&start, 0);   
    for(int i = 0; i < total; i++)
        array1[i] = data[i];
    first[1] = 0;
    last[1] = total - 1;

    for(int i = 1; i <= 15; i++)
        divide(i);
    for(int i=8;i<=15;i++)
        bubble_sort(i,first[i],last[i]);
    for(int j = 7; j>= 1; j--)
        merge(j);
    gettimeofday(&end, 0);
    sec = end.tv_sec - start.tv_sec;
	usec = end.tv_usec - start.tv_usec;
    printf("ST sorting time : %lf\n",sec+(usec/100000.0));
    fp = fopen("output2.txt", "w");
	for(int i=0; i<total; i++) {
		fprintf(fp, "%d ", array1[i]);
	}
    fclose(fp);

    return 0;

}