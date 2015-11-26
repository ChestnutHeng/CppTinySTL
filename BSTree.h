#include "Bintree.h"

#define EQUAL(e,v) (!(v) || (e) == (v) -> data)

template <typename T>
class BSTree : public BinTree<T>
{
protected:
	BinNodePosi(T) _hot;
	BinNodePosi(T) connect34(
		BinNodePosi(T), BinNodePosi(T), BinNodePosi(T),
		BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T)
	);
	BinNodePosi(T) rotateAt(BinNodePosi(T) x);
	BinNodePosi(T) &searchIn(BinNodePosi(T) &v,const T&e,BinNodePosi(T) &hot);
	BinNodePosi(T) removeAt(BinNodePosi(T) &x,BinNodePosi(T) &hot);
	void swap(T &a,T &b);
public:
	virtual BinNodePosi(T) &search(const T&e);
	virtual BinNodePosi(T) insert(const T&e);
	virtual bool remove(const T&e);

};

template <typename T>
void BSTree<T>::swap(T &a, T &b){
	T tmp  = a;
	a = b;
	b = tmp;
}

template <typename T>
BinNodePosi(T) BSTree<T>::rotateAt(BinNodePosi(T) v){
	BinNodePosi(T) p = v -> parent;		//papa
	BinNodePosi(T) g = p -> parent;		//greatpa
	if( IsLChild(*p) ){ //Zig
		if( IsLChild(*v) ){		//Zig-Zig
			p -> parent = g -> parent;
			return connect34(v,p,g,v -> lc,v -> rc,p -> rc,g -> rc);
		}else{		//Zig-Zag
			v -> parent = g -> parent;
			return connect34(p,v,g,p -> lc,v -> lc,v -> rc,g -> rc);
		}
	}else{	//Zag
		if( IsRChild(*v) ){ //Zag-Zag
			p -> parent = g -> parent;
			return connect34(g,p,v,g -> lc, p-> lc,v -> lc,v -> rc);
		}else{ //Zag-Zig
			v -> parent = g -> parent;
			return connect34(g,v,p,g -> lc,v -> lc,v -> rc,p -> rc);
		}
	}
}

template <typename T>
BinNodePosi(T) BSTree<T>::connect34(
	BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c,
	BinNodePosi(T) T0, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3){
	a -> lc = T0; if( T0 ) T0 -> parent = a;
	a -> rc = T1; if( T1 ) T1 -> parent = a;
	this -> updateHeight(a);
	c -> lc = T2; if( T2 ) T2 -> parent = c;
	c -> rc = T3; if( T3 ) T3 -> parent = c;
	this -> updateHeight(c);
	b -> lc = a; a -> parent = b;
	b -> rc = c; c -> parent = b;
	this -> updateHeight(b);
	return b;
}


template <typename T>
BinNodePosi(T) BSTree<T>::insert(const T&e){
	BinNodePosi(T) &x = search(e);
	if(x) return x;
	x = new BinNode<T>(e,_hot);
	(this -> _size )++;
	this -> updateHeightAbove(x);
	return x;
}

template <typename T>
BinNodePosi(T)& BSTree<T>::search(const T&e){
	return searchIn(this -> _root,e,this -> _hot = NULL);
}

template <typename T>
BinNodePosi(T)& BSTree<T>::searchIn(BinNodePosi(T) &v,const T&e,BinNodePosi(T) &hot){
	if( EQUAL(e,v) ){
		return v;
	}
	hot = v;
	while(true){
		BinNodePosi(T) &c = (e < hot -> data) ? hot -> lc : hot -> rc ;
		if(EQUAL(e,c)) return c;
		hot = c;
	}
}

template <typename T>
bool BSTree<T> ::remove(const T&e){
	BinNodePosi(T) &x = search(e);
	if(!x) return false;
	removeAt(x,_hot);
	(this -> _size )--;
	this -> updateHeightAbove(_hot);
	return true;
}

template <typename T>
BinNodePosi(T) BSTree<T> ::removeAt(BinNodePosi(T) &x,BinNodePosi(T) &hot){
	BinNodePosi(T) w = x;
	BinNodePosi(T) succ = NULL;
	if( !HasLChild(*x) ){
		succ = x = x -> rc;
	}else if( !HasRChild(*x) ){
		succ = x = x -> rc;
	}else{
		w = w -> succ();
		swap(x -> data, w -> data);
		BinNodePosi(T) u = w -> parent;
		( (u == x) ? u -> rc : u -> lc ) = succ = w -> rc;
	}
	hot = w -> parent;
	if(succ)
		succ -> parent = hot;
	delete w;
	return succ;
}


#define Balanced(x) ( stature((x).lc) == stature((x).rc) )
#define BalFac(x) (stature((x).lc) - stature((x).rc)) 
#define AvlBalanced(x) ( ( -2 < BalFac(x) ) && ( BalFac(x) < 2 ) )
#define FromParentTo_AVL(x) (IsRoot(x)? this -> _root : (IsLChild(x) ? (x).parent -> lc : (x).parent -> rc))
#define tallerChild(x) (\
	stature( (x) -> lc ) > stature( (x) -> rc ) ? (x) -> lc : (\
	stature( (x) -> lc ) < stature( (x) -> rc ) ? (x) -> rc : (\
	IsLChild(( *x )) ? (x) -> lc : (x) -> rc \
	)\
	)\
)

template <typename T>
class AVLTree : public BSTree<T>
{
public:
	BinNodePosi(T) insert (const T&e);
	bool remove(const T &e);
};

template <typename T>
BinNodePosi(T) AVLTree<T>::insert(const T&e){
	BinNodePosi(T) &x = this -> search(e);
	if( x ) return x;
	BinNodePosi(T) xx = x = new BinNode<T>(e,this -> _hot);
	(this -> _size)++;
	for (BinNodePosi(T) g = this -> _hot; g != NULL; g = g -> parent){
		if(!AvlBalanced(*g)){		
			int tag = -1;
			if(IsRoot(*g)){
				tag = 0;
			}else if(IsLChild(*g)){
				tag = 1;
			}else if(IsRChild(*g)){
				tag = 2;
			}
			BinNodePosi(T) ori_p = g -> parent;
			g  = this -> rotateAt( tallerChild ( tallerChild (g) ) );
			g -> parent = ori_p;
			if(tag == 0){
				this -> _root = g;
			}else if(tag == 1){
				g -> parent -> lc = g;
			}else if(tag == 2){
				g -> parent -> rc = g;
			}
			break;
		}else{
			this -> updateHeight(g);
		}
	}
	return xx;
}


template <typename T>
bool AVLTree<T>::remove(const T&e){
	BinNodePosi(T) &x = this -> search(e);
	if(!x) return false;
	this -> removeAt(x, this -> _hot);
	(this -> _size )--;
	for (BinNodePosi(T) g = this -> _hot;g != NULL;g = g -> parent){
		if(!AvlBalanced(*g)){
			int tag = -1;
			if(IsRoot(*g)){
				tag = 0;
			}else if(IsLChild(*g)){
				tag = 1;
			}else if(IsRChild(*g)){
				tag = 2;
			}
			BinNodePosi(T) ori_p = g -> parent;
			g  = this -> rotateAt( tallerChild ( tallerChild (g) ) );
			g -> parent = ori_p;
			if(tag == 0){
				this -> _root = g;
			}else if(tag == 1){
				g -> parent -> lc = g;
			}else if(tag == 2){
				g -> parent -> rc = g;
			}
			break;
		}
		this -> updateHeight(g);
	}
	return true;
}

