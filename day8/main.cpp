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


    unordered_map<char, vector<pair<int, int>>> antenas;

    for(int i = 0; i < text.size(); i++){
        for(int j = 0; j < text[i].length(); j++){
            if(text[i][j] != '.'){ antenas[text[i][j]].push_back({i, j}); }
        }
    }

    /* for(auto at : antenas){
        cout << at.first << endl;
        for(auto loc : at.second){
            cout << loc.first << " " << loc.second << endl;
        }
        cout << endl;
    } */

    set<pair<int, int>> anti;
    for(auto at : antenas){
        for(auto loc1 : at.second){
            for(auto loc2 : at.second){
                if(loc1 == loc2){ continue; }

                auto [y1, x1] = loc1;
                auto [y2, x2] = loc2;
                anti.insert({y1, x1});
                anti.insert({y2, x2});

                int x_diff = x2 - x1;
                int y_diff = y2 - y1;
                int a_x = x2 + x_diff;
                int a_y = y2 + y_diff;

                while(true){
                    if(a_x < 0 || a_x >= text[0].size()){ break; }
                    if(a_y < 0 || a_y >= text.size()){ break; }

                    anti.insert({a_y, a_x});
                    a_x += x_diff;
                    a_y += y_diff;
                }

                x_diff = x1 - x2;
                y_diff = y1 - y2;
                a_x = x1 + x_diff;
                a_y = y1 + y_diff;

                while(true){
                    if(a_x < 0 || a_x >= text[0].size()){ break; }
                    if(a_y < 0 || a_y >= text.size()){ break; }

                    anti.insert({a_y, a_x});
                    a_x += x_diff;
                    a_y += y_diff;
                }

            }
        }
    }

    cout << "Total Antinodes: " << anti.size() << endl;

    return 0;
}