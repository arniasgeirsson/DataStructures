//
//  vEBTree.h
//  DSX
//
//  Created by Arni Asgeirsson on 22/02/13.
//  Copyright (c) 2013 Arni Asgeirsson. All rights reserved.
//

#ifndef DSX_vEBTree_h
#define DSX_vEBTree_h

typedef struct vEBTree_ {
    int unisize;
    struct vEBTree_ *summary;
    struct vEBTree_ **cluster;
    int allowMultKeys;
    int min;
    int max;
} vEBTree;

int vEBTree_upper_sqroot(int u);
int vEBTree_lower_sqroot(int u);

int vEBTree_high(int x, int u);
int vEBTree_low(int x, int u);
int vEBTree_index(int x, int y, int u);

vEBTree* vEBTree_init(int unisize, int allowMltKeys);
void vEBTree_destroy(vEBTree **tree);

void vEBTree_printContent(vEBTree **tree, int offset);

int vEBTree_search(vEBTree *tree, int x);
int vEBTree_member(vEBTree *tree, int x);
void vEBTree_insert_empty_tree(vEBTree *tree, int x);
int vEBTree_insert(vEBTree *tree, int x);
int vEBTree_delete(vEBTree *tree, int x);
int vEBTree_minimum(vEBTree *tree);
int vEBTree_maximum(vEBTree *tree);
int vEBTree_successor(vEBTree *tree, int x);
int vEBTree_predecessor(vEBTree *tree, int x);

int vEBTree_extract_minimum(vEBTree *tree);
int vEBTree_extract_maximum(vEBTree *tree);
void vEBTree_change_key(vEBTree *tree, int oldkey, int newkey);

#endif
