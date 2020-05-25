#include"texture.h"

void make_tree()
{
	int   i, j, c;

	for (i = 0; i < TSIZE; i++)
		for (j = 0; j < TSIZE; j++) {
			if (j > i / 2 && j <= 64 - i / 2) c = 255;
			else c = 0;
			tree[i][j][0] = c / 8;
			tree[i][j][1] = c / 2;
			tree[i][j][2] = c / 4;
			if (c == 255) tree[i][j][3] = 255;
			else tree[i][j][3] = 0;
		}
	//Generate trunk
	for (i = 0; i < TSIZE / 3; i++) {
		for (j = 0; j < TSIZE / 2 - 4; j++) tree[i][j][3] = 0;
		for (j = TSIZE / 2 + 4; j < TSIZE; j++) tree[i][j][3] = 0;
	}
}
void Create_Texture_Circle()
{
	int  y, x, i, temp;
	for (y = 0; y < 64; y++)
	{
		for (x = 0; x < 64; x++)
		{
			circle[y][x][0] = 100;
			circle[y][x][1] = 100;
			circle[y][x][2] = 100;
			circle[y][x][3] = 255;
		}
	}
	for (y = 16, x = 0; y < 48; y++)
	{
		if (y <= 20 && y >= 17)
			x = x + 2;
		else if (y == 22 || y == 25 || y == 31)
			x = x + 1;
		else if (y == 42 || y == 39 || y == 33)
			x = x - 1;
		else if (y <= 47 && y >= 44)
			x = x - 2;
		temp = x;
		for (x = 0; x < temp; x++)
		{
			circle[y][x][0] = 150;
			circle[y][x][1] = 150;
			circle[y][x][2] = 150;
			circle[y][x][3] = 255;
		}
		for (x = 64 - temp; x < 64; x++)
		{
			circle[y][x][0] = 150;
			circle[y][x][1] = 150;
			circle[y][x][2] = 150;
			circle[y][x][3] = 255;
		}
		x = temp;
	}

	for (x = 16, y = 0; x < 48; x++)
	{
		if (x <= 20 && x >= 17)
			y = y + 2;
		else if (x == 22 || x == 25 || x == 31)
			y = y + 1;
		else if (x == 42 || x == 39 || x == 33)
			y = y - 1;
		else if (x <= 47 && x >= 44)
			y = y - 2;
		temp = y;
		for (y = 0; y < temp; y++)
		{
			circle[y][x][0] = 200;
			circle[y][x][1] = 200;
			circle[y][x][2] = 200;
			circle[y][x][3] = 255;
		}
		for (y = 64 - temp; y < 64; y++)
		{
			circle[y][x][0] = 200;
			circle[y][x][1] = 200;
			circle[y][x][2] = 200;
			circle[y][x][3] = 255;
		}
		y = temp;
	}
	for (i = 0; i < 61; i++)
	{
		for (y = i; y < 4 + i; y++)
		{
			for (x = i; x < 4 + i; x++)
			{
				circle[y][x][0] = 255;
				circle[y][x][1] = 255;
				circle[y][x][2] = 255;
				circle[y][x][3] = 255;
			}
		}
	}
	for (i = 0; i < 61; i++)
	{
		for (y = i; y < 4 + i; y++)
		{
			for (x = 60 - i; x < 64 - i; x++)
			{
				circle[y][x][0] = 255;
				circle[y][x][1] = 255;
				circle[y][x][2] = 255;
				circle[y][x][3] = 255;
			}
		}
	}
}
void Create_Texture_Waterwave()
{
	int x, y, i;

	for (x = 0; x < 64; x++)
		for (y = 0; y < 32; y++)
		{
			waterwave[x][y][0] = 0;
			waterwave[x][y][1] = 100;
			waterwave[x][y][2] = 255;
			waterwave[x][y][3] = 255;
		}

	x = 0;	y = 4;
	while (y <= 28)
	{
		for (i = x; i < 32; i++)
		{
			waterwave[i][y][0] = 200;
			waterwave[i][y][1] = 255;
			waterwave[i][y][2] = 255;
			waterwave[i][y][3] = 255;
		}
		y++;
		if (y < 9)
			x += 3;
		else if (y == 9)
			x++;
		else if (y == 10)
			x += 2;
		else if (y == 11)
			x++;
		else if (y == 12)
			x += 2;
		else if (y == 13)
			x++;
		else if (y == 14)
			x += 2;
		else if (y == 16)
			x++;
		else if (y == 19)
			x++;
		else if (y == 21)
			x++;
		else if (y == 23)
			x++;
		else if (y == 26)
			x++;
		else
			x++;
	}
	x = 0;	y = 0;
	while (y <= 24)
	{
		for (i = x; i < 32; i++)
		{
			waterwave[i][y][0] = 0;
			waterwave[i][y][1] = 100;
			waterwave[i][y][2] = 255;
			waterwave[i][y][3] = 255;
		}
		y++;
		if (y < 5)
			x += 3;
		else if (y == 5)
			x++;
		else if (y == 6)
			x += 2;
		else if (y == 7)
			x++;
		else if (y == 8)
			x += 2;
		else if (y == 9)
			x++;
		else if (y == 10)
			x += 2;
		else if (y == 11)
			x++;
		else if (y == 14)
			x++;
		else if (y == 16)
			x++;
		else if (y == 18)
			x++;
		else if (y == 21)
			x++;
		else
			x++;
	}

	for (x = 63; x > 31; x--)
		for (y = 0; y < 32; y++)
			for (i = 0; i < 4; i++)
				waterwave[x][y][i] = waterwave[63 - x][y][i];

	for (y = 32; y < 64; y++)
		for (x = 0; x < 64; x++)
			for (i = 0; i < 4; i++)
			{
				if (x >= 47)
					waterwave[x][y][i] = waterwave[x - 47][y - 32][i];
				else
					waterwave[x][y][i] = waterwave[x + 16][y - 32][i];
			}
}

void Create_Texture_Land()
{
	int x, y, i;

	for (y = 0; y < 32; y++)
		for (x = 0; x < 32; x++)
		{
			land[x][y][0] = 240;
			land[x][y][1] = 240;
			land[x][y][2] = 240;
			land[x][y][3] = 255;
		}


	for (x = 24; x < 32; x++)
	{
		land[x][0][0] = 255;
		land[x][0][1] = 200;
		land[x][0][2] = 200;
		land[x][0][3] = 255;

		land[0][x][0] = 255;
		land[0][x][1] = 200;
		land[0][x][2] = 200;
		land[0][x][3] = 255;
	}
	for (x = 26; x < 32; x++)
	{
		land[x][1][0] = 255;
		land[x][1][1] = 200;
		land[x][1][2] = 200;
		land[x][1][3] = 255;

		land[1][x][0] = 255;
		land[1][x][1] = 200;
		land[1][x][2] = 200;
		land[1][x][3] = 255;
	}
	for (x = 27; x < 32; x++)
	{
		for (y = 2; y < 4; y++)
		{
			land[x][y][0] = 255;
			land[x][y][1] = 200;
			land[x][y][2] = 200;
			land[x][y][3] = 255;

			land[y][x][0] = 255;
			land[y][x][1] = 200;
			land[y][x][2] = 200;
			land[y][x][3] = 255;
		}
	}
	for (x = 28; x < 32; x++)
	{
		for (y = 4; y < 7; y++)
		{
			land[x][y][0] = 255;
			land[x][y][1] = 200;
			land[x][y][2] = 200;
			land[x][y][3] = 255;

			land[y][x][0] = 255;
			land[y][x][1] = 200;
			land[y][x][2] = 200;
			land[y][x][3] = 255;
		}
	}
	for (x = 29; x < 32; x++)
	{
		for (y = 7; y < 9; y++)
		{
			land[x][y][0] = 255;
			land[x][y][1] = 200;
			land[x][y][2] = 200;
			land[x][y][3] = 255;

			land[y][x][0] = 255;
			land[y][x][1] = 200;
			land[y][x][2] = 200;
			land[y][x][3] = 255;
		}
	}
	for (x = 30; x < 32; x++)
	{
		for (y = 9; y < 12; y++)
		{
			land[x][y][0] = 255;
			land[x][y][1] = 200;
			land[x][y][2] = 200;
			land[x][y][3] = 255;

			land[y][x][0] = 255;
			land[y][x][1] = 200;
			land[y][x][2] = 200;
			land[y][x][3] = 255;
		}
	}
	for (x = 31; x < 32; x++)
	{
		for (y = 12; y < 16; y++)
		{
			land[x][y][0] = 255;
			land[x][y][1] = 200;
			land[x][y][2] = 200;
			land[x][y][3] = 255;

			land[y][x][0] = 255;
			land[y][x][1] = 200;
			land[y][x][2] = 200;
			land[y][x][3] = 255;
		}
	}

	for (y = 16; y < 32; y++)
		for (x = 16; x < 32; x++)
		{
			land[x][y][0] = 200;
			land[x][y][1] = 160;
			land[x][y][2] = 255;
			land[x][y][3] = 255;
		}
	for (y = 20; y < 32; y++)
		for (x = 20; x < 32; x++)
		{
			land[x][y][0] = 255;
			land[x][y][1] = 200;
			land[x][y][2] = 255;
			land[x][y][3] = 255;
		}

	for (x = 63; x > 31; x--)
	{
		for (y = 0; y < 32; y++)
			for (i = 0; i < 4; i++)
				land[x][y][i] = land[63 - x][y][i];
	}

	/* Create the rest half part */
	for (y = 32; y < 64; y++)
		for (x = 0; x < 64; x++)
			for (i = 0; i < 4; i++)
				land[x][y][i] = land[x][63 - y][i];
}

void Create_Texture_Star()
{
	int x, y, i;

	for (x = 0; x < 64; x++)
		for (y = 0; y < 64; y++)
		{
			star[x][y][0] = 255;
			star[x][y][1] = 255;
			star[x][y][2] = 255;
			star[x][y][3] = 255;
		}

	x = 31;	y = 60;
	while (x >= 12)
	{
		for (i = y; i > 4; i--)
		{
			star[x][i][0] = 100;
			star[x][i][1] = 100;
			star[x][i][2] = 255;
			star[x][i][3] = 255;
		}
		y -= 3;
		x--;
	}
	x = 31;	y = 20;
	while (x >= 12)
	{
		for (i = y; i > 4; i--)
		{
			star[x][i][0] = 255;
			star[x][i][1] = 255;
			star[x][i][2] = 255;
			star[x][i][3] = 255;
		}
		y -= 1;
		x--;
	}
	x = 4;	y = 40;
	while (y >= 18)
	{
		for (i = x; i < 32; i++)
		{
			star[i][y][0] = 100;
			star[i][y][1] = 100;
			star[i][y][2] = 255;
			star[i][y][3] = 255;
		}
		y -= 1;
		if ((y % 2) == 1)
			x += 2;
		else
			x++;
	}

	for (x = 63; x > 31; x--)
		for (y = 0; y < 64; y++)
			for (i = 0; i < 4; i++)
				star[x][y][i] = star[63 - x][y][i];
}

void brick_pattern()
{
	int  y, x, i;


	for (y = 0; y < 12; y++) {    /*----Create the first row of bricks----*/
		for (x = 0; x < 2; x++) {
			brick[y][x][0] = 140;
			brick[y][x][1] = 140;
			brick[y][x][2] = 140;
			brick[y][x][3] = 255;
		}

		for (x = 2; x < 30; x++) {
			brick[y][x][0] = 200;
			brick[y][x][1] = 0;
			brick[y][x][2] = 0;
			brick[y][x][3] = 255;
		}

		for (x = 30; x < 34; x++) {
			brick[y][x][0] = 140;
			brick[y][x][1] = 140;
			brick[y][x][2] = 140;
			brick[y][x][3] = 255;
		}

		for (x = 34; x < 62; x++) {
			brick[y][x][0] = 200;
			brick[y][x][1] = 0;
			brick[y][x][2] = 0;
			brick[y][x][3] = 255;
		}

		for (x = 62; x < 64; x++) {
			brick[y][x][0] = 140;
			brick[y][x][1] = 140;
			brick[y][x][2] = 140;
			brick[y][x][3] = 255;
		}
	}

	for (y = 12; y < 16; y++)     /*--Create the cement between two breick layers */
		for (x = 0; x < 64; x++) {
			brick[y][x][0] = 140;
			brick[y][x][1] = 140;
			brick[y][x][2] = 140;
			brick[y][x][3] = 255;
		}

	for (y = 16; y < 28; y++) {    /*--Create the 2nd layer of bricks---*/
		for (x = 0; x < 14; x++) {
			brick[y][x][0] = 200;
			brick[y][x][1] = 0;
			brick[y][x][2] = 0;
			brick[y][x][3] = 255;
		}

		for (x = 14; x < 18; x++) {
			brick[y][x][0] = 140;
			brick[y][x][1] = 140;
			brick[y][x][2] = 140;
			brick[y][x][3] = 255;
		}

		for (x = 18; x < 46; x++) {
			brick[y][x][0] = 200;
			brick[y][x][1] = 0;
			brick[y][x][2] = 0;
			brick[y][x][3] = 255;
		}

		for (x = 46; x < 50; x++) {
			brick[y][x][0] = 140;
			brick[y][x][1] = 140;
			brick[y][x][2] = 140;
			brick[y][x][3] = 255;
		}

		for (x = 50; x < 64; x++) {
			brick[y][x][0] = 200;
			brick[y][x][1] = 0;
			brick[y][x][2] = 0;
			brick[y][x][3] = 255;
		}
	}

	for (y = 28; y < 32; y++) /*---Add another layer of cement----*/
		for (x = 0; x < 64; x++) {
			brick[y][x][0] = 140;
			brick[y][x][1] = 140;
			brick[y][x][2] = 140;
			brick[y][x][3] = 255;
		}

	for (y = 32; y < 64; y++)
		for (x = 0; x < 64; x++)
			for (i = 0; i < 4; i++) brick[y][x][i] = brick[y - 32][x][i];
}
void make_check()
{
	int   i, j, c;

	for (i = 0; i < 256; i++)
		for (j = 0; j < 256; j++) {
			c = (((i & 0x10) == 0) ^ ((j & 0x10) == 0)) * 255;
			checkboard[i][j][0] = c;
			checkboard[i][j][1] = c;
			checkboard[i][j][2] = c;
			checkboard[i][j][3] = 255;
		}
}