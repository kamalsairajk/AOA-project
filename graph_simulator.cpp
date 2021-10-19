#include "graph.h"

Graph generateNcycle (int nodes)
{
    int i;
    Graph g (nodes);
    for (i =0;i< (nodes-1);i++)
    {
        g.addEdge (i,i+1);
    }
    g.addEdge (i,0);
    return g;
}

Graph generateCompleteGraph (int nodes)
{
    Graph g (nodes);
    for (int i=0;i< nodes;i++)
        for (int j = i+1;j<nodes;j++)
            g.addEdge (i,j); 
    return g;
}

Graph generateEmptyGraph (int nodes)
{
    Graph g(nodes);
    return g;
}

Graph generateHeap (int nodes)
{
    Graph g(nodes);
    int i;
    if(nodes%2 == 0){
        for (i=0; i< (nodes/2-1);i++)
        {
           g.addEdge (i,2*i+1);
           g.addEdge (i,2*i+2);
        }
        g.addEdge (i,2*i+1);
    } else {
        for (i=0; i< nodes/2;i++)
        {
           g.addEdge (i,2*i+1);
           g.addEdge (i,2*i+2);
        }
    }
    return g;
}

Graph generateTruncHeap (int nodes)
{

    int m;
    Graph g (nodes);
    cout<<"Enter m value\n";
    cin>>m;
    if (m <= nodes)
    {
        int i;
        for (i=m;i<(nodes-1)/2;i++)
        {
            g.addEdge (i,2*i+1);
            g.addEdge (i,2*i+2);
        }
        if (2*m+2 == nodes)
        {
            g.addEdge (i,2*i+1);
        }
        
    } else {

        cout<<"Invalid m value : m value greater than total number of graph vertices\n";
    }
    return g;
}