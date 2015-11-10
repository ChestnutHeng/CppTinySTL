#ifndef _QUEUE_H_
#define _QUEUE_H_

#ifndef NULL 
	#define NULL 0
#endif

typedef int Rank;

template <typename T>
struct QueueNode
{
	T data;
	struct QueueNode *succ;
	struct QueueNode *pred;
};


template <typename T>
class Queue
{
public:
	int clear();
	Rank size() const{return _size;}
	bool empty(){return _size == 0;}
	void enqueue (T const& e);
	T dequeue();
	T& front();
	Queue<T>& operator = (Queue<T> const&L);
private:
	QueueNode<T> *head;
	QueueNode<T> *tail;
	Rank _size;
protected:
	void init();
	T& get(Rank r)const;
public:
	Queue(){init();};
	~Queue(){clear();delete head;delete tail;};
	Queue(Queue<T> const&L){
		init();
		for(int i = 0;i < L.size(); ++i) 
			this-> enqueue(L.get(i));
	}
};

template <typename T>
void Queue<T>::init(){
	head = new QueueNode<T>;
	tail = new QueueNode<T>;
	head -> succ = tail;
	head -> pred = NULL;
	tail -> pred = head;
	tail -> succ = NULL;
	_size = 0;
}

template <typename T>
T &Queue<T>::get(Rank r)const{
	QueueNode<T> *p = this -> head;
	while(r-- > -1){			//  [0,n)
		p = p -> succ;
	}
	return p -> data;
}

template <typename T>
int Queue<T>::clear(){
	Rank old_size = _size; 
	while(_size > 0)
		dequeue();
	return old_size;
}

template <typename T>
void Queue<T>::enqueue(T const& e){
	QueueNode<T> *tmp = new QueueNode<T>;
	tmp -> succ = tail;
	tail -> pred -> succ = tmp;
	tmp -> pred = tail -> pred;
	tail -> pred = tmp;
	tmp -> data = e;
	_size++;
}

template <typename T>
T Queue<T>::dequeue(){
	T ele = head -> succ -> data;
	head -> succ = head -> succ -> succ;
	delete head -> succ -> pred;
	head -> succ -> pred = head;
	_size--;
	return ele;
}


template <typename T>
T & Queue<T>::front(){
	return head -> succ -> data;
}

template <typename T>
Queue<T> &Queue<T>::operator = (Queue<T> const&L){
	if(this == &L)
		return *this;
	this -> clear();
	for(int i = 0;i < L.size(); ++i)
 		this->enqueue(L.get(i));
 	return *this;
}

#endif

