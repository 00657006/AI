#include "Collision_Detection.h"
static float Canves[5][3] = {
	{169.0f, 0.0f, 156.0f}, {57.0f, 0.0f, 100.0f}, {144.0f, 0.0f, 7.0f}, {7.0f, 0.0f, 119.0f}, {143.0f, 0.0f, 100.0f}
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
	unsigned char index = rand() % 5;
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
	else if (index == 3)
	{//方向只有下
		direction = 2;
		object->Direction = 2;
		object->speed[2] = 1.0f;
		object->speed[0] = 0.0f;
		object->xyz[0] = Canves[index][0] + Forward_Vector[direction][0] * (7.0f + object->R);
		object->xyz[2] = Canves[index][2] + Forward_Vector[direction][2] * (7.0f + object->R);
	}
	else if (index == 4)
	{//方向只有上 下 右
		if (direction == 1)
			direction = 3;
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
	else if (Conditional_Judge(object, '&', 0.0f, 14.0f, 176.0f, 200.0f))//第0區
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
	else if (Conditional_Judge(object, '&', 157.0f, 200.0f, 0.0f, 55.0f))//第1區
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
			if (object->BottleNeck > 1)
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
		if (Conditional_Judge(object, '&', 52.0f, 63.0f, 87.0f, 113.0f))//第4區:open space左邊的Portal
			DecideDirection(object);
		else if (Conditional_Judge(object, '&', 137.0f, 148.0f, 87.0f, 113.0f))//第4區:open space左邊的Portal
			DecideDirection(object);
		else if (Wall_Detection(object, 48.0f, 52.0f, 75.0f, 125.0f))
			Reaction(object);
		else if (Wall_Detection(object, 148.0f, 152.0f, 75.0f, 125.0f))
			Reaction(object);
		else if (Wall_Detection(object, 73.0f, 127.0f, 46.0f, 50.0f))
			Reaction(object);
		else if (Wall_Detection(object, 73.0f, 127.0f, 148.0f, 152.0f))
			Reaction(object);
		else if (Wall_Detection(object, 139.0f, 149.0f, 139.0f, 149.0f))//cylinder
			Reaction(object);
		else if (Wall_Detection(object, 139.0f, 149.0f, 51.0f, 61.0f))//cylinder
			Reaction(object);
		else if (Wall_Detection(object, 51.0f, 61.0f, 139.0f, 149.0f))//cylinder
			Reaction(object);
		else if (Wall_Detection(object, 51.0f, 61.0f, 51.0f, 61.0f))//cylinder
			Reaction(object);
		
	}
	else if (Conditional_Judge(object, '&', 14.0f, 157.0f, 157.0f, 200.0f))//第7區:open space 下方的區域
	{
		if (object->Area == 7)
		{
			object->BottleNeck++;
			if (object->BottleNeck > 5)
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
		if (Wall_Detection(object, 24.0f, 28.0f, 166.0f, 200.0f))//最左邊wall
			Reaction(object);
		if(Wall_Detection(object, 68.0f, 78.0f, 188.0f, 192.0f))//T字wall(上)
			Reaction(object);
		if (Wall_Detection(object, 68.0f, 72.0f, 192.0f, 200.0f))//T字wall(下)
			Reaction(object);
		if (Wall_Detection(object, 50.0f, 90.0f, 174.0f, 178.0f))//刀字wall(上)
			Reaction(object);
		if (Wall_Detection(object, 86.0f, 90.0f, 178.0f, 200.0f))//刀字wall(下)
			Reaction(object);
		if (Wall_Detection(object, 90.0f, 130.0f, 188.0f, 192.0f))//刀字wall(下)
			Reaction(object);
		if (Wall_Detection(object, 108.0f, 112.0f, 166.0f, 190.0f))//刀字wall(下)
			Reaction(object);
	}
	else if (Conditional_Judge(object, '&', 157.0f, 200.0f, 55.0f, 200.0f))//第8區:Maze 右下方的區域
	{
		if (object->Area == 8)
		{
			object->BottleNeck++;
			if (object->BottleNeck > 10)
			{
				object->BottleNeck = 0;
				object->right = object->right == true ? false : true;
			}
		}
		else
		{
			object->Area = 8;
			object->BottleNeck = 0;
		}
		if (Wall_Detection(object, 177.0f, 185.0f, 188.0f, 200.0f))//右下角cylinder
			Reaction(object);
		else if (Wall_Detection(object, 175.0f, 200.0f, 98.0f, 102.0f))//一字wall
			Reaction(object);
		else if (Wall_Detection(object, 196.0f, 200.0f, 70.0f, 130.0f))//|字wall
			Reaction(object);
		else if (Conditional_Judge(object, '&', 162.0f, 175.0f, 149.0f, 162.0f))//第3區:右下的Portal
			DecideDirection(object);
	}
	else if (Conditional_Judge(object, '&', 0.0f, 43.0f, 0.0f, 157.0f))//第8區:Maze 右下方的區域
	{
		if (object->Area == 9)
		{
			object->BottleNeck++;
			if (object->BottleNeck > 50)
			{
				object->BottleNeck = 0;
				object->right = object->right == true ? false : true;
			}
		}
		else
		{
			object->Area = 9;
			object->BottleNeck = 0;
		}
		if (Wall_Detection(object, 0.0f, 10.0f, 0.0f, 10.0f))//第9區 左上角cylinder
			Reaction(object);
		else if (Wall_Detection(object, 0.0f, 25.0f, 98.0f, 102.0f))//第9區 一字wall
			Reaction(object);
		else if (Wall_Detection(object, 12.0f, 18.0f, 60.0f, 140.0f))//第9區  | 字wall
			Reaction(object);
		else if (Conditional_Judge(object, '&', 0.0f, 13.0f, 112.0f, 126.0f))//第9區:中下的Portal
			DecideDirection(object);
	}
	else if (Conditional_Judge(object, '&', 43.0f, 157.0f, 0.0f, 41.0f))//第8區:Maze 右下方的區域
	{
		if (object->Area == 10)
		{
			object->BottleNeck++;
			if (object->BottleNeck > 50)
			{
				object->BottleNeck = 0;
				object->right = object->right == true ? false : true;
			}
		}
		else
		{
			object->Area = 10;
			object->BottleNeck = 0;
		}
		if (Conditional_Judge(object, '&', 137.0f, 150.0f, 0.0f, 13.0f))//第5區:右上的Portal
			DecideDirection(object);
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
			if (Conditional_Judge(object, '|', 161, 39, 159, 37))//偵測第6區x:43~157 y:41:157
				Reaction(object);
			else if (Wall_Detection(object, 48.0f, 52.0f, 83.0f, 127.0f))
				Reaction(object);
			else if (Wall_Detection(object, 148.0f, 152.0f, 83.0f, 127.0f))
				Reaction(object);
			else if (Wall_Detection(object, 73.0f, 127.0f, 46.0f, 50.0f))
				Reaction(object);
			else if (Wall_Detection(object, 73.0f, 127.0f, 148.0f, 152.0f))
				Reaction(object);
			else if (Wall_Detection(object, 139.0f, 149.0f, 139.0f, 149.0f))//cylinder
				Reaction(object);
			else if (Wall_Detection(object, 139.0f, 149.0f, 51.0f, 61.0f))//cylinder
				Reaction(object);
			else if (Wall_Detection(object, 51.0f, 61.0f, 139.0f, 149.0f))//cylinder
				Reaction(object);
			else if (Wall_Detection(object, 51.0f, 61.0f, 51.0f, 61.0f))//cylinder
				Reaction(object);
			InOpenSpace(object);
		}
		break;
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
void Investigation(ball* Balls)//Predator偵測是否遇到enemy或food，鎖定prey(屬於看到的反應 State : Search)
{
	for (int i = 0; i < 2; i++)
	{
		int Bindex = 0;
		int StartPos[3] = { Balls[i].xyz[0], Balls[i].xyz[1] ,Balls[i].xyz[2] };
		for (int length = 0, Break = 0; length <= 50; length++)
		{
			if (Break == 1)
				break;
			if (Balls[i].Direction == 0)
			{
				for (int k = StartPos[0] - Balls[i].R; k <= StartPos[0] + Balls[i].R; k++)
				{
					Bindex = StartPos[2] - length;
					if (Bindex == 0)
					{
						Break = 1;
						break;
					}
					if (Maze[Bindex][k] == 255)
					{
						Break = 1;
						break;
					}
					else if (Maze[Bindex][k] >= 2 && Maze[Bindex][k] < 4)
					{
						int enemy = Maze[Bindex][k];
						if (Balls[enemy].R >= Balls[i].R)//escape
						{
							fprintf(stderr, "%d escape from %d\n", i, enemy);
							fprintf(stderr, "%d %d\n", k, Bindex);
							fprintf(stderr, "Fuzzy %d \n", FuzzyLogic(length));
							if (FuzzyLogic(length) <= 1)
							{
								RotateY(Ball[i].speed, -90);
								Ball[i].Direction = (Ball[i].Direction + 1) % 4;
								Ball[i].prey = enemy;
								/*if (FuzzyLogic(length) == 1)
									Ball[i].speed[0] *= 1.5;
								else
									Ball[i].speed[0] *= 2;*/
							}
							else
							{
								Ball[i].prey = enemy;
								Ball[i].speed[2] *= -1;
							}
							Break = 1;
							break;
						}
						else if (Balls[enemy].R < Balls[i].R)//pursuit
						{
							fprintf(stderr, "%d pursuit %d\n", i, enemy);
							if (Ball[i].prey != enemy)
							{
								fprintf(stderr, "%d pursuit %d\n", i, enemy);
								fprintf(stderr, "%d\n", FuzzyLogic(length));
								Ball[i].prey = enemy;
								if (FuzzyLogic(length) == 0)//close
									Ball[i].speed[2] *= 1.2;
								else if (FuzzyLogic(length) == 1)//comfortable
									Ball[i].speed[2] *= 1.5;
								else
									Ball[i].speed[2] *= 2;
							}
							if (Ball[enemy].Direction == 1 || Ball[enemy].Direction == 3)//對方換方向，即將消失
							{
								fprintf(stderr, "%f %f %f\n", Ball[enemy].xyz[0], Ball[enemy].xyz[1], Ball[enemy].xyz[2]);
								Ball[i].Target[0] = Ball[enemy].xyz[0];
								Ball[i].Target[1] = Ball[enemy].xyz[1];
								Ball[i].Target[2] = Ball[enemy].xyz[2];
							}
							Break = 1;
							break;
						}
					}
					else if (Maze[Bindex][k] >= 3 && Maze[Bindex][k] < NumofBalls)
					{
						
						if (Ball[i].prey != Maze[Bindex][k])
						{
							fprintf(stderr, "%d pursuit food %d \n", i, Maze[Bindex][k]);
							fprintf(stderr, "%d\n", FuzzyLogic(length));
							Ball[i].prey = Maze[Bindex][k];
							if (FuzzyLogic(length) == 0)//close
								Ball[i].speed[2] *= 1.2;
							else if (FuzzyLogic(length) == 1)//comfortable
								Ball[i].speed[2] *= 1.5;
							else
								Ball[i].speed[2] *= 2;
						}
						Break = 1;
						break;
					}
				}
				
			}	
			else if (Balls[i].Direction == 1)
			{
				for (int k = StartPos[2] - Balls[i].R; k <= StartPos[2] + Balls[i].R; k++)
				{
					//fprintf(stderr, "%d %d %d %f %f\n", k, StartPos[2], i, Ball[i].xyz[0], Ball[i].xyz[2]);
					Bindex = StartPos[0] + length;
					if (Bindex == 200)
					{
						Break = 1;
						break;
					}
					if (Maze[k][Bindex] == 255)
					{
						Break = 1;
						break;
					}
					else if (Maze[k][Bindex] >= 2 && Maze[k][Bindex] < 4)
					{
						int enemy = Maze[k][Bindex];
						if (Balls[enemy].R >= Balls[i].R)//escape
						{
							fprintf(stderr, "%d escape from %d\n", i, enemy);
							fprintf(stderr, "Fuzzy %d \n", FuzzyLogic(length));
							if (FuzzyLogic(length) <= 1)
							{
								RotateY(Ball[i].speed, -90);
								Ball[i].Direction = (Ball[i].Direction + 1) % 4;
								Ball[i].prey = enemy;
								/*if (FuzzyLogic(length) == 1)
									Ball[i].speed[2] *= 1.5;
								else
									Ball[i].speed[2] *= 2;*/
							}
							else
							{
								Ball[i].prey = enemy;
								Ball[i].speed[0] *= -1;
							}
							Break = 1;
							break;
						}
						else if (Balls[enemy].R < Balls[i].R)//pursuit
						{
							
							if (Ball[i].prey != enemy)
							{
								fprintf(stderr, "%d pursuit %d\n", i, enemy);
								fprintf(stderr, "%d\n", FuzzyLogic(length));
								Ball[i].prey = enemy;
								fprintf(stderr, "%f %f %f\n", Ball[enemy].xyz[0], Ball[enemy].xyz[1], Ball[enemy].xyz[2]);
								if (FuzzyLogic(length) == 0)//close
									Ball[i].speed[2] *= 1.2;
								else if (FuzzyLogic(length) == 1)//comfortable
									Ball[i].speed[2] *= 1.5;
								else
									Ball[i].speed[2] *= 2;
							}
							Break = 1;
							break;
						}
					}
					else if (Maze[k][Bindex] >= 3 && Maze[k][Bindex] < NumofBalls)
					{
						
						if (Ball[i].prey != Maze[k][Bindex])
						{
							fprintf(stderr, "%d pursuit food %d \n", i, Maze[k][Bindex]);
							fprintf(stderr, "%d\n", FuzzyLogic(length));
							Ball[i].prey = Maze[k][Bindex];
							if (FuzzyLogic(length) == 0)//close
								Ball[i].speed[2] *= 1.2;
							else if (FuzzyLogic(length) == 1)//comfortable
								Ball[i].speed[2] *= 1.5;
							else
								Ball[i].speed[2] *= 2;
						}
						Break = 1;
						break;
					}
				}
				
			}
			else if (Balls[i].Direction == 2)
			{
				for (int k = StartPos[0] - Balls[i].R; k <= StartPos[0] + Balls[i].R; k++)
				{
					Bindex = StartPos[2] + length;
					if (Bindex == 200)
					{
						Break = 1;
						break;
					}
						
					if (Maze[Bindex][k] == 255)
					{
						Break = 1;
						break;
					}
					else if (Maze[Bindex][k] >= 2 && Maze[Bindex][k] < 4)
					{
						int enemy = Maze[Bindex][k];
						if (Balls[enemy].R >= Balls[i].R)//escape
						{
							fprintf(stderr, "%d %d \n", k, Bindex);
							fprintf(stderr, "%d escape from %d\n", i, enemy);
							fprintf(stderr, "%d\n", Maze[k][Bindex]);
							fprintf(stderr, "%f %f\n", Ball[enemy].xyz[0], Ball[enemy].xyz[2]);
							if (FuzzyLogic(length) <= 1)
							{
								RotateY(Ball[i].speed, -90);
								Ball[i].Direction = (Ball[i].Direction + 1) % 4;
								Ball[i].prey = enemy;
								/*if (FuzzyLogic(length) == 1)
									Ball[i].speed[0] *= 1.5;
								else
									Ball[i].speed[0] *= 2;*/
							}
							else
							{
								Ball[i].prey = enemy;
								Ball[i].speed[2] *= -1;
							}
							Break = 1;
							break;
						}
						else if (Balls[enemy].R < Balls[i].R)//pursuit
						{
							
							if (Ball[i].prey != enemy)
							{
								fprintf(stderr, "%d pursuit %d\n", i, enemy);
								fprintf(stderr, "%d\n", FuzzyLogic(length));
								fprintf(stderr, "%f %f %f\n", Ball[enemy].xyz[0], Ball[enemy].xyz[1], Ball[enemy].xyz[2]);
								Ball[i].prey = enemy;
								if (FuzzyLogic(length) == 0)//close
									Ball[i].speed[2] *= 1.2;
								else if (FuzzyLogic(length) == 1)//comfortable
									Ball[i].speed[2] *= 1.5;
								else
									Ball[i].speed[2] *= 2;
							}
							Break = 1;
							break;
						}
					}
					else if (Maze[Bindex][k] >= 3 && Maze[Bindex][k] < NumofBalls)
					{
						
						if (Ball[i].prey != Maze[Bindex][k])
						{
							fprintf(stderr, "%d pursuit food %d \n", i, Maze[Bindex][k]);
							fprintf(stderr, "%d\n", FuzzyLogic(length));
							Ball[i].prey = Maze[Bindex][k];
							if (FuzzyLogic(length) == 0)//close
								Ball[i].speed[2] *= 1.2;
							else if (FuzzyLogic(length) == 1)//comfortable
								Ball[i].speed[2] *= 1.5;
							else
								Ball[i].speed[2] *= 2;
						}
						Break = 1;
						break;
					}
				}
				
			}
			else if (Balls[i].Direction == 3)
			{
			for (int k = StartPos[2] - Balls[i].R; k <= StartPos[2] + Balls[i].R; k++)
			{
				Bindex = StartPos[0] - length;
				if (Bindex == 0)
				{
					Break = 1;
					break;
				}
				if (Maze[k][Bindex] == 255)
				{
					Break = 1;
					break;
				}
				else if (Maze[k][Bindex] >= 2 && Maze[k][Bindex] < 4)
				{
					int enemy = Maze[k][Bindex];
					if (Balls[enemy].R >= Balls[i].R)//escape
					{
						fprintf(stderr, "%d %d %d\n", Bindex, k, StartPos[2]);
						fprintf(stderr, "%d escape from %d\n", i, enemy);
						fprintf(stderr, "%d\n", FuzzyLogic(length));
						if (FuzzyLogic(length) <= 1)
						{
							RotateY(Ball[i].speed, -90);
							Ball[i].Direction = (Ball[i].Direction + 1) % 4;
							Ball[i].prey = enemy;
							/*if(FuzzyLogic(length)==1)
								Ball[i].speed[2] *= 1.5;
							else
								Ball[i].speed[2] *= 2;*/
						}
						else
						{
							Ball[i].prey = enemy;
							Ball[i].speed[0] *= -1;
						}
						Break = 1;
						break;
					}
					else if (Balls[enemy].R < Balls[i].R)//pursuit
					{
						
						if (Ball[i].prey != enemy)
						{
							fprintf(stderr, "%d pursuit %d\n", i, enemy);
							fprintf(stderr, "%d\n", FuzzyLogic(length));
							fprintf(stderr, "%f %f %f\n", Ball[enemy].xyz[0], Ball[enemy].xyz[1], Ball[enemy].xyz[2]);
							Ball[i].prey = enemy;
							if (FuzzyLogic(length) == 0)//close
								Ball[i].speed[2] *= 1.2;
							else if (FuzzyLogic(length) == 1)//comfortable
								Ball[i].speed[2] *= 1.5;
							else
								Ball[i].speed[2] *= 2;
						}
						Break = 1;
						break;
					}
				}
				else if (Maze[k][Bindex] >= 3 && Maze[k][Bindex] < NumofBalls)
				{
					
					if (Ball[i].prey != Maze[k][Bindex])
					{
						fprintf(stderr, "%d pursuit food %d \n", i, Maze[k][Bindex]);
						fprintf(stderr, "%d\n", FuzzyLogic(length));
						Ball[i].prey = Maze[k][Bindex];
						if (FuzzyLogic(length) == 0)//close
							Ball[i].speed[2] *= 1.2;
						else if (FuzzyLogic(length) == 1)//comfortable
							Ball[i].speed[2] *= 1.5;
						else
							Ball[i].speed[2] *= 2;
					}
					Break = 1;
					break;
				}
			}
			}
				
		}
	}
}

