#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>

#define ITER 2000
using namespace std;


long long nxt_sec (long long n){
    long long ans = n;
    ans = ((ans*64) ^ ans) % 16777216;
    ans = ((ans/32) ^ ans) % 16777216;
    ans = ((ans*2048) ^ ans) % 16777216;
    return ans;
}

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
    
    vector<long long> nums;
    for(auto l : text){ nums.push_back(stol(l)); }


    
    map<string, int> total_buy;

    for( auto n : nums){
        map<string, int> buy;
        vector<int> changes;
        auto sec = n;
        int price = sec % 10;
        int last_price = sec % 10;

        for(int i = 0; i < ITER; i++){
            /* cout << sec << ": " << price;
            if(i!=0){ cout << " (" << *changes.rbegin() << ")"; }
            cout << endl;
            */

            sec = nxt_sec(sec);
            price = sec % 10;
            changes.push_back(price - last_price);

            if(changes.size() > 4){ changes.erase(changes.begin()); }
            if(changes.size() == 4){
                string k = "";
                for(auto c : changes){ k+=to_string(c);}

                if(buy.find(k) == buy.end()){
                    buy[k] = price;
                }
            }

            last_price = price;
        }
        
        for(auto it : buy){
            total_buy[it.first] += it.second;
        }
    }

    long maxi = 0;
    for(auto item : total_buy){
        if(item.second > maxi){
            maxi = item.second;
        }
    }

    cout << "Max bananas: " << maxi << endl;

    return 0;
}