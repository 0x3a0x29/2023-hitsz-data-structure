#include <stdio.h>
#include <stdlib.h>

typedef struct student{
	int Code;
	int Score[5];
} Student;

typedef struct rank{
	int Rank;
	int Code;
}Rank;

Student Students[50];
Rank 	Ranks[50];

int 	Priority[5];
double 	Weight[5];
int 	N;

void Swap(int i)
{
	int j;
	int temp;
	temp=Students[i].Code;
	Students[i].Code=Students[i+1].Code;
	Students[i+1].Code=temp;
	for (j=0;j<5;j++)
	{
		temp=Students[i].Score[j];
		Students[i].Score[j]=Students[i+1].Score[j];
		Students[i+1].Score[j]=temp;
	}
}

void CalcAndWriteRanks(){
	double scores[N];
	double temp1;
	int i,j,k,temp,pri[5];
	for (i=0;i<N;i++) scores[i]=0;
	for (i=0;i<5;i++)
		for (j=0;j<5;j++)
			if (Priority[i]==j+1)
			{
				pri[j]=i;
				break;
			}
	for (i=0;i<N;i++)
		for (j=0;j<5;j++)
			scores[i]+=Students[i].Score[j]*Weight[j];
	/*
	for (i=N-1;i>0;i--)//code
		for (j=0;j<i;j++)
			if (Students[j].Code>Students[j+1].Code)
				Swap(j);
	*/
	for (i=N-1;i>0;i--)
		for (j=0;j<i;j++)
		{
			if (scores[j]<scores[j+1])//weight
			{
				temp1=scores[j];
				scores[j]=scores[j+1];
				scores[j+1]=temp1;
				Swap(j);
			}
		}
	for (i=N-1;i>0;i--)
		for (j=0;j<i;j++)
		{
			if (scores[j]==scores[j+1])//pri
			{
				for (k=0;k<5;k++)
				{
					if (Students[j].Score[pri[k]]<Students[j+1].Score[pri[k]])
					{
						Swap(j);
						break;
					}
				}
			}
		}
	temp=0;
	for (i=0;i<N;i++)
	{
		k=1;
		if (i!=0&&scores[i-1]==scores[i])
		{
			for (j=0;j<5;j++)
			{
				if (Students[i-1].Score[pri[j]]>Students[i].Score[pri[j]])
				{
					k=2;
					break;
				}
			}
			if(k==1) k=0;
		}
		if (k)
		{
			temp=i;
			Ranks[i].Code=Students[i].Code;
		}
		else
		{
			for (j=i;j>=temp;j--)
				for (k=temp;k<j;k++)
					if (Students[k].Code>Students[k+1].Code)
						Swap(k);
			for (j=temp;j<=i;j++)
				Ranks[j].Code=Students[j].Code;
		}
		Ranks[i].Rank=temp+1;
	}
}

void PrintRanks(){
	for (int loop = 0; loop < N; loop++){
		printf("%d %d\n", Ranks[loop].Rank, Ranks[loop].Code);
	}
}

int main(int argc, char *argv[]) {
	// Input part, do not modify
	scanf("%d", &N);
	for (int loop = 0; loop < 5; loop++){
		scanf("%d", Priority + loop);
	}
	for (int loop = 0; loop < 5; loop++){
		scanf("%lf", Weight + loop);
	}
	
	for (int loop = 0; loop < N; loop++){
		scanf("%d", &Students[loop].Code);
		for (int j = 0; j < 5; j++){
			scanf("%d", Students[loop].Score + j);
		}
	}
	// Main process part
	CalcAndWriteRanks();
	// Output part, do not modify
	PrintRanks();
	return 0;
}