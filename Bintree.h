#define BinNodePosi(T) BinNode<T> *

#define stature(p) ((p)?(p)->height:-1)
#define MAX(a,b) (((a)>(b)) ? (a) : (b))

#define IsRoot(x) (!(x).parent)
#define IsLChild(x) (!IsRoot(x) && (& (x) == (x).parent -> lc))
#define IsRChild(x) (!IsRoot(x) && (& (x) == (x).parent -> rc))
#define HasParent(x) (!Isroot(x))
#define HasLChild(x) ((x).lc)
#define HasRChild(x) ((x).rc)
#define HasChild(x) (HasRChild(x) || HasLChild(x))
#define HasBothChild(x) (HasLChild(x) && HasRChild(x))
#define FromParentTo(x) (IsRoot(x)? _root : (IsLChild(x) ? (x).parent -> lc : (x).parent -> rc))
#define IsLeaf(x) (!HasChild(x))

#include <stddef.h>

#include "Queue.h"
#include "Stack.h"



typedef enum{RB_RED,RB_BLACK}RBColor;

template <typename T> 
struct BinNode
{
	T data;
	BinNodePosi(T) parent;
	BinNodePosi(T) lc;BinNodePosi(T) rc;
	int height;
	int npl;
	RBColor color;


	BinNode():
	parent(NULL),lc(NULL),rc(NULL),height(0),npl(1),color(RB_RED){}
	BinNode(T e,BinNodePosi(T) p = NULL,BinNodePosi(T) lc = NULL,BinNodePosi(T) rc = NULL,int h = 0,int l = 1,RBColor c = RB_RED):
	data(e),parent(p),lc(lc),rc(rc),height(h),npl(l),color(c){}


	int size();
	BinNodePosi(T) insertAsLC(T const&e){return lc = new BinNode<T>(e,this);};
	BinNodePosi(T) insertAsRC(T const&e){return rc = new BinNode<T>(e,this);};
	BinNodePosi(T) succ();

	template<typename VST>
	void travLevel(VST& visit){travLevel_I (this,visit);}
	template<typename VST>
	void travPre(VST& visit){travPre_I (this,visit);}
	template<typename VST>
	void travIn(VST& visit){travIn_I (this,visit);}
	template<typename VST>
	void travPost(VST& visit){travPost_I (this,visit);}

	bool operator < (BinNode const&e){return data < e.data;}
	bool operator <= (BinNode const&e){return data <= e.data;}
	bool operator > (BinNode const&e){return data > e.data;}
	bool operator >= (BinNode const&e){return data >= e.data;} 
	bool operator == (BinNode const&e){return data == e.data;}
};

template <typename T>
BinNodePosi(T) BinNode<T>::succ(){
	BinNodePosi(T) s = this;
	if (rc){
   		s = rc; 
    	while (HasLChild(*s)) 
    		s = s -> lc; 
    }else{
    	while(IsRChild(*s))
    		s = s -> parent;
    	s = s -> parent;
 	}
  	return s;
}

template <typename T, typename VST> 
void travIn_R(BinNodePosi(T) x, VST& visit){ 
   if ( !x ) return;
   travIn_R ( x->lc, visit );
   visit ( x->data );
   travIn_R ( x->rc, visit );
}

template <typename T, typename VST> 
void travIn_I(BinNodePosi(T) x, VST& visit){
	while(true){
		if(HasLChild(*x)){
			x = x ->lc;
		}else{
			visit(x -> data);
			while(!HasRChild(*x)){
				if(!(x = x -> succ())) return;
				else visit (x -> data);
			}
			x = x -> rc;
		}
	}
}

template <typename T, typename VST> 
void travLevel_I (BinNodePosi(T) x,VST& visit) {
   Queue <BinNodePosi(T)> Q; 
   Q.enqueue (x);
   while ( !Q.empty() ) { 
      x = Q.dequeue(); visit ( x->data ); 
      if (HasLChild ( *x )) Q.enqueue ( x->lc ); 
      if (HasRChild ( *x )) Q.enqueue ( x->rc );
   }
}

template <typename T, typename VST>
void travPre_R ( BinNodePosi(T) x, VST& visit ) {
   if ( !x ) return;
   visit ( x->data );
   travPre_R ( x->lc, visit );
   travPre_R ( x->rc, visit );
}

template <typename T, typename VST> 
void travPre_I(BinNodePosi(T) x, VST& visit){
	Stack <BinNodePosi(T)> S;
	while(true){
		while(x){			//push rightchild into stack
			visit( x -> data);
			if(HasRChild(*x))S.push(x -> rc);
			x = x ->lc;
		}
		if(S.empty()) break;
		x = S.pop();
	}
}

template <typename T, typename VST> 
void travPost_R ( BinNodePosi(T) x, VST& visit ) {
   if (!x) return;
   travPost_R (x->lc, visit);
   travPost_R (x->rc, visit);
   visit ( x->data );
}

template <typename T, typename VST> 
void travPost_I(BinNodePosi(T) x, VST& visit){
	Stack <BinNodePosi(T)> S;
	if(x) S.push(x);
	while(!S.empty()){
		if(S.top() != x -> parent){
			while(BinNodePosi(T) x = S.top()){
				if (HasLChild(*x)){
					S.push(x -> rc);
					S.push(x -> lc);
				}else{
					S.push(x -> rc);
				}
			}
			S.pop();
		}
		x = S.pop();
		visit(x -> data);
	}
}


template <typename T>
class BinTree
{
public:
	int size(){return _size;}
	bool empty(){return !_root;}
	int height(){return _root -> height;}
	int remove(BinNodePosi(T) x);
	BinNodePosi(T) root() const{return _root;}
	BinNodePosi(T) insertAsRoot(T const&e){_size = 1; return _root = new BinNode<T>(e);}
	BinNodePosi(T) insertAsLC(BinNodePosi(T) x,T const&e){_size++; x -> insertAsLC(e);updateHeightAbove(x);return x -> lc;}
	BinNodePosi(T) insertAsRC(BinNodePosi(T) x,T const&e){_size++; x -> insertAsRC(e);updateHeightAbove(x);return x -> rc;}
	BinNodePosi(T) attachAsLC(BinNodePosi(T) x,BinTree<T>*&S);
	BinNodePosi(T) attachAsRC(BinNodePosi(T) x,BinTree<T>*&S);

	template <typename VST>
    void travLevel(VST& visit) {if(_root)_root -> travLevel(visit);}
    template <typename VST>
    void travPre(VST& visit) {if(_root)_root -> travPre(visit);}
    template <typename VST>
    void travIn(VST& visit) {if(_root)_root -> travIn(visit);}
    template <typename VST>
    void travPost(VST& visit) {if(_root)_root -> travPost(visit);}

private:
	int _size;
	BinNodePosi(T) _root;
protected:
	virtual int updateHeight(BinNodePosi(T) x);
	int updateHeightAbove(BinNodePosi(T) x);
public:
	BinTree():_size(0),_root(NULL){}
	~BinTree(){if (_size > 0) remove(_root);}
	
};

template <typename T>
int BinTree<T>::remove(BinNodePosi(T) x){
	FromParentTo(*x) = NULL;
	updateHeightAbove(x -> parent);
	int n = removeAt(x);
	_size -= n;
	return n;
}

template <typename T>
static int removeAt (BinNodePosi(T) x) {
   if (!x) return 0;
   int n = 1 + removeAt(x -> lc) + removeAt(x -> rc);
   //release ( x->data );
   delete x;
   return n;
}


template <typename T>
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x,BinTree<T>*&S){
	if(S -> root){
		x -> lc = S -> root;
		x -> lc -> parent = x;
	}
	_size += S.size();
	S -> root = NULL;
	S -> _size = 0;
	remove(S);
	S =NULL;
	return x;
}

template <typename T>
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x,BinTree<T>*&S){
	if(S -> root){
		x -> rc = S -> root;
		x -> rc -> parent = x;
	}
	_size += S.size();
	S -> root = NULL;
	S -> _size = 0;
	remove(S);
	S =NULL;
	return x;
}

template <typename T>
int BinTree<T>::updateHeight(BinNodePosi(T) x){
	return x -> height = 1 + MAX(stature(x -> lc),stature(x -> rc));
}

template <typename T>
int BinTree<T>::updateHeightAbove(BinNodePosi(T) x){
	while(x){
		updateHeight(x);
		x = x -> parent;
	}
}

