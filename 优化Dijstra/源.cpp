#include <iomanip>
#include <iostream>
#include <stack>
#include <fstream>
#include <queue>
#include <vector>
#define MAX 10
#define INF 65535
typedef char Elem;
using namespace std;
typedef struct {
	int n, e;
	int edge[MAX][MAX];
	Elem vertex[MAX];
} MTGraph;
ifstream input("input.txt");
ofstream output("output.txt", ios::app);
int n, m;
struct node {
	int x, d;
	node() {}
	node(int a, int b) { x = a; d = b; }
	bool operator < (const node & a) const {
		if (d == a.d) return x<a.x;
		else return d > a.d;
	}
};
vector<node> eg[MAX];
int Locate(Elem vertex, MTGraph *G) {
	for (int i = 0; i<G->n; i++) {
		if (G->vertex[i] == vertex) return i;
	}
	return -1;
}
void CreateMTGraph(MTGraph *G) {
	for (int i = 0; i <= n; i++) eg[i].clear();
	input >> G->n >> G->e;
	n = G->n;
	m = G->e;
	output << "无向图的顶点、边个数为:" << setw(5) << G->n << setw(5) << G->e << endl;
	output << "顶点信息：";
	for (int i = 0; i<G->n; i++) {
		input >> G->vertex[i];
		output << setw(5) << G->vertex[i];
	}
	output << endl;
	for (int i = 0; i<G->n; i++) {
		for (int j = 0; j<G->n; j++) {
			G->edge[i][j] = INF;
		}
	}
	Elem head, tail;
	int weight;
	for (int i = 0; i<G->e; i++) {
		input >> head >> tail >> weight;
		output << "第" << i + 1 << "条边：" << head << "<-->" << tail << ":" << weight << endl;
		while (Locate(head, G) == -1 || Locate(tail, G) == -1) {
			input >> head >> tail >> weight;
			output << "边的信息不正确！" << endl;
			output << "第" << i + 1 << "条边：" << head << "<-->" << tail << ":" << weight << endl;
		}
		int k = Locate(head, G), l = Locate(tail, G);
		G->edge[k][l] = G->edge[l][k] = weight;
		eg[k].push_back(node(l, weight));
		eg[l].push_back(node(k, weight));
	}
	output << "*****无向图邻接矩阵已建成！*****" << endl;
}
int dis[MAX];
void Dijkstra(int s){
	for (int i = 0; i <n; i++) dis[i] = INF;
	dis[s] = 0;
	priority_queue<node> q;
	q.push(node(s, dis[s]));
	while (!q.empty()){
		node x = q.top(); q.pop();
		for (int i = 0; i<eg[x.x].size(); i++){
			node y = eg[x.x][i];
			if (dis[y.x]>x.d + y.d)	{
				dis[y.x] = x.d + y.d;
				q.push(node(y.x, dis[y.x]));
			}
		}
	}
}
int main(const int argv,const char** argc){
	MTGraph *G = new MTGraph;
	char choose;
	while (1) {
		cout << "是否开始：";
		cin >> choose;
		if (choose != 'y' && choose != 'Y') break;
		CreateMTGraph(G);
		Dijkstra(0);
		output <<"最短路径为："<< dis[n-3]<<endl;
	}
	system("pause");
	return 0;
}
