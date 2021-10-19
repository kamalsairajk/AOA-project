#include <windows.h>
#include <psapi.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <queue>
#include <stack>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Graph {

        vector<vector<int>> adjList;
        int nodes;
    public:

        Graph (int nodes){
            
            this->nodes = nodes;
            adjList.resize (nodes);
        } 
        inline int  getNodes (){

            return nodes;
        }
        void addEdge (int ver1,int ver2);
        void one_cycle ();
        int  detectCycle (int src_vertex,vector<bool>& visited,int parent_vertex);
        void DFS (int start_vertex,vector<bool>&visited, list<int>&conncomp);
        list<list<int>> connected_components ();
        vector<vector<int>> shortest_paths (int src);
};

Graph generateNcycle (int nodes);
Graph generateCompleteGraph (int nodes);
Graph generateHeap (int nodes);
Graph generateTruncHeap (int nodes);
Graph generateEmptyGraph (int nodes);