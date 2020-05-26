#pragma once
#ifndef COLLISION_DETECTION_H
#define COLLISION_DETECTION_H

#include<math.h>

typedef struct ball {
	float R;
	float speed[3] = { 0.0f };
	float xyz[3] = { 0.0f };
	int role;				//predator ¡B hover or food
};

extern ball Ball[12];
#endif