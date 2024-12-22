#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>

#define WIDTH 101
#define HEIGTH 103
#define T 100

using namespace std;

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

    vector<pair<int, int>> p;
    vector<pair<int, int>> v;

    for(auto l : text){

        l = l.substr(l.find('=')+1);
        int p_x = stoi(l.substr(0, l.find(',')));
        l = l.substr(l.find(',')+1);
        int p_y = stoi(l.substr(0, l.find(' ')));


        l = l.substr(l.find('=')+1);
        int v_x = stoi(l.substr(0, l.find(',')));
        l = l.substr(l.find(',')+1);
        int v_y = stoi(l.substr(0, l.find(' ')));

        p.push_back({p_x, p_y});
        v.push_back({v_x, v_y});
    }

    vector<string> og_grid;
    string l = "";
    for(int i = 0; i < WIDTH; i++){ l += "."; }
    for(int i = 0; i < HEIGTH; i++){ og_grid.push_back(l); }

    ofstream output;
    output.open("output.txt");
    bool print = false;
    for(int i = 0; i < 10000; i++ ){
        auto grid = og_grid;

        for(int j = 0; j < p.size(); j++ ){
            auto [px,py] = p[j];
            auto [vx,vy] = v[j];

            px += vx*i;
            px %= WIDTH;
            if( px<0 ){ px = WIDTH + px; }

            py += vy*i;
            py %= HEIGTH;
            if( py<0 ){ py = HEIGTH + py; }

            grid[py][px] = '#';

            int count = 0;
            for(int a = 0; a< 14; a++){
                if(grid[py][px-7+a] =='#'){ count ++; }
            }
            if(count >=7){ print = true; }
        }

        // cout << i << endl;
        if(print){
            output << i << endl;
            for(auto li : grid){output << li << endl;}
            output << endl;
            print = false;
        }
        
    }

    output.close();
    return 0;
}