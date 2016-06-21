
template <typename T>
class Queue{
	T* data_;
	int max_;
	int size_;
	int front_;
	int back_;
	void grow(){
		T* newdata=new T[max_+100];
		int j=front_;
		for(int i=0;i<size_;i++){
			newdata[i]=data_[j];
			j=(j+1)%max_;
		}
		max_=max_+100;
		front_=0;
		back_=size_;
		delete [] data_;
		data_=newdata;

	}
public:
	Queue(){
		data_=new T[100];
		max_=100;
		size_=0;
		front_=0;
		back_=0;

	}
	void enqueue(const T& data){
		if(size_ >=max_){
			grow();
		}
		data_[back_]=data;
		back_=(back_==max_-1? 0:back_+1);
		size_++;
	}
	void dequeue(){
		if(!isEmpty()){
			front_=(front_+1)%max_;
			size_--;
		}
	}
	T front() const{
		T rc;
		if(!isEmpty()){
			rc=data_[front_];
		}
		return rc;
	}
	bool isEmpty() const{
		return size_==0;
	}
	~Queue(){
		delete [] data_;
	}
}