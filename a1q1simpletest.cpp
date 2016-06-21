#include <iostream>
using namespace std;
void printList(DList<int>& list);

int main(void){
	DList<int> list;    //empty
	printList(list);
	list.insertFront(2);  // 2
	list.insertFront(3);  // 3 2
	printList(list);

	list.insertBack(1);   //3 2 1
	list.insertBack(5);   //3 2 1 5
	printList(list);

	DList<int> list2=list;
	printList(list2);	
}
void printList(DList<int>& list){
	DList<int>::iterator it;
	if(list.begin() == list.end()){
		cout << "empty list" << endl;
	}
	else{
		for(it=list.begin();it!=list.end();it++){
			cout << * it << endl;
		}
	}
}
