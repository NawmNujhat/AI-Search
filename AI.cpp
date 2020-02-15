#include<bits/stdc++.h>
#define up 1
#define down 2
#define right 4
#define left 3
using namespace std;
int taken_tile[100000];
map<string,int>dls_explored;
set<string>::iterator it;
int init_limit;
struct Node
{

    int state[10][10];
    int action;
    int path_cost;
    Node* parent;
};
int n;
int given;
Node Initial;
Node Goal;
Node Cutoff;
Node failure;
void input_puzzle(Node * node)
{
    int a;
    memset(taken_tile,0,sizeof(taken_tile));
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            printf("board[%d][%d]= ",i,j);
            cin>>a;
            cout<<endl;
            if(a>=0 && a<=(n*n)-1 && taken_tile[a]==0)
            {

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
void make_cutoff(Node * node)
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            node->state[i][j]=-1;
        }
    }
    node->action=-1;
    node->parent=NULL;
    node->path_cost=-1;

}
void make_failure(Node * node)
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            node->state[i][j]=-2;
        }
    }
    node->action=-1;
    node->parent=NULL;
    node->path_cost=-1;

}
void print_puzzle(Node * node)
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            printf("%d ",node->state[i][j]);
        }
        cout<<endl;
    }

}
int check_goal(Node * cur,Node * goal)
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(cur->state[i][j]!=goal->state[i][j])
            {
                return 0;
            }
        }
    }

    return 1;

}
string is_accepted(Node * node)
{
    string check;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
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

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
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
        swap( newNode->state[empty_slot_x][empty_slot_y],newNode->state[empty_slot_x-1][empty_slot_y]);
        newNode->action=up;
        return newNode;

    }
    else if(actions==down && empty_slot_x+1<n)
    {

        swap(newNode->state[empty_slot_x][empty_slot_y],newNode->state[empty_slot_x+1][empty_slot_y]);
        newNode->action=down;
        return newNode;

    }
    else if(actions==right && empty_slot_y+1<n)
    {

        swap(newNode->state[empty_slot_x][empty_slot_y], newNode->state[empty_slot_x][empty_slot_y+1]);
        newNode->action= right;
        return newNode;

    }
    else if(actions==left && empty_slot_y-1>=0)
    {

        swap(newNode->state[empty_slot_x][empty_slot_y], newNode->state[empty_slot_x][empty_slot_y-1]);
        newNode->action= left;
        return newNode;

    }
    free(newNode);
    return NULL;
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
        //string goal_check=is_accepted(&Goal);
        //cout<<visited_check<<endl;
        //cout<<goal_check<<endl;
        int compare=check_goal(visited,&Goal);
        //cout<<compare<<endl;
        if(compare==1)
        {
            cout<<"BFS solved"<<endl;
            cout<<"Path Cost: "<<visited->path_cost<<endl;
            break;
        }


        for(int action=1; action<=4; action++)
        {
            Node* child=CreateNode(visited,action);
            if(child!=NULL)
            {
                //print_puzzle(child);
                //printf("----------------\n");
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
struct comparepath_cost
{
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

        string visited_check=is_accepted(visited);
        explored.insert(visited_check);
        //string goal_check=is_accepted(&Goal);

        int compare=check_goal(visited,&Goal);
        if(compare==1)
        {
            cout<<"UCS solved"<<endl;
            cout<<"Path Cost: "<<visited->path_cost<<endl;
            break;
        }

        for(int action=1; action<=4; action++)
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
Node* dls(Node* node,int limit)
{

    string current_check=is_accepted(node);
    dls_explored[current_check]=1;
    //string goal_check=is_accepted(&Goal);
    int cutoff_occurred;
    // cout<<current_check<<endl;
    //cout<<goal_check<<endl;
    int compare=check_goal(node,&Goal);;


    if(compare==1)
    {
        //cout<<"DEBUG-1"<<endl;
        cout<<"DLS solved"<<endl;
        cout<<"Path Cost: "<<node->path_cost<<endl;
        return node;
    }


    else if (limit==0)
    {
        // dls_explored.insert(current_check);

        return &Cutoff;//returning a global cutoff node if limit exceeds
    }
    else
    {

        cutoff_occurred=0;

        //cout<<limit<<endl;
        for(int i=1; i<=4; i++)
        {
            Node* child=CreateNode(node,i);
            if(child!=NULL)
            {
                string check_explored=is_accepted(child);
                if(dls_explored[check_explored]==0||dls_explored.find(check_explored)==dls_explored.end())
                {

                    child->parent=node;
                    child->path_cost=child->parent->path_cost+1;
                    // cout>>child->path_cost>>endl;
                    dls_explored[check_explored]=1;
                    Node* result=dls(child,limit-1);
                    dls_explored[check_explored]=0;
                    //print_puzzle(result);
                    int compare_cutoff=check_goal(result,&Cutoff);
                    int compare_failure=check_goal(result,&failure);
                    if(compare_cutoff==1)
                    {
                        cutoff_occurred=1;
                    }
                    else if(compare_failure==0)
                    {
                        //cout<<"DEBUG2"<<endl;
                        return result;
                    }

                }


            }
            else
            {
                continue;
            }

        }

        if(cutoff_occurred==1)
        {
            //cout<<"DEBUG3"<<endl;
            return &Cutoff;
        }
        else
        {
            //cout<<"DEBUG4"<<endl;
            return &failure;//returning NULL for failure
        }

    }

}
Node* ids(Node * node)
{
    for(int depth=0;; depth++)
    {
        dls_explored.clear();
        Node* result=dls(node,depth);
        string result_check=is_accepted(result);
        string cutoff_check=is_accepted(&Cutoff);
        int compare=result_check.compare(cutoff_check);
        if(compare!=0)
        {
            cout<<"IDS solved"<<endl;
            cout<<"Path cost"<<result->path_cost<<endl;
            return result;
        }


    }


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
    // print_puzzle(&Initial);
    // print_puzzle(&Goal);
    make_cutoff(&Cutoff);
    make_failure(&failure);



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
        cin>>given;
        init_limit=given;

        clock_t start = clock();
        dls_explored.clear();
        Node *final_node=dls(&Initial,given);
        print_puzzle(final_node);
        // cout<<is_accepted(final_node)<<endl;
        double     runtime = (double)(clock() - start) / CLOCKS_PER_SEC;
        //
        cout << "Run: "<<runtime <<endl;
    }
    if(choice==4)
    {
        clock_t start = clock();

        Node *final_node=ids(&Initial);
        // cout<<is_accepted(final_node)<<endl;
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
