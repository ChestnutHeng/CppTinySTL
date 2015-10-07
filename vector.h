#ifndef VECTOR_H_
#define VECTOR_H_

#define DEFAULT_CAPACITY 5

#include <cstdlib>

typedef int Rank;

template <typename T> class vector
{
protected:
	Rank rank;
	int _size,_capacity;   //_size is vector's used size. _capacity is the real size
	T * _elem;
	Rank max(Rank lo,Rank hi);
	Rank partition(Rank lo,Rank hi);
	void copyfrom(T const*A,Rank lo,Rank hi);
	void expand();
	void shrink();
	void bubbleSort(Rank lo,Rank hi);
	void slectionSort(Rank lo,Rank hi);
	void merge(Rank lo,Rank mid,Rank hi);
	void mergeSort(Rank lo,Rank hi);
	void quicksort(Rank lo,Rank hi);
	void swap(T &e1,T &e2);

public:
	vector(int n = DEFAULT_CAPACITY,T ele = 0){
		_elem = new T[_capacity = n<<1];
		for(_size = 0; _size < n; _elem[_size++] = ele);
		expand();
	}
	//defalt init
	vector(const vector <T>& V){copyfrom(V._elem,0,V._size);}
	~vector(){delete [] _elem;}


	int size(){return _size;};
	T get(Rank rank){return _elem[rank];};
	void put(Rank rank,T const&ele){_elem[rank] = ele;};
	Rank insert(Rank rank,T const&ele);
	void remove(Rank rank);
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


};


template <typename T>
void vector<T>::expand(){
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
void vector<T>::shrink(){
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
Rank vector<T>::insert(Rank rank,T const&ele){
	expand();
	for(int i = _size++;i > rank; --i){
		_elem[i] = _elem[i-1]; 
	}
	_elem[rank] = ele;
	return rank;
}

template <typename T>
void vector<T>::remove(Rank rank){
	for (int i = rank; i < _size; ++i){
		_elem[i] = _elem[i+1];
	}
	_size--;
	shrink();
}

template <typename T>
bool vector<T>::disordered(){
	for(int i = 0;i < size;++i){
		if(_elem[i] > _elem[i+1]) return false;
	}
	return true;
}

template <typename T>
Rank vector<T>::search(T const&ele,Rank lo,Rank hi){
	while(lo < hi){
		Rank mid = (lo + hi) >> 1;
		(ele < _elem[mid]) ? hi = mid : lo = mid + 1;
	}
	return --lo;
}


template <typename T>
Rank vector<T>::find(T const&ele,Rank lo,Rank hi){
	while((lo < hi--) && (ele != _elem[hi]));
	return hi;
}

template <typename T>
Rank vector<T>::deduplicate(){
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
Rank vector<T>::uniquify(){
	Rank i = 0, j = 0;
	while (++j < _size) 
	   if ( _elem[i] != _elem[j] ) 
	      _elem[++i] = _elem[j];
	_size = ++i; shrink();
	return j - i; 
}

template <typename T>
Rank vector<T>::max(Rank lo,Rank hi){
	T tmp = _elem[lo++];
	while(lo <= hi) {
		if(tmp < _elem[lo]) tmp = _elem[lo++];
	}
}

template <typename T>
void vector<T>::swap(T &e1,T &e2){
	T tmp(e1);
	e1 = e2;
	e2 = tmp;
}

template <typename T>
Rank vector<T>::partition ( Rank lo, Rank hi ) {
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
void vector<T>::sort(Rank lo, Rank hi){ 
   if (hi - lo < 2) return;
   Rank mi = partition(lo,hi - 1);
   sort(lo, mi);
   sort(mi + 1,hi);
}

template <typename T>
void vector<T>::traverse (void( *visit)(T&)){
   for(int i = 0; i < _size; i++) visit(_elem[i]);
}

#endif
