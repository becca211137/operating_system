/*
Student No.: 0516222
Student Name: Fang Yu Syu
Email: becca211137@gmail.com
SE tag: xnxcxtxuxoxsx
Statement: I am fully aware that this program is not supposed to be posted to a public server, such as a public GitHub repository or a public web page. 
*/


#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <iostream>
#include <vector>
using namespace std;

struct MATRIX {
	unsigned int array[800][800];
} *matrix;

struct MATRIX2 {
	unsigned int array[800][800];
} *matrix2;

struct MATRIX3 {
	unsigned int array[800][800];
} *matrix3;

int main(){

    int  dimension, id, id2;
    cout << "Input the matrix dimension : ";
    cin >> dimension;

    id = shmget(IPC_PRIVATE, sizeof(MATRIX), IPC_CREAT | 0600);
    id2 = shmget(IPC_PRIVATE, sizeof(MATRIX2), IPC_CREAT | 0600);
    


    if( id == -1)   
        cout << "error\n";

    matrix = (struct MATRIX*)shmat(id, NULL, 0);
    matrix2 = (struct MATRIX2*)shmat(id2, NULL, 0);
    
    for(int i = 0, temp = 0; i < dimension; i++)
        for(int j = 0; j < dimension; j++) 
            matrix->array[i][j] = temp++;

    for(int i = 0, temp = 0; i < dimension; i++)
        for(int j = 0; j < dimension; j++) 
            matrix2->array[i][j] = temp++;



    for(int total_pro = 1; total_pro <= 16; total_pro++ ){
        struct timeval start, end;
		gettimeofday(&start, 0);
        int seg = dimension / total_pro;
        int id3 = shmget(IPC_PRIVATE, sizeof(MATRIX3), IPC_CREAT | 0600);
        matrix3= (struct MATRIX3*)shmat(id3, NULL, 0);
        for(int process = 1; process <= total_pro; process++ ){
            
            int pid=fork();
            if(pid == 0){
                
                int start = (process - 1) * seg;
                int end = process * seg - 1;
                if(process == total_pro)
                    end = dimension-1;
                for(int i = start; i <= end; i++){
                    for(int j = 0; j < dimension; j++){
                        for(int k = 0; k < dimension; k++)   { 
                            matrix3->array[i][j] += matrix->array[i][k] * matrix2->array[k][j];
                            //cout<<i<<" "<<j<<" "<<k<<endl;
                            //cout<<matrix3->array[i][j]<<"+=" <<matrix->array[i][k]<<"*" <<matrix2->array[k][j]<<endl;
                        }
                    }
                }
                shmdt(matrix3);
                return 0;
            }

        }
        for(int process = 1; process <= total_pro; process++ )
		{
			wait(NULL);
		}

        cout<<"Multiplying matrices using "<<total_pro<<( (total_pro==1)?" process":" processes")<<endl;

        
        gettimeofday(&end, 0);
        double sec = end.tv_sec - start.tv_sec;
		double usec = end.tv_usec - start.tv_usec;
        
        unsigned int sum = 0;
        for(int i = 0, temp = 0; i < dimension; i++)
            for(int j = 0; j < dimension; j++) 
                sum += matrix3->array[i][j];    
        cout << "Elapsed time: " << sec + (usec / 1000000.0) <<" sec, Checksum: "<<sum<<endl;

                
    }
    shmdt(matrix);
    shmdt(matrix2);
	shmctl(id, IPC_RMID, NULL);      
    shmctl(id2, IPC_RMID, NULL);    
    return 0;
}