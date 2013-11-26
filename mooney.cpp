#include<cstdlib>
#include<cstdio>
using namespace std;

int N, M;
int start, end;
char flag;
int count = 1;
int exitpos = 0;
int nodesize = 0;
int stacksize = 0;
int queue[500000];
int stack[500000];
int time = 0;
unsigned int answer = -1;
bool finished = false;

struct neighborlist
{
	int pos;       //邻居节点的序号
	neighborlist* next;
	neighborlist(int i = 0):pos(i), next(NULL) {}
}Temp[5000000];

struct node
{
	int order;       //点的序号
	int sign;           //强连通分量所用标记
	int subsign;        //强连通分量所用标记
	unsigned int moonmin;      //到起点经过的M数量
	bool moon;       //是否只有月亮
	bool visit;
	bool instack;     //当前在栈中
	int moneynum;        //到起点最多的钱数
	int money;       //该点（强连通分量）的钱数
	node* present;
	neighborlist *neighbor;
	node():moonmin(0), moneynum(-1), moon(1), neighbor(NULL), present(NULL) {}
}cross[500000], bignode[500000];	

node *target = NULL;
neighborlist* temp;
int newdis;

void search(node *n)
{
	neighborlist* t = n->neighbor;
	while (t && !finished)
	{
		node *m = &cross[t->pos]; 
		if (!m->visit)
		{
			m->visit = true;
			if (m->order == N - 1)
				finished = true;
			if (!m->moon)
			{
				m->moonmin = n->moonmin;
				search(m);
			}
			else
			{
				m->moonmin = n->moonmin + 1;
				queue[count] = m->order;
				count++;
			}
		}
		t = t->next;
	}
}

void findway()
{
	target = &cross[queue[exitpos]];
	target->visit = true;
	exitpos++;
	search(target);
}

int min(int a, int b)
{
	if (a > b)
		return b;
	return a;
}

void separate(node *n, neighborlist* list)
{
	n->sign = count;
	n->subsign = count;
	count++;
	n->instack = true;
	stack[stacksize] = n->order;
	stacksize++;
	while (list)
	{
		if (cross[list->pos].sign == 0)
		{
			separate(&cross[list->pos], cross[list->pos].neighbor);
			n->subsign = min(n->subsign, cross[list->pos].subsign);
		}
		else if (cross[list->pos].instack)
			n->subsign = min(n->subsign, cross[list->pos].sign);
		list = list->next;
	}
	if (n->sign == n->subsign)
	{
		bignode[nodesize] = *n;
		bignode[nodesize].neighbor = NULL;
		bignode[nodesize].order = nodesize;
		while (stack[stacksize-1] != n->order)
		{
			stacksize--;
			cross[stack[stacksize]].present = &bignode[nodesize];
			cross[stack[stacksize]].instack = false;
			bignode[nodesize].money += cross[stack[stacksize]].money;
		}
		n->present = &bignode[nodesize];
		n->instack = false;
		nodesize++;
		stacksize--;
	}
}

void addneighbor(node *n, node *m)
{
	if (!n || !m)
		return;
	start = n->order;
	end = m->order;
	if (start == end)
		return;
	Temp[time].pos = end;
	Temp[time].next = bignode[start].neighbor;
	bignode[start].neighbor = &Temp[time++];
}

void setneighbor(node *n)
{
	neighborlist* moveon;
	moveon = n->neighbor;
	while (moveon)
	{
		addneighbor(n->present, cross[moveon->pos].present);
		moveon = moveon->next;
	}
}

int findmoney(int number)
{
	int most = 0;
	neighborlist* moveon;
	if (bignode[number].moneynum >= 0)
		return bignode[number].moneynum;
	moveon = bignode[number].neighbor;
	while (moveon)
	{
		if (findmoney(moveon->pos) > most)
			most = bignode[moveon->pos].moneynum;
		moveon = moveon->next;
	}
	bignode[number].moneynum = most + bignode[number].money;
	return bignode[number].moneynum;
}

int main()
{
	#ifdef FUCKLYF
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	#endif
	scanf("%d %d", &N, &M);
	while (flag != 'm' && flag != 'M')
		flag = getchar();
	for (int i = 0;i < N;i++)
	{
		cross[i].order = i;
		if (flag == 'm')
		{
			cross[i].moon = false;
			cross[i].money = 1;
		}
		flag = getchar();
	}
	cross[0].moonmin = cross[0].moon;
	cross[0].visit = true;
	for (int i = 0;i < M;i++)
	{
		scanf("%d %d", &start, &end);
		Temp[time].pos = end;
		Temp[time].next = cross[start].neighbor;
		cross[start].neighbor = &Temp[time++];
	}
	queue[0] = 0;
	while (!finished)
		findway();
	printf("%u\n", cross[N-1].moonmin);
	count = 1;
	for (int i = 0;i < N;i++)
		if (cross[i].sign == 0)
			separate(&cross[i], cross[i].neighbor);
	for (int i = 0;i < N;i++)
		setneighbor(&cross[i]);
	answer = findmoney(cross[0].present->order);
	printf("%u\n", answer);
	return 0;
}
