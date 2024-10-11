
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
void nodeDegree(Graph g, int* node_degree);
double clusteringCoefficient(Graph g);


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
 * 计算每个点的度
 * @param g 图
 * @param node_degree 将每个点的度写到这个数组中
 */
void nodeDegree(Graph g, int *node_degree) {
    int i,j,temp;
    for (i=0;i<g.N;i++)
    {
        temp=-1;
        for (j=0;j<g.N;j++)
            if (g.matrix[i][j]!=max_dis)
                temp++;
        node_degree[i]=temp;
    }
}

/**
 * 计算图的聚类系数
 * @param g 图
 * @return 返回聚类系数
 */
double clusteringCoefficient(Graph g) {
    int i,j,k,top[g.N],neighbour[g.N][g.N];
    double clustering[g.N],result=0;
    for (i=0;i<g.N;i++)
    {
        top[i]=-1;
        for (j=0;j<g.N;j++)
        {
            if (i!=j&&g.matrix[i][j]!=max_dis)
            {
                top[i]++;
                neighbour[i][top[i]]=j;
            }
        }
    }
    for (i=0;i<g.N;i++)
    {
        clustering[i]=0;
        for (j=0;j<=top[i];j++)
            for (k=j+1;k<=top[i];k++)
                if (g.matrix[neighbour[i][j]][neighbour[i][k]]!=max_dis)
                    clustering[i]++;
        if (top[i]>0)
            clustering[i]/=(top[i]+1)*top[i]/2;
    }
    for (i=0;i<g.N;i++)
        result+=(double)clustering[i]/g.N;
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

    int *degree = (int *)malloc(sizeof(int) * g.N);
    nodeDegree(g, degree);
    printf("degree distribution:\n");
    for(int i=0; i<g.N; i++)
    {
        printf("node%s:%d,", g.vertex[i], degree[i]);
    }
    printf("\n");
    double c = clusteringCoefficient(g);
    printf("clustering coefficient:%f\n", c);

    return 0;
}