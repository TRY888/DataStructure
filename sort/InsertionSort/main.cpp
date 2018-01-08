#include <stdio.h>

struct SqList{
    #define MAXLEN 10
    int length;
    int r[MAXLEN + 1];
    SqList(){
        this->length = 0;
    }
};

void InsertionSort(SqList *l)
{
    for(int i=2; i<=l->length; i++)
    {
        int val = l->r[i];
        int j = i - 1;
        while(j>0 && val<l->r[j])
        {
            l->r[j+1] = l->r[j];
            j--;
        }
        l->r[j+1] = val;
    }
}

void print(SqList *l)
{
    printf("\n");
    for(int i=1; i<=l->length; i++)
        printf("%d ", l->r[i]);
    printf("\n");
}

int main(int argc, char *argv[])
{
    SqList l;
    l.length = 8;
    l.r[1] = 5;l.r[2] = 1;l.r[3] = 6;l.r[4] = 0;
    l.r[5] = 2;l.r[6] = 4;l.r[7] = 7;l.r[8] = 9;
    InsertionSort(&l);
    print(&l);

    return 0;
}
