#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stddef.h>

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
private:
	QueueNode<T> *head;
	QueueNode<T> *tail;
	Rank _size;
protected:
	void init();
	int clear();
public:
	Queue(){init();};
	~Queue(){clear();delete head;delete tail;};

	Rank size(){return _size;}
	bool empty(){return _size == 0;}
	void enqueue ( T const& e );
	T dequeue();
	T& front();
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

#endif

