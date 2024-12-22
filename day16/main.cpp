#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

#define BLINKS 75

class Record
{
    public:
        list<pair<int, int>> visited;

        void add(pair<int, int> pos){
            visited.push_back(pos);
        }
        bool check(pair<int, int> pos){
            return find(visited.begin(), visited.end(), pos) == visited.end();
        }
        int get_size(){
            return visited.size();
        }
};

struct Node{
    char c;
    int i, j, score;
    Record* rec;
    Node(char c, int i, int j, int score): c(c), i(i), j(j), score(score){
        rec = new Record;
        rec->add(make_pair(i, j));
    }
    Node(char c, int i, int j, int score, list<pair<int, int>>pos): c(c), i(i), j(j), score(score){
        rec = new Record;
        rec->visited = pos;
        rec->add(make_pair(i, j));
    }
};

bool operator<(const Node A, const Node B){
    return A.score > B.score;
}

vector<pair<char, int>> turn(char c){
    switch (c)
    {
    case '>':
        return {{'^', 1000}, {'v', 1000}, {'<', 2000}};
    case '<':
        return {{'^', 1000}, {'v', 1000}, {'>', 2000}};
    case 'v':
        return {{'<', 1000}, {'>', 1000}, {'^', 2000}};
    case '^':
        return {{'<', 1000}, {'>', 1000}, {'v', 2000}};
    default:
        cout << "Unrecognized char in turn" << endl;
        return {{'O', 0}};
    }
}

int main()
{

    ifstream inputFile("small.txt");
    if (!inputFile)
    {
        cerr << "Unable to open the file!" << std::endl;
        return 1;
    }

    vector<string> text;
    string line;

    while (getline(inputFile, line)){ text.push_back(line); }

    // Close the file
    inputFile.close();
    
    auto grid = text;

    int init_i, init_j;
    int end_i, end_j;
    for(int i = 0; i < grid.size(); i++){
        for(int j = 0; j < grid[i].size(); j++){
            if(grid[i][j] == 'S'){ 
                init_i = i;
                init_j = j;
                grid[i][j] = '.';
            }else if(grid[i][j] == 'E'){
                end_i = i;
                end_j = j;
                grid[i][j] = '.';
            }
        }
    }

    map<char, char> change_dir ={
        {'>', '^'},
        {'^', '<'},
        {'<', 'v'},
        {'v', '>'},
    };
    
    map<char, pair<int,int>> char_vec ={
        {'>', {0,1}},
        {'<', {0,-1}},
        {'^', {-1,0}},
        {'v', {1,0}}
    };

    vector<pair<int, int>> dirs{
        {0,1},
        {0,-1},
        {1,0},
        {-1,0}
    };

    priority_queue<Node> q;
    q.push(Node('>', init_i, init_j, 0));

    int best_score = 0;
    int path_count = 0;

    set<pair<int, int>> seats;
    while(!q.empty()){
        auto n = q.top();
        q.pop();

        // no more possible paths
        if(best_score && n.score > best_score){ break; }

        // check if reached end
        if(n.i == end_i && n.j == end_j){
            best_score = n.score;
            path_count++;
            continue;
        }

        auto [di, dj] = char_vec[n.c];
        if(grid[n.i+di][n.j+dj] == '.'){
            if(n.rec->check(make_pair(n.i+di, n.i+di))){
                q.push(Node(n.c, n.i+di, n.j+dj, n.score + 1, n.rec->visited));
            }
        }

        vector<pair<char, int>> t = turn(n.c);

        for(auto op : t){
            auto [di, dj] = char_vec[op.first];

            if(grid[n.i+di][n.j+dj] == '.'){
                if(n.rec->check(make_pair(n.i+di, n.i+di))){
                    q.push(Node(op.first, n.i+di, n.j+dj, n.score + 1 + op.second, n.rec->visited));
                }
            }
        }
    }

    cout << "Best score: " << best_score << endl;
    cout << "Options: " << path_count << endl;
    cout << "Seats: " << seats.size() << endl;

    
    return 0;
}