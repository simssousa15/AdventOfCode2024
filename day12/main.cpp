#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

#define BLINKS 75

struct Fence{
    int i, j;
    bool side;
    Fence(int i, int j, bool side): i(i), j(j), side(side){}

    // Overloading the equality operator (==)
    bool operator==(const Fence& other) const {
        return i == other.i && j == other.j && side == other.side;
    }

    // Overloading the less-than operator (<)
    bool operator<(const Fence& other) const {
        if (i != other.i) return i < other.i;
        return j < other.j;
    }
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
    
    vector<pair<int, int>> dirs = {
        {0, 1},
        {1, 0},
        {-1, 0},
        {0, -1}
    };
    
    // vert and hori fences
    int total = 0;
    for(int i = 0; i < text.size(); i++){
        for(int j = 0; j < text[0].size(); j++){
            
            if( !isalpha(text[i][j]) ){ continue; }

            queue<pair<int, int>> q;
            q.push(make_pair(i, j));

            char c = text[i][j];
            set<Fence> v_fences;
            set<Fence> h_fences;

            set<pair<int, int>> visited;
            while(!q.empty()){

                auto [_i_, _j_] = q.front();
                q.pop();
                visited.insert(make_pair(_i_, _j_));

                // cout << _i_ << " " << _j_ << " " << text[_i_][_j_] << endl;

                for(auto [di, dj] : dirs){
                    bool block = false;
                    if(_i_+di < 0 || _i_+di >= text.size()){
                        block = true;
                    }
                    else if(_j_+dj < 0 || _j_+dj >= text[0].size()){ 
                        block = true;
                    }
                    else if(c != text[_i_+di][_j_+dj] && visited.find(make_pair(_i_+di, _j_+dj)) == visited.end()){
                        block = true;
                    }else if (visited.find(make_pair(_i_+di, _j_+dj)) == visited.end()) {
                        q.push(make_pair(_i_+di, _j_+dj));
                    }

                    if(block){
                        if(di == 0){
                            if( dj < 0 ){
                                v_fences.insert(Fence(_i_, _j_, true));
                            }else{
                                v_fences.insert(Fence(_i_, _j_+1, false));
                            }
                        }else{
                            if( di < 0 ){
                                h_fences.insert(Fence(_i_, _j_, true));
                            }else{
                                h_fences.insert(Fence(_i_+1, _j_, false));
                            }
                        }
                    }
                }
                
                text[_i_][_j_] = '0';
            }

            int h = h_fences.size();
            // cout << "H" << endl;
            for(auto itr1 = h_fences.begin(); itr1 != h_fences.end(); itr1++){
                // cout << itr1->i <<  " " << itr1->j << endl;
                for(auto itr2 = itr1; itr2 != h_fences.end(); ++itr2){
                    if(
                        itr2->i == itr1->i
                        && abs(itr2->j - itr1->j) == 1
                        && itr1->side == itr2->side
                    )
                    h--;
                }
            }

            int v = v_fences.size();
            // cout << "V" << endl;
            for(auto itr1 = v_fences.begin(); itr1 != v_fences.end(); itr1++){
                // cout << itr1->i <<  " " << itr1->j << endl;
                for(auto itr2 = itr1; itr2 != v_fences.end(); ++itr2){
                    if(
                        itr1->j == itr2->j
                        && abs(itr1->i - itr2->i) == 1
                        && itr1->side == itr2->side
                    )
                    v--;
                }
            }
            total += visited.size()*(v+h);
            cout << c << " " << visited.size() << " * " << v + h << " = " << visited.size()*(v+h) << endl; 
        }
    }

    cout << "Total: " << total << endl;



    return 0;


    /* for(auto l : text){
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
    
    for(auto it : h_fences){}

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
    */

    return 0;
}