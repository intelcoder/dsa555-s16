#include "slist.h"
template <typename T>
class Stack{
	SList<T> data_;
public:
	Stack(){
	}
	void push(const T& data){
		data_.insertFront(data);
	}
	void pop(){
		data_.removeFront();
	}
	T top() const{
		return *(data_.begin());
	}
	bool isEmpty() const{
		return (data_.begin()==data_.end());
	}
}