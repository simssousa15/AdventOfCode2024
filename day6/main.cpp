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

    auto og_text = text;
    //find guard pos
    int gx, gy;
    for(int i = 0; i < text.size(); i++){
        for(int j = 0; j < text[i].size(); j++){
            if(text[i][j] != '.' && text[i][j] != '#'){
                gx = j;
                gy = i; 
            }
        }
    }

    map<char, pair<int, int>> char_to_dir = {
        {'^', {0, -1}},
        {'v', {0, 1}},
        {'>', {1, 0}},
        {'<', {-1, 0}},
    };

    map<char, char> change_dir = {
        {'^', '>'},
        {'>', 'v'},
        {'v', '<'},
        {'<', '^'},
    };

    set<pair<int, int>> unique_pos;
    unique_pos.insert({gy, gx});
    int st_x = gx;
    int st_y = gy;

    while(true){

        auto [dx, dy] = char_to_dir[text[gy][gx]];

        int n_gx = gx + dx;
        if(n_gx < 0 || n_gx >= text[0].size()){ break; }
        int n_gy = gy + dy;
        if(n_gy < 0 || n_gy >= text.size()){ break; }

        if( text[n_gy][n_gx] == '#' ){
            text[gy][gx] = change_dir[text[gy][gx]];
        }else{
            text[n_gy][n_gx] = text[gy][gx];
            text[gy][gx] = '.';

            gx = n_gx;
            gy = n_gy;
            unique_pos.insert({gy, gx});
        }
    }

    int loop_cnt = 0;
    for(auto pos : unique_pos){
        if(pos.second == st_x && pos.first == st_y){ continue; }
        
        text = og_text;
        text[pos.first][pos.second] = 'O';
        gx = st_x;
        gy = st_y;

        /* for(auto l : text){ cout << l << endl; }
        cout << endl; */
        
        // robot_dir, x, y
        set<pair<char, pair<int, int>>>hit_block;
        while(true){            

            auto [dx, dy] = char_to_dir[text[gy][gx]];

            int n_gx = gx + dx;
            if(n_gx < 0 || n_gx >= text[0].size()){ break; }
            int n_gy = gy + dy;
            if(n_gy < 0 || n_gy >= text.size()){ break; }

            if( text[n_gy][n_gx] == '#' || text[n_gy][n_gx] == 'O'){
                
                pair<char, pair<int, int>> hit;
                hit.first = text[gy][gx];
                hit.second.first = gx;
                hit.second.second = gy;

                if(hit_block.find(hit) != hit_block.end()){ 
                    loop_cnt ++; 
                    break; 
                }

                hit_block.insert(hit);
                text[gy][gx] = change_dir[text[gy][gx]];
            }else{
                text[n_gy][n_gx] = text[gy][gx];
                text[gy][gx] = '.';

                gx = n_gx;
                gy = n_gy;
            }
        }
    }

    cout << loop_cnt << endl;

    return 0;
}