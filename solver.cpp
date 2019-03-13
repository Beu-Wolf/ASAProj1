#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <set>

/*NOTA IMPORTANTE -> Aprensentar vertices e sempre indice + 1*/

/*
DFS e encontrar subgrafos / pontos de articulacao
Remover ligacoes de e para esses vertices
DFS na arvore resultante e encontrar maior subgrafo
*/


int Currtime = 0;


void addEdge(int src, int dest, std::vector<std::list<int>> &adjList);
int artPointFind(int vertex, std::vector<int> &pi, std::vector<int> &discover, std::vector<bool> &visited,  std::vector<int> &low, std::vector<std::list<int>> &adjList, std::set<int> &artPoints);
int minimum(int &a, int &b);

int main(){

    int V, numEdges, src, dest;


    std::cin >> V;


    //vectors needed for DFS / tarjan
    std::vector<int> pi (V, -1);
    std::vector<int> discover (V, -1);
    std::vector<bool> visited (V, false);
    std::vector<int> low (V);
    std::vector<std::list<int>> adjList (V);
    std::set<int> subGraphs;
    std::set<int> artPoints;

    

    std::cin >> numEdges;

    int i = 0;
    while ( i < numEdges){ // code to add new edges
        std::cin >> src >> dest;
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

    std::cout << subGraphs.size() << "\n";
    for (auto sub : subGraphs){
        std::cout << sub + 1 << " ";
    }

    std::cout << "\n" <<artPoints.size() << "\n";

    //delete egdes TO and From

    //DFS in new graph

    return 0;
}

void addEdge(int src, int dest, std::vector<std::list<int>> &adjList){
    adjList[src].push_back(dest);
    adjList[dest].push_back(src);
}

int artPointFind(int vertex, std::vector<int> &pi, std::vector<int> &discover, std::vector<bool> &visited,  std::vector<int> &low, std::vector<std::list<int>> &adjList, std::set<int> &artPoints){
    int currBig = vertex;
    int subBig;
    int numChildren = 0;
    visited[vertex] = true;
    
    discover[vertex] = low[vertex] = Currtime++;

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
                artPoints.insert(vertex);
            }
            if (pi[vertex] != -1 && (low[*it] >= discover[vertex])){
                artPoints.insert(vertex);
            }
        } else if (pi[vertex] != *it){
            low[vertex] = minimum(low[vertex], discover[*it]);
        }
    }
    return currBig;
}




int minimum(int &a, int &b){
    if ( a < b)
        return a;
    return b;
}