//queue 用front获得队首元素,然后top弹出,才能获得第二个"队首"
//引用做函数参数,需在函数外先对其赋初值,然后函数修改才有效
//vector不是数据类型,所以没有 vector a[10]这样表示10个vector组成数组的方式,只能写作
//vector <T> a[10] 
//遍历vector的所用元素,使用t.begin(),t.end()和迭代器 
//sort(start,end,cmp)cmp{return a<b;}时结果是升序 


#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;


const int maxn=1024;//maxn表示数组的最大边界 
const int Max=999999;//Max表示可能出现的最大数值 
int A[maxn][4];

inline void input(int A[maxn][4], int &len){
	cin>>len;
	for(int i=1;i<=len;i++){
		cin>>A[i][0]>>A[i][1]>>A[i][2];
	}
}


class Set{
	private:
		int S[maxn],len;
	public:
		Set(int l);
		int Find(int n);
		void Union(int a,int b);
		void show();
};
Set::Set(int l){
	for(int i=1;i<=l;i++)
		S[i]=i;
	len=l;
}
int Set::Find(int n){
	return S[n];
}
void Set::Union(int a,int b){
	//将跟b同集合的所有元素都并入a集合
	int temp=S[b];
	for(int i=1;i<=len;i++){
		if(S[i]==temp)
			S[i]=S[a];
	} 
}
void Set::show(){
	for(int i=1;i<=len;i++)
	cout<<S[i]<<' ';
}


class GNode{
	//此为邻接表中的节点 
	public:
		int end,weight;
};
class Node{
	public:
		int color,d,parent;
		Node(){
			//Dijkstra算法中,color=-1表示未确定到源点最短距离的点集
			//,color=0表示已确定的点集,d表示到源点的距离,d=-1表示源
			//点不可达,parent表示单源最短路径的前驱
			//搜索中,color=-1表示当前未知的点,color=0表示当前正在处
			//理的点,colo=1表示处理完成的点 
			color=-1;
			d=-1;
			parent=-1;
		}
};
class Edge{
	public:
		int a,b,w;
		bool select;
};
class Graph{
	private:
		vector <GNode> map[maxn];
		
		Edge ENode[maxn];		
		queue <int> V;
	public:	
		int Matrix[100][100];	
		Node VNode[maxn];
		int Elen,Vlen;
		void setup(int T[maxn][4],int len);
		void setupMatrix(int T[maxn][4],int len);
		void setupENode(int T[maxn][4],int len);
		void Kruskal(int T[maxn][4],int len);
		void BFS();
		void DFS();
		void SubDFS(int i);
		void Dijkstra(int n);
		inline int DijkstraFindAvailableShortest(int n);
		void Floyd();
		void show();	
};
void Graph::Floyd(){
	for(int k=1;k<=Vlen;k++){
		for(int i=1;i<=Vlen;i++)
		for(int j=1;j<=Vlen;j++)
			if(Matrix[i][k]+Matrix[k][j]<Matrix[i][j])
				Matrix[i][j]=Matrix[i][k]+Matrix[k][j]; 
	}
}
void Graph::setupMatrix(int T[maxn][4],int len){
	memset(Matrix,Max,sizeof(int)*10000);
	Elen=len;
	int maxx=-1;
	for(int i=1;i<=len;i++){
		Matrix[T[i][0]][T[i][1]]=T[i][2];
		if(T[i][0]>maxx)maxx=T[i][0];
	}
	Vlen=maxx;
	for(int i=1;i<=Vlen;i++)Matrix[i][i]=0;
}
void Graph::Dijkstra(int n){
	//i表示源点
	for(int i=1;i<=Vlen;i++){
		VNode[i].color=-1;
		VNode[i].d=-1;
		VNode[i].parent=-1;
	}		
	VNode[n].color=0;
	VNode[n].d=0;
	for(vector <GNode>::iterator j=map[n].begin();j<map[n].end();j++)
		VNode[(*j).end].d=(*j).weight;
	int t =DijkstraFindAvailableShortest(n);
 	while(t!=-1){
 		for(vector <GNode>::iterator j=map[t].begin();j<map[t].end();j++){
		 	int point = (*j).end;
		 	if(VNode[point].d<0){
	 			VNode[point].d=VNode[t].d+(*j).weight;
	 			VNode[point].parent=t;
	 		}else if(VNode[point].d>0){
		 		if((VNode[point].d)>(VNode[t].d+(*j).weight)){
		 			VNode[point].d=VNode[t].d+(*j).weight;
		 			VNode[point].parent=t;
		 		}
		 	}	
		 }
		 t=DijkstraFindAvailableShortest(n);
 	}
}
inline int Graph::DijkstraFindAvailableShortest(int n){
	//返回未确定集合中源点最近的可到达的点,没有时返回-1 
	int t=-1,minn=maxn;
	for(int i=1;i<=Vlen;i++){
		if(VNode[i].color==-1&&VNode[i].d>0&&VNode[i].d<minn){
			minn=VNode[i].d;
			t=i;
		}
	}
	if(t!=-1)
		VNode[t].color=0;
	return t;
}
bool cmp(Edge a,Edge b){
	return a.w<b.w;
}
void Graph::setupENode(int T[maxn][4],int len){
	Elen=len;
	int maxx=-1;
	for(int i=1;i<=len;i++){
		if(T[i][0]>maxx)maxx=T[i][0];
		ENode[i].a=T[i][0];
		ENode[i].b=T[i][1];
		ENode[i].w=T[i][2];
		ENode[i].select=false;
	}
	Vlen=maxx;
}
void Graph::Kruskal(int T[maxn][4],int len){
	setupENode(T,len);
	int k=0;
	sort(ENode+1,ENode+len+1,cmp);
	Set *tem=new Set(Vlen); 
	for(int i=1;i<=Elen;i++){
		if(k==(Vlen-1))return;
		int x = tem->Find(ENode[i].a);
		int y = tem->Find(ENode[i].b);
		if(x!=y){
			tem->Union(x,y);
			k++;
			ENode[i].select=true;
		}
	}
}
void Graph::setup(int T[maxn][4],int len){
	Elen=len;
	int maxx=-1;
	for(int i=1;i<=len;i++){
		int start = T[i][0];
		if(start>maxx)maxx=start;
		GNode e;
		e.end=T[i][1];
		e.weight=T[i][2];
		map[start].push_back(e);
	}
	Vlen=maxx;
}
void Graph::BFS(){
	for(int i=1;i<=Vlen;i++)VNode[i].color=-1;
	V.push(1);
	while(V.size()!=0){
		int i = V.front();
		V.pop();
		cout<<i<<" ";
		for(vector <GNode>::iterator j=map[i].begin();j<map[i].end();j++){
			int temp = (*j).end;
			if(VNode[temp].color==-1){
				V.push(temp);
				VNode[temp].color=0;
			}		
		}
		VNode[i].color=1;
	}
}
void Graph::DFS(){
	for(int i=1;i<=Vlen;i++)VNode[i].color=-1;
	for(int i=1;i<=Vlen;i++){
		if(VNode[i].color==-1)
			SubDFS(i);
	}
}
void Graph::SubDFS(int i){
	cout<<i<<" ";
	VNode[i].color=0;
	for(vector <GNode>::iterator j=map[i].begin();j<map[i].end();j++){
		if(VNode[(*j).end].color==-1)
			SubDFS((*j).end);
		VNode[(*j).end].color=1;
	}
}
void Graph::show(){
	for(int i=1;i<=Vlen;i++){
		cout<<map[i].size()<<endl;
		for(vector <GNode>::iterator j=map[i].begin();j<map[i].end();j++){
			GNode p=*j;
			cout<<p.end<<" "<<p.weight<<" ";
		}
		cout<<endl;	
	}
}


int main(){	
	int len=0;
	input(A,len);
	Graph T;
	T.setupMatrix(A,len);
	T.Floyd();
	for(int i=1;i<=T.Vlen;i++){
		for(int j=1;j<=T.Vlen;j++)
		cout<<T.Matrix[i][j]<<" ";
		cout<<endl;
	}
	
	return 0;
}