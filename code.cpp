#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

#define MAXN 20
#define MAXPATH 50

int N;
string cities[MAXN];
int graph[MAXN][MAXN];


// ----- Utility Functions -----
int getCityIndex(string name){
    for(int i=0;i<N;i++){
        if(cities[i]==name) return i;
    }
    return -1;
}

string toUpper(string s){
    for(int i=0;i<s.size();i++) s[i] = toupper(s[i]);
    return s;
}

bool edgeExists(string a, string b){
    int u=getCityIndex(a);
    int v=getCityIndex(b);
    if(u==-1 || v==-1) return false;
    return graph[u][v]==1;
}

int parseSequence(string input, string seq[]){ 
    // Students implement this
    stringstream city(input); 
    // an edge is between 2 vertices so whenever an edge is established we must have a vertex at the start.
    int count = 0; 
    string temp = "";
    while(getline(city, seq[count], '-')) {
        getline(city, temp, '>');
        seq[count] = toUpper(seq[count]);
        cout<<seq[count]<<endl;
        count++;
    }
    return count;
}

// ----- Student functions to implement -----
bool isWalk(string seq[], int len) {
    for (int i = 0; i < len - 1; i++) {
        // using a loop because by the definition of walk , EVERY consecutive pair should have an edge between them
        if (edgeExists(seq[i], seq[i+1])) {
                 return true;
        }
    }
    return false; 
}//implement and return appropriate values
bool isTrail(string seq[], int len) { 
    if(isWalk(seq,len)){
    
        for (int i = 0; i < len - 1; i++) {
                for (int j = i + 1; j < len - 1; j++) {
                    if (  (seq[i] == seq[j] && seq[i+1] == seq[j+1])  ) {
                        return false;
                    }
            }
        }        
}
    return true;
 }//implement and return appropriate values
bool isPath(string seq[], int len) { 
   if(isTrail(seq,len)){
     for (int i = 0; i < len ; i++) {
                for (int j = 0; j < len ; j++) {
                    if ( i != j && seq[i] == seq[j]  ) {
                        return false;
                    }
                }
           }
    }
    return true;
 }//implement and return appropriate values
bool isClosedWalk(string seq[], int len) { 
    if(isWalk(seq,len)){
        if(seq[0] == seq[len-1]){
            return true;
        }
    }
    return false; }//implement and return appropriate values
bool isCircuit(string seq[], int len) { 
    if (!isTrail(seq, len)) {
        return false;
    }
    if (!isClosedWalk(seq,len)) {
        return false;
    }
    if (len < 4) {
        return false;
    }

    return true;
}//implement and return appropriate values
bool isSimpleCircuit(string seq[], int len) { 
          
    if (!isCircuit(seq, len)) {
        return false;
    }
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - 1; j++) {
            if ( i != j && seq[i] == seq[j] ) {
                return false; 
            }
        }
    }
    return true; 
}//implement and return appropriate values

// ----- Map Display -----
void printMap(){ 
    cout<<"\n--- Map ---\n";
    for(int i=0;i<N;i++){
        cout<<cities[i]<<" connected to: ";
        bool first=true;
        for(int j=0;j<N;j++){
            if(graph[i][j]){
                if(!first) cout<<", ";
                cout<<cities[j];
                first=false;
            }
        }
        if(first) cout<<"None";
        cout<<"\n";
    }
}

// ----- Grading -----
int marks[6] = {0,0,0,0,0,0};
string moduleNames[6] = {"Path","Walk","Trail","Closed Walk","Circuit","Simple Circuit"};

void grade(string seq[], int len, bool expected[6]){
    bool results[6] = {
        isPath(seq,len),
        isWalk(seq,len),
        isTrail(seq,len),
        isClosedWalk(seq,len),
        isCircuit(seq,len),
        isSimpleCircuit(seq,len)
    };

    for(int i=0;i<6;i++){
        if(results[i] == expected[i]) marks[i] = 5;
        else marks[i] = 0;
    }
}

// ----- Main -----
int main(){
    ifstream fin("map.txt");
    if(!fin){ cout<<"Error: map.txt not found!\n"; return 1; }

    fin >> N;
    fin.ignore();
    for(int i=0;i<N;i++) getline(fin,cities[i]);
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            fin >> graph[i][j];
    fin.close();

    printMap();

    // ----- Predefined test sequence -----
    string testSeqStr = "ISLAMABAD->RAWALPINDI->SIALKOT->GUJRANWALA->LAHORE->ISLAMABAD";
    string seq[MAXPATH];
    int len = parseSequence(testSeqStr, seq);

    // Expected results for this test sequence
    bool expected[6] = {false,true,true,true,true,true};

    cout<<"\nTesting predefined sequence: "<<testSeqStr<<endl;
    cout<<"Length of sequence: "<<len<<endl;

    // Grade
    grade(seq,len,expected);

    // Print marks
    cout<<"\n--- Module Marks ---\n";
    int total = 0;
    for(int i=0;i<6;i++){
        cout<<i+1<<". "<<moduleNames[i]<<": "<<marks[i]<<"/5\n";
        total += marks[i];
    }
    cout<<"Total Score: "<<total<<"/30\n";

    //Do not change anything in main above this part.

    // ----- User input loop -----
    while(true){
        cout<<"\nEnter your own sequence (format A->B->C->...):\n";
        string input;
        getline(cin,input);
        len = parseSequence(input, seq);

        cout<<"\nLength (edges): "<<len-1<<"\n";
        cout<<"Sequence classification (Yes/No):\n";
        cout<<"Path: "<<(isPath(seq,len)?"Yes":"No")<<"\n";
        cout<<"Walk: "<<(isWalk(seq,len)?"Yes":"No")<<"\n";
        cout<<"Trail: "<<(isTrail(seq,len)?"Yes":"No")<<"\n";
        cout<<"Closed Walk: "<<(isClosedWalk(seq,len)?"Yes":"No")<<"\n";
        cout<<"Circuit: "<<(isCircuit(seq,len)?"Yes":"No")<<"\n";
        cout<<"Simple Circuit: "<<(isSimpleCircuit(seq,len)?"Yes":"No")<<"\n";
    }

    return 0;
}
