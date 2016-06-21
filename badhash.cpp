#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;
/*DO NOT USE THIS HASH FUNCTION.
IT IS REALLY REALLY BAD*/
int badHash(const char* key, int tablesize);

int main(int argc, char* argv[]){
	char key[100];
	int tablesize;
	if(argc != 3){
		cout << "usage: a.out key tablesize" << endl;
	}
	else{
		tablesize=atoi(argv[2]);
		strcpy(key,argv[1]);
		int idx = badHash(key,tablesize);
		cout << "index: " << idx  << endl;
	}
}

int badHash(const char* key, int tablesize){
	int total=0;
	for(int i=0;key[i]!='\0';i++){
		total=total + key[i];
	}
	return total%tablesize;
}


