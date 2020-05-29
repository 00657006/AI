#pragma once
#ifndef COLLISION_DETECTION_H
#define COLLISION_DETECTION_H

#include<math.h>
#include<stdio.h>
#include"Mathematical_Formula.h"

typedef struct ball {
	float R;
	float speed[3] = { 0.0f };
	float xyz[3] = { 0.0f };
	unsigned char Direction;		//0 1 2 3 ->up down left right
	unsigned char maze[201][201];	//for looking up table
	unsigned char Area;				//The ball's location area
	unsigned char BottleNeck;		//prevent the ball from falling into loop
	unsigned char role;				//predator ¡B hover or food
	bool right;
};

extern ball Ball[12];
extern int NumofBalls;

void Detect_Boundary(ball* );
void Investigation(ball* , int );
#endif