#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
using namespace std;

char s[100000];
char temp;
const char* sign = "Node\0";
const char* end = "/Node>\0";
const char* list = ",\"SonList\":[";
const char* name = "{\"Name\":";
bool haveson[10000000];
int count;
int deepest;

void move()
{
	count++;
	if (!haveson[count])
		haveson[count] = true;
	else printf(",");
	if (count > deepest)
		deepest = count;
}

bool wgg(char* primal)
{
	int i = 0, j = 0;
	*s = 0;
	while (1)
	{
		if (primal[i] == '\"')
		{
			s[j] = primal[i];
			i++;
			while (primal[i] != '\"')
			{
				j++;
				s[j] = primal[i];
				i++;
			}
			j++;
			s[j] = primal[i];
			i++;
			j++;
			s[j] = '\0';
			if (primal[i] == '/')
				return true;
			else return false;
		}
		else i++;
	}
}

int findword()
{
	while (temp != '<')
	{
		temp = getchar();
		if (temp < 0)
			return -3;
	}
	if (scanf("%s", &s) < 0)
		return -2;
	if (strcmp(s, sign) == 0)
	{
		scanf("%s", &s);
		if (wgg(s))
			return 2;
		else return 1;
	}
	if (strcmp(s, end) == 0)
		return 0;
	if (s[0] == '/')
	{
		printf("}");
		return -1;
	}
	printf("{\"");
	for (int i = 0;i < strlen(s);i++)
		if (s[i] != '>')
			printf("%c", s[i]);
	printf("\":");
	move();
	return 3;
}

int main ()
{
	#ifdef FUCKLYF
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	#endif
	int result = findword();
	while (result >= -1)
	{
		if (result == 0)
		{
			for (int i = count + 1;i <= deepest;i++)
				haveson[i] = false;
			deepest = count;
			count--;
			printf("]}");
		}
		if (result == 1)
		{
			move();
			printf("%s%s%s", name, s, list);
		}
		if (result == 2)
		{
			move();
			printf("%s%s}", name, s);
			count--;
		}
		temp = getchar();
		result = findword();
	}
	return 0;
}
