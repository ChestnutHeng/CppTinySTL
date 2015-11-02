#ifndef STACK_H_
#define STACK_H_

#define DEFAULT_CAPACITY 3
typedef int Rank;

template <typename T>
class Stack
{
public:
	void clear(){_size = 0;shrink();}
	bool empty(){return (_size == 0);}
	Rank size(){return _size;}
	void push(T const&e);
	T pop();
	T & top();
private:
	T *_elem;
	Rank _size;
	Rank _capacity;
protected:
	void copyFrom(T const* A,Rank lo,Rank hi);
	void expand();
	void shrink();
public:
	Stack(){
		_elem = new T[_capacity = DEFAULT_CAPACITY << 1];
		_size = 0;
		expand();
	}
	Stack(const Stack <T>& V){
		_elem = NULL;
		copyFrom(V._elem,0,V._size);
	}
	
	~Stack(){delete [] _elem;};
	
	Stack<T>& operator = (const Stack<T> &V){
		if(this == &V) return *this;
		Stack<T> t_V = const_cast<Stack<T>&>(V);
		copyFrom(t_V._elem,0,t_V.size());
		return *this;
	}
};

template <typename T>
void Stack<T>::copyFrom(T const* A,Rank lo,Rank hi){
	if (_elem != NULL)
		delete[] _elem;
   _elem = new T[_capacity = 2 * ( hi - lo )];
   _size = 0;
   while (lo < hi)
      _elem[_size++] = A[lo++];
}

template <typename T>
void Stack<T>::expand(){
	if(_size < _capacity) return;
	if(_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
	T *oldelem = _elem;
	_elem = new T[_capacity <<= 1];
	for(int i = 0;i < _size; ++i){
		_elem[i] = oldelem[i];
	}
	delete [] oldelem;
}

template <typename T>
void Stack<T>::shrink(){
	if(_capacity < DEFAULT_CAPACITY << 1) return;
	if(_size << 2 > _capacity) return;
	T *oldelem = _elem;
	_elem = new T[_capacity >>= 1];
	for(int i = 0;i < _size; ++i){
		_elem[i] = oldelem[i];
	}
	delete [] oldelem;

}

template <typename T>
void Stack<T>::push(T const&e){
	expand();
	_elem[_size++] = e;
}

template <typename T>
T Stack<T>::pop(){
	shrink();
	return _elem[_size-- - 1];
}

template <typename T>
T & Stack<T>::top(){
	return _elem[_size - 1];
}

#endif

