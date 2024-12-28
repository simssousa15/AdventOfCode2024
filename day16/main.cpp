#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

class Node{
    public:
        int i, j, score;
        char c;
        Node(char c, int i, int j, int score): c(c), i(i), j(j), score(score) { }

        bool operator<(const Node& other) const{
            return score > other.score;
        }
};

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

int cost ( char c1, char c2 ){
    if(c1 == c2){ return 0; }
    
    if( c1=='<' && c2 == '>'){ return 2000; }
    if( c1=='>' && c2 == '<'){ return 2000; }
    if( c1=='^' && c2 == 'v'){ return 2000; }
    if( c1=='v' && c2 == '^'){ return 2000; }

    return 1000;
}

int main()
{

    ifstream inputFile("real.txt");
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

    vector<Node> start_scores;
    vector<Node> end_scores;

    vector<char> char_dir = { '<', '>', '^', 'v'};

    /* for(auto d : char_dir){
        for(int i = 0; i < text.size(); i++){
            vector<int> tmp;
            for(int j = 0; j < text[i].size(); j++){
                tmp.push_back(INT_MAX);
            }
            start_scores[d].push_back(tmp);
            end_scores[d].push_back(tmp);
        }
    } */
    

    priority_queue<Node> q;
    q.push(Node('>', init_i, init_j, 0));

    int best_score = 0;
    int path_count = 0;

    set<pair<char, pair<int,int>>> visited;

    while(!q.empty()){
        auto n = q.top();
        q.pop();

        start_scores.push_back(n);

        auto p = make_pair(n.i, n.j);
        auto no = make_pair(n.c, p);

        // print no
        // cout << no.first << " " << no.second.first << " " << no.second.second << endl;

        if(visited.find(no) == visited.end()){
            visited.insert(no);
        }else{
            continue;
        }

        // no more possible paths
        if(best_score && n.score > best_score){ break; }

        // check if reached end
        if(n.i == end_i && n.j == end_j){
            best_score = n.score;
            break;
        }

        auto [di, dj] = char_vec[n.c];
        
        // cout << sizeof(n) << endl;
        // cout << q.size() << endl; 
        // cout << n.i << " " << n.j << endl;

        if(grid[n.i+di][n.j+dj] == '.'){            
            auto p = make_pair(n.i+di, n.j+dj);
            auto no = make_pair(n.c, p);
            if(visited.find(no) == visited.end()){
                q.push(Node(n.c, n.i+di, n.j+dj, n.score+1));
            }
        }

        vector<pair<char, int>> t = turn(n.c);

        for(auto op : t){
            auto [di, dj] = char_vec[op.first];

            auto p = make_pair(n.i, n.j);
            auto no = make_pair(op.first, p);
            
            if(visited.find(no) == visited.end()){
                q.push(Node(op.first, n.i, n.j, n.score+op.second));
            }
        }
    }

    cout << "Best Score: " << best_score << endl;

    /* for(auto n1 : start_scores){
        cout << n1.i << " " << n1.j << " " << n1.score << endl;
    } */
    
    visited.clear();
    while(!q.empty()){ q.pop(); }
    q.push(Node('>', end_i, end_j, 0));
    q.push(Node('^', end_i, end_j, 0));
    q.push(Node('v', end_i, end_j, 0));
    q.push(Node('<', end_i, end_j, 0));

    
    while(!q.empty()){
        auto n = q.top();
        q.pop();

        end_scores.push_back(n);
        
        auto p = make_pair(n.i, n.j);
        auto no = make_pair(n.c, p);
        if(visited.find(no) == visited.end()){
            visited.insert(no);
        }else{
            continue;
        }

        // no more possible paths
        if(best_score && n.score > best_score){ break; }

        auto [di, dj] = char_vec[n.c];
        
        // cout << sizeof(n) << endl;
        // cout << q.size() << endl; 
        // cout << n.i << " " << n.j << endl;
        
        // cout << n.i+di << " " << n.j+dj << " " << n.score << " " << grid[n.i+di][n.j+dj] << endl;

        if(grid[n.i+di][n.j+dj] == '.'){
            auto p = make_pair(n.i+di, n.j+dj);
            auto no = make_pair(n.c, p);

            if(visited.find(no) == visited.end()){
                q.push(Node(n.c, n.i+di, n.j+dj, n.score+1));
            }
        }

        vector<pair<char, int>> t = turn(n.c);

        for(auto op : t){
            auto [di, dj] = char_vec[op.first];

            auto p = make_pair(n.i, n.j);
            auto no = make_pair(op.first, p);
        
            if(visited.find(no) == visited.end()){
                q.push(Node(op.first, n.i, n.j, n.score+op.second));
            }
        }
    }

    /* for(auto n1 : end_scores){
        cout << n1.i << " " << n1.j << " " << n1.score << endl;
    } */

    set<pair<int, int>> seats;
    sort(start_scores.begin(), start_scores.end());
    sort(end_scores.begin(), end_scores.end());

    for(auto n1 : start_scores){
        for(auto n2 : end_scores){
            if( n1.i != n2.i || n1.j != n2.j ){ continue; }
            
            // cout << n1.i << " " << n1.j << " " << n1.score + n2.score << endl;
            if( ( n1.score + n2.score == best_score && cost(n1.c, n2.c) == 2000 ) ){
                seats.insert(make_pair(n1.i, n1.j));
            }
        }
    }

    for( auto s : seats ){ 
        grid[s.first][s.second] = 'O';
    }

    for(auto l : grid){
        cout << l << endl;
    }

    cout << seats.size() << endl;

    
    return 0;
}