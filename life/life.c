#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#define tall 60
#define wide 80
int print(int a[tall][wide],int);
int value(int (*p)[wide], int i, int j);
void randvalue(int(*p)[wide]);//the origenal board
void main(void)
{
	int printcount = 0;
	int a[tall][wide] = { 0 };
	int b[tall][wide];
	int (*p)[wide];
	p = a;
	randvalue(p);
	for (_Bool stop = 0; stop == 0;)
	{
		stop = 1;
		printcount=print(a,printcount);
		for (int i = 0; i < tall; i++)
			for (int j = 0; j < wide; j++)
			{b[i][j] = value(p, i, j);
				if (a[i][j] != b[i][j])//if the state not change than stop
					stop = 0;
			}
		for (int i = 0; i < tall; i++)
			for (int j = 0; j < wide; j++)
				a[i][j] = b[i][j];
		
		usleep(2000);//pause
	}
}
int print(int a[tall][wide],int printcount)
{
	printf("number %d\n",++printcount);
	for (int i = 0; i < tall; i++)
	{
		for (int j = 0; j < wide; j++)
			printf("%2d", a[i][j]);
		printf("\n");
	}
	printf("\n\n\n");
	return printcount;
}
void randvalue(int (*p)[wide])
{
	int count = 0;
        int i = 0, j = 0;
	for (; count < tall * wide / 5;)
	{
		i = rand() % tall;
		j = rand() % wide;
		if (*(*(p+i)+j) == 0)
		{
			*(*(p + i) + j) = 1;
			count++;
		}
	}
}

int value(int (*p)[wide], int i, int j)
{
	int count = 0;
	for (int x = 0; x < 3; x++)//loop-count the neighbor's value
		for (int y = 0; y < 3; y++)
		{
                        if (x == 1 && y == 1)//skip-not count itself
				continue;
			if (i-1 + x >= 0 && j - 1 + y >= 0 && i - 1 + x < tall && y + j - 1 < wide)
				if (*(*(p+i+x-1)+j+y-1)== 1)
					count++;
		}
	if (count == 3)
		return 1;
	if (count == 2 && *(*(p + i) + j) == 1)
		return 1;
	else
		return 0;


}
