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

int main(){

    int V, numEdges, src, dest;


    scanf("%d", &V);
    scanf("%d", &numEdges);

    //vectors needed for DFS / tarjan
    std::vector<int> pi (V, -1);
    std::vector<int> discover (V, -1);
    std::vector<bool> visited (V, false);
    std::vector<int> low (V);
    std::vector<std::list<int>> adjList (V);
    std::set<int> subGraphs;
    std::vector<bool> artPoints (V, false);
    
    
    // fransformar para for(int i = 0; i < numEdges; i++)?
    int i = 0;
    while (i < numEdges){ // code to add new edges
        scanf("%d %d", &src, &dest);
        src--;
        dest--;
        
        addEdge(src, dest, adjList);
        i++;
    }


    



    /*for (auto& lst : adjList){
        for(auto node : lst){
            std::cout << " to: " << node + 1;
        }
        std::cout << "\n";
    }*/

    for(int i = 0; i < V; i++){
        if(visited[i] == false){
            int biggestIndex = artPointFind(i, pi, discover, visited, low, adjList, artPoints);
            subGraphs.insert(biggestIndex);
        }

    }

    printf("%lu\n", subGraphs.size());
    for (auto sub : subGraphs){
        printf("%d ", sub +1);
    }

    printf("\n%d\n",numAPs);

    // delete egdes TO and From
    // nao esta ja feito quando adicionamos ao vetor de aps?

    //DFS in new graph

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




int minimum(int &a, int &b){
    if (a < b)
        return a;
    return b;
}
