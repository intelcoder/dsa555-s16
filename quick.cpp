#include <cstdlib>
#include <iostream>
#include <fstream>
#include "timer.h"

using namespace std;

void InsertionSort(int arr[],int left,int right){
  int curr;
  int i, j;
  for(i=left+1;i<=right;i++){
    curr=arr[i];
    for(j=i;j>0 && arr[j-1] > curr;j--){
      arr[j]=arr[j-1];
    }
    arr[j]=curr;
  }
}


void QuickSort(int arr[], int left, int right){
  if(right-left <=3){
    InsertionSort(arr,left,right);
  }
  else{
    int pivotpt=(left+right)/2;   //index of the pivot
    int i=left;
    int j=right-1;
    swap(arr[pivotpt],arr[right]);
    pivotpt=right;
    int pivot=arr[pivotpt];
    while(i<j){
      while(i< right-1 && arr[i]<pivot) i++;
      while(j > 0 && arr[j]>pivot) j--;
      if(i<j)
        swap(arr[i++],arr[j--]);
    }
    if(i==j && arr[i] < arr[pivotpt])
      i++;
    swap(arr[i],arr[pivotpt]);
    QuickSort(arr,left,i-1);
    QuickSort(arr,i+1,right);
  }
}

void QuickSort(int arr[],int size){
  QuickSort(arr,0,size-1);
}

int main(int argc, char* argv[]){
  int size=atoi(argv[1]);
  int* myarr=new int[size];
  Timer stopwatch;
  ofstream log("quick.log");
  for(int i=0;i<size;i++){
     myarr[i]=rand();
 //  myarr[i]=i+1;
  }
  stopwatch.start();
  QuickSort(myarr,size);
  stopwatch.stop();
  cout << stopwatch.currtime() << endl;
/*  for(int i=0;i<size;i++){
    log <<myarr[i]<< endl;
  }*/
  return 0;
}

