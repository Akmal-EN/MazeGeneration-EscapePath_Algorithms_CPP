#include <iostream>
#include <list>
#include <random>
#include<queue>
#include<vector>
using namespace std;
// generate labrynth = get random map (adjacency list)
// generate initial position = get a random number for vertex position
// have length/time for each edge
// generate the exit = get random number for vertex position of exit
// get the shortest path from each initial position to the exit
//Graph
struct LLnod
{
    int value=0;
    LLnod *next=nullptr;
    LLnod(int val) : value(val){};
};
class LL
{

public:
    LLnod *head;
    void insert(int val)
    {
        if (head == nullptr)
        {
            head = new LLnod(val);
        }
        else
        {
            LLnod *crawler = head;
            while (crawler->next != nullptr)
            {
                if (crawler->value == val)
                {
                    return;
                }
                
                crawler = crawler->next;
            }

            if (crawler->value == val)
            {
                return;
            }

            crawler->next = new LLnod(val);
        }
    }
    bool search(int val){
        if (head == nullptr)
        {
            return false;
        }
        else
        {
            LLnod *crawler = head;
            while (crawler != nullptr)
            {
                if (crawler->value == val)
                {
                    return true;
                }

                crawler = crawler->next;
            }
            return false;
        }
    }
};
class Graph
{    int numOfVex = 0;
    int my_exit=0;
    LL *adjList = new LL[numOfVex];
    int *prev=new int[numOfVex];
    //implement speeds
    int **speedmatrix=new int*[numOfVex];
    
public:
    Graph(int vexes):numOfVex(vexes){
        for(int i=0;i<numOfVex;i++){
            speedmatrix[i]=new int[numOfVex];
        }
    };
    ~Graph(){
        for(int i=0;i<numOfVex;i++){
            delete [] speedmatrix[i];
        }
        delete [] speedmatrix;
    }
    bool addEdge(int src, int dest)
    {   if(!(adjList[src].search(dest)))
            adjList[src].insert(dest);
            return false;
    
        return true;
    }
    //generating the maze
    //for each part of the maze
    void create_maze(int from,int to,int n){
        int paths=0,temp=from,prev = from,tofr=to-from,path_length;
        paths=(n/4)+rand()%((int)(n/2));
        for(int i=0;i<paths;i++){
            // cumulative:
            // temp=from+rand()%((int)(tofr));
            temp=rand()%((int)(numOfVex));
            
            path_length=rand()%100;
            while(temp==prev){
                temp=from+rand()%((int)(tofr));
            }
            addEdge(prev,temp);
            addEdge(temp,prev);
            speedmatrix[prev][temp]=path_length;
            speedmatrix[temp][prev]=path_length;
            prev=temp;
        }
        //create connection with bottom, top,left,right
        
    }
    //gen maze
    void generate_maze(int parts){
        int vexpart=(int)(numOfVex/parts);
        for(int i=0;i<parts;i++){
            create_maze((i*vexpart),(i+1)*(vexpart)-1,vexpart);
        }
    }
    //CUMULATIVE create path
    // void create_path(int from,int max){
    //     int edges=0,temp=from,prev=from;
    //     edges=rand()%((int)(numOfVex/10));
    //     for(int j=0;j<edges;j++){
    //         temp=temp+rand()%(6);
    //         while(temp==from ){
    //             temp=rand()%numOfVex;
    //             if(temp-5>=max){
    //                 break;
    //             }
    //         }
    //         if(temp-5>=max){
    //             temp=temp-6;
    //             break;
    //         }
    //         // cout<<"\n";
    //         // addEdge(prev,temp);
    //         // addEdge(temp,prev);
    //         // prev=temp;
    //         // std::cout<<temp<<",";
    //     }addEdge(prev,to);
    //     addEdge(to,prev);
    // };
    //create path
    void create_path(int from,int to,int parts_involved,int edgeratio){
        int edges=0,temp=0,prev=from, vexnum=numOfVex/parts_involved;
        edges=rand()%((int)(numOfVex/edgeratio));
        for(int j=0;j<parts_involved;j++){
            temp=j*(vexnum)+rand()%(vexnum);
            while(prev==temp||temp==from || temp==to){
                temp=j*(vexnum)+rand()%(vexnum);
            }
            // cout<<"\n";
            addEdge(prev,temp);
            addEdge(temp,prev);
            prev=temp;
            // std::cout<<temp<<",";
        }
        addEdge(prev,to);
        addEdge(to,prev);
    };
    void generate_graph(){
        // std::cout<<"\nGenerating the graph:\n";
        int num1=0,num2=0;
        for(int i=0;i<numOfVex;i+=2){
            // num1=rand()%((int)(numOfVex));
            num1=i;
            num2=rand()%((int)(numOfVex));
            // std::cout<<i<<"=";
            int temp,edges=rand()%10,prev=i;
            for(int j=0;j<edges;j++){
                temp=rand()%numOfVex;
                while(temp==i || temp==prev){
                    temp=rand()%numOfVex;
            // std::cout<<temp<<",";
                }
                // cout<<"\n";
                addEdge(i,temp);
                addEdge(temp,i);
                // std::cout<<temp<<",";
                temp=prev;
            }
            // std::cout<<"\n";
            // create_path(num1,num2,10,10);
        }
        std::cout<<"FINISHED GENERATING THE GRAPH\n";
    }

    void print_graph(){
    //    std::cout<<"Printing the graph:\n";
        LLnod *crawler;
        for (int i = 0; i < numOfVex; i++)
        {
            crawler=adjList[i].head;
            std::cout<<i<<"=";
            while (crawler != nullptr)
            {
                cout << crawler->value << ",";
                crawler = crawler->next;
            }
            cout << "\n";
        }
    }
	//getting random position for an exit
    int set_exit(int val){
        my_exit=val;
        return my_exit;
    }
    int rand_exit(){
        my_exit=rand()%numOfVex;
        return my_exit;
    }
    //getting random position for a wizard
	int set_wizard(){
        int temp=rand()%numOfVex;
        while(temp==my_exit){
            temp=rand()%numOfVex;
        }
        return temp;
    }
    //random graph generation
    //visiting all nodes of a graph
    //avoiding cycles
    bool search_vec(vector<int> myvec,int val){
        int myvec_size=myvec.size();
        for(int i=0;i<myvec_size;i++){
            if(myvec[i]==val){
                return true;
            }
        }
        return false;
    }
    int bfs(int start_point,int dest){
        queue<int> myq;
        bool *visited=new bool[numOfVex];
        int total_len=0;
        for(int i=0;i<numOfVex;i++){
            prev[i]=0;
        }
        //push graph vertices in the queuee
        //discover all nodes
        LLnod *crawler;
        myq.push(start_point);
        while(!myq.empty()){
            visited[myq.front()]=true;
            crawler=adjList[myq.front()].head;
            while(crawler!=nullptr){
                if(!visited[crawler->value]){
                    myq.push(crawler->value);
                    visited[crawler->value]=true;
                    prev[(crawler->value)+1]=1+myq.front();
                }
                crawler=crawler->next;
            }
            myq.pop();
        }
        
        
        //setting the path part
        vector<int> path;
        int temp=dest+1;
        int this_prev;
        while(temp!=(start_point+1)){
            if(search_vec(path,temp)){
              return 0; 
            }
            if(temp==0){
                return 0;
            }
            path.push_back(temp-1);
            this_prev=temp-1;
            temp=prev[temp];
            total_len+=speedmatrix[this_prev][temp-1];
        }
        path.push_back(temp-1);
        if(search_vec(path,start_point)){
            std::cout<<"PATH("<<start_point<<","<<dest<<"):";
            for(int i=path.size()-1;i>=0;i--){
                std::cout<<path[i]<<",";
            }
            std::cout<<"\n";
        }
        // std::cout<<path.size()<<":PATHSIZE\n";
        return total_len;
    }
};


int main()
{   
    srand((unsigned) time(0));
    int nodenum=401;
    int wiz,my_exit=rand()%nodenum,parts_involved=20;
    Graph mygraph(nodenum);
    // mygraph.generate_graph();
    mygraph.generate_maze(parts_involved);
    // mygraph.print_graph();
    int max=0,temp=0;
    // for(int i=0;i<nodenum;i++){
    //     for(int j=0;j<nodenum;j++){
    //         if(i==j)continue;
    //         temp=mygraph.bfs(i,j);
    //         if(max<temp){
    //             max=temp;
    //         }
    //         // std::cout<<i<<","<<j<<","<<temp<<"\n";
    //     }
    // }
    // std::cout<<"\nMaximum shortest path from one position to another in the maze:\n"<<max<<"\n";
    int places[3],current=0;
    temp=0;
    for(int i=0;i<3;i++){
        std::cout<<"Wizard #"<<i+1<<"\n";
        wiz=rand()%nodenum;
        while(wiz==my_exit){
            wiz=rand()%nodenum;
        }
        mygraph.create_path(wiz,my_exit,parts_involved,10);
        current=mygraph.bfs(wiz,my_exit);
        while(current==0)
        {
            wiz=rand()%nodenum;
            while(wiz==my_exit){
                wiz=rand()%nodenum;
            }
            mygraph.create_path(wiz,my_exit,parts_involved,10);    
            current=mygraph.bfs(wiz,my_exit);
        }
        places[i]=current;
    }
    while(places[0]==places[1]||places[1]==places[2]||places[0]==places[2]){
        places[0]+=rand()%10;
        places[1]+=rand()%10;
        places[2]+=rand()%10;
    }
    //scores
    for(int i=0;i<3;i++){
        std::cout<<"\nScoreboard:\nWizard #"<<i+1<<" : "<<places[i]<<"\n";
    }
    if(places[0]<places[1]){
        if(places[2]<places[0]){
            std::cout<<"The winner is Wizard #3";
        }
        else{
            std::cout<<"The winner is Wizard #1";
        }
    }
    else {
        if(places[1]<places[2])
            std::cout<<"The winner is Wizard #2";
        else{
            std::cout<<"The winner is Wizard #3";
        }
    }

    return 0;
}