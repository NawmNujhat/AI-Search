#include<bits/stdc++.h>
#define up 1
#define down 2
#define right 3
#define left 4
using namespace std;
int taken_tile[100000];
struct Node
{

    int state[25][25];
    int action;
    int path_cost;
    Node* parent;
    int pos_0x,  pos_0y;
};
int n;
int limit ;
Node Initial;
Node Goal;
void input_puzzle(Node * node)
{
    int a;
    memset(taken_tile,0,sizeof(taken_tile));
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
             printf("board[%d][%d]= ",i,j);
            cin>>a;

            cout<<endl;
            if(a>=0 && a<=(n*n)-1 && taken_tile[a]==0)
            {
                if(a==0)
                {
                    node->pos_0x=0;
                    node->pos_0y=0;
                }

                node->state[i][j]=a;
                taken_tile[a]=1;
            }
            else if(a<0 || a>(n*n)-1)
            {
                printf("Invalid. Please enter another number\n");
                j--;

            }
             else if(taken_tile[a]==1 && a>=0 && a<=(n*n)-1)
            {
                printf("Input received. Please enter another number\n");
                j--;
            }


        }
    }
    node->action=-1;
    node->parent=NULL;
    node->path_cost=0;



}
void print_puzzle(Node * node)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            printf("%d ",node->state[i][j]);
        }
        cout<<endl;
    }

}
string is_accepted(Node * node)
{
    string check;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            check+=node->state[i][j]+'0';
        }
    }
    return check;
}
Node* CreateNode(Node * node,int actions)
{
    Node *newNode=(Node*) malloc(sizeof(Node));
    int empty_slot_x,empty_slot_y;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(node->state[i][j]==0)
            {
                empty_slot_x=i;
                empty_slot_y=j;
            }
            newNode->state[i][j]=node->state[i][j];
        }
    }
    if(actions==up && empty_slot_x-1>=0)
    {
        int buffer=newNode->state[empty_slot_x-1][empty_slot_y];
        newNode->state[empty_slot_x-1][empty_slot_y]=0;
        newNode->state[empty_slot_x][empty_slot_y]=buffer;
        newNode->action=up;
        return newNode;

    }
    else if(actions==down && empty_slot_x+1<n)
    {
        int buffer=newNode->state[empty_slot_x+1][empty_slot_y];
        newNode->state[empty_slot_x+1][empty_slot_y]=0;
        newNode->state[empty_slot_x][empty_slot_y]=buffer;
        newNode->action=down;
        return newNode;

    }
    else if(actions==right && empty_slot_y+1<n)
    {
        int buffer=newNode->state[empty_slot_x][empty_slot_y+1];
        newNode->state[empty_slot_x][empty_slot_y+1]=0;
        newNode->state[empty_slot_x][empty_slot_y]=buffer;
        newNode->action= right;
        return newNode;

    }
    else if(actions==left && empty_slot_y-1>=0)
    {
        int buffer=newNode->state[empty_slot_x][empty_slot_y-1];
        newNode->state[empty_slot_x][empty_slot_y-1]=0;
        newNode->state[empty_slot_x][empty_slot_y]=buffer;
        newNode->action= left;
        return newNode;

    }
    free(newNode);
    return NULL;
}
/*Node* CreateNode(Node * node,int actions)
{
    Node *newNode=(Node*) malloc(sizeof(Node));
    int empty_slot_x,empty_slot_y;
    empty_slot_x=node->pos_0x;
    empty_slot_y=node->pos_0y;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            newNode->state[i][j]=node->state[i][j];
        }
    }
    if(actions==up && empty_slot_x-1>=0)
    {
        swap( newNode->state[empty_slot_x][empty_slot_y],newNode->state[empty_slot_x-1][empty_slot_y]);
        newNode->action=up;
        newNode->pos_0x=empty_slot_x-1;
        newNode->pos_0y=empty_slot_y;
        return newNode;

    }
    else if(actions==down && empty_slot_x+1<n)
    {

        swap(newNode->state[empty_slot_x][empty_slot_y],newNode->state[empty_slot_x+1][empty_slot_y]);
        newNode->pos_0x=empty_slot_x+1;
        newNode->pos_0y=empty_slot_y;
        newNode->action=down;
        return newNode;

    }
    else if(actions==right && empty_slot_y+1<n)
    {

        swap(newNode->state[empty_slot_x][empty_slot_y], newNode->state[empty_slot_x][empty_slot_y+1]);
        newNode->pos_0x=empty_slot_x;
        newNode->pos_0y=empty_slot_y+1;
        newNode->action= right;
        return newNode;

    }
    else if(actions==left && empty_slot_y-1>=0)
    {

        swap(newNode->state[empty_slot_x][empty_slot_y], newNode->state[empty_slot_x][empty_slot_y-1]);
        newNode->pos_0x=empty_slot_x;
        newNode->pos_0y=empty_slot_y-1;
        newNode->action= left;
        return newNode;

    }
    free(newNode);
    return NULL;
}*/

int MatchState(Node* Current,Node* Final)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(Current->state[i][j]!=Final->state[i][j])
            {
                return 0;
            }
        }
    }
    return 1;
}
void bfs()
{
    queue<Node*>frontier;
    frontier.push(&Initial);
    set<string>explored;
    while(!frontier.empty())
    {
        Node* visited;
        visited=frontier.front();
        frontier.pop();
        string visited_check=is_accepted(visited);
        explored.insert(visited_check);
        string goal_check=is_accepted(&Goal);
        cout<<visited_check<<endl;
        //cout<<goal_check<<endl;
        int compare=visited_check.compare(goal_check);
        //int match=MatchState(visited,&Goal);
        /*if(match==1)
        {
            cout<<"BFS solved"<<endl;
            cout<<"Path Cost: "<<visited->path_cost<<endl;
            break;
        }*/

        for(int action=1;action<=4;action++)
        {
            Node* child=CreateNode(visited,action);
            if(child!=NULL)
            {
                string check_explored=is_accepted(child);
                if(explored.find(check_explored)==explored.end())
                {
                    child->parent=visited;
                    child->path_cost=child->parent->path_cost+1;
                    frontier.push(child);
                    explored.insert(check_explored);


                }

            }


        }
    }
}
struct comparepath_cost{
    bool operator()(Node* const& n1, Node* const& n2)
    {
        // return "true" if "p1" is ordered
        // before "p2", for example:
        return n1->path_cost > n2->path_cost;
    }
};
void ucs()
{
    priority_queue<Node*,vector<Node*>,comparepath_cost>frontier;
     frontier.push(&Initial);
    set<string>explored;
    while(!frontier.empty())
    {
        Node* visited;
        visited=frontier.top();
        frontier.pop();
       int match=MatchState(visited,&Goal);
        if(match==1)
        {
            cout<<"BFS solved"<<endl;
            cout<<"Path Cost: "<<visited->path_cost;
            break;
        }
        for(int action=1;action<=4;action++)
        {
            Node* child=CreateNode(visited,action);
            if(child!=NULL)
            {
                string check_explored=is_accepted(child);
                if(explored.find(check_explored)==explored.end())
                {
                    child->parent=visited;
                    child->path_cost=child->parent->path_cost+1;
                    explored.insert(check_explored);
                    frontier.push(child);

                }

            }


        }
    }

}
void dls(Node* node,int limit)
{

}
void initial_puzzle()
{
    printf("-----This is a game of n-puzzle------\n");
    printf("-----Please Enter The Board Size(n)-----\n");
    cin>>n;
    printf("----Please Enter The Initial State.\n The numbers should be between 0 to (n*n)-1.\nZero is considered to be empty\n");
    input_puzzle(&Initial);
     printf("----Please Enter The Goal State.\n The numbers should be between 0 to (n*n)-1.\nZero is considered to be empty\n");
    input_puzzle(&Goal);
    print_puzzle(&Initial);
    print_puzzle(&Goal);



}
void choose_search()
{
    printf("Enter a number for algorithm simulation\n");
    int choice;
    cin>>choice;
    if(choice==1)
    {

         clock_t start = clock();
         bfs();
        double     runtime = (double)(clock() - start) / CLOCKS_PER_SEC;
       //
       cout << "Run: "<<runtime <<endl;
    }
     if(choice==2)
    {
        clock_t start = clock();
        ucs();
          double     runtime = (double)(clock() - start) / CLOCKS_PER_SEC;
       //
       cout << "Run: "<<runtime <<endl;
    }
    if(choice==3)
    {
        printf("Please enter your limit : \n");
        cin>>limit;
        clock_t start = clock();
        dls(&Goal,limit);
          double     runtime = (double)(clock() - start) / CLOCKS_PER_SEC;
       //
       cout << "Run: "<<runtime <<endl;
    }

}

int main()
{
   initial_puzzle();
   choose_search();
}

