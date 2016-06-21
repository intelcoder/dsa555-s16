/*********************************************************************/
/*                                                                   */
/* Tester for DSA555-s16 assignment 1, question 1                    */
/* Version 1.0                                                       */
/* To compile:                                                       */
/*                                                                   */
/*      g++ a1q1main.cpp -std=c++0x                                  */
/*                                                                   */
/* for memory leak check                                             */
/* valgrind --leak-check=full --track-origins=yes a.out              */
/* for vs: google for vld.h                                          */
/*********************************************************************/

#include "a1q1.h"
#include <cstring>
#include <iostream>
using namespace std;
//change the #define VERBOSE to 1 for a bit more error information
#define VERBOSE 1

struct Record{
	char word_[30];
	int count_;
};
ostream& operator<<(ostream& os, const Record rec){
	os << rec.word_;
	return os;
}
bool operator==(const Record& a,const Record& b){
	bool rc=false;
	if(strcmp(a.word_,b.word_)==0 && a.count_==b.count_){
		rc=true;
	}
	return rc;
}
bool operator!=(const Record& a,const Record& b){
	return !(a==b);
}

template <class T>
void removeItem(T arr[],int idx,int sz);
template <class T>
bool checkList(DList<T>& list,const T arr2[],int sz);
template <class T>
void duplicateArray(T dest[], const T src[],int sz);
template <class T>
void printLists(DList<T>& list,const T array[],int sz);
template <class T>
void removeRange(T arr[],int from,int to, int sz);

int main(void){
	const int cap=10000;
	const int numSearches=200;
	Record data[20]={
		{"the",1},
		{"quick",2},
		{"brown ",3},
		{"fox",4},
		{"jumped",5},
		{"over",6},
		{"lazy",7},
		{"dog",8},
		{"Calvin",9},
		{"and",10},
		{"Hobbes",11},
		{"night",12},
		{"watch",13},
		{"captain",14},
		{"carrot",15},
		{"lilac",16},
		{"lavender",17},
		{"lily",18},
		{"coffee",19},
		{"tea",20}
	};
	int intData[cap];

	//these array will mirror what happens to LL
	Record mirror[20];
	int intMirror[cap];



	DList<Record> recList;
	DList<int> intList;

	bool passtest=true;
	int numPassed=0;


	/* Test constructors, begin and end functions*/
	cout << "test 1: create list empty list, check begin() and end()" << endl;
	if((recList.begin() != recList.end()) || 
		(intList.begin() != intList.end())){
		cout << "error 1: check your constructor, begin() and end() functions" << endl;
		passtest=false;
	}
	else{
		numPassed++;
	}
	int idx=0;
	for(int i=0;i<20;i++){
		if(i!=0 && i!=2 && i!=8 && i!= 10 && i!=17 && i!=19){
			recList.insertBack(data[i]);
			mirror[idx++]=data[i];
		}
	}
	for(int i=0;i<cap;i++){
		intList.insertFront(cap-1-i);
		intData[i]=i;
		intMirror[i]=i;		
	}
	cout << "test 2: create list, insert some records." << endl;
	if(!checkList(recList,mirror,14)){
		passtest=false;
		cout << "Error 2a: Bug in either constructor, insertBack()or iterator (operator++(int) or operator*)"<< endl;
		#if VERBOSE >= 1
		printLists(recList,mirror,14);
		#endif		
	}
	if(!checkList(intList,intMirror,cap)){
		passtest=false;
		cout << "Error 2b: Bug in either constructor, insertFront() or iterator (operator++(int) or operator*)"<< endl;
	}
	if(passtest){
		numPassed++;
		cout << "test 3: check iterator, postfix ++ and -- operators"  << endl;
		DList<Record>::iterator it=recList.begin();
		for(int i=0;i<13 && passtest;i++){
			Record r=*(it++);
			if(mirror[i] != r){
				passtest=false;
				cout << "Error 3a: postfix ++ operator is not returning iterator to correct node" << endl;
				#if VERBOSE >= 1
				cout << "correct: " << mirror[i] << " ,your list: " << r << endl;
				#endif		
			}
		}
		for(int i=13;i>0 && passtest;i--){
			Record r=*(it--);
			if(mirror[i] != r){
				passtest=false;
				cout << "Error 3b: postfix -- operator is not returning iterator to correct node" << endl;
				#if VERBOSE >= 1
				cout << i << ": correct: " << mirror[i] << " ,your list: " << r << endl;
				#endif		
			}
		}
		for(int i=0;i<13 && passtest;i++){
			if(*(++it) != mirror[i+1]){
				passtest=false;
				cout << "Error 3c: prefix ++ operator is not returning iterator to correct node" << endl;
			}
		}
		for(int i=13;i>0 && passtest;i--){
			if(*(--it) != mirror[i-1]){
				passtest=false;
				cout << "Error 3d: prefix -- operator is not returning iterator to correct node" << endl;
			}
		}
	}

	if(passtest){
		numPassed++;
		cout << "test 4: insertBefore/insertAfter functions"  << endl;
		DList<Record>::iterator front=recList.begin();
		DList<Record>::iterator mid=recList.begin();
		DList<Record>::iterator back=recList.begin();

		for(int i=0;i<6;i++){
			mid++;
		}
		for(int i=0;i<13;i++){
			back++;
		}
		recList.insertAfter (front,data[2] );
		recList.insertBefore(front,data[0] );
		recList.insertBefore(mid  ,data[8] );
		recList.insertAfter (mid  ,data[10]);
		recList.insertBefore(back ,data[17]);
		recList.insertAfter (back ,data[19]);
		for(int i=0;i<20;i++){
			mirror[i]=data[i];
		}
		DList<Record>::iterator it=recList.begin();
		for(int i=0;i<19 && passtest;i++){
			Record r=*(it++);
			if(data[i] != r){
				passtest=false;
				cout << "Error 4a: List not correct after a series of insertBefore/insertAfter calls" << endl;
				#if VERBOSE >= 1
				cout << i << ": correct: " << mirror[i] << " ,your list: " << r << endl;
				#endif		
			}
		}
		for(int i=19;i>0 && passtest;i--){
			Record r=*(it--);
			if(data[i] != r){
				passtest=false;
				cout << "Error 4b: List not correct.  Check your prev pointers" << endl;
				#if VERBOSE >= 1
				cout << i << ": correct: " << mirror[i] << " ,your list: " << r << endl;
				#endif		
			}
		}
	}


	DList<Record> recCopy=recList;
	DList<int> intCopy=intList;
	if(passtest){
		numPassed++;
		cout << "test 5: create a duplicate of the lists with copy constructor, ensure they match" << endl;
		if(!checkList(recList,mirror,20)){
			passtest=false;
			cout << "Error 5a: Bug in copy constructor"  << endl;  		
		}
		if(!checkList(intList,intMirror,cap)){
			passtest=false;
			cout << "Error 5b: Bug in copy constructor" << endl;
		}
	}

	if(passtest){
		numPassed++;
		cout << "test 6: ensure that copied list were not altered (proper deep copy was made) " << endl;
		if(!checkList(recCopy,data,20)){
			passtest=false;
			cout << "Error 6a: Bug in copy constructor, deep copy not made?"  << endl;
			#if VERBOSE >= 1
			printLists(recCopy,data,20);
			#endif
		}
		if(!checkList(intCopy,intData,cap)){
			passtest=false;
			cout << "Error 6b: Bug in copy constructor, deep copy not made?" << endl;
			#if VERBOSE >= 2
			printLists(intCopy,intData,cap);
			#endif
		}
	}
	if(passtest){
		numPassed++;
		cout << "test 7: test assignment operator"  << endl;
		recCopy = recList;
		intCopy = intList;
		if(!checkList(recCopy,mirror,20)){
			passtest=false;
			cout << "Error 7a: Bug in = operator"  << endl;  		
			#if VERBOSE >= 1
			printLists(recCopy,mirror,20);
			#endif
		}
		if(!checkList(intCopy, intMirror,cap)){
			passtest=false;
			cout << "Error 7b: Bug in = operator"  << endl;  		
			#if VERBOSE >= 2
			printLists(intCopy,intMirror,cap);
			#endif
		}
		duplicateArray(data,mirror,20);
		duplicateArray(intData,intMirror,cap);
	}
	if(passtest){
		numPassed++;
		cout << "test 8: test erase(iterator) function"  << endl;
		DList<Record>::iterator it=recList.begin();
		DList<Record>::iterator rc;
		rc=recList.erase(it++);
		removeItem(mirror,0,20);
		if(it!=rc || !checkList(recList,mirror,19)){
			passtest=false;
			cout << "Error 8a: Bug in erase.  iterator was pointing at first item" << endl;
			#if VERBOSE >= 1
			printLists(recList,mirror,19);
			#endif
		}
		it=recList.begin();
		for(int i=0;i<18;i++){
			it++;
		}
		rc=recList.erase(it);
		removeItem(mirror,18,19);
		if(rc!=recList.end() || !checkList(recList,mirror,18)){
			passtest=false;
			cout << "Error 8b: Bug in erase. iterator was pointing at last item" << endl;
			#if VERBOSE >= 1
			printLists(recList,mirror,18);
			#endif
		}
		for(int i=0;i<3 && passtest;i++){
			int pick=rand()%(18-i);
			it=recList.begin();
			for(int j=0;j<pick;j++){
				it++;
			}

			rc=recList.erase(it++);
			removeItem(mirror,pick,18-i);
			if(rc!=it || !checkList(recList,mirror,18-i-1)){
				passtest=false;
				cout << "Error 8c:  Bug in erase." << endl;
			}
		}
		DList<int>::iterator it2=intList.begin(); 
		DList<int>::iterator rc2;
		rc2=intList.erase(it2++);
		removeItem(intMirror,0,cap);
		if(rc2!=it2 || !checkList(intList,intMirror,cap-1)){
			passtest=false;
			cout << "Error 8d: Bug in erase." << endl;
		}
		rc2=intList.erase(it2++);
		removeItem(intMirror,0,cap-1);
		if(rc2!=it2 || !checkList(intList,intMirror,cap-2)){
			passtest=false;
			cout << "Error 8e: Bug in erase." << endl;
		}
		it2=intList.begin();
		for(int i=0;i<cap-4;i++){
			it2++;
		}
		DList<int>::iterator secondLast=it2;
		it2++;
		rc2=intList.erase(it2++);
		removeItem(intMirror,cap-3,cap-2);
		if(rc2!=intList.end() || !checkList(intList,intMirror,cap-3)){
			passtest=false;
			cout << "Error 8f: Bug in remove." << endl;
		}
		rc2=intList.erase(secondLast);
		removeItem(intMirror,cap-4,cap-3);
		if(rc2!=intList.end() || !checkList(intList,intMirror,cap-4)){
			passtest=false;
			cout << "Error 8g: Bug in remove." << endl;
		}
		for(int i=0;i<100 && passtest;i++){
			int pick=rand()%(cap-i-4);

			it2=intList.begin();
			for(int j=0;j<pick;j++){
				it2++;
			}

			rc2=intList.erase(it2++);
			removeItem(intMirror,pick,cap-4-i);
			if(rc2!=it2 || !checkList(intList,intMirror,cap-i-5)){
				passtest=false;
				cout << "Error 8h:  Bug in remove." << endl;
			}
		}
	}
	if(passtest){
		numPassed++;
		cout << "test 9: test erase(from,to) function"  << endl;
		DList<Record>::iterator from=recList.begin();
		DList<Record>::iterator to=from;
		DList<Record>::iterator rc;
		for(int i=0;i<3;i++){
			to++;
		}
		rc=recList.erase(from,to);
		removeRange(mirror,0,3,15);
		if(rc!=to || !checkList(recList,mirror,12)){
			passtest=false;
			cout << "Error 9a: Bug in erase(from,to).  removed first 3 items" << endl;
			#if VERBOSE >= 1
			printLists(recList,mirror,12);
			#endif
		}
		from=recList.begin();
		for(int i=0;i<9;i++){
			from++;
		}
		rc=recList.erase(from,recList.end());
		removeRange(mirror,9,12,12);
		if(rc!=recList.end() || !checkList(recList,mirror,9)){
			passtest=false;
			cout << "Error 9b: Bug in erase(from,to).  removed last 3 items" << endl;
			#if VERBOSE >= 1
			printLists(recList,mirror,9);
			#endif			
		}
		from=recList.begin();
		for(int i=0;i<3;i++){
			from++;
		}
		to=from;
		for(int i=0;i<3;i++){
			to++;
		}
		rc=recList.erase(from,to);
		removeRange(mirror,3,6,9);
		if(rc!=to || !checkList(recList,mirror,6)){
			passtest=false;
			cout << "Error 9c: Bug in erase(from,to).  removed 4th,5th and 6th item" << endl;
			#if VERBOSE >= 1
			printLists(recList,mirror,6);
			#endif			
		}

	}

	if(passtest){
		numPassed++;
		cout << "test 10: test assignment operator (deep copy)"  << endl;
		if(!checkList(recCopy,data,20)){
			passtest=false;
			cout << "Error 10a: Bug in = operator, no deepcopy?"  << endl;
		}
		if(!checkList(intCopy,intData,cap)){
			passtest=false;
			cout << "Error 10b: Bug in = operator,no deep copy?"  << endl;     
		}
	}
	if(passtest){
		numPassed++;
	}
	if(numPassed == 10){
		cout << "Testing for Assignment 1 completed successfully" << endl;
	}
	else{
		cout << numPassed << " / 10 tests passed.  Looks like you still" << endl;
		cout << "have some work to do" << endl;
	}
	return 0;
}

template <class T>
void removeItem(T arr[],int idx,int sz){
	for(int i=idx;i<sz-1;i++){
		arr[i]=arr[i+1];
	}
}
template <class T>
void removeRange(T arr[],int from,int to, int sz){
	int diff=to-from;
	for(int i=from;i<sz-diff;i++){
		arr[i]=arr[i+diff];
	}
}

template <class T>
bool checkList(DList<T>& list,const T array[],int sz){
	bool rc=true;
	auto it=list.begin();
	int i;
	for(i=0;i<sz-1 && it!=list.end() && rc;i++,it++){
		if(*it != array[i]){
			rc=false;
		}
	}
	if(*it != array[i]){
		rc=false;
	}
	for(i=sz-1;i>0 && it!=list.begin() && rc; i--, it-- ){
		if(*it != array[i]){
			rc=false;
		}

	}
	if(*it != array[i]){
		rc=false;
	}
	for(i=0;i<sz && it!=list.end() && rc;i++,it++){
		if(*it != array[i]){
			rc=false;
		}
	}

	if(it!=list.end() || i < sz){
		rc=false;
	}
	return rc;
}

template <class T>
void duplicateArray(T dest[], const T src[],int sz){
	for(int i=0;i<sz;i++){
		dest[i]=src[i];
	}
}

template <class T>
void printLists(DList<T>& list,const T array[],int sz){
	auto it=list.begin();
	for(int i=0;i<sz;i++,it++){
		cout << "correct: "  << array[i] << " your list: " << *it << endl;

	}
}
