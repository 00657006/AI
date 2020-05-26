#pragma once
#ifndef RENDERING_H
#define RENDERING_H

#include<GL\freeglut.h>
#include"texture.h"
#include"Collision_Detection.h"

extern int width, height;

void Init();
void display();
void reshape(int, int);
void keyin(unsigned char, int, int);
void myIdle();
void draw_scene();

#endif