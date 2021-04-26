#include "ThreadedBST.h"
//#include <bits/stdc++.h>
//using namespace std;

template <typename KEY, typename T>
bool ThreadedBST<KEY, T> :: insert(Elem *& root, const KEY &key, const T &data, Elem *lastLeft){
	
		Elem *ptr = root;
    Elem *par = NULL; // Parent of key to be inserted
    while (ptr != NULL)
    {
        // If key already exists, return
        if (key == (ptr->key))
        {
            cout<<"Duplicate Key !\n";
            return false;
        }
 
        par = ptr; // Update parent pointer
 
        // Moving on left subtree.
        if (key < ptr->key)
        {
        		ptr = ptr -> left;
        }
				else
        {
            if (ptr->rightThread == false)
                ptr = ptr -> right;
            else
                break;
        }
    }
 
    // Create a new node
    Elem *tmp = new Elem;
    tmp -> key = key;
    tmp -> data = data;
    tmp -> rightThread = true;
    _size++;
 
    if (par == NULL)
    {
        root = tmp;
        tmp -> left = NULL;
        tmp -> right = NULL;
    }
    else if (key < (par -> key))
    {
        tmp -> left = NULL;
        tmp -> right = par;
        par -> left = tmp;
    }
    else
    {
        tmp -> right = par -> right;
        par -> rightThread = false;
        par -> right = tmp;
    }
 
    return true;
}

template <typename KEY, typename T>
void ThreadedBST<KEY, T> :: printTree(ostream& out, int level, Elem *p) const
{
	if (p == NULL){
        cout<<"Tree is empty"<<endl;
        return;
  }
 
    // Reach leftmost node
    struct Elem *ptr = p;
    while (ptr -> left)
        ptr = ptr -> left;
 
    // One by one print successors
    while (ptr != NULL)
    {
        out<<ptr -> data<<" ";
        
        if (ptr -> rightThread == true)
        	ptr = ptr->right;
        else{
        	 ptr = ptr -> right;
   				 while (ptr -> left)
        			ptr = ptr -> left;
        }
    }     
    out<<endl;
}

template <typename KEY, typename T>
void ThreadedBST<KEY, T> :: destructCode(Elem *& p){
	deleteInPostOrder(p, NULL);
}

template <typename KEY, typename T>
void ThreadedBST<KEY, T> :: deleteInPostOrder(Elem *& ptr, Elem *par){
	if(ptr == NULL)
		return; 
	
	deleteInPostOrder(ptr->left, ptr);	
	if(!ptr->rightThread)
		deleteInPostOrder(ptr->right, ptr);
		
	if(!par){
		free(ptr);
		ptr = NULL;
		return;
	}
	
	if(par->left && par->left->key == ptr->key)
		par->left = NULL;
	else
		par->right = NULL;
		
	free(ptr);
}


int main(){
	
	ThreadedBST<int, int> *threadedBST = new ThreadedBST<int, int>;
	threadedBST->_root = NULL;   
	threadedBST->_size = 0;
 
  threadedBST->insert(threadedBST->_root, 20, 20, NULL);
  threadedBST->insert(threadedBST->_root, 10, 10, NULL);
  threadedBST->insert(threadedBST->_root, 30, 30, NULL);
  threadedBST->insert(threadedBST->_root, 5 , 5 , NULL);
  threadedBST->insert(threadedBST->_root, 16, 16, NULL);
  threadedBST->insert(threadedBST->_root, 14, 14, NULL);
  threadedBST->insert(threadedBST->_root, 17, 17, NULL);
  threadedBST->insert(threadedBST->_root, 13, 13, NULL);
 	
  threadedBST->printTree(cout, 0, threadedBST->_root);
  
  threadedBST->destructCode(threadedBST->_root);
  
  threadedBST->printTree(cout, 0, threadedBST->_root);
	return 0;
}

