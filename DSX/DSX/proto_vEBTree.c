//
//  proto_vEBTree.c
//  DSX
//
//  Created by Arni Asgeirsson on 27/02/13.
//  Copyright (c) 2013 Arni Asgeirsson. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "proto_vEBTree.h"
#include <math.h>

proto_vEBTree_struct* proto_vEBTree_init(int unisize)
{
    if (unisize == -1) /* Should make sure unisize has correct size. */
    {
        return NULL;
    }
    proto_vEBTree_struct *tree = (proto_vEBTree_struct*)malloc(sizeof(proto_vEBTree_struct));
    
    tree->unisize = unisize;
    if (unisize > 2) {
        int clustersize = sqrtf(unisize);
        tree->cluster = malloc(sizeof(proto_vEBTree_struct)*clustersize);
        
        tree->summary = proto_vEBTree_init(clustersize);
        
        for (int i=0; i < clustersize; i++) {
            proto_vEBTree_struct *clust = proto_vEBTree_init(clustersize);
            tree->cluster[i] = clust;
        }
    } else {
        tree->summary = NULL;
        tree->cluster = NULL;
    }
    tree->array[0] = 0;
    tree->array[1] = 0;
    return tree;
}

int proto_vEBTree_high(int x, int u)
{
    return floorf(x/sqrtf(u));
}

int proto_vEBTree_low(int x, int u)
{
    return  (int)x % (int)sqrtf(u);
}

int proto_vEBTree_index(int x, int y, int u)
{
    return x * sqrtf(u) + y;
}

int proto_vEBTree_search(proto_vEBTree_struct *vebTree, int x)
{
    /* Is just member in disguise */
    return proto_vEBTree_member(vebTree, x);
}

int proto_vEBTree_member(proto_vEBTree_struct *vebTree, int x)
{
    if (x < 0 || x >= vebTree->unisize) {
        printf("Member, x is out of bounds %d\n", x);
        return -1; /* Error x is out of bounds. */
    }
    
    if (vebTree->unisize == 2)
    {
        return vebTree->array[x];
    }
    return proto_vEBTree_member(vebTree->cluster[proto_vEBTree_high(x, vebTree->unisize)]
                                , proto_vEBTree_low(x, vebTree->unisize));
}

int proto_vEBTree_insert(proto_vEBTree_struct *vebTree, int x)
{
    if (x < 0 || x >= vebTree->unisize) {
        printf("Insert, x is out of bounds %d\n", x);
        return -1; /* Error x is out of bounds. */
    }
    int a;
    int b;
    if (vebTree->unisize == 2) {
        vebTree->array[x] = 1;
    } else {
        a = proto_vEBTree_insert(vebTree->cluster[proto_vEBTree_high(x, vebTree->unisize)], proto_vEBTree_low(x, vebTree->unisize));
        b = proto_vEBTree_insert(vebTree->summary, proto_vEBTree_high(x, vebTree->unisize));
    }
    
    if (a == -1 || b == -1) {
        return -1;
    }
    return 0;
}

int proto_vEBTree_delete(proto_vEBTree_struct *vebTree, int x)
{
    if (x < 0 || x >= vebTree->unisize) {
        printf("Delete, x is out of bounds %d\n", x);
        return -1; /* Error x is out of bounds. */
    }
    
    int set0 = 0; /* 0 no, 1 yes */
    
    if (vebTree->unisize == 2) {
        vebTree->array[x] = 0;
        set0 = vebTree->array[0] == 0 && vebTree->array[1] == 0;
    } else {
        int nextClus = proto_vEBTree_high(x, vebTree->unisize);
        int lowX = proto_vEBTree_low(x, vebTree->unisize);
        set0 = proto_vEBTree_delete(vebTree->cluster[nextClus], lowX);
        if (set0) {
            set0 = proto_vEBTree_delete(vebTree->summary, nextClus);
        }
    }
    
    return set0;
}

int proto_vEBTree_minimum(proto_vEBTree_struct *vebTree)
{
    if (vebTree->unisize == 2) {
        if (vebTree->array[0] == 1) {
            return 0;
        } else if (vebTree->array[1] == 1) {
            return 1;
        } else {
            return -1; /* -1 denotes NULL atm */
        }
    } else {
        int min_cluster = proto_vEBTree_minimum(vebTree->summary);
        if (min_cluster == -1) {
            return -1;
        } else {
            int offset = proto_vEBTree_minimum(vebTree->cluster[min_cluster]);
            return proto_vEBTree_index(min_cluster, offset, vebTree->unisize);
        }
    }
}

int proto_vEBTree_maximum(proto_vEBTree_struct *vebTree)
{
    if (vebTree->unisize == 2) {
        if (vebTree->array[1] == 1) {
            return 1;
        } else if (vebTree->array[0] == 1) {
            return 0;
        } else {
            return -1; /* -1 denotes NULL atm */
        }
    } else {
        int max_cluster = proto_vEBTree_maximum(vebTree->summary);
        if (max_cluster == -1) {
            return -1;
        } else {
            int offset = proto_vEBTree_maximum(vebTree->cluster[max_cluster]);
            return proto_vEBTree_index(max_cluster, offset, vebTree->unisize);
        }
    }
}

int proto_vEBTree_successor(proto_vEBTree_struct *vebTree, int x)
{
    if (x < 0 || x >= vebTree->unisize) {
        printf("Succ, x is out of bounds %d\n", x);
        return -1; /* Error x is out of bounds. */
    }
    if (vebTree->unisize == 2) {
        if (x == 0 && vebTree->array[1] == 1) {
            return 1;
        } else {
            return -1;
        }
    } else {
        int offset = proto_vEBTree_successor(vebTree->cluster[proto_vEBTree_high(x, vebTree->unisize)], proto_vEBTree_low(x, vebTree->unisize));
        if (offset >= 0) {
            return proto_vEBTree_index(proto_vEBTree_high(x, vebTree->unisize)
                                       , offset, vebTree->unisize);
        } else {
            int succ_cluster = proto_vEBTree_successor(vebTree->summary, proto_vEBTree_high(x, vebTree->unisize));
            if (succ_cluster == -1) {
                return -1;
            } else {
                offset = proto_vEBTree_minimum(vebTree->cluster[succ_cluster]);
                return proto_vEBTree_index(succ_cluster, offset, vebTree->unisize);
            }
        }
    }
}

int proto_vEBTree_predecessor(proto_vEBTree_struct *vebTree, int x)
{
    if (x < 0 || x >= vebTree->unisize) {
        printf("Succ, x is out of bounds %d\n", x);
        return -1; /* Error x is out of bounds. */
    }
    
    if (vebTree->unisize == 2) {
        if (x == 1 && vebTree->array[0] == 1) {
            return 0;
        } else {
            return -1;
        }
    } else {
        int offset = proto_vEBTree_predecessor(vebTree->cluster[proto_vEBTree_high(x, vebTree->unisize)], proto_vEBTree_low(x, vebTree->unisize));
        if (offset >= 0) {
            return proto_vEBTree_index(proto_vEBTree_high(x, vebTree->unisize)
                                       , offset, vebTree->unisize);
        } else {
            int pre_cluster = proto_vEBTree_predecessor(vebTree->summary, proto_vEBTree_high(x, vebTree->unisize));
            if (pre_cluster == -1) {
                return -1;
            } else {
                offset = proto_vEBTree_maximum(vebTree->cluster[pre_cluster]);
                return proto_vEBTree_index(pre_cluster, offset, vebTree->unisize);
            }
        }
    }
}

void proto_vEBTree_printContent(proto_vEBTree_struct *vebTree, int offset)
{
    if (vebTree->unisize == 2) {
        printf("[%d] = %d\n[%d] = %d\n", offset, vebTree->array[0], offset+1, vebTree->array[1]);
    } else {
        int clsz = sqrtf(vebTree->unisize);
        for (int i=0; i < clsz; i++) {
            proto_vEBTree_printContent(vebTree->cluster[i],offset+(i*sqrtf(vebTree->unisize)));
        }
    }
}

