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
	bool right;
	int Area;
	int BottleNeck;
	int role;				//predator ¡B hover or food
};

extern ball Ball[12];

void Detect_Boundary(ball* );
#endif