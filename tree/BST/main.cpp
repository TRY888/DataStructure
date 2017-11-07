#include <iostream>
#include <stack>

using namespace std;

struct BSTreeNode{
	int val;
	BSTreeNode *left,*right,*parent;
};

//
BSTreeNode *search1(BSTreeNode *root, int key)
{
	if(root==NULL || root->val==key)
		return root;
	if(key > root->val)
		return search1(root->right, key);
	else
		return search1(root->left, key);
}

// 
BSTreeNode *search2(BSTreeNode *root, int key)
{
	while(root!=NULL && root->val!=key)
	{
		if(key > root->val)
			root = root->right;
		else
			root = root->left;	
	}
	return root;
} 

//
BSTreeNode *maximum(BSTreeNode *root)
{
	if(root==NULL)
		return NULL;
	while(root->right!=NULL)
	{
		root = root->right;
	}
	return root;
} 

//
BSTreeNode *minimum(BSTreeNode *root)
{
	if(root==NULL)
		return NULL;
	while(root->left!=NULL)
	{
		root = root->left;
	}
	return root;
}

//
BSTreeNode *predecessor(BSTreeNode *target)
{
	if(target->left!=NULL)
		return maximum(target->left);
	BSTreeNode *p = target->parent;
	while(p!=NULL && p->right!=target)
	{
		target = p;
		p = p->parent;
	}
	return p;
}

//
BSTreeNode *successor(BSTreeNode *target)
{
	if(target->right!=NULL)
		return minimum(target->right);
	BSTreeNode *p = target->parent;
	while(p!=NULL && p->left!=target)
	{
		target = p;
		p = p->parent;
	}
	return p;
}

BSTreeNode *insert(BSTreeNode *root, BSTreeNode *target)
{
	if(root==NULL)
	{
		root = target;
		return root;
	}
	BSTreeNode *p, *q;
	q = root;
	p = NULL;
	while(q!=NULL)
	{
		if(target->val==q->val)
		{
			free(target);
			return root;
		}
		else if(target->val>q->val)
		{
			p = q;
			q = q->right;
		}	
		else
		{
			p = q;
			q = q->left;
		}
	}
	target->parent = p;
	if(target->val>p->val)
		p->right = target;
	else
		p->left = target;
	return root;
}


// don't use parent pointer
BSTreeNode *instead1(BSTreeNode *root, BSTreeNode *q, BSTreeNode *q_father, BSTreeNode *instead)
{
	if(q_father==NULL)
	{
		return instead;
	}
	else if(q_father->left == q)// q is his parent's left child
	{
		q_father->left = instead;
	}
	else//q is his parent's right child
	{
		q_father->right = instead; 
	}
	return root;
} 
// don't use parent pointer
BSTreeNode *delete1(BSTreeNode *root, int key)
{
	BSTreeNode *p,*q;
	p = NULL;
	q = root;
	while(q!=NULL && q->val!=key)//find the node with key 
	{
		p = q;
		if(key > q->val)
			q = q->right;
		else
			q = q->left;
	}
	if(q == NULL) // node with key don't exist
		return root;
	if(q->left == NULL)
	{
		root = instead1(root, q, p, q->right);
		free(q);
	}
	else if(q->right == NULL)
	{
		root = instead1(root, q, p, q->left);
		free(q);
	}
	else
	{
		BSTreeNode *back = q->right;
		BSTreeNode *back_father = q;
		while(back->left!=NULL)
		{
			back_father = back;
			back = back->left;
		}
		if(q->right == back)
		{
			root = instead1(root, q, p, q->right);
			q->right->left = q->left;

		}
		else
		{
			root = instead1(root, back, back_father, back->right);
			root = instead1(root, q, p, back);
			back->right = q->right;
			back->left = q->left;	
		}
		free(q);
	}
	return root;	
}

// use parent pointer
BSTreeNode *instead2(BSTreeNode *root, BSTreeNode *q, BSTreeNode *instead)
{
	if(q->parent == NULL)
	{
		instead->parent = NULL;
		return instead;
	}
	else if(q->parent->left == q)
	{
		q->parent->left = instead;
	}
	else
	{
		q->parent->right = instead;
	}
	return root;
} 
// use parent pointer
BSTreeNode *delete2(BSTreeNode *root, int key)
{
	BSTreeNode *p, *q;
	p = NULL;
	q = root;
	while(q!=NULL && q->val!=key)
	{
		p = q;
		if(key > q->val)
			q = q->right;
		else
			q = q->left;
	}
	if(q == NULL)
		return root;
	if(q->left == NULL)
	{
		root = instead2(root, q, q->right);
		free(q);
	}
	else if(q->right == NULL)
	{
		root = instead2(root, q, q->left);
		free(q);
	}
	else
	{
		BSTreeNode *back = q->right;
		while(back->left!=NULL)
		{
			back = back->left;
		} 
		if(q->right == back)
		{
			root = instead2(root, q, q->right);
			q->right->left = q->left;
		}
		else
		{
			root = instead2(root, back, back->right);
			root = instead2(root, q, back);
			back->left = q->left;
			back->right = q->right;
		}
		free(q);
	}
	return root;
}

void destory1(BSTreeNode **root)
{
	if(*root!=NULL)
	{
		destory1(&((*root)->left));
		BSTreeNode *temp1 = (*root)->right;
		free(*root);
		*root = NULL;
		destory1(&temp1);
	}
}
void destory2(BSTreeNode **root)
{
	stack<BSTreeNode *> s;
	BSTreeNode *temp = *root;
	while(temp != NULL)
	{
		s.push(temp);
		temp = temp->left;
		if(temp == NULL)
		{
			while(!s.empty())
			{
				BSTreeNode *temp1 = s.top();
				s.pop();
				BSTreeNode *temp2 = temp1->right;
				free(temp1);
				if(temp2!=NULL)
				{
					temp = temp2;
					break;
				}
			}
		}
	}
	*root = NULL;
}

void inorder(BSTreeNode *root)
{
	if(root!=NULL)
	{
		inorder(root->left);
		cout << root->val << " ";
		inorder(root->right); 
	}
}



int main(int argc, char *argv[])
{
	BSTreeNode *root = NULL;
	for(int i=0; i<10; i++)
	{
		BSTreeNode *node = (BSTreeNode *)malloc(sizeof(BSTreeNode));
		node->val = i;
		node->left = node->right = node->parent=NULL;
		root = insert(root, node);
	}
	inorder(root);
	cout << endl;
	BSTreeNode *find = search2(root, 6);
	cout << successor(find)->val << endl;
	cout << predecessor(find)->val << endl;
	root = delete2(root, 4);
	inorder(root);
	cout << endl;
	root = delete2(root, 4);
	inorder(root);
	cout << endl;
	root = delete2(root, 0);
	inorder(root);
	cout << endl;
	root = delete2(root, 9);
	inorder(root);
	cout <<endl << "---------------" <<endl;
	destory2(&root);
//	destory1(&root);
	inorder(root);
	return 0;
}
