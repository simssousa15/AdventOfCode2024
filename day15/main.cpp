#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>

#define GRID_SIZE 71
#define FALLEN_BYTES 1024
using namespace std;

struct Node{
    int x, y, st;
    Node(int x, int y, int steps): x(x), y(y), st(steps) {}
};

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

    map<char, pair<int,int>> char_to_dir = {
        {'<', {0, -1}},
        {'>', {0, 1}},
        {'^', {-1, 0}},
        {'v', {1, 0}},
    };


    vector<string> grid;
    int grid_size = 0;
    for( auto l : text ){
        if(l[0] != '#'){ break; }
        grid.push_back(l);
        grid_size++;
    }
    grid_size += 1;
    
    string moves = "";
    for(int j = grid_size; j < text.size(); j++){
        moves += text[j];
    }
    
    //alter grid
    vector<string> new_grid;
    for( auto l : grid ){
        string lin = "";
        for( auto c : l ){
            if(c == '#'){ lin += "##"; }
            else if(c == 'O'){ lin += "[]"; }
            else if(c == '.'){ lin += ".."; }
            else if(c == '@'){ lin += "@."; }
        }
        new_grid.push_back(lin);
    }
    grid = new_grid;

    /* for(auto l : grid){ cout << l << endl; }
    cout << endl << moves.length() << endl; */

    //find robot pos
    int x, y;
    for( int i = 0; i<grid.size(); i++){
        for(int j =0; j<grid[i].length(); j++){
            if(grid[i][j] == '@'){
                x = j;
                y = i;
            }
        }
    }

    for( char m : moves){
        auto [dy, dx] = char_to_dir[m];

        if( grid[y+dy][x+dx] == '#' ){ continue; }
        else if( grid[y+dy][x+dx] == '.' ){ 
            grid[y+dy][x+dx] = '@';
            grid[y][x] = '.';
        }else if( grid[y+dy][x+dx] == '[' || grid[y+dy][x+dx] == ']' ){
            if(m == '<' || m == '>'){
                int cnt = 2;
                while( grid[y+dy*cnt][x+dx*cnt] == '[' || grid[y+dy*cnt][x+dx*cnt] == ']' ){cnt++;}
                if(grid[y+dy*cnt][x+dx*cnt] == '#'){continue;}
                else{
                    grid[y][x] = '.';
                    grid[y+dy][x+dx] = '@';
                    for(int i = 0; i < cnt; i++){
                        if(grid[y+dy*i][x+dx*i] == '['){ grid[y+dy*i][x+dx*i] = ']'; }
                        else if(grid[y+dy*i][x+dx*i] == ']'){ grid[y+dy*i][x+dx*i] = '['; }
                    }
                    if(m == '<'){ grid[y+dy*cnt][x+dx*cnt] = '['; }
                    else{ grid[y+dy*cnt][x+dx*cnt] = ']'; }
                }
            }else{
                vector<pair<int, set<int>>> x_boxes;
                set<int>row;
                if(grid[y+dy][x] == '['){ row.insert(x); }
                else if(grid[y+dy][x] == ']'){ row.insert(x-1); }
                else if( grid[y+dy][x] == '#' ){ continue; }
                else{
                    grid[y][x] = '.';
                    grid[y+dy][x+dx] = '@';
                    continue;
                }
                x_boxes.push_back({y+dy, row});

                int cnt = 1;
                bool fina = false;
                bool blocked = false;
                while(!fina){
                    cnt++;
                    row.clear();
                    for(int x_ : x_boxes.rbegin()->second ){
                        if(grid[y+dy*cnt][x_] == '#'){
                            fina = true;
                            blocked = true;
                            break;
                        }
                        else if(grid[y+dy*cnt][x_] == '['){
                            row.insert(x_);
                        }
                        else if(grid[y+dy*cnt][x_] == ']'){
                            row.insert(x_-1);
                        }

                        if(grid[y+dy*cnt][x_+1] == '#'){
                            fina = true;
                            blocked = true;
                            break;
                        }
                        else if(grid[y+dy*cnt][x_+1] == '['){
                            row.insert(x_+1);
                        }
                        else if(grid[y+dy*cnt][x_+1] == ']'){
                            row.insert(x_);
                        }
                    }
                    if(row.empty()){fina = true;}
                    else if(!fina){x_boxes.push_back({y+dy*cnt, row});}
                }

                if(blocked){ continue; }

                for(int i = x_boxes.size() - 1; i >= 0; i--){
                    for( auto x_ : x_boxes[i].second){
                        grid[x_boxes[i].first+dy][x_] = '[';
                        grid[x_boxes[i].first+dy][x_+1] = ']';
                        grid[x_boxes[i].first][x_] = '.';
                        grid[x_boxes[i].first][x_+1] = '.';
                    }
                }
                grid[y][x] = '.';
                grid[y+dy][x+dx] = '@';
            }
            
        }
        x += dx;
        y += dy;

        /* cout << endl << "move: " << m << endl;
        for(auto l : grid){ cout << l << endl; } */
    }

    /* cout << endl << endl << "Final grid" << endl;
    for(auto l : grid){ cout << l << endl; } */

    int sum = 0;
    for( int i = 0; i<grid.size(); i++){
        for(int j =0; j<grid[i].length(); j++){
            if(grid[i][j] == '['){
                sum += 100*i + j;
            }
        }
    }
    cout << "Result: " << sum;

    return 0;
}