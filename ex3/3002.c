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
int isConnected(Graph g);
int Diameter(Graph g);
int Radius(Graph g);
int dijkstra(Graph g, int start, int end, int* path);
void printPath(int d, int* diameter_path, Graph g);

void DFS(Graph g, int i, int* visited, int* count);
int DFSTraverse(Graph g);
void floyd(Graph g, int** dist, int** path);


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
 * 根据距离d和路径数组path输出路径，这样就不需要路径的节点数也能正确输出路径
 * @param d 路径长度
 * @param diameter_path 储存路径的数组
 * @param g 图
 */
void printPath(int d, int *diameter_path, Graph g)
{
    int k = 0;
    int path_length = 0;
    printf("Path: ");
    do {
        printf("%s->", g.vertex[diameter_path[k]]);
        path_length += g.matrix[diameter_path[k]][diameter_path[k + 1]];
        k++;
    } while (path_length < d);
    printf("%s\n", g.vertex[diameter_path[k]]);
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


/**
 * 使用dijkstra算法计算单源最短路径
 * @param g 图
 * @param start 起点
 * @param end 终点
 * @param path 从start到end的路径, [start,...,end]
 * @return 路径长度
 */
int dijkstra(Graph g, int start, int end, int *path)
{
    int D[g.N],S[g.N],P[g.N],i,j,k,v,temp,length=0;
    for (i=0;i<g.N;i++)
    {
        S[i]=0;
        D[i]=g.matrix[start][i];
        if (g.matrix[start][i]!=max_dis)
            P[i]=start;
        else
            P[i]=-1;
    }
    S[start]=1;
    for (i=0;i<g.N;i++)
    {
        if (i==start) i++;
        temp=max_dis;
        v=-1;
        for (j=0;j<g.N;j++)
            if (j!=start)    
                if (!S[j]&&D[j]<temp) 
                {
                    temp=D[j];
                    v=j;
                }
        S[v]=1;
        for (j=0;j<g.N;j++)
            if (j!=start)
                if (!S[j]&&D[v]+g.matrix[v][j]<D[j])
                {
                    D[j]=D[v]+g.matrix[v][j];
                    P[j]=v;
                }
    }
    temp=end;
    while (temp!=start)
    {
        temp=P[temp];
        length++;
    }
    for (temp=end,i=0;temp!=start;i++)
    {
        path[length-i]=temp;
        temp=P[temp]; 
    }
    path[0]=start;
    return D[end];    
}

/**
 * 计算图的直径。提示：Floyd算法
 * @param g 图
 * @return 直径的长度
 */
int Diameter(Graph g) {
    int i,j,k,distance[g.N][g.N],eccentricity[g.N],result=-max_dis;
    for (i=0;i<g.N;i++)
        for (j=0;j<g.N;j++)
            distance[i][j]=g.matrix[i][j];
    for (k=0;k<g.N;k++)
        for (i=0;i<g.N;i++)
            for (j=0;j<g.N;j++)
                if (distance[i][k]+distance[k][j]<distance[i][j])
                    distance[i][j]=distance[i][k]+distance[k][j];
    for (i=0;i<g.N;i++)
    {
        eccentricity[i]=-max_dis;
        for (j=0;j<g.N;j++)
            if (distance[i][j]>eccentricity[i]&&distance[i][j]!=max_dis)
                eccentricity[i]=distance[i][j];
    }
    for (i=0;i<g.N;i++)
        if (eccentricity[i]>result)
            result=eccentricity[i];
    return result;
}


/**
 * 计算图的半径
 * @param g 图
 * @return 半径长度
 */
int Radius(Graph g) {
    int i,j,k,distance[g.N][g.N],eccentricity[g.N],result=max_dis;
    for (i=0;i<g.N;i++)
        for (j=0;j<g.N;j++)
            distance[i][j]=g.matrix[i][j];
    for (k=0;k<g.N;k++)
        for (i=0;i<g.N;i++)
            for (j=0;j<g.N;j++)
                if (distance[i][k]+distance[k][j]<distance[i][j])
                    distance[i][j]=distance[i][k]+distance[k][j];
    for (i=0;i<g.N;i++)
    {
        eccentricity[i]=-max_dis;
        for (j=0;j<g.N;j++)
            if (distance[i][j]>eccentricity[i]&&distance[i][j]!=max_dis)
                eccentricity[i]=distance[i][j];
    }
    for (i=0;i<g.N;i++)
        if (eccentricity[i]<result)
            result=eccentricity[i];
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
    printf("connected: %d\n", isConnected(g));

    if (isConnected(g))
    {
        int* short_path = (int*)malloc(sizeof(int) * g.N);
        int dis = dijkstra(g, 1, 3, short_path);
        printf("the minimum fare between 1 and 3: %d\n", dis);
        printPath(dis, short_path, g);
        free(short_path);
        int d = Diameter(g);
        printf("diameter:%d\n", d);

        int r = Radius(g);
        printf("radius:%d\n", r);
    }

    return 0;
}