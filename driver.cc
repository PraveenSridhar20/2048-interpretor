#include "parser.tab.hh"
#include "pl.h"
using namespace std; 

int a[4][4];
map<string,pair<int,int>> m;
int mode=0;
void stderr_op(int a[4][4]){
    for (int i=0;i<4;i++)
        for (int j=0;j<4;j++)
            fprintf(stderr,"%d ",a[i][j]);
    map<pair<int,int>,vector<string>> temp;
    for (auto it:m){
        temp[make_pair(it.second.first+1,it.second.second+1)].push_back(it.first);
    }
    for (auto it:temp){
        fprintf(stderr,"%d,%d",it.first.first,it.first.second);
        for (int i=0;i<it.second.size();i++){
            fprintf(stderr,"%s",it.second[i].c_str());
            if (i!=it.second.size()-1)
                fprintf(stderr,",");
            
        }
        fprintf(stderr," ");    
    }

    fprintf(stderr,"\n");
    cout<<"2048>>>";
}

bool moveLeft(int a[4][4],int op){
    int n=4;

    int b[4][4];

    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++)
            b[i][j]=a[i][j];
    }
    for (int i=0;i<n;i++){
        int count=0;
        for (int j=0;j<n;j++){
            if (a[i][j]!=0){//0 means empty, the tracking of the tile with the map starts here
                for (auto it:m){
                    if (it.second.first==i && it.second.second==j){
                        m[it.first]=make_pair(i,count);
                    }
                }
                swap(a[i][j],a[i][count]);
                count++;
            }
        }
        
    }//this loop shifts everything to the left
    vector<string> v;
    for (int i=0;i<n;i++){//merge operation
        for (int j=0;j<n-1;j++){
            if (a[i][j]==a[i][j+1] && a[i][j]!=0){
                for (auto it : m){
                    if (it.second.first==i && it.second.second==j+1){
                        m[it.first]=make_pair(i,j);
                    }
                }
                if (op==1)
                    a[i][j]*=2;
                else if (op==2){
                    for (auto it:m){
                        if (it.second.first==i && it.second.second==j){
                            v.push_back(it.first);
                        }
                    }
                    if (mode==1)
                        a[i][j]=0;
                    else if (mode==2)
                        a[i][j]=-1;//tile destroyed but not to be used till later
                }
                else if (op==3)
                    a[i][j]*=a[i][j];
                else if (op==4)
                    a[i][j]=1;
                a[i][j+1]=0;
                j++;
            }
        }
    }

    for (auto it:v){
        cout<<"Variable "<<it<<" freed\n";
        m.erase(it);
    }

    //shift everything again after the merge
    for (int i=0;i<n;i++){
        int count=0;
        for (int j=0;j<n;j++){
            if (a[i][j]!=0){//0 means empty
                for (auto it:m){
                    if (it.second.first==i && it.second.second==j){
                        m[it.first]=make_pair(i,count);
                    }
                }
                swap(a[i][j],a[i][count]);
                count++;
            }
        }
        
    }
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++)
            if(a[i][j]<0)
                a[i][j]=0;
    }
    //this loop is for checking if any change has happened in game state
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++)
            if(b[i][j]!=a[i][j])
                return true;//if any change return valid move
    }
    return false;//else return invalid move 
}

bool moveRight(int a[4][4],int op){
    int n=4;
  
    int b[4][4];

    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++)
            b[i][j]=a[i][j];
    }
    for (int i=0;i<n;i++){
        int count=0;
        for (int j=0;j<n;j++){
            if (a[i][n-1-j]!=0){
                for (auto it:m){
                    if (it.second.first==i && it.second.second==n-1-j){
                        m[it.first]=make_pair(i,n-1-count);
                    }
                }
                swap(a[i][n-1-j],a[i][n-1-count]);
                count++;
            }
        }
        
    }
    vector<string> v;
    for (int i=0;i<n;i++){
        for (int j=n-1;j>0;j--){
            if (a[i][j]==a[i][j-1] && a[i][j]!=0){
                for (auto it : m){
                    if (it.second.first==i && it.second.second==j-1){
                        m[it.first]=make_pair(i,j);
                    }
                }
                if (op==1)
                    a[i][j]*=2;
                else if (op==2){
                    for (auto it:m){
                        if (it.second.first==i && it.second.second==j){
                            v.push_back(it.first);
                        }
                    }
                    if (mode==1)
                        a[i][j]=0;
                    else if (mode==2)
                        a[i][j]=-1;
                }
                else if (op==3)
                    a[i][j]*=a[i][j];
                else if (op==4)
                    a[i][j]=1;
                a[i][j-1]=0;
                j--;
            }
        }
    }

    for (auto it:v){
        cout<<"Variable "<<it<<" freed\n";
        m.erase(it);
    }
    
    for (int i=0;i<n;i++){
        int count=0;
        for (int j=0;j<n;j++){
            if (a[i][n-1-j]!=0){
                for (auto it:m){
                    if (it.second.first==i && it.second.second==n-1-j){
                        m[it.first]=make_pair(i,n-1-count);
                    }
                }
                swap(a[i][n-1-j],a[i][n-1-count]);
                count++;
            }
        }
        
    }

    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++)
            if(a[i][j]<0)
                a[i][j]=0;
    }

    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++)
            if(b[i][j]!=a[i][j])
                return true;
    }
    return false;
}


bool moveUp(int a[4][4],int op){
    int n=4;

    int b[4][4];

    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++)
            b[i][j]=a[i][j];
    }
    for (int i=0;i<n;i++){
        int count=0;
        for (int j=0;j<n;j++){
            if (a[j][i]!=0){
                for (auto it:m){
                    if (it.second.first==j && it.second.second==i){
                        m[it.first]=make_pair(count,i);
                    }
                }
                swap(a[j][i],a[count][i]);
                count++;
            }
        }
        
    }
    vector<string> v; 
    for (int i=0;i<n;i++){
        for (int j=0;j<n-1;j++){
            if (a[j][i]==a[j+1][i] && a[j][i]!=0){
                for (auto it : m){
                    if (it.second.first==j+1 && it.second.second==i){
                        m[it.first]=make_pair(j,i);
                    }
                }
                if (op==1)
                    a[j][i]*=2;
                else if (op==2){
                     for (auto it:m){
                        if (it.second.first==j && it.second.second==i){
                            v.push_back(it.first);
                        }
                    }
                    if (mode==1)
                        a[j][i]=0;
                    else if (mode==2)
                        a[j][i]=-1;
                }
                else if (op==3)
                    a[j][i]*=a[j][i];
                else if (op==4)
                    a[j][i]=1;
                a[j+1][i]=0;
                j++;
            }
        }
    }

    for (auto it:v){
        cout<<"Variable "<<it<<" freed\n";
        m.erase(it);
    }
    
    for (int i=0;i<n;i++){
        int count=0;
        for (int j=0;j<n;j++){
            if (a[j][i]!=0){
                for (auto it:m){
                    if (it.second.first==j && it.second.second==i){
                        m[it.first]=make_pair(count,i);
                    }
                }
                swap(a[j][i],a[count][i]);
                count++;
            }
        }
        
    }

    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++)
            if(a[i][j]<0)
                a[i][j]=0;
    }

    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++)
            if(b[i][j]!=a[i][j])
                return true;
    }
    return false;
}

bool moveDown(int a[4][4],int op){
    int n=4;

    int b[4][4];

    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++)
            b[i][j]=a[i][j];
    }
    for (int i=0;i<n;i++){
        int count=0;
        for (int j=0;j<n;j++){
            if (a[n-1-j][i]!=0){
                for (auto it:m){
                    if (it.second.first==n-1-j && it.second.second==i){
                        m[it.first]=make_pair(n-1-count,i);
                    }
                }
                swap(a[n-1-j][i],a[n-1-count][i]);
                count++;
            }
        }
        
    }
    vector<string> v;
    for (int i=0;i<n;i++){
        for (int j=n-1;j>0;j--){
            if (a[j][i]==a[j-1][i] && a[j][i]!=0){
                for (auto it : m){
                    if (it.second.first==j-1 && it.second.second==i){
                        m[it.first]=make_pair(j,i);
                    }
                }
                if (op==1)
                    a[j][i]*=2;
                else if (op==2){
                    for (auto it:m){
                        if (it.second.first==j && it.second.second==i){
                            v.push_back(it.first);
                        }
                    }
                    if (mode==1)
                        a[j][i]=0;
                    else if (mode==2)
                        a[i][j]=-1;
                }
                else if (op==3)
                    a[j][i]*=a[j][i];
                else if (op==4)
                    a[j][i]=1;
                a[j-1][i]=0;
                j--;
            }
        }
    }

    for (auto it:v){
        cout<<"Variable "<<it<<" freed\n";
        m.erase(it);
    }
    
    for (int i=0;i<n;i++){
        int count=0;
        for (int j=0;j<n;j++){
            if (a[n-1-j][i]!=0){
                for (auto it:m){
                    if (it.second.first==n-1-j && it.second.second==i){
                        m[it.first]=make_pair(n-1-count,i);
                    }
                }
                swap(a[n-1-j][i],a[n-1-count][i]);
                count++;
            }
        }
        
    }

    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++)
            if(a[i][j]<0)
                a[i][j]=0;
    }

    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++)
            if(b[i][j]!=a[i][j])
                return true;
    }
    return false;
}

void rand_pos_gen(int a[4][4]){
    vector<pair<int,int>> v;
    //insert all coordinates with blanks into a vector
    for (int i=0;i<4;i++)
        for (int j=0;j<4;j++)
            if (a[i][j]==0)
                v.push_back(make_pair(i,j));

    if (v.empty()){
        return;
    }
    //shuffle the vector randomly to get a random position at the front of the vector
    //no need to check for clash by doing this
    random_shuffle(v.begin(),v.end());
    int x=rand()%10;
    x=(x<=7)?2:4;//this is to have a greater probability of randomly instantiating a 2 than a 4

    //after instantiation, put the element at the random position from the shuffle
    a[v[0].first][v[0].second]=x; 
    
}

void move (int a[4][4],int op , int dir){
    bool flag=false;
    if (dir==1)
        flag=moveLeft(a,op);
    else if (dir==2)
        flag=moveRight(a,op);
    else if (dir==3)
        flag=moveUp(a,op);
    else if (dir==4)
        flag=moveDown(a,op);

    if (!flag){
        cout<<"The move did not change the state\n";
    }
    else{
        for (auto it:m)
        cout<<"Variable, tile coordinates and value:"<<it.first<<' '<<it.second.first+1<<','<<it.second.second+1<<' '<<a[it.second.first][it.second.second]<<'\n';
        cout<<"Move done and random tile generated\n";
        rand_pos_gen(a);
    }
    
}

void printBoard(int  a[4][4]){
    for (int i =0;i<4;i++){
        for (int j=0;j<4;j++){
            cout<<a[i][j]<<'\t';
            
        }
        cout<<"\n";
    }
    cout<<"\n";
}



int main(int argc, char* argv[]){
    if (argc != 2){
        cout<<"Invalid argument count. Please enter one of the following numbers as the argument:\n";
        cout<<"1. 4224 SUBTRACT LEFT. -> 4400\n";
        cout<<"2. 4224 SUBTRACT LEFT. -> 4040\n";
        return 1;
    }

    if (atoi(argv[1])!=1 && atoi (argv[1])!=2){
        cout<<"Invalid option. Please enter one of the following numbers as the argument:\n";
        cout<<"1. 4224 SUBTRACT LEFT. -> 4400\n";
        cout<<"2. 4224 SUBTRACT LEFT. -> 4040\n";
        return 1; 
    }
    mode= atoi (argv[1]);
    srand(time(0));//setting seed based on time to avoid redundant games
    
    cout<<" Hi, I am the 2048-game Engine\n\n";
    memset(a,0,sizeof(a));
    rand_pos_gen(a);
    printBoard(a);
    cout<<"2048>>>";
    yyparse();

    return 0;
}