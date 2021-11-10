#include <iostream>
#include <algorithm>
#include <time.h> 
using namespace std;

#define l(i, j) list[i*5+j]
#define SETSIZE 20

struct steps
{
public:
	int steplist[15];
	int steppoint = -1;

	void randomGenerate()
	{
		for (int i = 0; i < 15; ++i)
		{
			steplist[i] = rand() % 30;
		}
	}

	steps* randomVariate()
	{
		while (1)
		{
			steps* q = new steps(*this);
			for (int i = 0; i < 5; ++i)
			{
				q->steplist[rand() % 15] = rand() % 30;
			}
			for (int i = 0; i < 15; ++i)
			{
				if (q->steplist[i] == steplist[i]) continue;
				else return q;
			}
		}
	}

	steps()
	{
		randomGenerate();
	}

	steps(steps& p)
	{
		for (int i = 0; i < 15; ++i)
		{
			steplist[i] = p.steplist[i];
		}
	}
};

class arrlist
{
public:
	int list[30];
	
	int point = 0;

	int maxSingleMove = 0;

	inline bool isvalid(int i, int j)
	{
		return (i >= 0 && i <= 5) && (j >= 0 && j <= 4);
	}

	void act(int i, int j)
	{
		++point;
		switch (l(i, j))
		{
		case 0: l(i, j) = 1; if (isvalid(i, j + 1)) act(i, j + 1); break;
		case 1: l(i, j) = 2; if (isvalid(i + 1, j)) act(i + 1, j); break;
		case 2: l(i, j) = 3; if (isvalid(i, j - 1)) act(i, j - 1); break;
		case 3: l(i, j) = 0; if (isvalid(i - 1, j)) act(i - 1, j); break;
		}
	}

	void change(int num)
	{
		int i = num / 5;
		int j = num % 5;
		act(i, j);
		if (point > maxSingleMove) maxSingleMove = point;
		point = 0;
	}

	arrlist()
	{
		memset(list, 0, sizeof(int) * 30);
	}
};

int simulate(steps* s)
{
	arrlist* p = new arrlist;
	for (int i = 0; i < 15; ++i)
	{
		p->change(s->steplist[i]);
	}
	s->steppoint = p->maxSingleMove;
	delete p;
	return s->steppoint;
}

bool compare(steps* a, steps* b)
{
	return a->steppoint < b->steppoint;
}

void print(steps** list)
{
	for (int i = SETSIZE; i < 2*SETSIZE; ++i)
	{
		cout << "Point: " << list[i]->steppoint << "\t"
			<< "List:";
		for (int j = 0; j < 15; ++j)
		{
			cout << " " << list[i]->steplist[j];
		}
		cout << endl;
	}
}

int main()
{
	srand((unsigned)time(0));
	steps* list[2*SETSIZE]; int leng = 0;

	for (int i = 0; i < 2*SETSIZE; ++i)
	{
		list[i] = new steps();
		simulate(list[i]);
	}
	while (1)
	{
		for (int i = 0; i < 2*SETSIZE; ++i)
		{
			if (list[i]->steppoint != -1) break;
			simulate(list[i]);
		}
		sort(&list[0], &list[2*SETSIZE], compare);
		//print(list);
		//system("pause");
		for (int i = SETSIZE + 2; i < 2*SETSIZE; ++i)
		{
			delete (list[i - SETSIZE]);
			list[i - SETSIZE] = list[i]->randomVariate();
		}
		delete (list[0]);
		list[0] = new steps();
		delete (list[1]);
		list[1] = new steps();
	}
}