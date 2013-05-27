//
//  algos.c
//  DSX
//
//  Created by Arni Asgeirsson on 27/05/13.
//  Copyright (c) 2013 Arni Asgeirsson. All rights reserved.
//

#include <stdio.h>
#include "algos.h"
#include <stdlib.h>
#include <math.h>

vectort* algos_createVector(pointt *p1, pointt *p2)
{
    vectort *vec = (vectort*)malloc(sizeof(vectort));
    vec->p1 = *p1;
    vec->p2 = *p2;
    vec->x = p2->x - p1->x;
    vec->y = p2->y - p1->y;
    return vec;
}

float algos_findAngle(vectort *v1, vectort *v2)
{
    // angle(v1, v2) = acos( (v1x * v2x + v1y * v2y) / (sqrt(v1x^2+v1y^2) * sqrt(v2x^2+v2y^2)) )
    return acosf( (v1->x * v2->x + v1->y * v2->y) / (sqrtf(powf(v1->x, 2) + powf(v1->y, 2)) * sqrtf(powf(v2->x, 2) + powf(v2->y, 2))));
}

pointt* algos_findIntersection(lineSegt *line1, lineSegt *line2)
{
    // I assume that they do intersect!
    
    float ang1 = algos_findAngle(algos_createVector(&line1->p1, &line2->p1),
                                 algos_createVector(&line1->p1, &line1->p2));
    ang1 = ang1 * (180/M_PI);
    float ang2 = algos_findAngle(algos_createVector(&line1->p1, &line2->p2),
                                 algos_createVector(&line1->p1, &line1->p2));
    ang2 = ang2 * (180/M_PI);
    float diff = (ang1 / (ang1+ang2));
    printf("Found two angels: %f, %f. The diff is: %f\n",ang1,ang2,diff);
    
    vectort *vec = algos_createVector(&line2->p1, &line2->p2);
    printf("vector is (%f,%f)\n", vec->x, vec->y);
    vec->x = vec->x * diff;
    vec->y = vec->y * diff;
    printf("vector is (%f,%f)\n", vec->x, vec->y);    
    pointt *p = (pointt*)malloc(sizeof(pointt));
    p->x = line2->p1.x + vec->x;
    p->y = line2->p1.y + vec->y;
    
    return p;
}

float algos_distance(pointt *p1, pointt *p2)
{
    return sqrtf(powf(p2->x - p1->x, 2) + powf(p2->y - p1->y, 2));
}

pointt* algos_findIntersection2(lineSegt *line1, lineSegt *line2)
{
    // I assume that they do intersect!
    
    // Special case 1: If they are the same line
    
    if (line1->p1.x - line2->p1.x == 0
        && line1->p1.y - line2->p1.y == 0
        && line1->p2.x - line2->p2.x == 0
        && line1->p2.y - line2->p2.y == 0)
    {
        pointt *p = (pointt*)malloc(sizeof(pointt));
        
        p->x = (line1->p1.x + line1->p2.x) / 2;
        p->y = (line1->p1.y + line1->p2.y) / 2;
        
        return p;
    }

    // Special case 2: One is point (not both, as then they would be special case 1)
    
    if (line1->p1.x == line1->p2.x && line1->p1.y == line1->p2.y)
    {
        pointt *p = (pointt*)malloc(sizeof(pointt));
        
        p->x = line1->p1.x;
        p->y = line1->p1.y;
        
        return p;
    } else if (line2->p1.x == line2->p2.x && line2->p1.y == line2->p2.y)
    {
        pointt *p = (pointt*)malloc(sizeof(pointt));
        
        p->x = line2->p1.x;
        p->y = line2->p1.y;
        
        return p;
    }
    
    // Special case 3: They intersect in two end points
    
    if ((line1->p1.x == line2->p1.x && line1->p1.y == line2->p1.y)
        || (line1->p1.x == line2->p2.x && line1->p1.y == line2->p2.y))
    {
        pointt *p = (pointt*)malloc(sizeof(pointt));
        
        p->x = line1->p1.x;
        p->y = line1->p1.y;
        
        return p;
    } else if ((line1->p2.x == line2->p1.x && line1->p2.y == line2->p1.y)
               || (line1->p2.x == line2->p2.x && line1->p2.y == line2->p2.y))
    {
        pointt *p = (pointt*)malloc(sizeof(pointt));
        
        p->x = line1->p2.x;
        p->y = line1->p2.y;
        
        return p;
    }
    
    // Normal case
    
    float B = algos_findAngle(algos_createVector(&line1->p1, &line2->p1),
                                 algos_createVector(&line1->p1, &line1->p2));
    //B = B * (180/M_PI);
    float A = algos_findAngle(algos_createVector(&line2->p1, &line2->p2),
                                 algos_createVector(&line2->p1, &line1->p1));
    //A = A * (180/M_PI);
    
    float C = M_PI - (A+B);

    printf("Found three angels: A %f, B %f, C %f\n",A,B,C);

    float c = algos_distance(&line1->p1, &line2->p1);
    
    
    printf("The first length is %f and angle is %f\n", c,C);
    
    float sinB = sinf(B)* (180/M_PI);
    float sinC = sinf(C)* (180/M_PI);
    float b = (c * sinB) / sinC;
    printf("sinB = %f sinC = %f, c = %f, result = %f\n",sinB,sinC,c,b);
    
    printf("The length b is %f\n",b);
    
    vectort *vec = algos_createVector(&line2->p1, &line2->p2);
    printf("vector is (%f,%f)\n", vec->x, vec->y);
    float len4 = algos_distance(&vec->p1, &vec->p2);
    len4 = b / len4;
    vec->x = vec->x * len4;
    vec->y = vec->y * len4;
    printf("vector is (%f,%f)\n", vec->x, vec->y);
    pointt *p = (pointt*)malloc(sizeof(pointt));
    p->x = line2->p1.x + vec->x;
    p->y = line2->p1.y + vec->y;
    
    return p;
}