#include "Collision_Detection.h"
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
		((object->xyz[0] - object->R >= left) && (object->xyz[0] - object->R <= right))) &&
		(((object->xyz[2] + object->R >= bottom) && (object->xyz[2] + object->R <= top)) ||
		 ((object->xyz[2] - object->R >= bottom) && (object->xyz[2] - object->R <= top))))
		return true;
	return false;
}
void Reaction(ball* object)
{
	object->xyz[0] -= object->speed[0]; //倒退一步
	object->xyz[1] -= object->speed[1];
	object->xyz[2] -= object->speed[2];
	if(object->right)
		RotateY(object->speed, -90);		//右轉
	else
		RotateY(object->speed, 90);		//右轉
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
		if (Wall_Detection(object, 0.0f, 4.0f, 182.0f, 186.0f))
			Reaction(object);
	}
	else if (Conditional_Judge(object, '&', 176.0f, 200.0f, 0.0f, 22.0f))//第1區
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
		if (Wall_Detection(object, 190.0f, 194.0f, 8.0f, 14.0f))
		{
			if (object->right)
				RotateY(object->speed, -90);	//右轉
			else
				RotateY(object->speed, 90);		//左轉
		}
		if (Wall_Detection(object, 190.0f, 194.0f, 0.0f, 6.0f))
			Reaction(object);
		if (Wall_Detection(object, 196.0f, 200.0f, 14.0f, 18.0f))
			Reaction(object);
		if (Wall_Detection(object, 180.0f, 188.0f, 14.0f, 18.0f))
			Reaction(object);
		if (Wall_Detection(object, 180.0f, 184.0f, 6.0f, 14.0f))
			Reaction(object);
	}
	else if (Conditional_Judge(object, '&', 180.0f, 200.0f, 22.0f, 50.0f))//第3區
	{	//是否進入右上出發點的區域，判斷是否碰撞
		if (object->Area == 3)
		{
			object->BottleNeck++;
			if (object->BottleNeck > 26)
			{
				object->BottleNeck = 0;
				object->right = object->right == true ? false : true;
			}
		}
		else
		{
			object->Area = 3;
			object->BottleNeck = 0;
		}
		if (Wall_Detection(object, 190.0f, 194.0f, 25.0f, 45.0f))
		{
			fprintf(stderr, "%f　%f %f\n", object->xyz[0], object->xyz[1], object->xyz[2]);
			Reaction(object);
		}
			
		if (Wall_Detection(object, 194.0f, 200.0f, 33.0f, 37.0f))
			Reaction(object);
	}
}
void Detect_Boundary(ball* object)//檢查是否超出地圖範圍或與牆壁發生碰撞
{
	static int gap = 0;
	switch (object->role)
	{
	case 0://predator
		Predator_Detection(object);
		break;
	case 1://hover
		object->BottleNeck++;
		if (object->BottleNeck % 200 == 0)
		{
			float direction[3] = { 100 - object->xyz[0] , 0.0f , 100 - object->xyz[2] };
			normalize(direction);
			object->xyz[0] += direction[0] * 5;
			object->xyz[2] += direction[2] * 5;
			gap++;
			if (gap == 14)
			{
				object->xyz[0] = 100.0f;
				object->xyz[2] = 100.0f;
				object->R++;
				if (object->R >= 4.0f)
					object->R = 4.0f;
				gap = 0;
			}
		}
		if (Conditional_Judge(object, '|', 136.0f-gap*2, 64.0f+ gap*2, 138.0f- gap*2, 62.0f+ gap*2))//偵測第二區x:64~136 y:62:138
			Reaction(object);
		if (Wall_Detection(object, 64.0f, 68.0f, 66.0f, 74.0f))
			Reaction(object);
		if (Wall_Detection(object, 64.0f, 72.0f, 62.0f, 66.0f))
			Reaction(object);
		if (Wall_Detection(object, 134.0f, 138.0f, 66.0f, 74.0f))
			Reaction(object);
		if (Wall_Detection(object, 128.0f, 136.0f, 62.0f, 66.0f))
			Reaction(object);
		if (Wall_Detection(object, 134.0f, 138.0f, 134.0f, 138.0f))
			Reaction(object);
		if (Wall_Detection(object, 128.0f, 136.0f, 126.0f, 134.0f))
			Reaction(object);
		if (Wall_Detection(object, 64.0f, 72.0f, 134.0f, 138.0f))
			Reaction(object);
		if (Wall_Detection(object, 64.0f, 68.0f, 126.0f, 134.0f))
			Reaction(object);
		break;
	}
}
bool MayMeet(const ball* object1, const ball* object2)//Return true if two objects may meet
{
	if (Length(object1->xyz, object2->xyz) < object1->speed[0] * 100)
		return true;
	else if (Length(object1->xyz, object2->xyz) < object1->speed[2] * 100)
		return true;
	return false;
}
void Investigation(ball* Balls, int WhichOne)//Predator偵測是否遇到enemy或food
{
	for (int i = 0; i < 4/*NumofBalls*/; i++)
	{
		if (i == WhichOne)
			continue;
		if (Balls[i].Area == Balls[WhichOne].Area)
		{
			if (MayMeet(&Ball[WhichOne], &Ball[i]))
			{
			
			}
		}
	}
}

