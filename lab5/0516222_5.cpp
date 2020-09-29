/*
Student No.: <0516222>
Student Name: <Fang Yu Syu>
Email: <becca211137@gmail.com>
SE tag: xnxcxtxuxoxsx
Statement: I am fully aware that this program is not 
supposed to be posted to a public server, such as a 
public GitHub repository or a public web page.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <sys/time.h>
#include <bits/stdc++.h> 
#include <stdio.h>
#include <stdlib.h>
using namespace std;


int input[50000000];

int main(int argc,char **argv){
    int total=0;    
    FILE *fp;
    fp = fopen(argv[1], "r");
    if(fp==NULL)
        cout<<"error"<<endl;
    while(1){
        if(fscanf(fp,"%d",&input[total])==EOF)
            break;
        total++;
    }
    struct timeval start, end;
    
    cout<<"LFU policy:"<<endl;
    cout<<"frame\thit\t\tmiss\t\tpage fault ratio\n";
    
    gettimeofday(&start, 0);
    for(int frame_num = 128; frame_num<=1024; frame_num *= 2){
        int miss = 0, hit = 0;
        int min = 1;
        int stamp[9000];
        unordered_map<int, list<int>::iterator> iter;
        unordered_map<int, list<int>> freq;
        unordered_map<int, int> map;
        for(int i=0; i < total; i++){
            int target = input[i];
            //miss, table is available
            if(map.find(target)==map.end()&&map.size() < frame_num){
                miss++;
                map[target] = 1;
                min = 1;
                freq[1].push_front(target);
                iter[target] = freq[1].begin();
                stamp[target] = i;
            }
            // miss, table is full 
            else if(map.find(target)==map.end()&&map.size() == frame_num){
                miss++;
                int discard_target = freq[min].front();
                //find which to discard
                for(list<int>::iterator temp = freq[min].begin(); temp!=freq[min].end(); temp++){
                    if(stamp[*temp] < stamp[discard_target])
                        discard_target = *temp;
                }
                //erase 
                freq[min].erase(iter[discard_target]);
                map.erase(discard_target);
                iter.erase(discard_target);
                stamp[discard_target] = 10000;
                //add
                map[target] = 1;
                min = 1;
                freq[1].push_front(target);
                iter[target] = freq[1].begin();
                stamp[target] = i; 
            }
            // hit
            else{
                hit++;
                freq[map[target]].erase(iter[target]);
                map[target]++;
                freq[map[target]].push_front(target);
                iter[target] = freq[map[target]].begin();
                if(freq[min].size()==0)
                    min++;                
            }
        }  
        cout<<frame_num<<"\t"<<hit<<"\t\t"<<miss<<"\t\t"<<(float)miss/(float)(miss+hit)<<endl;
    }
    gettimeofday(&end, 0);
    
    double sec = end.tv_sec - start.tv_sec;
    double usec = end.tv_usec - start.tv_usec;    
    printf("Total elapsed time : %.4lf sec\n\n",sec+(usec/1000000.0));

    cout<<"LRU policy:"<<endl;
    cout<<"frame\thit\t\tmiss\t\tpage fault ratio\n";
    gettimeofday(&start, 0);
    for(int frame_num = 128; frame_num<=1024; frame_num *= 2){
        list<int> page;
        unordered_map<int, list<int>::iterator> map;
        int hit = 0, miss = 0;
        for(int i = 0;i < total; i++){
            int target = input[i];
            //miss, page is full 
            if( map.find(target) == map.end() &&  page.size() == frame_num){
                miss++;
                page.push_front(target);
                map[target]=page.begin();
                map.erase(page.back());
                page.pop_back();
            }
            //miss, page is available
            else if(map.find(target) == map.end() && page.size() != frame_num){                
                miss++;
                page.push_front(target);
                map[target]=page.begin();                
            }
            //hit
            else{
                hit++;
                page.erase(map[target]);
                page.push_front(target);
                map[target]=page.begin();
            }
        }
        cout<<frame_num<<"\t"<<hit<<"\t\t"<<miss<<"\t\t"<<(float)miss/(float)(miss+hit)<<endl;
    }
    gettimeofday(&end, 0);
    sec = end.tv_sec - start.tv_sec;
    usec = end.tv_usec - start.tv_usec;    
    printf("Total elapsed time : %.4lf sec\n",sec+(usec/1000000.0));

     return 0;
}