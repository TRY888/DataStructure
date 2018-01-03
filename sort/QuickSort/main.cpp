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

int partition(SqList *l, int low, int high)
{
    int pivotkey = l->r[low];
    while(low<high)
    {
        while(low<high && l->r[high]>=pivotkey)
            high--;
        swap(l, low, high);
        while(low<high && l->r[low]<=pivotkey)
            low++;
        swap(l, low, high);
    }
    return low;
}

void QuickSort(SqList *l, int low, int high)
{
    if(low < high)
    {
        int pivot = partition(l, low, high);
        QuickSort(l, low, pivot-1);
        QuickSort(l, pivot+1, high);
    }
}

void QuickSort1(SqList *l, int low, int high)
{
    while(low < high)
    {
        int pivot = partition(l, low, high);
        QuickSort1(l, low, pivot-1);
        low = pivot + 1;
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
    l.length = 8;
    l.r[1] = 5;l.r[2] = 1;l.r[3] = 6;l.r[4] = 0;
    l.r[5] = 4;l.r[6] = 7;l.r[7] = 9;l.r[8] = 2;
    QuickSort1(&l, 1, l.length);
    print(&l);

    return 0;
}
