#include <stddef.h>
#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>

#include "Time.h"



struct TrieNode
{
	TrieNode *_children[27];
	double _freq;
	bool isword;
};


class TrieTree
{
private:
	TrieNode *_root;

public:
	TrieTree(){
		_root = new TrieNode();
		_root -> isword = true;
		for (int i = 0; i < 27; ++i)
		{
			_root -> _children[i] = NULL;
		}
	}
	~TrieTree(){
	    deltree(_root);
	}


	void addWord(const char *,double);
	double findWord(const char *);
	void deltree(TrieNode *_root);
};

void TrieTree::addWord(const char *input,double freq){
	char *pt;
	TrieNode *tra = _root;
	for (pt = (char *)input; *pt != '\0'; ++pt){
		if(*pt != '\''){
			if(tra -> _children[*pt - 'a'] == NULL)
				tra -> _children[*pt - 'a'] = new TrieNode();
			tra = tra -> _children[*pt - 'a'];
		}else{
			if(tra -> _children[26] == NULL)
				tra -> _children[26] = new TrieNode();
			tra = tra -> _children[26];
		}
	}
	tra -> isword = true;
	tra -> _freq = freq;
}



double TrieTree::findWord(const char *input){
	char *pt = (char *)input;
	TrieNode *tra = _root;

	while(*pt != '\0' ){
		if(*pt == '\''){
			tra = tra -> _children[26];
		}else{
			tra = tra -> _children[*pt - 'a'];
		}
		if(!tra) return 0;
		++pt;
	}
	if(tra -> isword)
		return tra -> _freq;
	else
		return 0;
}

void TrieTree::deltree(TrieNode *root){
	int i;
    for(i = 0;i < 27; ++i){
        if(root->_children[i] != NULL){
            deltree(root->_children[i]);
        }
    }
    delete root;
}


struct WordNode
{
	WordNode *_children[26];
	std::vector<std::string> words;
	bool isword;
	double unigram;
};


class WordTree
{
private:
	WordNode *_root;

public:
	WordTree(){
		_root = new WordNode();
		_root -> isword = true;
		for (int i = 0; i < 26; ++i)
		{
			_root -> _children[i] = NULL;
		}
	}
	~WordTree(){
	    deltree(_root);
	}


	void addWord(std::string ,const char *,double freq);
	std::vector<std::string> findWord(const char *);
	std::vector<std::string> dfsWord(const char *); 
	void deltree(WordNode *_root);

	double finduni(const char *input){
		std::vector<std::string> v;
		char *pt = (char *)input;
		WordNode *tra = _root;

		while(*pt != '\0' ){
			tra = tra -> _children[*pt - 'a'];
			if(!tra) return 0;
			++pt;
		}

		return tra -> unigram;
	}
};

void WordTree::addWord(std::string word,const char *code,double freq){
	char *pt;
	WordNode *tra = _root;
	for (pt = (char *)code; *pt != '\0'; ++pt){
		if(*pt != '\''){
			if(tra -> _children[*pt - 'a'] == NULL)
				tra -> _children[*pt - 'a'] = new WordNode();
			tra = tra -> _children[*pt - 'a'];
		}
	}
	tra -> isword = true;
	tra -> unigram = freq;
	tra -> words.push_back(word);
}

std::vector<std::string> WordTree::findWord(const char *input){
	std::vector<std::string> v;
	char *pt = (char *)input;
	WordNode *tra = _root;

	while(*pt != '\0' ){
		tra = tra -> _children[*pt - 'a'];
		if(!tra) return v;
		++pt;
	}

	return tra -> words;
}

void dfsword(std::string inp,WordNode *tra,std::vector<std::string> &v){
	if(tra == NULL) return;
	
	v.push_back(inp);

	for (int i = 0; i < 26; ++i){
		if(tra -> _children[i] != NULL){
			dfsword(inp + (char)('a' + i), tra -> _children[i],v);
		}
	}
}

std::vector<std::string> WordTree::dfsWord(const char *input){
	char *pt = (char *)input;
	WordNode *tra = _root;
	std::vector<std::string> v;
	std::string inp(input);

	while(*pt != '\0' ){
		tra = tra -> _children[*pt - 'a'];
		if(tra == NULL) return v;
		++pt;
	}
	dfsword(inp,tra,v);
	return v;
}

void WordTree::deltree(WordNode *root){
	int i;
    for(i = 0;i < 26; ++i){
        if(root->_children[i] != NULL){
            deltree(root->_children[i]);
        }
    }
    delete root;
}