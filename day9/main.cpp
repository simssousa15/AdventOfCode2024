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


    vector<pair<int, int>> blocks;
    int id = 0;
    for(int i = 0; i < text[0].length(); i++){
        if(i%2==0){
            blocks.push_back({id++, text[0][i]-'0'});
        }else{
            blocks.push_back({-1, text[0][i]-'0'});
        }
    }

    /* for(auto b : blocks){
        cout << "[" << b.first << "," << b.second << "] ";
    }
    cout << endl;

    return 0; */

    int free_idx;
    int mem_idx = blocks.size();
    while(blocks[--mem_idx].first == -1){}
    /* cout << mem_idx << endl; */


    while(true){
        free_idx = -1;
        while(true){
            if(++free_idx == blocks.size()){ break; }
            if(blocks[free_idx].first == -1 && blocks[free_idx].second >= blocks[mem_idx].second){
                break;
            }
        }
        
        if(free_idx < mem_idx){ 
            if(blocks[free_idx].second == blocks[mem_idx].second){ 
            blocks[free_idx].first = blocks[mem_idx].first;
            }else{
                auto mem_block = blocks[mem_idx];
                blocks.insert(blocks.begin()+free_idx, mem_block);
                blocks[free_idx+1].second -= mem_block.second;
                mem_idx++;
            }
            blocks[mem_idx].first = -1;

            /* for(auto b : blocks){
            cout << "[" << b.first << "," << b.second << "] ";
            }
            cout << endl; */
        }
        
        while(--mem_idx >= 0 && blocks[mem_idx].first == -1){}
        if(mem_idx < 0){ break; }
    }
    

    int idx = 0;
    long long checksum = 0;
    for(auto b : blocks){
        if(b.first != -1){ 
            for(int i = idx; i < idx+b.second; i++ ){
                checksum += i*b.first;
            }
        }

        idx += b.second;
    }

    cout << checksum << endl;
    
    return 0;
}