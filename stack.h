
template <typename T>
class Stack{
	T* data_;
	int max_;
	int size_;
	void grow(){
		T* newdata=new T[max_+100];
		for(int i=0;i<size_;i++){
			newdata[i]=data_[i];
		}
		max_=max_+100;
		delete [] data_;
		data_=newdata;
	}
public:
	Stack(){
		data_=new T[100];
		max_=100;
		size_=0;
	}
	void push(const T& data){
		if(size_ >= max_){
			grow();
		}
		data_[size_++]=data;
	}
	void pop(){
		if(!isEmpty()){
			size_--;
		}
	}
	T top() const{
		T rc;
		if(!isEmpty()){
			rc= data_[size_-1];
		}
		return rc;
	}
	bool isEmpty() const{
		return (size_==0);
	}
	~Stack(){
		delete [] data_;
	}
}