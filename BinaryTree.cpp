#include<iostream>
#include<string>
using namespace std;

template<typename elemType>
class BinaryTree;

/*==============================================================*/
template<typename valType>
class BTnode{
public:
	valType _val;
	int _cnt;
	BTnode *_parent;
	BTnode *_lchild;
	BTnode *_rchild;

public:
	BTnode(const valType&);

	void insert_value(const valType&);
	void remove_value(const valType&, BTnode<valType>*&);
	void preorder(BTnode<valType> *pt) const;
	void display(int indent=4);
	void inorder(BTnode<valType> *pt) const;

	//friend class BinaryTree<valType>;
};
/*---------------------------------------*/
//preferred initialization method for
//type parameter passed to a constructor
template <typename valType>
inline BTnode<valType>::
BTnode(const valType &val):_val(val)//just in case valType is a class type;requires only a single step.
{
	//_val=val; not recommended;could be a class type
	_cnt=1;
	_lchild=0;
	_rchild=0;
}
template <typename valType>
void BTnode<valType>::
preorder(BTnode<valType> *pt) const
{
	if(pt)
	{
		cout<<pt->_val<<' ';

		if(pt->_lchild)
			preorder(pt->_lchild);
		if(pt->_rchild)
			preorder(pt->_rchild);
	}
}
template <typename valType>
void BTnode<valType>::
display(int indent)
{
	cout<<string(indent,' ')<<'>'<<_val<<endl;

	if(_lchild)
		_lchild->display(indent+4);
	if(_rchild)
		_rchild->display(indent+4);
}
template <typename valType>
void BTnode<valType>::
inorder(BTnode<valType> *pt) const
{
	if(pt)
	{
		if(pt->_lchild)
			inorder(pt->_lchild);

		cout<<pt->_val<<' ';

		if(pt->_rchild)
			inorder(pt->_rchild);
	}
}

/*==============================================================*/

/*==============================================================*/
template <typename elemType>
class BinaryTree{

private: 
	BTnode<elemType> *_root;

public:
	BinaryTree();
    BinaryTree(const BinaryTree&);
    ~BinaryTree();
    BinaryTree& operator=(const BinaryTree&);

    bool empty(){ return _root==0; }
    void clear()
    {
    	if(_root)
    	{
    		clear(_root);
    		_root = 0;
    	}
    }
	void insert(const elemType&);
	void preorder() const
	{
		_root->preorder(_root);
	}
	void inorder() const
	{
		_root->inorder(_root);
	}
	void clear(BTnode<elemType>*);
	void remove(const elemType&);
	void remove_root();
	void printtree() const;

private: 
	void copy(BTnode<elemType>*tar, BTnode<elemType>*src );

};
/*---------------------------------------*/
template<typename elemType>
inline BinaryTree<elemType>::
BinaryTree():_root(0)
{

}
template<typename elemType>
inline BinaryTree<elemType>::
BinaryTree(const BinaryTree &rhs)
{
	copy(_root,rhs._root);
}
template <typename elemType>
inline BinaryTree<elemType>::
~BinaryTree()
{
	clear();
}
template <typename elemType>
inline BinaryTree<elemType>&
BinaryTree<elemType>::
operator=(const BinaryTree &rhs)
{
	if(this!=&rhs)
	{
		clear();
		copy(_root, rhs._root);
	}
	return *this;
}
template <typename elemType>
inline void
BinaryTree<elemType>::
insert(const elemType &elem)
{
	if(!_root)
		//Two Steps For new:
		//         Memory is requested of the program's free store.return a pointer or raise exception
		//         If the first step succeeds and an initial value is specified, initialize
		_root = new BTnode<elemType>(elem);
	else
		_root->insert_value(elem);
}
template <typename valType>
void BTnode<valType>::
insert_value( const valType &val )
{
	if(val==_val)
	{
		_cnt++;
		return;
	}
	if(val<_val)
	{
		if(!_lchild)
			_lchild = new BTnode(val);
		else
			_lchild->insert_value(val);
	}
	else
	{
		if(!_rchild)
			_rchild = new BTnode(val);
		else
			_rchild->insert_value(val);
	}
}
template <typename elemType>
inline void
BinaryTree<elemType>::
remove( const elemType &elem)
{
	if(_root)
	{
		if(_root->_val == elem)
			remove_root();
		else
			_root->remove_value(elem, _root);
	}
}
//remove_root() resets the root node to one of its children,if a child node is present.
//if the right child is present,it becomes the new root node;
//if the right child is null,_root is set to the left child.
//the left node,if present,is reattached either directly or through a call of lchild_leaf().
template <typename elemType>
void BinaryTree<elemType>::
remove_root()
{
	if(!_root) return;

	BTnode<elemType> *tmp = _root;
	if(_root->_rchild)
	{
		_root = _root->_rchild;

		if(tmp->_lchild)
		{
			BTnode<elemType> *lc = tmp->_lchild;
			BTnode<elemType> *newlc = _root->_lchild;
			if(!newlc)
				//no subtree,let's directly attach it
				_root->_lchild = lc;
			else
				while(newlc->_lchild)
					newlc = newlc->_lchild;
				newlc->_lchild = lc;
		}
	}
	else
	{
		_root = _root->_lchild;

		delete tmp;
	}
}
template <typename valType>
void BTnode<valType>::
remove_value( const valType &val, BTnode *& prev)
{
	if (val<_val)
	{
		if(!_lchild)
			return;
		else
			_lchild->remove_value(val,_lchild);
	}
	else
	if(val>_val)
	{
		if(!_rchild)
			return;
		else
			_rchild->remove_value(val,_rchild);
	}	
	else
	{
		// ok:  found it;
		// reset the tree then delete this node
		if(_rchild)
		{
			prev = _rchild;
			if(_lchild)
				if(!prev->_lchild)
					prev->_lchild = _lchild;
				else
				{
					BTnode *leaf=_lchild;
					BTnode *subtree=prev->_lchild;
					while(subtree->_lchild)
						subtree = subtree->_lchild;
					subtree->_lchild=leaf;
				}
		}
		else
			prev = _lchild;

		delete this;
	}
}
template <typename elemType>
void BinaryTree<elemType>::
clear(BTnode<elemType> *pt)
{
	if(pt)
	{
		clear(pt->_lchild);
		clear(pt->_rchild);
		delete pt;
	}
}
template <typename elemType>
void BinaryTree<elemType>::
printtree() const
{
	_root->display();
}
/*==============================================================*/


int main()
{
	BinaryTree<string> bt;
	bt.insert("Piglet");
	bt.insert("Eeyore");
	bt.insert("Roo");
	bt.insert("Tigger");
	bt.insert("Chris");
	bt.insert("Pooh");
	bt.insert("Kanga");

	bt.printtree();

	cout<<"Preorder Traversal:"<<endl;
	bt.preorder();

	bt.remove("Piglet");
	cout<<endl<<endl<<"Preorder Traversal After Piglet Removal:"<<endl;
	bt.preorder();

	bt.remove("Eeyore");
	cout<<endl<<endl<<"Preorder Traversal After Eeyore Removal:"<<endl;
	bt.preorder();

/*==============================================================*/
	bt.insert("Piglet");
	bt.insert("Eeyore");

	cout<<endl;
	bt.printtree();

	cout<<"Inorder Traversal:"<<endl;
	bt.inorder();

	bt.remove("Piglet");
	cout<<endl<<endl<<"Inorder Traversal After Piglet Removal:"<<endl;
	bt.inorder();

	bt.remove("Eeyore");
	cout<<endl<<endl<<"Inorder Traversal After Eeyore Removal:"<<endl;
	bt.inorder();

	return 0;
}