#ifndef LIST_H_
#define LIST_H_

#include "ListNode.h"
#include <iostream>

template <typename T>
class List{
private:
	int _size;
	ListNodePosi(T) head;
	ListNodePosi(T) tail;
protected:
	void init();
	int clear();
	void copyNodes(ListNodePosi(T),int);
	void merge(ListNodePosi(T)&,int,List<T>&,ListNodePosi(T),int);
	void mergeSort(ListNodePosi(T)&,int);

public:
	List(){init();}
	List(List<T> const&L){}
	List(List<T> const&L,Rank r,int n){}
	~List(){clear();delete head;delete tail;};

	Rank size() const{return _size;}
	bool empty() const{return (_size <= 0);}
	T &operator[](Rank r)const;
	ListNodePosi(T) first()const{return head -> succ;}
	ListNodePosi(T) last()const{return tail -> pred;}
	void swap(ListNodePosi(T) &p1,ListNodePosi(T) &p2){ListNodePosi(T) tmp = p1;p1 = p2;p2 = tmp;};
	bool valid(ListNodePosi(T) p);
	int disodered()const;
	ListNodePosi(T) find(T const&e){return find(e,_size,last()-> succ);};
	ListNodePosi(T) find(T const&e,int n,ListNodePosi(T) p);
	ListNodePosi(T) insertAsFirst(T const&e);
	ListNodePosi(T) insertAsLast (T const&e);
	ListNodePosi(T) insertA(ListNodePosi(T) p,T const& e);
	ListNodePosi(T) insertB(ListNodePosi(T) p,T const& e);
	ListNodePosi(T) push_back(T const& e);
	T remove(ListNodePosi(T) p);
	void sort(ListNodePosi(T) p,int n);
	void sort(){sort(first(),_size);}
	int deduplicate();
	int uniquify();
	void reverse();
	void traverse(void(*)(T &));

	void add_up(List<T> l2);

};

template <typename T>
void List<T>::init(){
	head = new ListNode<T>;
	tail = new ListNode<T>;
	head -> pred = NULL;
	tail -> succ = NULL;
	head -> succ = tail;
	tail -> pred = head;
	_size = 0;
}

template <typename T>
int List<T>::clear(){
	int old_size = _size;
	while(_size > 0)
		remove(head -> succ);
	return old_size;
}

template <typename T>
T &List<T>::operator[](Rank r)const{
	ListNodePosi(T) p = first();
	while(r-- > 0){			//  (0,n)
		p = p -> succ;
	}
	return p -> data;
}
template <typename T>
bool List<T>::valid(ListNodePosi(T) p){
	ListNodePosi(T) tmp = first();
	for(int i = 0;i < _size -1;tmp = tmp -> succ,i++){
		if(tmp == p) return true;
	}
	return false;
}

template <typename T>
int List<T>::disodered()const{
	int n = 0; ListNode<T>* p = first();
    for ( int i = 0; i < _size - 1; p = p->succ, i++ )
      if ( p->data > p->succ->data ) n++;
    return n;
}

template <typename T>
ListNodePosi(T) List<T>::find(T const&e,int n,ListNodePosi(T) p){
	while(0 < n--)
		if( e == ( p = p->pred) -> data) return p;
	return NULL;
}

template <typename T>
ListNodePosi(T) List<T>::insertAsFirst(T const&e){
	_size++;
	return head -> insertAsSucc(e);
}

template <typename T>
ListNodePosi(T) List<T>::insertAsLast (T const&e){
	_size++;
	return tail -> insertAsPred(e);
}

template <typename T>
ListNodePosi(T) List<T>::insertA(ListNodePosi(T) p,T const& e){
	_size++;
	return p -> insertAsSucc(e);
}

template <typename T>
ListNodePosi(T) List<T>::insertB(ListNodePosi(T) p,T const& e){
	_size++;
	return p -> insertAsPred(e);
}

template <typename T>
ListNodePosi(T) List<T>::push_back(T const& e){
	_size++;
	return tail -> insertAsPred(e);
}
template <typename T>
T List<T>::remove(ListNodePosi(T) p){
	_size--;
	T old_data = p -> data;
	p -> pred -> succ = p -> succ;
	p -> succ -> pred = p -> pred;
	delete p;
	return old_data;
}

template <typename T>
void List<T>::reverse(){
	if (_size < 2) return;
    for (ListNodePosi(T) p = head;p;p = p->pred)
    	swap(p->pred, p->succ); 
    swap(head,tail);
}

template <typename T>
void List<T>::traverse(void( *visit)(T &)){
	for(ListNodePosi(T) p = head->succ; p != tail; p = p->succ)
		visit (p->data);
}

template <typename T>
void List<T>::sort(ListNodePosi(T) p,int n){
	mergeSort(p,n);
}

template <typename T> //
void List<T>::mergeSort (ListNodePosi(T) &p, int n ) {
   if ( n < 2 ) return; 
   int m = n >> 1; 
   ListNodePosi(T) q = p; for ( int i = 0; i < m; i++ ) q = q -> succ; 
   mergeSort ( p, m ); mergeSort ( q, n - m );
   merge ( p, m, *this, q, n - m ); 
}

template <typename T>
void List<T>::merge ( ListNodePosi(T) &p, int n, List<T>& L, ListNodePosi(T) q, int m ) {
   ListNodePosi(T) pp = p-> pred;
    while ( 0 < m )
       if (( 0 < n ) && ( p->data <= q->data )) 
          {if( q == (p = p->succ)) break; n--;} 
       else 
          {insertB(p, L.remove ((q = q->succ)->pred));m--;} 
   p = pp -> succ;
}


#endif