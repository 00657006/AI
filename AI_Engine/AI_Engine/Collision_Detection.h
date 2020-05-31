#pragma once
#ifndef COLLISION_DETECTION_H
#define COLLISION_DETECTION_H

#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"Mathematical_Formula.h"

typedef struct ball {
	float R;
	float speed[3] = { 0.0f };
	float xyz[3] = { 0.0f };
	unsigned char Direction;		//0 1 2 3 ->up right down left 
	unsigned char Area;				//The ball's location area
	int BottleNeck;		//prevent the ball from falling into loop
	unsigned char role;				//predator ¡B hover or food
	bool right;
};

extern ball Ball[12];
extern int NumofBalls;
extern float Forward_Vector[4][3];
extern unsigned char Maze[201][201];
extern unsigned char gap;

void Detect_Boundary(ball* , int);
void Investigation(ball*);
#endif