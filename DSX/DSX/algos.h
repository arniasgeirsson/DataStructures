//
//  algos.h
//  DSX
//
//  Created by Arni Asgeirsson on 27/05/13.
//  Copyright (c) 2013 Arni Asgeirsson. All rights reserved.
//

#ifndef DSX_algos_h
#define DSX_algos_h

typedef struct pointt_ {
    float x;
    float y;
} pointt;

typedef struct vectort_ {
    pointt p1;
    pointt p2;
    float x;
    float y;
} vectort;

typedef struct lineSegt_ {
    pointt p1;
    pointt p2;
} lineSegt;

vectort* algos_createVector(pointt *p1, pointt *p2);
float algos_findAngle(vectort *v1, vectort *v2);
pointt* algos_findIntersection(lineSegt *line1, lineSegt *line2);
pointt* algos_findIntersection2(lineSegt *line1, lineSegt *line2);
float algos_distance(pointt *p1, pointt *p2);

#endif
