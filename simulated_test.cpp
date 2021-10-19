#include "graph.h"

Graph generateGraph ()
{
    int choice = 0, nodes;
    cout<<"Enter number of nodes\n";
    cin>>nodes;
    cout<<"Enter choice of graph to be generated\n";
    cin>>choice;
    switch (choice)
    {
        case 1: return generateNcycle (nodes); 
        case 2: return generateCompleteGraph (nodes);
        case 3: return generateEmptyGraph (nodes);
        case 4: return generateHeap (nodes); 
        case 5: return generateTruncHeap (nodes);
        default: Graph g(0);return g;
    }
}

int main ()
{
    Graph g = generateGraph ();
    clock_t time;
    time = clock();
    list<list<int>>connected_comp = g.connected_components ();
    time = clock()-time;
    cout<<"\nProcessor time taken for connected components is %f milliseconds:"<<((float)time/CLOCKS_PER_SEC)*1000<<endl;
    ofstream fout1 ("D:\\AOA\\connectedcomp.txt",ios::out);
    fout1<<"The following is the list of connected components:"<<endl;
    for (auto i: connected_comp){
        for (auto j: i)
        {
            fout1<<j<<" ";
        }
        fout1<<endl;
    }
    fout1.close ();

    time = clock();
    g.one_cycle ();
    time = clock()-time;
    cout<<"\nProcessor time taken for detecting cycle is %f milliseconds:"<<((float)time/CLOCKS_PER_SEC)*1000;
    time = clock();
    vector<vector<int>> sp = g.shortest_paths (0);
    time = clock()-time;
    cout<<"\nProcessor time taken for getting shortest paths is %f milliseconds:"<<((float)time/CLOCKS_PER_SEC)*1000;
    ofstream fout2 ("D:\\AOA\\shortestpath.txt",ios::out);
    fout2<<"\nPath:\n"; 
     
    for (int i=0 ;i<sp.size();i++)
    {      
        for (auto j: sp[i]) {

            fout2<<j << " ";      
        }
        fout2<<endl;
    }
    fout2.close();
    
    return 0;
}
