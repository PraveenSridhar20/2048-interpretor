
%{

#define YYSTYPE char*
#include "pl.h"
using namespace std;

int yyerror (char const *s);
extern int yylex(void);

%}

%token ADD SUBTRACT MULTIPLY DIVIDE LEFT RIGHT UP DOWN ASSIGN TO VAR IS VALUE IN 
%token NUMBER COMMA VARIABLE
%token END NEWLINE EXIT


%define parse.error verbose
%start Input
%%

Input: 
    | Input Line {}
    | Input error NEWLINE{
            cout<<"\nError!\n\n"; 
            fprintf(stderr,"%d\n",-1);
            printBoard(a);
            cout<<"2048>>>";
        }
 

Line: NEWLINE
    |Expression NEWLINE{}
  

Expression:   Operation Move END{  
                                cout<<"\nOperation followed by direction\n"; 
                                move (a,atoi($1),atoi($2));  
                                printBoard(a);
                                stderr_op(a);
                        
                            }
            | ASSIGN Num TO Num COMMA Num END{
                    if (atoi($4)>4 || atoi($4)<=0|| atoi($6)>4||atoi($6)<=0){
                        cout<<"\nIndex out of bounds Exception\n\n";
                        printBoard(a);
                        fprintf(stderr,"%d\n",-1);
                        cout<<"2048>>>";
                    }
                    else {
                        a[atoi($4)-1][atoi($6)-1]=atoi($2);
                        vector<string> v;
                        if (atoi($2)==0){
                            for (auto it:m){
                                if (it.second.first==atoi($4)-1 && it.second.second==atoi($6)-1){
                                    v.push_back(it.first);
                                }
                            }
                            for (auto it:v){
                                cout<<"Variable "<<it<<" freed\n";
                                m.erase(it);
                            }
                        }
                        cout<<"\nAssigning num to tile:"<<a[atoi($4)-1][atoi($6)-1]<<'\n';
                        cout<<"Operation successful\n";
                        printBoard(a);
                        stderr_op(a);
                        
                    }
                }
            | VAR VARIABLE IS Num COMMA Num END{
                    if (atoi($4)>4 || atoi($4)<=0|| atoi($6)>4||atoi($6)<=0){
                        cout<<"\nIndex out of bounds Exception\n\n";
                        printBoard(a);
                        fprintf(stderr,"%d\n",-1);
                        cout<<"2048>>>";
                    }
                    else{
                       
                        char* temp=$2;
                        string s="";   
                        for (;temp!=$4-4;temp++){
                            s=s+*temp;
                        }
                        if (a[atoi($4)-1][atoi($6)-1]==0){
                            cout<<"No tile found at this location\n\n";
                            fprintf(stderr,"%d\n",-1);
                            printBoard(a);
                            cout<<"2048>>>";
                        }
                        else{
                            m[s]=make_pair(atoi($4)-1,atoi($6)-1);
                            cout<<"Tile assigned to Variable "<<s<<" and stored in symbol table\n";
                            cout<<"\nOperation successful\n";
                            printBoard(a);
                            stderr_op(a);
                        }
                        
                        
                    }
                }
            | VALUE IN Num COMMA Num END{
                if (atoi($3)>4 || atoi($3)<=0|| atoi($5)>4||atoi($5)<=0){
                        cout<<"\nIndex out of bounds Exception\n\n";
                        printBoard(a);
                        cout<<"2048>>>";
                        fprintf(stderr,"%d\n",-1);
                }
                else {
                    cout<<"\nGetting value at tile "<<atoi($3)<<','<<atoi($5)<<':'<<a[atoi($3)-1][atoi($5)-1];
                    cout<<"\nOperation successful\n";
                    printBoard(a);
                    stderr_op(a);
                }
            }
            | VARIABLE END {
                string s="";
                char* temp=$1;
                for (;*(temp)!='.';temp++){
                    s+=*temp;
                }
                if (m.find(s)!=m.end()){
                    cout<<"\nVariable "<<s<<" has coordinates "<<m[s].first+1<<','<<m[s].second+1<<" and value "<<a[m[s].first][m[s].second]<<"\n\n";
                    stderr_op(a);
                }
                else {
                    cout<<'\n'<<s<<" not defined\n\n";
                    printBoard(a);
                    cout<<"2048>>>";
                    fprintf(stderr,"%d\n",-1);
                }
            }
            | EXIT END{
                cout<<"Thank you, exiting...\n";
                exit(0);
            }

Num: NUMBER {$$=$1;}
    | VALUE IN Num COMMA Num {
        if (atoi($3)>4 || atoi($3)<=0|| atoi($5)>4||atoi($5)<=0){
                    cout<<"\nIndex out of bounds Exception\n\n";
                    fprintf(stderr,"%d\n",-1);
            }
            else {
                cout<<"\nGetting value at tile "<<atoi($3)<<','<<atoi($5)<<':'<<a[atoi($3)-1][atoi($5)-1];
                char temp[100];
                snprintf(temp,sizeof(temp),"%d",a[atoi($3)-1][atoi($5)-1]);
                $$=temp;
                cout<<"Operation successful\n\n";
            }
    }

Operation: ADD {$$=(char*)"1";}
    | SUBTRACT {$$=(char*)"2";}
    | MULTIPLY {$$=(char*)"3";}
    | DIVIDE {$$=(char*)"4";}
    
Move: LEFT {$$=(char*)"1";}
    | RIGHT {$$=(char*)"2";}
    | UP {$$=(char*)"3";}
    | DOWN {$$=(char*)"4";}



%%

int yyerror(char const *s){
    cout<<s<<'\n';
    return 0;
}