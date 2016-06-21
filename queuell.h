
template <typename T>
class Queue{
	SList<T> data_;
public:
	Queue();
	void enqueue(const T& data){
		data_.insertBack(data);
	}
	void dequeue(){
		data_.removeFront();
	}
	T front() const{
		return *(data_.begin());
	}
	bool isEmpty() const{
		return (data_.begin()==data_.end());
	}
}