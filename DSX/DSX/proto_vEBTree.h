//
//  proto_vEBTree.h
//  DSX
//
//  Created by Arni Asgeirsson on 27/02/13.
//  Copyright (c) 2013 Arni Asgeirsson. All rights reserved.
//

#ifndef DSX_proto_vEBTree_h
#define DSX_proto_vEBTree_h

typedef struct proto_vEBTree_struct_ {
    int unisize;
    struct proto_vEBTree_struct_ *summary;
    struct proto_vEBTree_struct_ **cluster;
    int array[2]; /* Use two bits instead, 1 is yes, 0 is no? To optimize. */
} proto_vEBTree_struct;

int proto_vEBTree_high(int x, int u);
int proto_vEBTree_low(int x, int u);
int proto_vEBTree_index(int x, int y, int u);

proto_vEBTree_struct* proto_vEBTree_init(int unisize);

int proto_vEBTree_search(proto_vEBTree_struct *vebTree, int x);
int proto_vEBTree_member(proto_vEBTree_struct *vebTree, int x);
int proto_vEBTree_insert(proto_vEBTree_struct *vebTree, int x);
int proto_vEBTree_delete(proto_vEBTree_struct *vebTree, int x);
int proto_vEBTree_minimum(proto_vEBTree_struct *vebTree);
int proto_vEBTree_maximum(proto_vEBTree_struct *vebTree);
int proto_vEBTree_successor(proto_vEBTree_struct *vebTree, int x);
int proto_vEBTree_predecessor(proto_vEBTree_struct *vebTree, int x);

void proto_vEBTree_printContent(proto_vEBTree_struct *vebTree, int offset);

#endif
