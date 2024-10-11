#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define max_dis 100000

typedef char vextype[20];

typedef struct {
    int N, E;//N是顶点数，E是边数
    int** matrix;//储存邻接矩阵
    vextype* vertex;//存储节点的名字
} Graph;

Graph createGraph(int n);
int LeastTree(Graph g);
int isConnected(Graph g);


/**
 * 创建一个节点数为n的图
 * @param n 节点个数
 * @return 返回这个图
 */
Graph createGraph(int n) {
    int i, j;
    Graph g;
    g.N = n;
    g.matrix = (int**)malloc(sizeof(int*) * g.N);
    for (i = 0; i < n; i++) {
        g.matrix[i] = (int*)malloc(sizeof(int) * g.N);
    }
    for (i = 0; i < g.N; i++) {
        for (j = 0; j < g.N; j++) {
            g.matrix[i][j] = max_dis;
        }
    }
    for (i = 0; i < g.N; i++) {
        g.matrix[i][i] = 0;
    }
    g.vertex = (vextype*)malloc(sizeof(vextype) * g.N);
    return g;
}
/**
 * 判断图是否连通
 * @param g 图
 * @return 连通返回1，否则返回0
 */
int isConnected(Graph g) {
    int i,j,k,node[g.N],top,temp;
    for (i=0;i<g.N;i++)
        node[i]=-1;
    node[0]=0;
    top=0;
    for (i=0;i<g.N&&node[i]!=-1;i++)
    {
        for (j=0;j<g.N;j++)
        {
            temp=0;
            if (g.matrix[node[i]][j]!=max_dis)
            {
                temp=1;
                for (k=0;k<=top;k++)
                    if (j==node[k])
                    {
                        temp=0;
                        break;
                	}
            }
            if (temp)
            {
                top++;
                node[top]=j;
            }
        }
    }
    if (node[g.N-1]==-1)
        return 0;
    return 1;
}

//返回最小生成树长度的函数
int LeastTree(Graph g)//逻辑出现了大问题,我只能这么说
{
    int i,j,k,node[g.N],top,temp,length,v,result=0;
    for (i=0;i<g.N;i++)
        node[i]=-1;
    node[0]=0;
    top=0;
    for (i=0;i<g.N-1;i++)
    {
        length=max_dis;
        v=-1;
        for (j=0;j<g.N;j++)
        {
            temp=1;
            for (k=0;k<=top;k++)
                if (j==node[k])
                {
                    temp=0;
                    break;
                }
            for (k=0;k<=top;k++)
            {
            	if (node[k]!=j&&temp)
            	{
            		if (g.matrix[node[k]][j]<length)
            		{
            	    	v=j;
            	    	length=g.matrix[node[k]][j];
            		}
				}   
			}
             
        }
		top++;
        node[top]=v;
        result+=length;
    }
    return result;
}


int main() {
    int node_num;
    int edge_num;

    scanf("%d %d", &node_num, &edge_num);

    Graph g = createGraph(node_num);
    for(int i = 0; i < node_num; i++) {
        sprintf(g.vertex[i], "%d", i);
    }

    for (int i = 0; i < edge_num; i++) {
        int start_idx, end_idx, weight;
        scanf("%d %d %d", &start_idx, &end_idx, &weight);
        g.matrix[start_idx][end_idx] = weight;
        g.matrix[end_idx][start_idx] = weight;
    }
    if (isConnected(g)) 
		printf("%d",LeastTree(g));
    return 0;
}