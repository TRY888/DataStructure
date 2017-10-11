#include <iostream>
#include <stack>
using namespace std;

typedef int DataType;
typedef struct tnode{
	DataType data;
	tnode *lchild;
	tnode *rchild;
}BiNode, BiTree;

void preOrder1(BiTree *t)
{
	BiNode *temp = t;
	stack<BiNode *> s;
	while(temp != NULL)
	{
		cout << temp->data << " ";
		if(temp->rchild!=NULL)
		{
			s.push(temp->rchild);
		}
		temp = temp->lchild;
		if(temp == NULL)
		{
			while(!s.empty())
			{
				BiNode *t = s.top();
				s.pop();
				cout << t->data << " ";
				if(t->rchild!=NULL)
					s.push(t->rchild);
				temp = t->lchild;
				if(temp != NULL)
				{
					break;
				}
			}
		}
	}
} 

void preOrder2(BiTree *t)
{
	if(t == NULL)
	{
		return;
	}
	else
	{
		cout << t->data << " ";
		preOrder2(t->lchild);
		preOrder2(t->rchild);
	}
}

void inOrder1(BiTree *t)
{
	BiNode *temp = t;
	stack<BiNode *> s;
	while(temp != NULL)
	{
		s.push(temp);
		temp = temp->lchild;
		if(temp == NULL)
		{
			while(!s.empty())
			{
				cout << s.top()->data << " ";
				temp = s.top()->rchild;
				s.pop();
				if(temp != NULL)
				{
					break;	
				}
			}
		}	
	}
}

void inOrder2(BiTree *t)
{
	if(t == NULL)
	{
		return;
	}
	else
	{
		inOrder2(t->lchild);
		cout << t->data << " ";
		inOrder2(t->rchild);
	}
}
 

void postOrder1(BiTree *t)
{
	BiNode *temp = t;
	stack<BiNode *> s1;
	stack<int> s2;
	while(temp != NULL)
	{
		s1.push(temp);
		s2.push(1);
		temp = temp->lchild;
		if(temp == NULL)
		{
			while(!s1.empty())
			{
				int cnt = s2.top();
				s2.pop();
				if(cnt == 1)
				{
					temp = s1.top()->rchild;
					if(temp == NULL)
					{
						cout << s1.top()->data << " ";
						s1.pop();
					}
					else
					{
						s2.push(2);
						break;	
					}
				}
				else
				{
					cout << s1.top()->data << " ";
					s1.pop();
				}
			}
		}
	} 
} 

void postOrder2(BiTree *t)
{
	if(t == NULL)
	{
		return;
	}
	else
	{
		postOrder2(t->lchild);
		postOrder2(t->rchild);
		cout << t->data << " ";
	}
} 

int treeDepth(BiTree *t)
{
	int h,h1,h2;
	if(t == NULL)
	{
		h = 0;
	}
	else
	{
		h1 = treeDepth(t->lchild);
		h2 = treeDepth(t->rchild);
		if(h1>=h2) 
			h = h1 + 1;
		else
			h = h2 + 1;
	}
	return h;
}

int treeLeaf(BiTree *t)
{
	if(t==NULL)
	{
		return 0;
	}	
	else
	{
		if(t->lchild==NULL && t->rchild==NULL)
			return 1;
		else
			return treeLeaf(t->lchild) + treeLeaf(t->rchild);
	} 
}

#define len 10
int main(int argc, char *argv[])
{
	BiNode *t[len];
	for(int i=0; i<len; i++)
	{
		t[i] = new BiNode();
		t[i]->data = i;
	}
	for(int i=1; i<len; i++)
	{
		if(2*i>len-1)
			t[i]->lchild = NULL;
		else
			t[i]->lchild = t[2*i];
		if(2*i+1>len-1)
			t[i]->rchild = NULL;
		else
			t[i]->rchild = t[2*i+1];
	}
	BiNode *t1[3];
	for(int i=0; i<3; i++)
	{
		t1[i] = new BiNode();
		t1[i]->data = len + i;
	}
	t[len-1]->rchild = t1[0];
	t1[0]->lchild = t1[1];
	t1[0]->rchild = t1[2];
	t1[1]->lchild = NULL;
	t1[1]->rchild = NULL;
	t1[2]->lchild = NULL;
	t1[2]->rchild = NULL;
	postOrder1(t[1]);
	cout << endl;
	postOrder2(t[1]);	
	cout << endl;
	inOrder1(t[1]);
	cout << endl;
	inOrder2(t[1]); 
	cout << endl;
	preOrder1(t[1]);
	cout << endl;
	preOrder2(t[1]); 
	cout << endl;
	cout << "depth: " << treeDepth(t[1]);
	cout << endl;
	cout << "leaf: " << treeLeaf(t[1]);
	cout << endl;
	return 0;
}
