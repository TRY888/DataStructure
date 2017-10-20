#include <iostream>
#include <queue>

using namespace std;

typedef int DataType;
typedef struct binode{
	DataType data;
	binode *lchild,*rchild; 
}BiNode, BiTree;

void level_traverse(BiTree *t)
{
	queue<BiNode *> q;
	BiNode *temp = t;
	int cnt = 0;
	int count = 0;
	if(temp!=NULL)
	{
		q.push(temp);
		cnt++;
		temp = temp->lchild;
		while(temp!=NULL)
		{
			while(cnt!=0)
			{
				cnt--;
				temp = q.front();
				q.pop();
				cout << temp->data << " ";
				if(temp->lchild!=NULL)
				{
					q.push(temp->lchild);
					count++;
				}
				if(temp->rchild!=NULL)
				{
					q.push(temp->rchild);
					count++;
				}
			}
			if(q.empty())
			{
				temp = NULL;
			}
			else
			{
				temp = q.front();
			}
			cnt = count;
			count = 0;
			
		}
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
	level_traverse(t[1]);

	return 0;
}
