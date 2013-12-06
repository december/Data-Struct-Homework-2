#include<cstdio>
#include<cstdlib>
using namespace std;

int origin[6];
int waitsize = 1;

struct data
{
	int line;
	int col;
	int number[6];
}wait[20000];

struct node
{
	int pos;
	unsigned int dis;
	bool choosed;
	node* neighbor[4];
	node():dis(-1), choosed(0)
	{
		for (int k = 0;k < 4;k++)
			neighbor[k] = NULL;
	}
}chess[8][8][6][6][6][6][6][6];

void setneighbor(int i, int j, int f, int l, int b, int r, int u, int d)
{
	node *n = &chess[i][j][f][l][b][r][u][d];
	if (j > 0)
	{
		n->neighbor[0] = &chess[i][j-1][u][l][d][r][b][f];
		n->neighbor[0]->pos = waitsize;
		wait[waitsize++] = (data){i, j - 1, u, l, d, r, b, f};
	}
	if (i > 0)
	{
		n->neighbor[1] = &chess[i-1][j][f][u][b][d][r][l];
		n->neighbor[1]->pos = waitsize;
		wait[waitsize++] = (data){i - 1, j, f, u, b, d, r, l};
	}
	if (j < 7)
	{
		n->neighbor[2] = &chess[i][j+1][d][l][u][r][f][b];
		n->neighbor[2]->pos = waitsize;
		wait[waitsize++] = (data){i, j + 1, d, l, u, r, f, b};
	}
	if (i < 7)
	{
		n->neighbor[3] = &chess[i+1][j][f][d][b][u][l][r];
		n->neighbor[3]->pos = waitsize;
		wait[waitsize++] = (data){i + 1, j, f, d, b, u, l, r};
	}
}

int start[2], end[2];
int order[6] = {0, 2, 4, 3, 5, 1};   //更改输入顺序为前左后右上下
node *target = NULL;
int count = 0;
node visited[5000];
unsigned int answer = -1;
bool ended = false;

void solve()
{
	int p, temp;
	for (int i = 0;i <= count;i++)
	{
		p = visited[i].pos;
		for (int j = 0;j < 4;j++)
		{
			if (visited[i].neighbor[j] == NULL || visited[i].neighbor[j]->choosed) 
				continue;
			temp = visited[i].dis + origin[wait[p].number[j]];
			if (temp < visited[i].neighbor[j]->dis)
				visited[i].neighbor[j]->dis = temp;
			if (visited[i].neighbor[j]->dis < answer)
			{
				answer = visited[i].neighbor[j]->dis;
				target = visited[i].neighbor[j];
			}
		}
	}
	p = target->pos;
	target->choosed = true;
	if (wait[p].line == end[0] && wait[p].col == end[1])
	{
		ended = true;
		return;
	}
	setneighbor(wait[p].line, wait[p].col, wait[p].number[0], wait[p].number[1], wait[p].number[2], wait[p].number[3], wait[p].number[4], wait[p].number[5]);
	count++;
	visited[count] = *target;
	answer = -1;
}

int main ()
{
	#ifdef FUCKLYF
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	#endif
	start[0] = getchar() - 'a';
	start[1] = getchar() - '1';
	getchar();
	end[0] = getchar() - 'a';
	end[1] = getchar() - '1';
	for (int i = 0;i < 6;i++)
	{
		scanf("%d", &origin[order[i]]);
		wait[0].number[i] = i;
	}
	wait[0].line = start[0];
	wait[0].col = start[1];
	chess[start[0]][start[1]][0][1][2][3][4][5].pos = 0;
	chess[start[0]][start[1]][0][1][2][3][4][5].choosed = 1;
	chess[start[0]][start[1]][0][1][2][3][4][5].dis = origin[5];
	if (start[0] == end[0] && start[1] == end[1])
	{
		printf("%d", origin[5]);
		return 0;
	}
	setneighbor(start[0], start[1], 0, 1, 2, 3, 4, 5);
	visited[0] = chess[start[0]][start[1]][0][1][2][3][4][5];
	while (!ended)
		solve();
	printf("%u", answer);
	return 0;
}
