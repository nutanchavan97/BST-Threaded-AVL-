#include "ThreadedAVL.h"
//#include <bits/stdc++.h>
//using namespace std;


template <typename KEY, typename T>
void ThreadedAVL<KEY, T> :: rotateRight(Elem *& node){
	Elem oldRoot = *node;
	Elem x = *(oldRoot.left);
    Elem *T2 = NULL;
	
	if(!x.rightThread)
		T2 = x.right;
 
    // Perform rotation
    x.right = node;
	x.rightThread = false;
    node->left = T2;
 
    // Update heights
    oldRoot.height = max(height(oldRoot.left),
                    height(oldRoot.right)) + 1;
    x.height = max(height(x.left),
                    height(x.right)) + 1;
					
	node = &x;
}

template <typename KEY, typename T>
void ThreadedAVL<KEY, T> :: rotateLeft(Elem *& node){
	
	Elem oldRoot = *node;
	Elem *x = oldRoot.right;
    Elem *T2 = x->left;
 
    // Perform rotation
    x->left = node;
    node->right = T2;
	
	if(T2 == NULL){
		cout<<"T2 is NULL"<<endl;
		node->right = x;
		node->rightThread = true;
	}
	
    oldRoot.height = max(height(oldRoot.left),
                    height(oldRoot.right)) + 1;
	
    x->height = max(height(x->left),
                    height(x->right)) + 1;
						
	node = x;
}

/*template <typename KEY, typename T>
void ThreadedAVL<KEY, T> :: updateHeight(Elem*& cur){
	
}*/

template <typename KEY, typename T>
bool ThreadedAVL<KEY, T> :: insert(Elem *& root, const KEY &key, const T &data, Elem *lastLeft){
	
	Elem *ptr = root;
    if (ptr != NULL)
    {
        // If key already exists, return
        if (key == (ptr->key))
        {
            cout<<"Duplicate Key !\n";
            return false;
        }
 
		bool result = false;
        // Moving on left subtree.
        if (key < ptr->key)
        {
        	result = insert(ptr->left, key, data, ptr) ? true : false;			
        }
		else
        {
			if(ptr->rightThread){				
				Elem *tmp = new Elem;
				tmp -> key = key;
				tmp -> data = data;
				tmp -> rightThread = true;
				tmp -> height = 1;
				tmp -> right = ptr -> right;
				tmp->left = NULL;
				_size++;
				ptr->right = tmp;
				ptr->rightThread = false;
				result = true;
			}
			else			
				result = insert(ptr->right, key, data, ptr) ? true : false;
        }
		
		ptr->height = 1 + max(height(ptr->left), height(ptr->right));
		int diff = balanceFactor(ptr);
		root = ptr;
		cout<<"diff: "<<diff<<endl;		
		
		// Left Left case
		if (diff > 1 && key < ptr->left->key){
			rotateRight(ptr);
			root = ptr;
		}
 
		// Right Right Case
		if (diff < -1 && key > ptr->right->key){
			rotateLeft(ptr);
			root = ptr;
		}
	 
		// Left Right Case
		if (diff > 1 && key > ptr->left->key)
		{
			rotateLeft(ptr->left);
			rotateRight(ptr);
			root = ptr;
		}
	 
		// Right Left Case
		if (diff < -1 && key < ptr->right->key)
		{
			rotateRight(ptr->right);
			rotateLeft(ptr);
			root = ptr;
		}

		return result;
    }
 
    // Create a new node
    Elem *tmp = new Elem;
    tmp -> key = key;
    tmp -> data = data;
    tmp -> rightThread = true;
    tmp -> height = 1;
    _size++;
 
    if (lastLeft == NULL)
    {        
        tmp -> left = NULL;
        tmp -> right = NULL;
		tmp -> rightThread = false;
		root = tmp;
    }
    else if (key < (lastLeft -> key))
    {
        tmp -> left = NULL;
        tmp -> right = lastLeft;
        lastLeft -> left = tmp;
    }
    else
    {
        tmp -> right = lastLeft -> right;
		tmp -> rightThread = lastLeft -> rightThread;
        lastLeft -> rightThread = false;
        lastLeft -> right = tmp;
    }
     
    return true;
}

int max(int a, int b){
	return a > b ? a : b;
}

template <typename KEY, typename T>
int ThreadedAVL<KEY, T> :: height(Elem *node){
	if(node == NULL)
		return 0;
	else
		return node->height;
}

template <typename KEY, typename T>
int ThreadedAVL<KEY, T> :: balanceFactor(Elem *cur){
	if (cur == NULL)
        return 0;
    return height(cur->left) - height(cur->right);
}	

template <typename KEY, typename T>
void ThreadedAVL<KEY, T> :: printTree(ostream& out, int level, Elem *p) const
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
   				 while (ptr && ptr -> left)
        			ptr = ptr -> left;
        }
    }     
    out<<endl;
}

template <typename KEY, typename T>
void ThreadedAVL<KEY, T> :: destructCode(Elem *& p){
	deleteInPostOrder(p, NULL);
}

template <typename KEY, typename T>
void ThreadedAVL<KEY, T> :: deleteInPostOrder(Elem *& ptr, Elem *par){
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
	
	ThreadedAVL<int, int> *threadedAVL = new ThreadedAVL<int, int>;
	threadedAVL->_root = NULL;   
	threadedAVL->_size = 0;
 
  threadedAVL->insert(threadedAVL->_root, 20, 20, NULL);
  threadedAVL->printTree(cout, 0, threadedAVL->_root);
  threadedAVL->insert(threadedAVL->_root, 10, 10, NULL);
  threadedAVL->printTree(cout, 0, threadedAVL->_root);
  threadedAVL->insert(threadedAVL->_root, 30, 30, NULL);
  threadedAVL->printTree(cout, 0, threadedAVL->_root);
  threadedAVL->insert(threadedAVL->_root, 5, 5, NULL);
  threadedAVL->printTree(cout, 0, threadedAVL->_root);
  threadedAVL->insert(threadedAVL->_root, 16, 16, NULL);
  threadedAVL->printTree(cout, 0, threadedAVL->_root);
  threadedAVL->insert(threadedAVL->_root, 14, 14, NULL);
  threadedAVL->printTree(cout, 0, threadedAVL->_root);
  threadedAVL->insert(threadedAVL->_root, 17, 17, NULL);
  threadedAVL->printTree(cout, 0, threadedAVL->_root);
  threadedAVL->insert(threadedAVL->_root, 13, 13, NULL);
  threadedAVL->printTree(cout, 0, threadedAVL->_root);
  
  
 	
  threadedAVL->printTree(cout, 0, threadedAVL->_root);
  
  threadedAVL->destructCode(threadedAVL->_root);
  
  threadedAVL->printTree(cout, 0, threadedAVL->_root);
	return 0;
}

