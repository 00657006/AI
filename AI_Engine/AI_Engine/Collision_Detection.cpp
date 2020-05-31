#include "Collision_Detection.h"
static float Canves[4][3] = {
	{182.0f, 0.0f, 169.0f}, {57.0f, 0.0f, 100.0f}, {144.0f, 0.0f, 7.0f}
};
float Forward_Vector[4][3] = {
	{0.0f, 0.0f, -1.0f}, { 1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}
};
bool Conditional_Judge(ball* object, const char Operator, float left, float right, float bottom, float top)
{
	if (Operator == '&')
	{
		if ((object->xyz[0] >= left + object->R) && (object->xyz[0]) <= (right - object->R) &&
			(object->xyz[2] >= bottom + object->R) && (object->xyz[2]) <= (top - object->R))
			return true;
	}
	else if (Operator == '|')
	{
		if ((object->xyz[0] > left - object->R) || (object->xyz[0]) < (right + object->R) ||
			(object->xyz[2] > bottom - object->R) || (object->xyz[2]) < (top + object->R))
			return true;
	}
	return false;
}
bool Wall_Detection(ball* object, float left, float right, float bottom, float top)
{
	if ((((object->xyz[0] + object->R >= left) && (object->xyz[0] + object->R <= right)) ||
		((object->xyz[0] - object->R >= left) && (object->xyz[0] - object->R <= right))||
		((object->xyz[0] - object->R <= right) && (object->xyz[0] + object->R >= right)) ||
		((object->xyz[0] - object->R <= left) && (object->xyz[0] + object->R >= left))) &&
		(((object->xyz[2] + object->R >= bottom) && (object->xyz[2] + object->R <= top)) ||
		 ((object->xyz[2] - object->R >= bottom) && (object->xyz[2] - object->R <= top)) ||
			((object->xyz[2] - object->R <= top) && (object->xyz[2] + object->R >= top)) ||
			((object->xyz[2] - object->R <= bottom) && (object->xyz[2] + object->R >= bottom))))
		return true;
	return false;
}
void Reaction(ball* object)
{
	object->xyz[0] -= object->speed[0]; //倒退一步
	object->xyz[1] -= object->speed[1];
	object->xyz[2] -= object->speed[2];
	if (object->right)
	{
		RotateY(object->speed, -90);		//右轉
		object->Direction = (object->Direction + 1) % 4;
	}
	else
	{
		RotateY(object->speed, 90);		//左轉
		object->Direction = (object->Direction - 1) == -1 ? 3 : (object->Direction - 1);
	}
}
void DecideDirection(ball* object)
{
	unsigned char index = rand() % 3;
	unsigned char direction = rand() % 4;
	unsigned char before = object->Direction;
	if (index == 0)
	{//方向有上 左 下 右
		object->Direction = direction;
		RotateY(object->speed, -90.0f * (direction - before));
		object->xyz[0] = Canves[index][0] + Forward_Vector[direction][0] * (7.0f + object->R);
		object->xyz[2] = Canves[index][2] + Forward_Vector[direction][2] * (7.0f + object->R);
	}
	else if (index == 1)
	{//方向只有上 下 右
		if (direction == 3)
			direction = 1;
		object->Direction = direction;
		RotateY(object->speed, -90.0f * (direction - before));
		object->xyz[0] = Canves[index][0] + Forward_Vector[direction][0] * (7.0f + object->R);
		object->xyz[2] = Canves[index][2] + Forward_Vector[direction][2] * (7.0f + object->R);
	}
	else if (index == 2)
	{//方向只有左 下 右
		if (direction == 0)
			direction = 1;
		object->Direction = direction;
		RotateY(object->speed, -90.0f * (direction - before));
		object->xyz[0] = Canves[index][0] + Forward_Vector[direction][0] * (7.0f + object->R);
		object->xyz[2] = Canves[index][2] + Forward_Vector[direction][2] * (7.0f + object->R);
	}
}
void InOpenSpace(ball* object)
{
	if (Wall_Detection(object, 64.0f, 68.0f, 66.0f, 74.0f))
		Reaction(object);
	else if (Wall_Detection(object, 64.0f, 72.0f, 62.0f, 66.0f))
		Reaction(object);
	else if (Wall_Detection(object, 134.0f, 138.0f, 66.0f, 74.0f))
		Reaction(object);
	else if (Wall_Detection(object, 128.0f, 136.0f, 62.0f, 66.0f))
		Reaction(object);
	else if (Wall_Detection(object, 134.0f, 138.0f, 134.0f, 138.0f))
		Reaction(object);
	else if (Wall_Detection(object, 128.0f, 136.0f, 126.0f, 134.0f))
		Reaction(object);
	else if (Wall_Detection(object, 64.0f, 72.0f, 134.0f, 138.0f))
		Reaction(object);
	else if (Wall_Detection(object, 64.0f, 68.0f, 126.0f, 134.0f))
		Reaction(object);
}
void Predator_Detection(ball * object)
{
	if (Conditional_Judge(object, '|', 200.0f, 0.0f, 200.0f, 0.0f))//偵測有沒有超出範圍x、y : 0~200
		Reaction(object);
	else if (Conditional_Judge(object, '&', 0.0f, 14.0f, 178.0f, 200.0f))//第0區
	{	//是否進入左下corner的區域，判斷是否碰撞
		if (object->Area == 0)
		{
			object->BottleNeck++;
			if (object->BottleNeck > 22)
			{
				object->BottleNeck = 0;
				object->right = object->right == true ? false : true;
			}
		}
		else
		{
			object->Area = 0;
			object->BottleNeck = 0;
		}
		if (Wall_Detection(object, 6.0f, 10.0f, 192.0f, 200.0f))
			Reaction(object);
		else if (Wall_Detection(object, 0.0f, 4.0f, 182.0f, 186.0f))
			Reaction(object);
	}
	else if (Conditional_Judge(object, '&', 176.0f, 200.0f, 0.0f, 50.0f))//第1區
	{	//是否進入右上corner的區域，判斷是否碰撞
		if (object->Area == 1)
		{
			object->BottleNeck++;
			if (object->BottleNeck > 24)
			{
				object->BottleNeck = 0;
				object->right = object->right == true ? false : true;
			}
		}
		else
		{
			object->Area = 1;
			object->BottleNeck = 0;
		}
		/*if (Wall_Detection(object, 190.0f, 194.0f, 8.0f, 14.0f))
		{
			if (object->right)
			{
				RotateY(object->speed, -90);	//右轉
				object->Direction = (object->Direction + 1) % 4;
			}
			else
			{
				RotateY(object->speed, 90);		//左轉
				object->Direction = (object->Direction + 3) % 4;
			}
		}*/
		if (Wall_Detection(object, 190.0f, 194.0f, 0.0f, 6.0f))
			Reaction(object);
		else if (Wall_Detection(object, 196.0f, 200.0f, 14.0f, 18.0f))
			Reaction(object);
		else if (Wall_Detection(object, 180.0f, 188.0f, 14.0f, 18.0f))
			Reaction(object);
		else if (Wall_Detection(object, 180.0f, 184.0f, 6.0f, 14.0f))
			Reaction(object);
		else if (Wall_Detection(object, 190.0f, 194.0f, 25.0f, 45.0f))
			Reaction(object);
		else if (Wall_Detection(object, 194.0f, 200.0f, 33.0f, 37.0f))
			Reaction(object);
	}
	else if (Conditional_Judge(object, '&', 43.0f, 157.0f, 41.0f, 157.0f))//第6區:open space
	{
		if (object->Area == 6)
		{
			object->BottleNeck++;
			if (object->BottleNeck > 100)
			{
				object->BottleNeck = 0;
				object->right = object->right == true ? false : true;
			}
		}
		else
		{
			object->Area = 6;
			object->BottleNeck = 0;
		}
		InOpenSpace(object);
		if (Wall_Detection(object, 48.0f, 52.0f, 73.0f, 127.0f))
			Reaction(object);
		else if (Wall_Detection(object, 148.0f, 152.0f, 73.0f, 127.0f))
			Reaction(object);
		else if (Wall_Detection(object, 73.0f, 127.0f, 46.0f, 50.0f))
			Reaction(object);
		else if (Wall_Detection(object, 73.0f, 127.0f, 148.0f, 152.0f))
			Reaction(object);
	}
	else if (Conditional_Judge(object, '&', 175.0f, 188.0f, 162.0f, 175.0f))//第3區:右下的Portal
		DecideDirection(object);
	else if (Conditional_Judge(object, '&', 52.0f, 62.0f, 87.0f, 113.0f))//第4區:open space左邊的Portal
		DecideDirection(object);	
	else if (Conditional_Judge(object, '&', 137.0f, 150.0f, 0.0f, 13.0f))//第5區:右上的Portal
		DecideDirection(object);
	else
	{
		if (object->Area == 7)
		{
			object->BottleNeck++;
			if (object->BottleNeck > 300)
			{
				object->BottleNeck = 0;
				object->right = object->right == true ? false : true;
			}
		}
		else
		{
			object->Area = 7;
			object->BottleNeck = 0;
		}
	}
}
void Detect_Boundary(ball* object, int WhichOne)//檢查是否超出地圖範圍或與牆壁發生碰撞
{
	switch (object->role)
	{
	case 0://predator
		Predator_Detection(object);
		break;
	case 1://hover
		if (WhichOne == 3)
		{
			object->BottleNeck++;
			if (object->BottleNeck == 200)
			{
				object->BottleNeck = 0;
				float direction[3] = { 100 - object->xyz[0] , 0.0f , 100 - object->xyz[2] };
				normalize(direction);
				object->xyz[0] += direction[0] * 5;
				object->xyz[2] += direction[2] * 5;
				gap++;
				if (gap == 14)
				{
					object->xyz[0] = 100.0f;
					object->xyz[2] = 100.0f;
					int Bindex = Maze[(int)object->xyz[2]][(int)object->xyz[0]];
					if (Bindex >= 2 && Bindex < NumofBalls)
					{
						if (object->R > Ball[Bindex].R)
						{
							Maze[(int)object->xyz[2]][(int)object->xyz[0]] = WhichOne;
							object->R += Ball[Bindex].R;
							object->xyz[1] = object->R;
							Ball[Bindex].R = 0.0f;
						}
						else if (object->R < Ball[Bindex].R)
						{
							Maze[(int)object->xyz[2]][(int)object->xyz[0]] = Bindex;
							Ball[Bindex].R += object->R;
							Ball[Bindex].xyz[1] = object->R;
							object->R = 0.0f;
						}
					}
					else
						Maze[(int)object->xyz[2]][(int)object->xyz[0]] = WhichOne;
					gap = 0;
				}
			}
			if (Conditional_Judge(object, '|', 136.0f - gap * 2, 64.0f + gap * 2, 138.0f - gap * 2, 62.0f + gap * 2))//偵測第二區x:64~136 y:62:138
				Reaction(object);
			InOpenSpace(object);
		}
		else
		{
			object->BottleNeck++;
			if (object->BottleNeck == 500)
			{
				object->BottleNeck = 0;
				object->Direction = (object->Direction + 2) % 4;
				object->right = !object->right;
			}
			if (Conditional_Judge(object, '|', 157, 43, 157, 41))//偵測第6區x:43~157 y:41:157
				Reaction(object);
			else if (Wall_Detection(object, 48.0f, 52.0f, 83.0f, 127.0f))
				Reaction(object);
			else if (Wall_Detection(object, 148.0f, 152.0f, 83.0f, 127.0f))
				Reaction(object);
			else if (Wall_Detection(object, 73.0f, 127.0f, 46.0f, 50.0f))
				Reaction(object);
			else if (Wall_Detection(object, 73.0f, 127.0f, 148.0f, 152.0f))
				Reaction(object);
		}
		break;
	}
}
void Investigation(ball* Balls)//Predator偵測是否遇到enemy或food(屬於看到的反應 State : Search)
{
	for (int i = 0; i < 2; i++)
	{
		int Bindex = 0;
		int StartPos[3] = { Balls[i].xyz[0], Balls[i].xyz[1] ,Balls[i].xyz[2] };
		for (int length = 0; length <= 50; length++)
		{
			if (Balls[i].Direction == 0)
			{
				Bindex = StartPos[2] - length;
				if (Bindex == 0)
					break;
				if (Maze[Bindex][StartPos[0]] == 255)
					break;
				else if (Maze[Bindex][StartPos[0]] >= 2 && Maze[Bindex][StartPos[0]] < 4)
				{
					int enemy = Maze[Bindex][StartPos[0]];
					if (Balls[enemy].R >= Balls[i].R)//escape
					{
						fprintf(stderr, "%d escape from %d\n", i, enemy);
						fprintf(stderr, "%d %d\n", StartPos[0], Bindex);
						RotateY(Ball[i].speed, -90);
						Ball[i].Direction = (Ball[i].Direction + 1) % 4;
						break;
					}
					else if (Balls[enemy].R < Balls[i].R)//pursuit
					{
						fprintf(stderr, "%d pursuit %d\n", i, enemy);
						break;
					}
				}
				else if (Maze[Bindex][StartPos[0]] >= 3 && Maze[Bindex][StartPos[0]] < NumofBalls)
				{
					fprintf(stderr, "%d pursuit food %d \n", i, Maze[Bindex][StartPos[0]]);
					break;
				}
			}	
			else if (Balls[i].Direction == 1)
			{
				Bindex = StartPos[0] + length;
				if (Bindex == 200)
					break;
				if (Maze[StartPos[2]][Bindex] == 255)
					break;
				else if (Maze[StartPos[2]][Bindex] >= 2 && Maze[StartPos[2]][Bindex] < 4)
				{
					int enemy = Maze[StartPos[2]][Bindex];
					if (Balls[enemy].R >= Balls[i].R)//escape
					{
						RotateY(Ball[i].speed, -90);
						Ball[i].Direction = (Ball[i].Direction + 1) % 4;
						fprintf(stderr, "%d escape from %d\n", i, enemy);
						break;
					}
					else if (Balls[enemy].R < Balls[i].R)//pursuit
					{
						fprintf(stderr, "%d pursuit %d\n", i, enemy);
						break;
					}
				}
				else if (Maze[StartPos[2]][Bindex] >= 3 && Maze[StartPos[2]][Bindex] < NumofBalls)
				{
					fprintf(stderr, "%d pursuit food %d \n", i, Maze[StartPos[2]][Bindex]);
					break;
				}
			}
			else if (Balls[i].Direction == 2)
			{
				Bindex = StartPos[2] + length;
				if (Bindex == 200)
					break;
				if (Maze[Bindex][StartPos[0]] == 255)
					break;
				else if (Maze[Bindex][StartPos[0]] >= 2 && Maze[Bindex][StartPos[0]] < 4)
				{
					int enemy = Maze[Bindex][StartPos[0]];
					if (Balls[enemy].R >= Balls[i].R)//escape
					{
						fprintf(stderr, "%d %d \n", StartPos[0], Bindex);
						fprintf(stderr, "%d escape from %d\n", i, enemy);
						fprintf(stderr, "%d\n", Maze[StartPos[0]][Bindex]);
						fprintf(stderr, "%f %f\n", Ball[enemy].xyz[0], Ball[enemy].xyz[2]);
						RotateY(Ball[i].speed, -90);
						Ball[i].Direction = (Ball[i].Direction + 1) % 4;
						break;
					}
					else if (Balls[enemy].R < Balls[i].R)//pursuit
					{
						fprintf(stderr, "%d pursuit %d\n", i, enemy);
						break;
					}
				}
				else if (Maze[Bindex][StartPos[0]] >= 3 && Maze[Bindex][StartPos[0]] < NumofBalls)
				{
					fprintf(stderr, "%d pursuit food %d \n", i, Maze[Bindex][StartPos[0]]);
					break;
				}
			}
			else if (Balls[i].Direction == 3)
			{
				Bindex = StartPos[0] - length;
				if (Bindex == 0)
					break;
				if (Maze[StartPos[2]][Bindex] == 255)
					break;
				else if (Maze[StartPos[2]][Bindex] >= 2 && Maze[StartPos[2]][Bindex] < 4)
				{
					int enemy = Maze[StartPos[2]][Bindex];
					if (Balls[enemy].R >= Balls[i].R)//escape
					{
						fprintf(stderr, "%d %d \n", Bindex, StartPos[2]);
						fprintf(stderr, "%d escape from %d\n", i, enemy);
						RotateY(Ball[i].speed, -90);
						Ball[i].Direction = (Ball[i].Direction + 1) % 4;
						break;
					}
					else if (Balls[enemy].R < Balls[i].R)//pursuit
					{
						fprintf(stderr, "%d pursuit %d\n", i, enemy);
						break;
					}
				}
				else if (Maze[StartPos[2]][Bindex] >= 3 && Maze[StartPos[2]][Bindex] < NumofBalls)
				{
					fprintf(stderr, "%d pursuit food %d \n", i, Maze[StartPos[2]][Bindex]);
					break;
				}
			}
				
		}
	}
}
unsigned char FuzzyLogic(float distance)
{//0 represent close  1 represent comfortable 2 represent far
	if (distance <= 15)
		return 0;
	else if (distance > 15 && distance <= 20)
	{
		int close = 100 - 10 * (distance - 10), comfortable = 20 * (distance - 15);
		return close > comfortable ? 0 : 1;
	}
	else if (distance > 20 && distance <= 25)
		return 1;
	else if (distance > 25 && distance < 30)
	{
		int comfortable = 100 - 10 * (distance - 20), far = 20 * (distance - 25);
		return comfortable > far ? 1 : 2;
	}
	else
		return 2;
}
