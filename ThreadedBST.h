#ifndef __THREADED_BST_H__
#define __THREADED_BST_H__

#include <bits/stdc++.h>
using namespace std;

template <typename KEY, typename T>
class ThreadedBST{
	public:
	struct Elem {
		KEY key;
		T data;
		Elem *left;
		Elem *right;
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

};


#endif //__THREADED_BST_H__