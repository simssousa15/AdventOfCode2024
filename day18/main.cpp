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

    ifstream inputFile("input.txt");
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

    vector<string> grid;
    string l = "";

    for(int i = 0; i < GRID_SIZE; i++){ l += '.'; }
    for(int i = 0; i < GRID_SIZE; i++){ grid.push_back(l); }
    	
    int x, y;
    string cord;
    for( int i = 0; i < FALLEN_BYTES; i++ ){
        cord = text[i];
        x = stoi(cord.substr(0, cord.find(',')));
        y = stoi(cord.substr(cord.find(',')+1));

        grid[y][x] = '#';
    }

    for( string r : grid ){
        cout << r << endl;
    }

    vector<int> dirs = {0, 1, 0, -1, 0};
    queue<pair<int, int>> q;
    
    
    int new_x, new_y;
    auto og_grid = grid;

    for( int j = FALLEN_BYTES; j < text.size(); j++){

        cord = text[j];
        new_x = stoi(cord.substr(0, cord.find(',')));
        new_y = stoi(cord.substr(cord.find(',')+1));
        grid = og_grid;
        grid[new_y][new_x] = '#';
        og_grid = grid;
        
        cout << new_x << "," << new_y << endl;
        // for( string r : grid ){cout << r << endl;}

        bool found = false;
        q.push({0,0});
        while(!q.empty()){
            auto c = q.front();
            q.pop();

            for(int i = 0; i < 4; i++){
                x = c.second + dirs[i];
                if(x < 0 || x >= GRID_SIZE){ continue; }
                y = c.first + dirs[i+1];
                if(y < 0 || y >= GRID_SIZE){ continue; }

                if(grid[y][x] == '.'){
                    if( x == GRID_SIZE-1 && y == GRID_SIZE-1 ){
                        found = true;
                        break;
                    }

                    q.push({y, x});
                    grid[y][x] = 'O';
                }
            }
        }
    	
        while(!q.empty()){ q.pop(); }

        if(!found){
            cout << new_x << "," << new_y << endl;
            break;
        }

    }
    
    return 0;
}