#include <stdio.h>
#include <stdlib.h>

#define EH 0
#define LH 1
#define RH -1

typedef struct BiNode{
    int key;
    int bf;
    BiNode *left, *right;
    BiNode(int key){
        this->key = key;
        this->bf = 0;
        this->left = this->right = NULL;
    }
}*BiTree;

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

//右平衡操作：当结点的平衡因子为-2时
void r_balance(BiTree &root)
{
    BiTree r = root->right;
    switch(r->bf)
    {
        case RH:
            {
                r->bf = root->bf = EH;
                l_rotate(root);
                break;
            }
        case EH:
            {
                r->bf = LH;
                root->bf = RH;
                l_rotate(root);
                break;
            }
        case LH:
            {
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
        default:break;
    }
}

//左平衡操作：当结点的平衡因子为2时
void l_balance(BiTree &root)
{
    BiTree l = root->left;
    switch(l->bf)
    {
        case LH:
            {
                l->bf = root->bf = EH;
                r_rotate(root);
                break;
            }
        case EH:
            {
                l->bf = RH;
                root->bf = LH;
                r_rotate(root);
                break;
            }
        case RH:
            {
                BiTree lr = l->right;
                switch(lr->bf)
                {
                    case EH:
                        root->bf = l->bf = EH;
                        break;
                    case LH:
                        root->bf = RH;
                        l->bf = EH;
                        break;
                    case RH:
                        root->bf = EH;
                        l->bf = LH;
                        break;
                    default:break;
                }
                lr->bf = EH;
                l_rotate(root->left);
                r_rotate(root);
                break;
            }
        default:break;
    }
}

bool avl_insert(BiTree &root, int key, bool &taller)
{
    if(root == NULL)
    {
        BiTree p = new BiNode(key);
        taller = true;
        root = p;
        return true;
    }
    if(key == root->key)
    {
        taller = false;
        return false;
    }
    else if(key > root->key)
    {
        if(avl_insert(root->right, key, taller) == false)
            return false;
        if(taller == true)
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
        return true;
    }
    else
    {
        if(avl_insert(root->left, key, taller) == false)
            return false;
        if(taller == true)
        {
            switch(root->bf)
            {
                case EH:
                    root->bf = LH;
                    taller = true;
                    break;
                case LH:
                    root->bf = EH;
                    taller = false;
                    break;
                case RH:
                    l_balance(root);
                    taller = false;
                    break;
                default:break;
            }
        }
        return true;
    }
}

bool avl_delete(BiTree &root, int key, bool &lower)
{
    bool r,l;
    r = l = false;
    if(root == NULL)
    {
        lower = false;
        return false;
    }
    if(key == root->key)
    {
        lower = true;
        if(root->right != NULL)
        {
            BiTree p = root->right;
            while(p->left != NULL)
                p = p->left;
            root->key = p->key;
            avl_delete(root->right, p->key, lower);
            r = true;
        }
        else
        {
            BiTree temp = root->left;
            free(root);
            root = temp;
            return true;
        }
    }
    else if(key > root->key)
    {
        avl_delete(root->right, key, lower);
        r = true;
    }
    else
    {
        avl_delete(root->left, key, lower);
        l = true;
    }
    if(lower == true && root!=NULL)
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
                    if(root->right->bf == EH)
                        lower = false;
                    else if(root->right ->bf == LH)
                        lower = true;
                    else
                        lower = true;
                    r_balance(root);
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
                    if(root->left->bf == EH)
                        lower = false;
                    else if(root->left ->bf == LH)
                        lower = true;
                    else
                        lower = true;
                    l_balance(root);
                    break;
                default:break;
            }
        }
    }
    return true;
}

void avl_preorder(BiTree &root)
{
    if(root != NULL)
    {
        printf("%d(%d) ", root->key, root->bf);
        avl_preorder(root->left);
        avl_preorder(root->right);
    }
}

int avl_height(BiTree &root)
{
    if(root == NULL)
        return 0;
    int lh = avl_height(root->left);
    int rh = avl_height(root->right);
    if(lh > rh)
        lh = lh + 1;
    else
        rh = rh + 1;
    return lh>rh?lh:rh;
}

int main(int argc, char *argv[])
{
    BiTree root = NULL;
    bool taller = false;
    for(int i=0; i<10; i++)
        avl_insert(root, i, taller);
    printf("\n\navl height: %d\n", avl_height(root));
    avl_preorder(root);

    bool lower = false;
    avl_delete(root, 9, lower);
    printf("\n\navl delete 9 height: %d\n", avl_height(root));
    avl_preorder(root);

    avl_delete(root, 8, lower);
    printf("\n\navl delete 8 height: %d\n", avl_height(root));
    avl_preorder(root);

    avl_delete(root, 3, lower);
    printf("\n\navl delete 3 height: %d\n", avl_height(root));
    avl_preorder(root);

    avl_delete(root, 4, lower);
    printf("\n\navl delete 4 height: %d\n", avl_height(root));
    avl_preorder(root);

    avl_delete(root, 7, lower);
    printf("\n\navl delete 7 height: %d\n", avl_height(root));
    avl_preorder(root);

    avl_delete(root, 6, lower);
    printf("\n\navl delete 6 height: %d\n", avl_height(root));
    avl_preorder(root);

    avl_delete(root, 0, lower);
    printf("\n\navl delete 0 height: %d\n", avl_height(root));
    avl_preorder(root);

    avl_delete(root, 2, lower);
    printf("\n\navl delete 2 height: %d\n", avl_height(root));
    avl_preorder(root);

    avl_delete(root, 5, lower);
    printf("\n\navl delete 5 height: %d\n", avl_height(root));
    avl_preorder(root);

    return 0;
}
