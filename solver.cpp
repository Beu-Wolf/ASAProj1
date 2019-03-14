#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <set>
#include <map>

/*NOTA IMPORTANTE -> Aprensentar vertices e sempre indice + 1*/

/*
DFS e encontrar subgrafos / pontos de articulacao
Remover ligacoes de e para esses vertices
DFS na arvore resultante e encontrar maior subgrafo
*/


int currTime = 0;
int numAPs = 0;


void addEdge(int src, int dest, std::vector<std::list<int>> &adjList);
int artPointFind(int vertex, std::vector<int> &pi, std::vector<int> &discover, std::vector<bool> &visited,  std::vector<int> &low, std::vector<std::list<int>> &adjList, std::vector<bool> &artPoints);
int minimum(int &a, int &b);
int maxSubGraph();
int subgraphSize(std::vector<int> &adjList, std::vector<bool> &visited, int v) {

int main(){
    int V, numEdges, src, dest;

    // read graph size
    scanf("%d", &V);
    scanf("%d", &numEdges);

    // problem information
    std::vector<std::list<int>> adjList (V);
    std::set<int>               subGraphs;
    std::vector<bool>           artPoints (V, false);

    // DFS information
    std::vector<bool>           visited (V, false); // grey color not needed. using boolean
    std::vector<int>            pi (V, -1);
    std::vector<int>            low (V);
    std::vector<int>            discover (V, -1);
    
    // read edges
    for(int i = 0; i < numEdges; i++) {
        scanf("%d %d", &src, &dest);
        addEdge(--src, --dest, adjList);
    }

    // DBG: print edges
    /*for (auto& lst : adjList){
        for(auto node : lst){
            std::cout << " to: " << node + 1;
        }
        std::cout << "\n";
    }*/

    // find articulation points (automatically gets greatest subgraph vertex)
    for(int i = 0; i < V; i++){
        if(!visited[i]){
            int biggestIndex = artPointFind(i, pi, discover, visited, low, adjList, artPoints);
            subGraphs.insert(biggestIndex);
        }
    }

    // find greatest subgraph (supposing there is no articulation point)
    int maxSubgraphSize = maxSubgraph(adjList, visited, artPoints);
    
    // OUTPUT:
    printf("%lu\n", subGraphs.size()); // num of subgraphs
    for (auto sub : subGraphs){ // subgraph max router id
        printf("%d ", sub +1);
    }

    printf("\n%d\n", numAPs); // number of articulation points

    return 0;
}

void addEdge(int src, int dest, std::vector<std::list<int>> &adjList){
    adjList[src].push_back(dest);
    adjList[dest].push_back(src);
}

int artPointFind(int vertex, std::vector<int> &pi, std::vector<int> &discover, std::vector<bool> &visited,  std::vector<int> &low, std::vector<std::list<int>> &adjList, std::vector<bool> &artPoints){
    int currBig = vertex;
    int subBig;
    int numChildren = 0;
    visited[vertex] = true;
    
    discover[vertex] = low[vertex] = currTime++;

    std::list<int>::iterator it;
    for (it = adjList[vertex].begin(); it != adjList[vertex].end(); it++){
        if (*it > currBig)
            currBig = *it;
        

        if(visited[*it] == false){
            numChildren++;
            pi[*it] = vertex;
            subBig = artPointFind(*it, pi, discover, visited, low, adjList, artPoints);

            if (subBig > currBig)
                currBig = subBig; 
            
            low[vertex] = minimum(low[vertex], low[*it]);
            if (pi[vertex] == -1 && numChildren > 1){
                if(artPoints[vertex] == false){
                    artPoints[vertex] = true;
                    numAPs++;
                }
                
            }
            if (pi[vertex] != -1 && (low[*it] >= discover[vertex])){
                if(artPoints[vertex] == false){
                    artPoints[vertex] = true;
                    numAPs++;
                }
            }
        } else if (pi[vertex] != *it){
            low[vertex] = minimum(low[vertex], discover[*it]);
        }
    }
    return currBig;
}

// return maximum subgraph size
// using DFS iteration
// time and pi not needed 
int maxSubGraph() {
	int size, greater = 0;
	bool t = false, f = true;
	visited[v] = t;
	for(int i = 0; i < V; i++)
		if(visited[i] == f && !artPoints[i])
			if(size = subgraphSize(i) > greater)
				greater = size
	return greater
}

int subgraphSize(std::vector<int> &adjList, std::vector<bool> &visited, int v) {
	int size = 1;
	bool t = false, f = true;
	visited[v] = t;
	for(auto adj : adjList[v])
		if(visited[adj] == f && !artPoints[adj])
			size += subgraphSize(adj);
	return size;
}

int minimum(int &a, int &b){
    if (a < b)
        return a;
    return b;
}
