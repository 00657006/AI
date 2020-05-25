#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

extern enum {
	TSIZE=64, TSIZE2=256
};
extern unsigned char  checkboard[TSIZE2][TSIZE2][4];   /* checkboard textures */
extern unsigned char  tree[TSIZE][TSIZE][4];   /* checkboard textures */
extern unsigned char  texture[TSIZE][TSIZE][4];   /* checkboard textures */
extern unsigned char  brick[TSIZE][TSIZE][4];        /* brick wall textures */
extern unsigned char circle[TSIZE][TSIZE][4];
extern unsigned char waterwave[TSIZE][TSIZE][4];
extern unsigned char star[TSIZE][TSIZE][4];
extern unsigned char land[TSIZE][TSIZE][4];
extern unsigned int   textName[3];                   /* declare two texture maps*/
extern unsigned int TextureID[4];

void make_check();
void make_tree();
void Create_Texture_Circle();
void Create_Texture_Waterwave();
void Create_Texture_Land();
void Create_Texture_Star();
void brick_pattern();

#endif