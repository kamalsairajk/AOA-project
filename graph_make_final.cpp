#include "graph.h"
using namespace std;

int getYear (string s)
{
    return stoi(s.substr (0,4));
}

int getMonth (string s)     
{
    return stoi(s.substr (5,7));
}

/*
   After reading data from all 4 files, we filter out 1 star customer reviews which have been given in date range of 
   July-Dec, 2005. Customers who have given between 10-20 such ratings are connected to each other, another giving 20-40 
   are connected to each other, and all above 40 are connected to each other. Graph is created with this adjacency criteria
   and connected component size calculated. Peak memory and time has been calculated for both operations and output of connected
   component size written to file
*/ 
int main()
{
    int movieid, customerid, rating, counter = 0, i = 0;
    string review_date, line;
    unordered_map<int, int> customer_ratings;
    unordered_map<int, int> customer_mapping;
    char delimiter = ',';
    vector<string> filelist = {"D:\\AOA\\ratings_data_1.txt","D:\\AOA\\ratings_data_2.txt"
    ,"D:\\AOA\\ratings_data_3.txt","D:\\AOA\\ratings_data_4.txt "};
    for (string k: filelist){
        // File pointer 
        ifstream fin(k, ios::in);
        if (fin.fail())
        {
            return 0;
        }
        while (getline(fin, line)) {
            if (line[line.length() - 1] == ':')
            {
                movieid = stoi(line.substr(0, line.length() - 1));
            }
            else {
                size_t find = line.find(delimiter);
                customerid = stoi(line.substr(0, find));
                rating = stoi(line.substr(find + 1, line.find(delimiter, find + 1)));
                find = line.find(delimiter,find+1);
                review_date = line.substr(find+1);

                //checks for 1 star rating in July-Dec2005 reviews
                if ((rating==1) && (getYear(review_date)==2005) && (getMonth(review_date)>6) && (getMonth(review_date)<=12)) {
                    if (customer_ratings.find(customerid) == customer_ratings.end())
                    {
                        customer_mapping.insert({ customerid,counter });
                        counter++; // counter to keep track of unique customers and assign them node values
                        customer_ratings.insert({ customerid,1});
                    }
                    else {
                        //increasing the review count of customer
                        customer_ratings[customerid]+=1;
                    }
                }
            }
        }

        fin.close();
    }
    clock_t time;
    time = clock();
    PROCESS_MEMORY_COUNTERS info;
    Graph g(customer_ratings.size());
    list<int>customer_subset1,customer_subset2,customer_subset3;
    for (auto i : customer_ratings)
    {
        //Adding customers to different subsets depending on their number of reviews.
        int reviews = i.second;
        if (reviews>10 && reviews<=20)
            customer_subset1.push_back(customer_mapping[i.first]);
        else if (reviews>20 && reviews<40)
            customer_subset2.push_back(customer_mapping[i.first]);
        else if (reviews>40)
            customer_subset3.push_back (customer_mapping[i.first]);
    }
    customer_ratings.clear();

    //Creating edge between every two customers in a subset.
    for (auto i = customer_subset1.begin(); i != customer_subset1.end(); i++) {
        for (auto j = next(customer_subset1.begin()); j != customer_subset1.end(); j++)
        {
            g.addEdge(*i, *j);
        }
    }
    for (auto i = customer_subset2.begin(); i != customer_subset2.end(); i++) {
        for (auto j = next(customer_subset2.begin()); j != customer_subset2.end(); j++)
        {
            g.addEdge(*i, *j);
        }
    }
    for (auto i = customer_subset3.begin(); i != customer_subset3.end(); i++) {
        for (auto j = next(customer_subset3.begin()); j != customer_subset3.end(); j++)
        {
            g.addEdge(*i, *j);
        }
    }
    time = clock() - time;
    GetProcessMemoryInfo (GetCurrentProcess(),&info,sizeof(info));

    cout<<"Peak memory for graph generation : "<<(size_t)info.PeakWorkingSetSize <<endl;
    cout << "Time taken for graph generation : " << ((float)time / CLOCKS_PER_SEC) * 1000 <<endl;

    customer_subset1.clear();
    customer_subset2.clear();
    customer_subset3.clear();
    customer_mapping.clear();

    time = clock();
    PROCESS_MEMORY_COUNTERS info1;

    list <list<int>>conn_comp = g.connected_components ();

    time = clock() - time;
    GetProcessMemoryInfo (GetCurrentProcess(),&info1,sizeof(info1));

    cout<<"Peak memory for getting connected components : "<<(size_t)info1.PeakWorkingSetSize <<endl;
    cout << "Time taken for getting connected components : " << ((float)time / CLOCKS_PER_SEC) * 1000<<endl;

    //Writing the length of each connected component to a file
    ofstream fout("D:\\AOA\\connectedcomp.txt", ios::out);

    fout << "The following is the list of connected components:" << endl;
    int total_size = 0;
    for (auto i : conn_comp) {
        fout << i.size();
        total_size+=i.size();
        fout << endl;
    }
    fout<<"Total size:" << total_size;

    fout.close();
    
    return 0;
}
