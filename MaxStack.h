#ifndef _MAX_STACK_
#define _MAX_STACK_

#include "Stack.h"

#ifndef NULL 
	#define NULL 0
#endif

template <typename T>
class MaxStack
{
private:
	Stack <T> max_stack;
	Stack <T> _data;
public:
	bool empty(){
		return _data.empty();
	}
	T max(){
		return max_stack.top();
	}
	void push(T ele){
		_data.push(ele);
		if(max_stack.empty() || ele >= max_stack.top()){
			max_stack.push(ele);
		}
	}
	T pop(){
		T tmp = _data.top();
		if(_data.pop() == max_stack.top()){
			max_stack.pop();
		}
		return tmp;
	}
	T top(){
		return _data.top();
	}
};

template <typename T>
class MaxQueue{
private:
	MaxStack <T> s1,s2;

public:
	bool empty(){
		return s1.empty() && s2.empty();
	}
	void enqueue(T ele){
		s1.push(ele);
	}
	T dequeue(){
		if(s2.empty()){
			while(!s1.empty()){
				s2.push(s1.top());
				s1.pop();
			}
		}
		return s2.pop();
	}
	T front(){
		if(s2.empty()){
			while(!s1.empty()){
				s2.push(s1.top());
				s1.pop();
			}
		}
		return s2.top();
	}
	T max(){
		if((!s1.empty()) && (!s2.empty()))
			return (s1.max() > s2.max() ? s1.max() : s2.max());
		else if ((!s1.empty()) && (s2.empty()))
			return s1.max();
		else return s2.max();
	}
};

template <typename T>
class MinStack
{
private:
	Stack <T> min_stack;
	Stack <T> _data;
public:
	bool empty(){
		return _data.empty();
	}
	T min(){
		return min_stack.top();
	}
	void push(T ele){
		_data.push(ele);
		if(min_stack.empty() || ele <= min_stack.top()){
			min_stack.push(ele);
		}
	}
	T pop(){
		T tmp = _data.top();
		if(_data.pop() == min_stack.top()){
			min_stack.pop();
		}
		return tmp;
	}
	T top(){
		return _data.top();
	}
};

template <typename T>
class MinQueue{
private:
	MinStack <T> s1,s2;

public:
	bool empty(){
		return s1.empty() && s2.empty();
	}
	void enqueue(T ele){
		s1.push(ele);
	}
	T dequeue(){
		if(s2.empty()){
			while(!s1.empty()){
				s2.push(s1.top());
				s1.pop();
			}
		}
		return s2.pop();
	}
	T front(){
		if(s2.empty()){
			while(!s1.empty()){
				s2.push(s1.top());
				s1.pop();
			}
		}
		return s2.top();
	}
	T max(){
		if((!s1.empty()) && (!s2.empty()))
			return (s1.min() > s2.min() ? s1.min() : s2.min());
		else if ((!s1.empty()) && (s2.empty()))
			return s1.min();
		else return s2.min();
	}
};

#endif

