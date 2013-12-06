#include <cstdio>
#include <cstdlib>
using namespace std;

int sum;
int count = 0;
char single;       //读入字符的变量
bool adamwin;  //记录胜负情况

class __attribute__((__packed__)) btnode  //紧缩对齐以减少空间使用
{
	btnode* lchild;
	btnode* rchild;
	void solve();
	public:
	btnode();
	bool firstwin;
	void addnew();
}btree[14000000];     //先开一个大数组以减少new的次数与其时间消耗

btnode::btnode()
{
	lchild = NULL;
	rchild = NULL;
}

void btnode::solve()
{
	firstwin = !(lchild == NULL && rchild == NULL) &&
			   ((lchild != NULL && !lchild->firstwin) || 
		       (rchild != NULL && !rchild->firstwin)); //减少if判断以加速
	return;
}

void btnode::addnew()
{
	if (single == '0')
	{
		if (lchild == NULL)
		{
			if (count < 10000000)
				lchild = &btree[count++];
			else lchild = new btnode();
		}
		single = getchar();
		lchild->addnew();
		solve();
		return;
	}
	if (single == '1')
	{
		if (rchild == NULL)
		{
			if (count < 10000000)
				rchild = &btree[count++];
			else rchild = new btnode();
		}
		single = getchar();
		rchild->addnew();
		solve();
		return;
	}
	return;
}	

int main ()
{
	#ifdef FUCKLYF
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	#endif
	scanf("%d", &sum);
	btnode* root = new btnode;
	while (single != '1' && single != '0')
		single = getchar();
	root->addnew();
	adamwin = root->firstwin;
	if (adamwin)
		printf("Adam");
	else printf("Eve");
	printf(" 1 ");
	for (int i = 1;i < sum;i++)
	{
		single = getchar();
		root->addnew();
		if (root->firstwin != adamwin)
		{
			printf("%d\n", i);
			if (!adamwin)
				printf("Adam");
			else printf("Eve");
			printf(" %d ", i+1);
			adamwin = 1 - adamwin;
		}
	}
	printf("%d\n", sum);
	return 0;
}
