Tags : Git_Readme

#Cpp STL
---
A tiny stl for c++ to memorize data structures and algorithms.

##Vector.h
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

API:

|API|Info|
|---|---|
|bool empty()|return this stack is empty or not|
|int size()|return the size of this stack|
|void push(T const&e)|push an element into stack|
|T pop()|pop an element out of stack|
|T top()|return top element of stack|


---


##Queue.h

API:

|API|Info|
|---|---|
|size()|return _size|
|empty()|return if empty or not|
|void enqueue ( T const& e )|入队：尾部插入|
|T dequeue()|出队：首部删除|
|T& front()|返回队首|

