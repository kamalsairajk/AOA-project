#include"graph.h"
#define INF 0x3f3f3f3f 
  
// iPair ==>  Integer Pair 
typedef pair<int, int> iPair; 

/*Adds two vertices sharing an edge to each other's
  adjacency list*/
void Graph::addEdge (int ver1, int ver2)
{
    adjList[ver1].push_back(ver2);
    adjList[ver2].push_back(ver1);
} 

/*input : source vertex
        : boolean vector containing information regarding which nodes have been visited.
        : A list storing the nodes of a particular connected component.
Recursive function which traverses along the graph in depth first manner from a given source vertex.
*/
void Graph::DFS (int src_vertex,vector<bool>&visited, list<int>&conncomp)
{          
    visited[src_vertex] = true;
    conncomp.push_back(src_vertex);
    for (auto i : adjList[src_vertex]) {
        if (!visited[i]) {

            DFS(i, visited,conncomp);
        }
    }
}

/*Return value : list of connected components, each containing a list of nodes in the component.
  Calls DFS from a node if it has not been visited. DFS call is made, once for every connected component.
*/
list<list<int>> Graph::connected_components (){

    list<list<int>>connectedcomp;
    vector<bool>visited(nodes, false);
    for (int i = 0; i < nodes; i++)
    {
        if (!visited[i]) {
            //list to store the nodes of a particular connected component
            list<int>component;  
            DFS(i, visited,component);
            connectedcomp.push_back(component);
        }
    }
    return connectedcomp;
}

/* 
   Input: source vertex
          boolean vector containing information regarding which nodes have been visited.
          parent vertex which is used to detect cycle.
   Recursive call which uses backtracking to print the cycle path,
   and in case cycle is found on reaching a particular vertex or in its child, it's value is returned,
   else -1 is returned, indicating no cycle. If a cycle is found, the function returns immediately.*/
   int Graph::detectCycle (int src_vertex,vector<bool>& visited,int parent_vertex)
{
    visited[src_vertex]= true;
    for (auto i:adjList[src_vertex]) 
    {
        if(!visited[i]) {
            int val = detectCycle (i,visited,src_vertex);
            if (val != -1) {
                cout<<i<<" ";
                if (val == i){
                    
                    return -1;
                }
            }
            return val;
        }
        else {
            // if a node is already visited and is not its parent vertex, then cycle is detected.
            if(i!=parent_vertex){

                cout<<i<<" ";
                return i;
            } 
        }
    } 
    return -1;
}

/*Walks each connected component to detect cycles */
void Graph::one_cycle ()
{
    vector<bool>visited(nodes,false);
    for(int i=0;i<nodes;i++)
    {
        fill(visited.begin(),visited.end(),false);
        int val;
        if(!visited[i]){

            int val = detectCycle (i,visited,i);
            if (val!=-1) {

                cout<<i<<" ";
                break;
            }
        }
    }
} 

/*Input : source vertex : Based on distance from this, all other distances will be calculated.
  Returns: vector of vectors containing the shortest paths from every node to every other node.
  This function calculates the shortest paths between every two nodes, by making use of priority 
  queue */
vector<vector<int>> Graph::shortest_paths (int src) 
{ 
    priority_queue< iPair, vector <iPair> , greater<iPair> > pq; 
    vector<int> dist(nodes, INF); 
    vector<vector<int>> sp;
    sp.resize (nodes);
    pq.push(make_pair(0, src)); 
    dist[src] = 0; 
    while (!pq.empty()) 
    { 
        int u = pq.top().second; 
        pq.pop(); 
        for (auto x : adjList[u]) 
        {             
            int v = x; 
            if (dist[v] > dist[u] + 1) 
            { 
                dist[v] = dist[u] + 1; 
                pq.push(make_pair(dist[v], v));                 
                sp[v].push_back(u);   
                for (auto k: sp[u]) 
                    sp[v].push_back(k);
            } 
        } 
    }
    for(int i =0 ;i<nodes;i++)
    {
        sp[i].insert(sp[i].begin(),i);
    }
    
    return sp;
}





