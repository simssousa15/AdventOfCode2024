#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>

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

    auto grid = text;
    vector<vector<int>> t;

    int init_i, init_j;
    int end_i, end_j;
    for(int i = 0; i < grid.size(); i++){
        vector<int> tmp;
        for(int j = 0; j < grid[i].size(); j++){
            tmp.push_back(-1);
            if(grid[i][j] == 'S'){ 
                init_i = i;
                init_j = j;
            }else if(grid[i][j] == 'E'){
                end_i = i;
                end_j = j;
                grid[i][j] = '.';
            }
        }
        t.push_back(tmp);
    }

    vector<pair<int, int>> dirs = {
        {0, 1},
        {0, -1},
        {-1, 0},
        {1, 0},
    };

    int i = init_i;
    int j = init_j;

    int cnt = 0;
    while(true){
        grid[i][j] = 'x';
        t[i][j] = cnt++;
        if(i == end_i && j == end_j){ break; }

        
        for(auto [di, dj] : dirs){
            if(grid[i+di][j+dj] == '.'){
                i += di;
                j += dj;
                break;
            }
        }
    }

    /* for(auto vec : t){
        for(auto pic : vec){
            cout << "|" << pic << "|";
        }
        cout << endl;
    } */

    vector<int> cheats;
    // time_Saved, count
    map<int, int> cheats_print;

    for(int i = 1; i < t.size()-1; i++){
        for(int j = 1; j < t[i].size()-1; j++){
            if(t[i][j] != -1){
                for(int i2 = 1; i2 < t.size()-1; i2++){
                    for(int j2 = 1; j2 < t[i2].size()-1; j2++){
                        int dist = abs(i-i2) + abs(j-j2);
                        if(t[i][j] < t[i2][j2] && dist <= 20){
                            cheats.push_back(t[i2][j2] - t[i][j] - dist);
                            cheats_print[t[i2][j2] - t[i][j] - dist]++;
                        }
                    }
                }
            }
        }
    }

    /* for(auto items : cheats_print){
        cout << items.first << "ps " << items.second << endl;
    } */


    sort(cheats.begin(), cheats.end());
    auto itr = lower_bound(cheats.begin(), cheats.end(), 100);
    cout << cheats.end() - itr << endl;
    

    

    return 0;
}