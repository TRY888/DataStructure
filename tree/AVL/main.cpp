#include <stdio.h>
#include <stdlib.h>

#define LH 1
#define EH 0
#define RH -1

typedef struct node{
    int key,bf;
    node *left, *right;
    node(int key){
        this->key = key;
        this->left = this->right = NULL;
        this->bf = 0;
    }
}BiNode, *BiTree;

//右旋操作
void r_rotate(BiTree &root)
{
    BiTree l = root->left;
    root->left = l->right;
    l->right = root;
    root = l;
}

//左旋操作
void l_rotate(BiTree &root)
{
    BiTree r = root->right;
    root->right = r->left;
    r->left = root;
    root = r;
}

//右边高时需要的平衡操作
void r_balance(BiTree &root)
{
    BiTree r = root->right;
    switch(r->bf)
    {
        case EH:
            r->bf = LH;
            root->bf = RH;
            l_rotate(root);
            break;
        case RH:
            r->bf = root->bf = EH;
            l_rotate(root);
            break;
        case LH:
            BiTree rl = r->left;
            switch(rl->bf)
            {
                case EH:
                    root->bf = r->bf = EH;
                    break;
                case LH:
                    root->bf = EH;
                    r->bf = RH;
                    break;
                case RH:
                    root->bf = LH;
                    r->bf = EH;
                    break;
                default:break;
            }
            rl->bf = EH;
            r_rotate(root->right);
            l_rotate(root);
            break;
    }
}

//左边高时需要的平衡操作
void l_balance(BiTree &root)
{
    BiTree l = root->left;
    switch(l->bf)
    {
        case EH:
            l->bf = RH;
            root->bf = LH;
            r_rotate(root);
            break;
        case LH:
            l->bf = root->bf = EH;
            r_rotate(root);
            break;
        case RH:
            BiTree lr = l->right;
            switch(lr->bf)
            {
                case EH:
                    l->bf = root->bf = EH;
                    break;
                case LH:
                    l->bf = EH;
                    root->bf = RH;
                    break;
                case RH:
                    l->bf = LH;
                    root->bf = EH;
                    break;
                default:break;
            }
            lr->bf = EH;
            l_rotate(root->left);
            r_rotate(root);
            break;
    }
}

bool avl_insert(BiTree &root, int key, bool &taller)
{
    if(root==NULL)
    {
        root = new BiNode(key);
        taller = true;
        return true;
    }
    else
    {
        if(key == root->key)
        {
            taller = false;
            return false;
        }
        if(key > root->key)
        {
            if(avl_insert(root->right, key, taller) == false)
                return false;
            if(taller==true)
            {
                switch(root->bf)
                {
                    case EH:
                        root->bf = RH;
                        taller = true;
                        break;
                    case LH:
                        root->bf = EH;
                        taller = false;
                        break;
                    case RH:
                        r_balance(root);
                        taller = false;
                        break;
                    default:break;
                }
            }
        }
        else
        {
            if(avl_insert(root->left, key, taller) == false)
                return false;
            if(taller==true)
            {
                switch(root->bf)
                {
                    case EH:
                        root->bf = LH;
                        taller = true;
                        break;
                    case LH:
                        l_balance(root);
                        taller = false;
                        break;
                    case RH:
                        root->bf = EH;
                        taller = false;
                        break;
                    default:break;
                }
            }
        }
        return true;
    }
}

bool avl_delete(BiTree &root, int key, bool &lower)
{
    bool r,l;
    r = l = false;
    if(root==NULL)
    {
        lower = false;
        return false;
    }
    if(root->key == key)
    {
        lower = true;
        if(root->right != NULL)
        {
            BiTree p;
            p = root->right;
            while(p->left!=NULL)
                p = p->left;
            root->key = p->key;
            avl_delete(root->right, p->key, lower);
            r = true;
        }
        else
        {
            BiTree temp = root;
            root = root->left;
            free(temp);
            return true;
        }

    }
    else if(key>root->key)
    {
        avl_delete(root->right, key, lower);
        r = true;
    }
    else
    {
        avl_delete(root->left, key, lower);
        l = true;
    }
    if(lower==true && root!=NULL)
    {
        if(l == true)
        {
            switch(root->bf)
            {
                case EH:
                    root->bf = RH;
                    lower = false;
                    break;
                case LH:
                    root->bf = EH;
                    lower = true;
                    break;
                case RH:
                    r_balance(root);
                    lower = true;
                    break;
                default:break;
            }
        }
        else
        {
            switch(root->bf)
            {
                case EH:
                    root->bf = LH;
                    lower = false;
                    break;
                case RH:
                    root->bf = EH;
                    lower = true;
                    break;
                case LH:
                    l_balance(root);
                    lower = true;
                    break;
                default:break;
            }
        }
    }
    return true;
}

void avl_preorder(BiTree &root)
{
    if(root!=NULL)
    {
        printf("%d-%d ", root->key, root->bf);
        avl_preorder(root->left);
        avl_preorder(root->right);
    }
}

int avl_height(BiTree &root)
{
    if(root==NULL)
        return 0;
    else
    {
        int lh = avl_height(root->left);
        int rh = avl_height(root->right);
        if(lh>rh)
            lh = lh+1;
        else
            rh = rh+1;
        return lh>rh?lh:rh;
    }
}

int main(int argc, char *argv[])
{
    BiTree root = NULL;
    bool taller = true;
    int a[]={4,3,2,7,9,11,10,15};
    for(int i=0; i<sizeof(a)/sizeof(int); i++)
        avl_insert(root, a[i], taller);
    printf("\nheight: %d\n", avl_height(root));
    avl_preorder(root);
    bool lower = true;
    avl_delete(root, 2, lower);
    printf("\ndelete 2 height: %d\n", avl_height(root));
    avl_preorder(root);
    avl_delete(root, 4, lower);
    printf("\ndelete 4 height: %d\n", avl_height(root));
    avl_preorder(root);



    return 0;
}
