#include <iostream>
using namespace std;


struct PriorityQueue{
    PriorityQueue(){
        this->H[0].key = INT_MIN;
        this->size = 0;
    }
    #define MAX 100
    #define KeyType int
    struct Heap{
        KeyType key;
    };
    int size;
    Heap H[MAX];
    void insert(KeyType key)
    {
        int i;
        for(i=++size; key < H[i/2].key; i/=2)
            H[i].key = H[i/2].key;
        H[i].key = key;
    }
    int DeleteMin()
    {
        if(size == 0)
            return H[0].key;
        int child,i;
        KeyType minElement, lastElement;
        minElement = H[1].key;
        lastElement = H[size--].key;
        for(i=1; 2*i<=size; i=child)
        {
            child = 2*i;
            if(child!=size && H[child+1].key<H[child].key)
                child++;
            if(lastElement>H[child].key)
                H[i].key = H[child].key;
            else
                break;
        }
        H[i].key = lastElement;
        return minElement;
    }
};




int main(int argc, char *argv[])
{
    PriorityQueue pq;
    for(int i=50; i>0; i--)
        pq.insert(i);
    pq.insert(-1999);
    for(int i=51; i>0; i--)
        cout << pq.DeleteMin() << endl;
    return 0;
}

