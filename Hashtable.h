#include <iostream>
#include "Bintree.h"

#ifndef NULL
	#define NULL 0
#endif

#define DEBUG std::cout << "fuck" << std::endl;
#define HASH_TABLE_SIZE 4096

template <typename Key,typename Value>
struct Key_Value_couple
{
	Key key;
	Value value;
	Key_Value_couple(){}
	bool operator == (Key_Value_couple ano){
		return this->key == ano.key;
	}
	void operator = (Key_Value_couple ano){
		this -> key = ano.key;
		this -> value = ano.value;
	}
};

template <typename Key,typename Value>
struct HashLinkNode
{
	HashLinkNode *next;
	Key_Value_couple<Key,Value> data;
	HashLinkNode(){
		this -> next = NULL;
	}
};
template <typename Key,typename Value>
class HashLinkList
{
private:
	HashLinkNode<Key,Value> *head;
	HashLinkNode<Key,Value> *tail;
	int _size;
public:
	HashLinkList(){
		this -> head = new HashLinkNode<Key,Value>();
		this -> tail = new HashLinkNode<Key,Value>();
		this -> head -> next = this -> tail;
		this -> tail -> next = NULL;
		this -> _size = 0;
	}
	~HashLinkList(){
		HashLinkNode<Key,Value> *tra = head;
		HashLinkNode<Key,Value> *tmp = head -> next;
		while(tra){
			tmp = tra -> next;
			delete tra;
			tra = tmp;
		}
	}

	void insert(Key_Value_couple<Key,Value> data){
		if(_size == 0){
			head -> data = data;
			_size++;
		}
		HashLinkNode<Key,Value> *new_node = new HashLinkNode<Key,Value>();
		new_node -> data.key = data.key;
		new_node -> data.value = data.value;
		new_node -> next = this -> head;
		this -> head = new_node;
		this -> _size++;
	}

	void update(Key target,Value value){
		HashLinkNode<Key,Value> *tra = this -> head;
		while(tra != tail){
			if(tra -> data.key == target){
				tra -> data.value = value;
				return;
			}
			tra = tra -> next;
		}
	}

	bool found(Key target){
		HashLinkNode<Key,Value> *tra = this -> head;
		while(tra != tail){
		std::cout << tra -> data.key<< std::endl;
			if(tra -> data.key == target){
				return true;
			}
			tra = tra -> next;
		}
		return false;
	}

	Value find(Key target){
		HashLinkNode<Key,Value> *tra = this -> head;
		while(tra != tail){
			if(tra -> data.key == target){
				return tra -> data.value;
			}
			tra = tra -> next;
		}
	}

	int size(){
		return this -> _size;
	}
};


template <typename Key,typename Value>
class HashTable
{
private:
	HashLinkList<Key,Value> *table;
	int _size;
protected:
	int get_hash_code(Key key){
		int k = (int)key;
		return k % HASH_TABLE_SIZE;
	}
public:
	HashTable(){
		_size = 0;
		table = new HashLinkList<Key,Value>[HASH_TABLE_SIZE];
	}
	~HashTable(){
		delete[] table;
	}
	int size(){
		return this -> _size;
	}
	void insert(Key key,Value value){
		int hashcode = get_hash_code(key);
		Key_Value_couple<Key,Value> data;
	 	data.key = key;
	 	data.value = value;
		if(table[hashcode].size() == 0 || (!table[hashcode].found(key))){
			table[hashcode].insert(data);
			_size++;
		}else{
			table[hashcode].update(data.key,data.value);
		}
	}

	Value find(Key key){
		int hashcode = get_hash_code(key);
		return table[hashcode].find(key);
	}
	//many bugs
	// Value& operator[](Key key){
	// 	int hashcode = get_hash_code(key);
	// 	if(table[hashcode].find(key,value)){
	// 		return value;
	// 	}else{
	// 		Key_Value_couple<Key,Value> data;
	// 		data.key = key;
	// 		table[hashcode].insert(data);
	// 		DEBUG
	// 		table[hashcode].find(key,value);
	// 		_size++;
	// 		return value;
	// 	}
	// }
};
