//
//  vEBTree.c
//  DSX
//
//  Created by Arni Asgeirsson on 22/02/13.
//  Copyright (c) 2013 Arni Asgeirsson. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vEBTree.h"

int vEBTree_upper_sqroot(int u)
{
    return powf(2, ceilf((log10f(u)/log10f(2))/2));
}

int vEBTree_lower_sqroot(int u)
{
    return powf(2, floorf((log10f(u)/log10f(2))/2));
}

int vEBTree_high(int x, int u)
{
    return floorf(x/vEBTree_lower_sqroot(u));
}

int vEBTree_low(int x, int u)
{
    return x % vEBTree_lower_sqroot(u);
}

int vEBTree_index(int x, int y, int u)
{
    return x * vEBTree_lower_sqroot(u) + y;
}

vEBTree* vEBTree_init(int unisize, int allowMltKeys)
{
    if (unisize == -1)
    {
        printf("Error: given size %d, is not of proper form.\n", unisize);
        return NULL;
    }
    
    vEBTree *tree = (vEBTree*)malloc(sizeof(vEBTree));
    tree->unisize = unisize;
    tree->allowMultKeys = allowMltKeys;
    tree->min = -1;
    tree->max = -1;
    
    if (unisize > 2)
    {
        int clustamount = vEBTree_upper_sqroot(unisize);
       /* printf("clsa = %d\n", clustamount);*/
        int clustsz = vEBTree_lower_sqroot(unisize);
       /* printf("clsz = %d\n", clustsz);*/
        tree->cluster = malloc(sizeof(vEBTree)*clustamount);
        for (int i=0; i < clustamount; i++)
        {
            tree->cluster[i] = vEBTree_init(clustsz, allowMltKeys);
        }
        tree->summary = vEBTree_init(clustamount, 0);
    } else {
        tree->summary = NULL;
        tree->cluster = NULL;
    }
    return tree;
}

void vEBTree_destroy(vEBTree **tree)
{
    int clusamount = vEBTree_upper_sqroot((*tree)->unisize);
    if (clusamount > 2)
    {
        for (int i=0; i < clusamount; i++)
        {
            vEBTree_destroy(&(*tree)->cluster[i]);
        }
        free((*tree)->cluster);
        vEBTree_destroy(&(*tree)->summary);
    }
    free(*tree);
    *tree = NULL;
}

int vEBTree_minimum(vEBTree *tree)
{
    return tree->min;
}

int vEBTree_maximum(vEBTree *tree)
{
    return tree->max;
}

void vEBTree_printContent(vEBTree **tree, int offset)
{
    if (tree == NULL)
    {
        printf("Error: PrintContent, tree cannot be NULL.\n");
        return;
    }
    /*
    if (tree->unisize == 2) {
        printf("[%d] = %d\n[%d] = %d\n", offset, tree->min, offset+1, tree->max);
    } else {
       / printf("Summary: \n");
         vEBTree_printContent(tree->summary, 0);
         printf("Summary done\n");/
        int clustamount = vEBTree_upper_sqroot(tree->unisize);
        for (int i=0; i < clustamount; i++) {
            vEBTree_printContent(tree->cluster[i],offset+(i*vEBTree_lower_sqroot(tree->unisize)));
        }
    }*/
    /*
    printf("vEB(%d) min: %d, max: %d -> summary ommited\n", (*tree)->unisize, (*tree)->min, (*tree)->max);
    int clustamount = vEBTree_upper_sqroot((*tree)->unisize);
    for (int i=0; i < clustamount; i++) {
        vEBTree_printContent(&((*tree)->cluster[i]),offset+(i*vEBTree_lower_sqroot((*tree)->unisize)));
    }*/
    
    int usz = (*tree)->unisize;
    if ((*tree)->min == -1)
    {
        /* Tree is empty. */
        for (int i=0; i<usz; i++) {
            printf("[%d] = -1\n",i+offset);
        }
    } else if ((*tree)->min == (*tree)->max) {
        /* Tree has only one element */
        for (int i=0; i<usz; i++) {
            if (i == (*tree)->min) {
                printf("+[%d] = 1\n",i+offset);
            } else {
                printf("[%d] = -1\n",i+offset);
            }
        }
    } else {
        /* Tree has more than one element */
        printf("-[%d] = 1\n",(*tree)->min+offset);
        int clustamount = vEBTree_upper_sqroot(usz);
        int clustsz = vEBTree_lower_sqroot(usz);
        for (int i=0; i < clustamount; i++) {
            vEBTree_printContent(&((*tree)->cluster[i]), offset+(i*clustsz));
        }
    }
    
}

int vEBTree_search(vEBTree *tree, int x)
{
    return vEBTree_member(tree, x);
}

int vEBTree_member(vEBTree *tree, int x)
{
    if (x == tree->min || x == tree->max) {
        return 1;
    } else if (tree->unisize == 2)
    {
        return 0;
    }
    return vEBTree_member(tree->cluster[vEBTree_high(x, tree->unisize)]
                          , vEBTree_low(x, tree->unisize));
}

void vEBTree_insert_empty_tree(vEBTree *tree, int x)
{
   // printf("asdsdasaddsa %d\n",x);
    //vEBTree_printContent(&tree, 0);
    tree->max = x;
    tree->min = x;
      //  vEBTree_printContent(&tree, 0);
}

int vEBTree_insert(vEBTree *tree, int x)
{
    if (vEBTree_member(tree, x))
    {
        printf("%d is already a member\n",x);
        return -1;
    }
    if (tree->min == -1)
    {
        //printf("DFdf");
        vEBTree_insert_empty_tree(tree, x);
    } else {
        if (x < tree->min)
        {
            int tmp = x;
            x = tree->min;
            tree->min = tmp;
        }
        int x_h = vEBTree_high(x, tree->unisize);
        int x_l = vEBTree_low(x, tree->unisize);
        if (tree->unisize > 2)
        {
            if (vEBTree_minimum(tree->cluster[x_h]) == -1)
            {
                vEBTree_insert(tree->summary, x_h);
                vEBTree_insert_empty_tree(tree->cluster[x_h], x_l);
            } else {
                vEBTree_insert(tree->cluster[x_h], x_l);
            }
        }
        if (x > tree->max)
        {
            tree->max = x;
        }
    }
    return 0;
}

int vEBTree_delete(vEBTree *tree, int x)
{
    if (tree->min == tree->max)
    {
        tree->min = -1;
        tree->max = -1;
    } else if (tree->unisize == 2)
    {
        if (x == 0) {
            tree->min = 1;
        } else {
            tree->min = 0;
        }
        tree->max = tree->min;
    } else {
        if (x == tree->min)
        {
            int frst_cls = vEBTree_minimum(tree->summary);
            x = vEBTree_index(frst_cls, vEBTree_minimum(tree->cluster[frst_cls]), tree->unisize);
            tree->min = x;
        }
        int x_h = vEBTree_high(x, tree->unisize);
        int x_l = vEBTree_low(x, tree->unisize);
        vEBTree_delete(tree->cluster[x_h], x_l);
        if (vEBTree_minimum(tree->cluster[x_h]) == -1)
        {
            vEBTree_delete(tree->summary, x_h);
            if (x == tree->max)
            {
                int sum_max = vEBTree_maximum(tree->summary);
                if (sum_max == -1)
                {
                    tree->max = tree->min;
                } else {
                    tree->max = vEBTree_index(sum_max, vEBTree_maximum(tree->cluster[sum_max]), tree->unisize);
                }
            }
        } else if (x == tree->max)
        {
            tree->max = vEBTree_index(x_h, vEBTree_maximum(tree->cluster[x_h]), tree->unisize);
        }
    }
    return 0;
}

int vEBTree_successor(vEBTree *tree, int x)
{
    int unisz = tree->unisize;
    if (unisz == 2)
    {
        if (x == 0 && tree->max == 1) {
            return 1;
        } else {
            return -1;
        }
    } else if (tree->min != -1 && x < tree->min)
    {
        return tree->min;
    } else {
        int x_h = vEBTree_high(x, unisz);
        int x_l = vEBTree_low(x, unisz);
        int max_low = vEBTree_maximum(tree->cluster[x_h]);
        
        if (max_low != -1 && x_l < max_low)
        {
            int offset = vEBTree_successor(tree->cluster[x_h], x_l);
            return vEBTree_index(x_h, offset, unisz);
        } else {
            int succ_cls = vEBTree_successor(tree->summary, x_h);
            if (succ_cls == -1)
            {
                return -1;
            } else {
                int offset = vEBTree_minimum(tree->cluster[succ_cls]);
                return vEBTree_index(succ_cls, offset, unisz);
            }
        }
    }
}

int vEBTree_predecessor(vEBTree *tree, int x)
{
    int unisz = tree->unisize;
    if (unisz == 2)
    {
        if (x == 1 && tree->min == 0) {
            return 0;
        } else {
            return -1;
        }
    } else if (tree->max != -1 && x > tree->max)
    {
        return tree->max;
    } else {
        int x_h = vEBTree_high(x, unisz);
        int x_l = vEBTree_low(x, unisz);
        int min_low = vEBTree_minimum(tree->cluster[x_h]);
        
        if (min_low != -1 && x_l > min_low)
        {
            int offset = vEBTree_predecessor(tree->cluster[x_h], x_l);
            return vEBTree_index(x_h, offset, unisz);
        } else {
            int pred_cls = vEBTree_predecessor(tree->summary, x_h);
            if (pred_cls == -1)
            {
                if (tree->min != -1 && x > tree->min)
                {
                    return tree->min;
                } else {
                    return -1;
                }
            } else {
                int offset = vEBTree_maximum(tree->cluster[pred_cls]);
                return vEBTree_index(pred_cls, offset, unisz);
            }
        }
    }
}


int vEBTree_extract_minimum(vEBTree *tree)
{
    int min = tree->min;
    vEBTree_delete(tree, min);
    return min;
}

int vEBTree_extract_maximum(vEBTree *tree)
{
    int max = tree->max;
    vEBTree_delete(tree, max);
    return max;
}

void vEBTree_change_key(vEBTree *tree, int oldkey, int newkey)
{
    vEBTree_delete(tree, oldkey);
    vEBTree_insert(tree, newkey);
}

