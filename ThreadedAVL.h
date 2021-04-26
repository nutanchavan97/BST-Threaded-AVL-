#ifndef __THREADED_AVL_H__
#define __THREADED_AVL_H__

#include <bits/stdc++.h>
using namespace std;

template <typename KEY, typename T>
class ThreadedAVL{
	public:
	struct Elem {
		Elem():left(0), right(0), height(-1), rightThread(false) {}
		KEY key;
		T data;
		Elem *left;
		Elem *right;
		int height;
		bool rightThread; //normal right child link or a threadlink
	};
	                       
	//template <typename KEY, typename T>
	Elem *_root; // a dummy root sentinel
	int _size;
	
	// helper method for inserting record into tree.
	bool insert(Elem *& root, const KEY &key, const T &data, Elem *lastLeft);
	
	// helper method for print tree
	void printTree(ostream& out, int level, Elem *p) const;
	
	// common code for deallocation
	void destructCode(Elem *& p);
	
	void deleteInPostOrder(Elem *& ptr, Elem *par);
	
	void rotateRight(Elem *& node);
	void rotateLeft(Elem *& node);
	void doubleRotateRight(Elem *& node);
	void doubleRotateLeft(Elem *& node);
	int balanceFactor(Elem *cur);
	void balance(Elem*& cur, const KEY &key);
	int height(Elem *node);
	void updateHeight(Elem*& cur);

};


#endif //__THREADED_AVL_H__