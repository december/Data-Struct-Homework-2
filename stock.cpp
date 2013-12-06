#include<cstdio>
#include<cstdlib>
using namespace std;

int n;
double result;
unsigned long long time;
int d;
char read;
int hp;

class queue
{
	int enter;
	int exit;
	int maximum[10000000];
	int count[10000000];
	bool isempty();
	public:
	queue();
	void enqueue(int x);
	void dequeue();
}q;

queue::queue()
{
	enter = 0;
	exit = 1;
	maximum[0] = 10000;
}

bool queue::isempty()
{
	if (enter < exit)
		return true;
	return false;
}

void queue::enqueue(int x)
{
	if (!isempty())
		result = maximum[exit] * d + result;
	hp = 1;
	while (x > maximum[enter])
	{
		hp = hp + count[enter];
		enter--;
	}
	enter++;
	maximum[enter] = x;
	count[enter] = hp;
	return;
}

void queue::dequeue()
{
	result = maximum[exit] * d + result;
	count[exit]--;
	if (count[exit] == 0)
	{
		maximum[exit] = 10000;
		exit++;
	}
	return;
}

int prepare()
{
	int temp = 0;
	read = getchar();
	while (read >= '0' && read <= '9')
	{
		temp = temp * 10 + (read - '0');
		read = getchar();
	}
	return temp;
}

int main ()
{
	#ifdef FUCKLYF
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	#endif
	scanf("%d", &n);
	n = n * 2;
	read = getchar();
	for (int i = 0;i < n;i++)
	{
		d = prepare();
		time = time + d;
		if (read == ' ')
			q.enqueue(prepare());
		else q.dequeue();
	}
	result = result / time;
	printf("%.2lf", result);
	return 0;
}
