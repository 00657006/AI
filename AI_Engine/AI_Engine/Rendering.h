#pragma once
#ifndef RENDERING_H
#define RENDERING_H


#include<GL\freeglut.h>
#include<stdio.h>
#include"texture.h"
#include"Collision_Detection.h"
#include"Mathematical_Formula.h"

extern int width, height;
extern int Display_Mode;
extern enum list {
	Reset, FULL_SCREEN, FOLLOW_BALL_0, FOLLOW_BALL_1
};

void Init();
void display();
void reshape(int, int);
void keyin(unsigned char, int, int);
void myIdle();
void draw_scene();
void SetUpObject();

#endif