#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

#define BLINKS 75

int main()
{

    ifstream inputFile("large.txt");
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
    
    vector<pair<int, int>> dirs = {
        {0, 1},
        {1, 0},
        {-1, 0},
        {0, -1}
    };
    
    // vert and hori fences
    map<char, vector<pair<int,int>>> h_fences;
    map<char, vector<pair<int,int>>> v_fences; 

    map<char, int> area;

    for(int i = 0; i < text.size(); i++){
        for(int j = 0; j < text[0].size(); j++){

            area[text[i][j]]++;

            for(auto [di, dj] : dirs){
                bool block = false;
                if(i+di < 0 || i+di >= text.size()){
                    block = true;
                }
                else if(j+dj < 0 || j+dj >= text[0].size()){ 
                    block = true;
                }
                else if(text[i][j] != text[i+di][j+dj]){
                    block = true;
                }

                if(block){
                    if(di == 0){
                        if( dj < 0 ){
                            v_fences[text[i][j]].push_back({i, j});
                        }else{
                            v_fences[text[i][j]].push_back({i, j+1});
                        }
                    }else{
                        if( di < 0 ){
                            h_fences[text[i][j]].push_back({i, j});
                        }else{
                            h_fences[text[i][j]].push_back({i+1, j});
                        }
                    }
                }
            }
        }
    }

    for(auto l : text){
        cout << l << endl;
    }

    long price = 0;
    cout << "Fences" << endl;
    for(auto item : h_fences){
        cout << item.first << endl;
        cout << "area: " << area[item.first] << endl;
        cout << "vertical: " << v_fences[item.first].size() << endl;
        cout << "horizontal: " << h_fences[item.first].size() << endl;

        price += area[item.first] * (v_fences[item.first].size() + h_fences[item.first].size());
    }
    cout << "Price: " << price << endl;
    cout << "################" << endl;

    map<char, int> h;
    map<char, int> v;
    
    for(auto it : h_fences){
        
        auto fences = h_fences[it.first];
        h[it.first] = fences.size();
        for(int i = 0; i < fences.size(); i++){
            for(int j = i+1; j < fences.size(); j++ ){
                if(
                    fences[i].first == fences[j].first
                    && abs(fences[i].second - fences[j].second) == 1
                )
                h[it.first]--;
            }
        }

        fences = v_fences[it.first];
        v[it.first] = fences.size();
        for(int i = 0; i < fences.size(); i++){
            for(int j = i+1; j < fences.size(); j++ ){
                if(
                    fences[i].second == fences[j].second
                    && abs(fences[i].first - fences[j].first) == 1
                )
                v[it.first]--;
            }
        }


    }

    price = 0;
    cout << "Connected Fences" << endl;
    for(auto item : h){
        cout << item.first << endl;
        cout << "area: " << area[item.first] << endl;
        cout << "vertical: " << v[item.first] << endl;
        cout << "horizontal: " << h[item.first] << endl;

        price += area[item.first] * (v[item.first] + h[item.first]);
    }
    cout << "Price with bulk discount: " << price << endl;

    return 0;
}