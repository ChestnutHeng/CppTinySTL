##Cpp STL
A tiny stl for c++ to memorize data structures and algorithms.

###API
Vector.h

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

