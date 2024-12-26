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

    vector<vector<int>> locks;
    vector<vector<int>> keys;
    
    for(int i = 0; i < text.size(); i+=8){
        if(text[i][0] == '#'){

            vector<int> l;
            cout << "Lock: ";
            for(int j = 0; j < text[i].length(); j++){
                int itr = 1;
                while(text[i + itr][j] == '#'){
                    itr ++;
                }
                l.push_back(itr-1);
                cout << itr - 1 << ", ";
            }
            cout << endl;
            locks.push_back(l);

        }else if(text[i][0] == '.'){
            
            vector<int> k;
            cout << "Key: ";
            for(int j = 0; j < text[i].length(); j++){
                int itr = 1;
                while(text[i + itr][j] == '.'){
                    itr ++;
                }
                k.push_back(5 - (itr - 1));
                cout << 5 - (itr - 1) << ", ";
            }
            cout << endl;
            keys.push_back(k);
        }else{
            cout << "Unrecognized if key or lock" << endl;
        }
    }

    int total = 0;
    for(auto l : locks){
        for(auto k : keys){
            bool overlap = false;
            for(int i = 0; i < k.size(); i++){
                if( k[i] + l[i] > 5){
                    overlap	= true;
                }
            }
            if(!overlap){ total++; }
        }
    }

    cout << total << endl;

    return 0;
}