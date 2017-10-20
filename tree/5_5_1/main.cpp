#include <iostream>
#include <stack>

using namespace std;

void preorder_array(int *a, int lengt)
{
	stack<int> s;
	int index = 1;
	while(index < lengt)
	{
		cout << a[index] << " ";
		s.push(a[index]);
		index = 2 * index;
		if(index >= lengt )
		{
			while(!s.empty())
			{
				index = s.top();
				s.pop();
				index = 2 * index + 1;
				if(index < lengt)
				{
					break;
				} 
			}
		}	
	}
} 

int main(int argc, char *argv[])
{
	#define length 10
	int val[length];
	for(int i=0; i<length; i++)
	{
		val[i] = i;
	}
	preorder_array(val, length);

	return 0;
}
