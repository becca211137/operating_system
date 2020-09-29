/*
Student No.: 0516222
Student Name: Fang Yu Syu
Email: becca211137@gmail.com
SE tag: xnxcxtxuxoxsx
Statement: I am fully aware that this program is not supposed to be posted to a public server, such as a public GitHub repository or a public web page. 
*/

#include <iostream>
#include <stdio.h>
#include <sys/time.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <sstream>
using namespace std;
#define mb 1048576;

long node;
char name[1000];
long size_max, size_min;
bool input_inode = false, input_name = false, input_min = false, input_max = false;

void find(string dirname) {

  	DIR *dir;
	struct dirent *dirp;
    struct stat st;
	dir = opendir(dirname.c_str());

	while((dirp = readdir(dir)) != NULL) {
		if(strcmp(dirp->d_name, ".") != 0 && strcmp(dirp->d_name, "..") != 0) {
            
            string file = dirname + "/" + dirp->d_name;
            int print = 1;                    
            stat(file.c_str(), &st);
            double filesize = 0;
            filesize = (double) st.st_size / (double) mb;
            
            if(input_inode && st.st_ino != node)					
                print = 0;
            if(input_name && strcmp(dirp->d_name, name) != 0)		
                print = 0;
            if(input_min && filesize < size_min)	
                print= 0;
            if(input_max && filesize > size_max)	
                print = 0;

            time_t rawtime;
            time (&rawtime);          
            
            if(print == 1) {
                printf("%s  %lu  %lf MB %s", file.c_str(), st.st_ino, filesize, ctime(&rawtime));
            }	

            switch (st.st_mode & S_IFMT) {
                case S_IFDIR:  
                    find(file);
                break;
            }
        }
        		
	}

}

int main(int argc, char **argv) {

	for(int i=2; i<argc; i+=2) {	
		if(strcmp(argv[i], "-name") == 0) {
            input_name = true;
            strcpy(name,argv[i+1]);
		}
        else if(strcmp(argv[i], "-size_min") == 0) {			
            input_min = true;    
            string str=argv[i+1];
            istringstream is(str);
            is>>size_min;			
		}
		else if(strcmp(argv[i], "-inode") == 0) {
			input_inode = true;            
            string str=argv[i+1];
            istringstream is(str);
            is>>node;
		}

		else if(strcmp(argv[i], "-size_max") == 0) {
            input_max = true;
            string str=argv[i+1];
            istringstream is(str);
            is>>size_max;
		}
	}

	find(string(argv[1]));
	
	return 0;
}