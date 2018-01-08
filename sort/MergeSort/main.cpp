#include <stdio.h>
#include <stdlib.h>

struct SqList{
#define MAXLEN 10
    int length;
    int r[MAXLEN + 1];
    SqList(){
        this->length = 0;
    }
};


void merge(SqList *l, int p, int q, int r)
{
    int n1 = q - p + 1;
    int n2 = r - q;
    int *A = new int[n1];
    int *B = new int[n2];
    for(int i=0; i<n1; i++)
        A[i] = l->r[p+i];
    for(int i=0; i<n2; i++)
        B[i] = l->r[q+i+1];
    int i,j,k;
    i = p;
    j = k = 0;
    while(i<=r)
    {
        if(A[j]<=B[k])
        {
            l->r[i++] = A[j];
            j++;
            if(j==n1)
            {
                for(int h=k; h<n2; h++)
                    l->r[i++] = B[h];
                break;
            }
        }
        else
        {
            l->r[i++] = B[k];
            k++;
            if(k==n2)
            {
                for(int h=j; h<n1; h++)
                    l->r[i++] = A[h];
                break;
            }
        }
    }
    delete []A;
    delete []B;
}

void MergeSort(SqList *l, int p, int r)
{
    if(p<r)
    {
        int q = (p+r)/2;
        MergeSort(l, p, q);
        MergeSort(l, q+1, r);
        merge(l, p, q, r);
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
    l.r[1] = 1; l.r[2] = 5; l.r[3] = 2; l.r[4] = 3;
    l.r[5] = 7; l.r[6] = 4; l.r[7] = 9; l.r[8] = 0;
    print(&l);
    MergeSort(&l, 1, 8);
    print(&l);
    return 0;
}
