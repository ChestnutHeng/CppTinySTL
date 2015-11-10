#ifndef VECTOR_H_
#define VECTOR_H_

#define DEFAULT_CAPACITY 3

#ifndef NULL 
	#define NULL 0
#endif

#include <stdlib.h>

typedef int Rank;

template <typename T> class Vector
{
public:
	int size(){return _size;};
	void clear(){_size = 0;shrink();}
	T get(Rank rank){return _elem[rank];};
	void put(Rank rank,T const&ele){_elem[rank] = ele;};
	Rank insert(Rank rank,T const&ele);
	void push_back(T const&ele);
	T pop_back(){return _elem[_size - 1];}
	T remove(Rank rank);
	bool disordered();
	Rank find(T const&ele,Rank lo,Rank hi);
	Rank find(T const&ele){find(ele,0,_size);};
	Rank search(T const&ele,Rank lo,Rank hi);
	Rank search(T const&ele){search(ele,0,_size);}
	Rank deduplicate();
	Rank uniquify();
	void sort(Rank lo,Rank hi);
	void sort(){sort(0,_size);}
	void traverse (void( *visit)(T&));
	T& operator[] (Rank r) const{return _elem[r];}
	
protected:
	Rank rank;
	int _size,_capacity;   //_size is Vector's used size. _capacity is the real size
	T * _elem;
	Rank max(Rank lo,Rank hi);
	Rank partition(Rank lo,Rank hi);
	void copyFrom(T const*A,Rank lo,Rank hi);
	void expand();
	void shrink();
	void bubbleSort(Rank lo,Rank hi);
	void slectionSort(Rank lo,Rank hi);
	void merge(Rank lo,Rank mid,Rank hi);
	void mergeSort(Rank lo,Rank hi);
	void quicksort(Rank lo,Rank hi);
	void swap(T &e1,T &e2);

public:
	Vector(){
		_elem = new T[_capacity = DEFAULT_CAPACITY << 1];
		_size = 0;
		expand();
	}//defalt init

	Vector(T ele){
		_elem = new T[_capacity = DEFAULT_CAPACITY << 1];
		for(_size = 0; _size < DEFAULT_CAPACITY; _elem[_size++] = ele);
		expand();
	}
	Vector(int n,T ele){
		_elem = new T[_capacity = n << 1];
		for(_size = 0; _size < n; _elem[_size++] = ele);
		expand();
	}
	Vector(const Vector <T>& V){
		_elem = NULL;
		copyFrom(V._elem,0,V._size);
	}
	Vector(Vector<T>const& V,Rank lo,Rank hi){
		_elem = NULL;
		copyFrom(V._elem,lo,hi);
	}
	Vector(Vector<T>& V,Rank lo,Rank hi){
		_elem = NULL;
		copyFrom(V._elem,lo,hi);
	}
	~Vector(){delete [] _elem;}



	Vector<T>& operator = (const Vector<T> &V){
		if(this == &V) return *this;
		Vector<T> t_V = const_cast<Vector<T>&>(V);
		copyFrom(t_V._elem,0,t_V.size());
		return *this;
	}  //copy vector to another vector

};

template <typename T>
void Vector<T>::copyFrom(T const* A,Rank lo,Rank hi){
	if (_elem != NULL)
		delete[] _elem;
   _elem = new T[_capacity = 2 * ( hi - lo )];
   _size = 0;
   while (lo < hi)
      _elem[_size++] = A[lo++];
}

template <typename T>
void Vector<T>::expand(){
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
void Vector<T>::shrink(){
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
Rank Vector<T>::insert(Rank rank,T const&ele){
	expand();
	for(int i = _size++;i > rank; --i){
		_elem[i] = _elem[i-1]; 
	}
	_elem[rank] = ele;
	return rank;
}

template <typename T>
void Vector<T>::push_back(T const&ele){
	insert(size(),ele);
}

template <typename T>
T Vector<T>::remove(Rank rank){
	T old_e = _elem[rank];
	for (int i = rank; i < _size; ++i){
		_elem[i] = _elem[i+1];
	}
	_size--;
	shrink();
	return old_e;
}

template <typename T>
bool Vector<T>::disordered(){
	for(int i = 0;i < size;++i){
		if(_elem[i] > _elem[i+1]) return false;
	}
	return true;
}

template <typename T>
Rank Vector<T>::search(T const&ele,Rank lo,Rank hi){
	while(lo < hi){
		Rank mid = (lo + hi) >> 1;
		(ele < _elem[mid]) ? hi = mid : lo = mid + 1;
	}
	return --lo;
}


template <typename T>
Rank Vector<T>::find(T const&ele,Rank lo,Rank hi){
	while((lo < hi--) && (ele != _elem[hi]));
	return hi;
}

template <typename T>
Rank Vector<T>::deduplicate(){
	Rank old_size = _size;
	for(Rank i = 1;i < _size; ++i){
		Rank tmp = find(_elem[i],0,i);
		if(tmp >= 0) {
			i--;
			remove(tmp);
		}
	}
	return old_size - _size;
}

template <typename T>
Rank Vector<T>::uniquify(){
	Rank i = 0, j = 0;
	while (++j < _size) 
	   if ( _elem[i] != _elem[j] ) 
	      _elem[++i] = _elem[j];
	_size = ++i; shrink();
	return j - i; 
}

template <typename T>
Rank Vector<T>::max(Rank lo,Rank hi){
	T tmp = _elem[lo++];
	while(lo <= hi) {
		if(tmp < _elem[lo]) tmp = _elem[lo++];
	}
}

template <typename T>
void Vector<T>::swap(T &e1,T &e2){
	T tmp(e1);
	e1 = e2;
	e2 = tmp;
}

template <typename T>
Rank Vector<T>::partition ( Rank lo, Rank hi ) {
   swap ( _elem[lo], _elem[lo + rand() % ( hi - lo + 1 ) ]); 
   T pivot = _elem[lo]; 
   int mi = lo;
   for (int k = lo + 1; k <= hi; k++)
      if (_elem[k] < pivot)
         swap ( _elem[++mi], _elem[k]); 
   swap (_elem[lo], _elem[mi]); 
   return mi; 
}

template <typename T>
void Vector<T>::sort(Rank lo, Rank hi){ 
   if (hi - lo < 2) return;
   Rank mi = partition(lo,hi - 1);
   sort(lo, mi);
   sort(mi + 1,hi);
}

template <typename T>
void Vector<T>::traverse (void( *visit)(T&)){
   for(int i = 0; i < _size; i++) visit(_elem[i]);
}

#endif

