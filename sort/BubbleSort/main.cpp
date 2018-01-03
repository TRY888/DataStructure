#include <stdio.h>

struct SqList{
    #define MAXLEN 10
    int r[MAXLEN + 1];
    int length;
    SqList(){
        this->length = 0;
    }
};

void swap(SqList *l, int pos1, int pos2)
{
    int temp = l->r[pos1];
    l->r[pos1] = l->r[pos2];
    l->r[pos2] = temp;
}

void BubbleSort0(SqList *l)
{
    for(int i=1; i<l->length; i++)
    {
        for(int j=i+1; j<=l->length; j++)
        {
            if(l->r[i] > l->r[j])
                swap(l, i, j);
        }
    }
}

void BubbleSort1(SqList *l)
{
    for(int i=1; i<l->length; i++)
    {
        for(int j=l->length-1; j>=i; j--)
        {
            if(l->r[j] > l->r[j+1])
                swap(l, j, j+1);
        }
    }
}

void BubbleSort2(SqList *l)
{
    bool flag = true;
    for(int i=1; i<l->length && flag; i++)
    {
        flag = false;
        for(int j=l->length-1; j>=i; j--)
        {
            if(l->r[j] > l->r[j+1])
            {
                swap(l, j, j+1);
                flag = true;
            }
        }
    }
}


void print(SqList *l)
{
    printf("\n");
    for(int i=1; i<=l->length; i++)
        printf("%d ", l->r[i]);
    printf("\n");
}

int main()
{
    SqList l;
    l.length = 4;
    l.r[1] = 5;l.r[2] = 1;l.r[3] = 6;l.r[4] = 0;
//    BubbleSort0(&l);
//    BubbleSort1(&l);
    BubbleSort2(&l);
    print(&l);

    return 0;
}
