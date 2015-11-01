#include <stddef.h>
#include <limits.h>

#include "Stack.h"
#include "Queue.h"
#include "Vector.h"

using namespace std;

typedef enum{UNDISCOVERED,DISCOVERED,VISITED}VStatus;
typedef enum{UNDETERMINED,TREE,CROSS,FORWARD,BACKWORD}EType;

template <typename Tv,typename Te>
class Graph
{
private:
	int count_v;
	int count_e;
	
public:
	void reset(){
		for (int i = 0; i < count_v; ++i)
		{
			status(i) = UNDISCOVERED;
			dTime(i) = fTime(i) = -1;
			parent(i) = -1;
			priority(i) = INT_MAX;
			for (int j = 0; j < count_v; ++j){
				if(exists(i,j)) type(i,j) = UNDETERMINED;
			}
		}
	}

	Graph(){};
	~Graph(){};

	int getCount_v(){return count_v;}
	void setCount_v(int v){count_v = v;}
	int getCount_e(){return count_v;}
	void setCount_e(int e){count_e = e;}
	void BFS(int,int&);
	void DFS(int,int&);
	void BCC(int,int&,Stack<int>&);
	void TSort(int,int&,Stack<Tv>*);
	template <typename PU> void PFS(int,PU);

	//vertex func
	virtual int insert(Tv const&) = 0;
	virtual Tv remove(int) = 0;
	virtual Tv& vertex(int) = 0;
	virtual int inDegree(int) = 0;
	virtual int outDegree(int) = 0;
	virtual int firstNbr(int) = 0;
	//virtual int nextNbr(int) = 0;
	virtual VStatus &status(int) = 0;
	virtual int&dTime(int) = 0;
	virtual int&fTime(int) = 0;
	virtual int&parent(int) = 0;
	virtual int&priority(int) = 0;

	//edge func
	virtual bool exists(int,int) = 0;
	virtual void insert(Te const&,int,int,int) = 0;
	virtual Te remove(int,int) = 0;
	virtual EType& type(int,int) = 0;
	virtual Te& edge(int,int) = 0;
	virtual int&weight(int,int) = 0;

	void bfs(int);
	void dfs(int);
	void bcc(int);
	Stack<Tv>* tSort(int);
	void prim(int);
	void dijkstra(int);
	template <typename PU> void pfs(int,PU);
};


template <typename Tv>
struct Vertex
{
	Tv data;
	int inDegree;
	int outDegree;
	VStatus status;
	int dTime,fTime;
	int parent;
	int priority;
	Vertex(Tv const&d = (Tv)0):
		data(d),inDegree(0),outDegree(0),status(UNDISCOVERED),
		dTime(-1),fTime(-1),parent(-1),priority(INT_MAX){}
};

template <typename Te>
struct Edge
{
	Te data;
	int weight;
	EType type;
	Edge(Te const&d,int w):data(d),weight(w),type(UNDETERMINED){}
};

template <typename Tv,typename Te>
class GraphMatrix : public Graph <Tv,Te>
{
private:
	Vector< Vertex<Tv> > V;
	Vector <Vector < Edge<Te> * > > E;

public:
	GraphMatrix(){this -> setCount_e(0);this -> setCount_v(0);};
	~GraphMatrix(){
		for (int i = 0; i < this -> getCount_v(); ++i)
			for (int j = 0; j < this -> getCount_e(); ++j)
				delete E[i][j];
	}

	virtual Tv& vertex(int i){return V[i].data;}
	virtual int inDegree(int i){return V[i].inDegree;}
	virtual int outDegree(int i){return V[i].outDegree;}
	virtual int firstNbr(int i){return nextNbr(i,this -> getCount_v());}
	virtual int nextNbr(int i,int j){while((j > -1) && (!exists(i,--j)));return j;}
	virtual VStatus& status(int i){return V[i].status;}
	virtual int &dTime(int i){return V[i].dTime;}
	virtual int &fTime(int i){return V[i].fTime;}
	virtual int &parent(int i){return V[i].parent;}
	virtual int &priority(int i){return V[i].priority;}

	virtual int insert(Tv const&vertex){
		int count_v = this -> getCount_v();
		for (int i = 0; i < count_v; ++i){
			E[i].push_back(NULL);
		}
		this -> setCount_v(++count_v);
		E.push_back(Vector< Edge<Te>* > (count_v,(Edge<Te>*)NULL));
		V.push_back(Vertex<Tv>(vertex));
		return 0; //return rank of vector
	}
	virtual Tv remove(int j){
		int count_v = this -> getCount_v();
		for (int i = 0; i < count_v; ++i) {
			if(exists(j,i)) {delete E[i][j];V[j].inDegree--;}
		}
		E.remove(j);
		this -> setCount_v(--count_v);
		Tv tmp = vertex(j);
		V.remove(j);
		for (int i = 0; i < count_v; ++i){
			if(Edge<Te> *e = E[i][i]){
				E[i].remove(i);
				delete e;
				V[i].outDegree--;
			}
		}
		return tmp;
	}

	virtual bool exists(int i,int j){
		return (i >= 0)&&(i < this -> getCount_v())&&(j >= 0)&&(j < this -> getCount_v())&&(E[i][j] != NULL);
	}
	virtual EType& type(int i,int j){return E[i][j] -> type;}
	virtual Te& edge(int i,int j){return E[i][j] -> data;}
	virtual int &weight(int i,int j){return E[i][j] -> weight;}
	virtual void insert(Te const&edge,int w,int i,int j){
		if(exists(i,j)) return;
		E[i][j] = new Edge<Te> (edge,w);
		this -> setCount_e(this -> getCount_e() + 1);
		V[i].outDegree++;
		V[j].inDegree++;
	}
	virtual Te remove(int i,int j){
		Te tmp = edge(i,j);
		delete E[i][j];
		E[i][j] = NULL;
		this -> setCount_e(this -> getCount_e() - 1);
		V[i].outDegree--;
		V[j].inDegree--;
	}

	virtual void BFS(int,int&);
	virtual void dijkstra(int);

};

template <typename Tv, typename Te>
void GraphMatrix<Tv,Te>::BFS(int v,int &clock){
	Queue<int>Q;
	status(v) = DISCOVERED;
	Q.enqueue(v);
	while(!Q.empty()){
		int v = Q.dequeue();
		dTime(v) = ++clock;
		for (int u = firstNbr(v); u > -1; u = nextNbr(v,u)){
			if(UNDISCOVERED == status(u)){
				status(u) = DISCOVERED;
				Q.enqueue(u);
				type(v,u) = TREE;
				parent(u) = v;
			} else {
				type(v,u) = CROSS;
			}
		}
		status(v) = VISITED;
	}
}

template <typename Tv,typename Te>
void GraphMatrix<Tv, Te>::dijkstra (int s) {
    this -> reset();
    priority (s) = 0;
    for (int i = 0;i < this -> getCount_v(); i++){
        status(s) = VISITED;
        if (-1 != parent(s)) type(parent(s),s) = TREE;
        for (int j = firstNbr(s); -1 < j; j = nextNbr(s,j)) 
        	if ((status(j) == UNDISCOVERED) && (priority(j) > priority(s) + weight(s,j))){
         		priority(j) = priority(s) + weight(s, j);
         		parent (j) = s;
        }
    	for (int shortest = INT_MAX, j = 0; j < this -> getCount_v(); j++ ) 
         	if ((status (j) == UNDISCOVERED) && (shortest > priority(j))){
         		shortest = priority(j);
         		s = j;
        }
    }
}
