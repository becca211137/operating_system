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

int total, data[1000010],ans[1000010],total_thread;
int first[20], last[20];
sem_t mul_thread[23],bubble_thread[23],mul_finish,mul_merge[23];
int array1[1000010];
sem_t list, count, pool[8];


struct Job_list{
    int job_id;
    struct Job_list *next;
}*head,*tail;

typedef struct Job_list Job_list;

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


void bubble_sort(int id){
    // printf("bubble id %d\n",id);
    int i = first[id];
    int j = last[id];
    int length = last[id] - first[id] + 1;
    if(i <= j){
        for(int x = 0; x<length;x++){
            for(int y=first[id]; y<last[id]-x; y++){
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

void add_job(int id) {
    if(head == NULL){
        head = (Job_list *)malloc(sizeof(Job_list));		
		head->job_id = id;
		head->next = NULL;
		tail = head;
    }
    else{
        Job_list *j = (Job_list *)malloc(sizeof(Job_list));	
		j->job_id = id;
		j->next = NULL;
		tail->next = j;
		tail = tail->next;

    }

}

void *step1(void *temp){

    int id =  (long)temp;
    while(1){

        sem_wait(&pool[id]);
        sem_wait(&count);
        sem_wait(&list);
        Job_list *temp = head;
        int job_id = head->job_id;
        head = head->next;
        free(temp);
        sem_post(&list);

        //0~7 work divide
        if( job_id <= 7){
            divide(job_id);
            sem_wait(&list);
            add_job(2*job_id);
            add_job(2*job_id+1);
            sem_post(&list);
            sem_post(&count);
            sem_post(&count);
        }
        //8~15 bubble sort
        else if(job_id <=15){
            divide(job_id);
            bubble_sort(job_id);
            sem_post(&bubble_thread[job_id]);
            //如果兩個bubble都做完就add新job
            if(job_id%2 == 1){
               int temp;
               sem_getvalue(&bubble_thread[job_id-1],&temp);
               if(temp==1){
                   sem_wait(&list);
                   add_job((job_id-1)/2+12);
                   sem_post(&list);
                   sem_post(&count);
               }
            }
            else{
                int temp1;
                sem_getvalue(&bubble_thread[job_id+1],&temp1);
                if(temp1==1){
                   sem_wait(&list);
                   add_job(job_id/2+12);
                   sem_post(&list);
                   sem_post(&count);
               }
                
            }
            
        }
        //16~22 merge
        else{
            switch(job_id){
                case 16:
                    merge(4);
                    sem_post(&mul_merge[16]);
                    int temp1;
                    sem_getvalue(&mul_merge[17],&temp1);
                    if(temp1==1){
                        sem_wait(&list);
                        add_job(20);
                        sem_post(&list);
                        sem_post(&count);
                    }                    
                    break;
                case 17:
                    merge(5);
                    sem_post(&mul_merge[17]);
                    int temp2;
                    sem_getvalue(&mul_merge[16],&temp2);
                    if(temp2==1){
                        sem_wait(&list);
                        add_job(20);
                        sem_post(&list);
                        sem_post(&count);
                    }  
                    break;
                case 18:
                    merge(6);
                    sem_post(&mul_merge[18]);
                    int temp3;
                    sem_getvalue(&mul_merge[19],&temp3);
                    if(temp3==1){
                        sem_wait(&list);
                        add_job(21);
                        sem_post(&list);
                        sem_post(&count);
                    }  
                    break;
                case 19:
                    merge(7);
                    sem_post(&mul_merge[19]);
                    int temp4;
                    sem_getvalue(&mul_merge[18],&temp4);
                    if(temp4==1){
                        sem_wait(&list);
                        add_job(21);
                        sem_post(&list);
                        sem_post(&count);
                    }  
                    break; 
                case 20:
                    merge(2);
                    sem_post(&mul_merge[20]);
                    int temp5;
                    sem_getvalue(&mul_merge[21],&temp5);
                    if(temp5==1){
                        sem_wait(&list);
                        add_job(22);
                        sem_post(&list);
                        sem_post(&count);
                    }  
                    break; 
                case 21:
                    merge(3);
                    sem_post(&mul_merge[21]);
                    int temp6;
                    sem_getvalue(&mul_merge[20],&temp6);
                    if(temp6==1){
                        sem_wait(&list);
                        add_job(22);
                        sem_post(&list);
                        sem_post(&count);
                    }  
                    break;
                case 22:
                    merge(1);
                    sem_post(&mul_finish);
                    break;          
            }

        }
        sem_post(&pool[id]);
    }
}

int main(){
    //read data
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
    //set initial data
    pthread_t thread_id[8];
    struct timeval start, end;
    sem_init(&list,0,1);
    sem_init(&count,0,0);
    for(int i=0;i<8;i++)
        sem_init(&pool[i],0,0);
    
    total_thread = 1;
    //create all thread
    for(int i = 0; i <= 7; i++){
        if(pthread_create(&thread_id[i], NULL, step1, (void*)i)!=0)
            printf("error\n");
    }
    first[1] = 0;
    last[1] = total-1;
    for(;total_thread<=8;total_thread++){
        gettimeofday(&start, 0);
        //reset array
        for(int i = 0; i < total; i++)
            array1[i] = data[i];
        
        //bubble做完會變1
        
        for(int i=8;i<=15;i++)
            sem_init(&bubble_thread[i],0,0);
        for(int i = 16; i <= 22; i++)
            sem_init(&mul_merge[i], 0, 0);
        sem_init(&mul_finish,0,0);
        //add first job
        sem_wait(&list);
        head = NULL;
        
        add_job(1);
        sem_post(&list);
        sem_post(&count);
        sem_post(&pool[total_thread-1]);

        sem_wait(&mul_finish);
        gettimeofday(&end, 0);
        double sec = end.tv_sec - start.tv_sec;
        double usec = end.tv_usec - start.tv_usec;
        printf("%d thread sorting time : %lf\n",total_thread,sec+(usec/1000000.0));

        FILE *f;
        char output[200];
        sprintf(output,"output_%d.txt",total_thread);
        f = fopen(output, "w");
        for(int i=0; i<total; i++) {
            fprintf(f, "%d ", array1[i]);
        }
        fclose(f);
    }
    return 0;

}