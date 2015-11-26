Tags : Git_Readme

#Cpp STL
---
A tiny stl for c++ to memorize data structures and algorithms.

##Vector.h
Vector&lt; typename Te&gt;value;
###API

| API | Info |
|:----------|:----------|
|  size()     |  return vector's size|
|  get(const rank) |return element's value|
|  put(const rank,const element) |change element's value|
| insert(const rank,const element) |insert a value|
|  remove(const rank)| del|
|   disordered()| return ordered or not|
|  sort()|quicksort|
|  find(const element)| return element with max rank|
| search(const element)| return element LSQ than e with max rank|
| deduplicate() |remove the deduplicate element (disordered vector)|
| uniquify()|remove the deduplicate element(ordered vector)|
|traverse() |traverse the vector and edit every element|
|  [],=,==,>,<,>=,<=|operaters|

###Tips:
|Function|Tips|
|---|---|
|extand()|扩容的条件和方式|
|shrink() |注意return的条件|
|find() |从后向前|
|search() fib,bin |Fib类的构造和用法|
|uniquify()  |注意O(n)复杂度,扫描一遍即可|
|deduplicate() |扫描每个元素的前置元素以保证清除彻底|
|traverse()|函数指针和函数对象的应用|


---



##List.h

List&lt; typename Te&gt;value;

API:

| API | Info |
|:---|:---|
|Rank size() const |规模|
|bool empty() const|判空|
|T& operator[] ( Rank r ) const |重载，支持循秩访问（效率低）|
|ListNodePosi(T) first() const|首节点位置|
|ListNodePosi(T) last() const|末节点位置|
|bool valid ( ListNodePosi(T) p ) |判断位置p是否对外合法|
|bool disordered() const|判断列表是否已排序|
|ListNodePosi(T) find ( T const& e ) const|无序列表查找|
|ListNodePosi(T) find ( T const& e, int n, ListNodePosi(T) p ) const|无序区间查找|
|ListNodePosi(T) search ( T const& e ) const|有序列表查找|
|ListNodePosi(T) search ( T const& e, int n, ListNodePosi(T) p ) const|有序区间查找|
|ListNodePosi(T) selectMax ( ListNodePosi(T) p, int n )|在p及其n-1个后继中选出最大者
|ListNodePosi(T) selectMax() { return selectMax ( header->succ, _size )|整体最大者
|ListNodePosi(T) insertAsFirst ( T const& e )|将e当作首节点插入
|ListNodePosi(T) insertAsLast ( T const& e )|将e当作末节点插入
|ListNodePosi(T) insertA ( ListNodePosi(T) p, T const& e )|将e当作p的后继插入
|ListNodePosi(T) insertB ( ListNodePosi(T) p, T const& e )|将e当作p的前驱插入
|ListNodePosi(T) push_back(T const& e)|将e推入结尾
|T remove ( ListNodePosi(T) p )|删除合法位置p处的节点,返回被删除节点
|void merge ( List<T>& L ) { merge ( first(), size, L, L.first(), L._size )|全列表归并
|void sort ( ListNodePosi(T) p, int n )|列表区间排序
|void sort() { sort ( first(), _size )|列表整体排序
|int deduplicate()|无序去重|
|int uniquify()|有序去重|
|void reverse()|前后倒置（习题）|
|void traverse ( void (* ) ( T& ) )|遍历，依次实施visit操作（函数指针，只读或局部性修改）|



---
##Stack.h
Stack&lt; typename Te&gt;value;
*MinStack&lt; typename Te&gt;value;
*MaxStack&lt; typename Te&gt;value;
*MinQueue&lt; typename Te&gt;value;
*MaxQueuek&lt; typename Te&gt;value;

API:

|API|Info|
|---|---|
|bool empty()|return this stack is empty or not|
|int size()|return the size of this stack|
|void push(T const&e)|push an element into stack|
|T pop()|pop an element out of stack|
|T top()|return top element of stack|
|T max()|*return max element of stack|
|T min()|*return min element of stack|
*in MaxStack.h


---


##Queue.h
Queue&lt; typename Te&gt;value;
API:

|API|Info|
|---|---|
|size()|return _size|
|empty()|return if empty or not|
|void enqueue ( T const& e )|入队：尾部插入|
|T dequeue()|出队：首部删除|
|T& front()|返回队首|


---

##BinTree.h
Bintree&lt; typename Te&gt;value;
API:
|API|INFO|
|---|---|
|int size() const |规模
|bool empty() const |判空
| BinNodePosi(T) root()|树根
|BinNodePosi(T) insertAsRoot ( T const& e )|插入根节点
|BinNodePosi(T) insertAsLC ( BinNodePosi(T) x, T const& e )|e作为x的左孩子（原无）插入
|BinNodePosi(T) insertAsRC ( BinNodePosi(T) x, T const& e )|e作为x的右孩子（原无）插入
|BinNodePosi(T) attachAsLC ( BinNodePosi(T) x, BinTree<T>* &T )|T作为x左子树接入
|BinNodePosi(T) attachAsRC ( BinNodePosi(T) x, BinTree<T>* &T )|T作为x右子树接入
| int remove ( BinNodePosi(T) x )|删除以位置x处节点为根的子树，返回该子树原先的规模
|BinTree<T>* secede ( BinNodePosi(T) x )|将子树x从当前树中摘除，并将其转换为一棵独立子树
|void travLevel ( VST& visit ) { if ( _root ) _root->travLevel ( visit )|层次遍历
|void travPre ( VST& visit ) { if ( _root ) _root->travPre ( visit )|先序遍历
|oid travIn ( VST& visit ) { if ( _root ) _root->travIn ( visit )|中序遍历
|void travPost ( VST& visit ) { if ( _root ) _root->travPost ( visit )|后序遍历
|bool operator < ( BinTree<T> const& t )|比较器（==,>,<,>=,<=）
|void dbgPrint()|打印二叉树（竖着看）

###Tips:
|Function|Tips|
|---|---|
|travLevel()|把每层的节点依次压入队列|
|travIn()|不断迭代到左侧最深叶子处(访问)，然后返回直接后继(访问)，再按本算法处理右子树|
|travPre()|不断访问左孩子，把右孩子压入栈中，左侧到底后弹出栈顶，按本算法处理栈顶，直至为空|
|travPost()|递归实现|


---

##Graph.h
GraphList&lt; typename Tv, typename Te &gt;value;
GraphMatrix&lt; typename Tv, typename Te &gt;value;

###API:
|API|INFO|
|---|---|
| void BFS ( int, int& )|（连通域）广度优先搜索算法
|void DFS ( int, int& )|（连通域）深度优先搜索算法
|void BCC ( int, int&, Stack<int>& )|（连通域）基于DFS的双连通分量分解算法
|bool TSort ( int, int&, Stack<Tv>* )|（连通域）基于DFS的拓扑排序算法
|void PFS ( int, PU )|（连通域）优先级搜索框架
|virtual int insert ( Tv const& ) = 0|插入顶点，返回编号
|virtual Tv remove ( int ) = 0|删除顶点及其关联边，返回该顶点信息
|virtual Tv& vertex ( int ) = 0|顶点v的数据（该顶点的确存在）
|virtual int inDegree ( int ) = 0|顶点v的入度（该顶点的确存在）
|virtual int outDegree ( int ) = 0|顶点v的出度（该顶点的确存在）
|virtual int firstNbr ( int ) = 0|顶点v的首个邻接顶点
| virtual int nextNbr ( int, int ) = 0|顶点v的（相对于顶点j的）下一邻接顶点
| virtual VStatus& status ( int ) = 0|顶点v的状态
| virtual int& dTime ( int ) = 0|顶点v的时间标签dTime
|virtual int& fTime ( int ) = 0|顶点v的时间标签fTime
|virtual int& parent ( int ) = 0|顶点v在遍历树中的父亲
|virtual int& priority ( int ) = 0|顶点v在遍历树中的优先级数
|virtual bool exists ( int, int ) = 0|边(v, u)是否存在
|virtual void insert ( Te const&, int, int, int ) = 0|在顶点v和u之间插入权重为w的边e
|virtual Te remove ( int, int ) = 0|删除顶点v和u之间的边e，返回该边信息
|virtual EType& type ( int, int ) = 0|边(v, u)的类型
|virtual Te& edge ( int, int ) = 0|边(v, u)的数据（该边的确存在）
|virtual int& weight ( int, int ) = 0|边(v, u)的权重
|void bfs ( int )|广度优先搜索算法
|void dfs ( int )|深度优先搜索算法
|void bcc ( int )|基于DFS的双连通分量分解算法
|Stack<Tv>* tSort ( int )|基于DFS的拓扑排序算法
|void prim ( int )|最小支撑树Prim算法
|void dijkstra ( int )|最短路径Dijkstra算法
|template <typename PU> void pfs ( int, PU )|优先级搜索框架


---

##BSTree.h
BSTree &lt; typename T &gt; value;
###API:
|API|INFO|
|---|---|
|virtual BinNodePosi(T) &search(const T&e)|搜索
|virtual BinNodePosi(T) insert(const T&e)|插入
|virtual bool remove(const T&e)|删除
AVLTree &lt; typename T &gt; value;
|API|INFO|
|---|---|
|BinNodePosi(T) insert (const T&e)|插入
|bool remove(const T &e)|删除

