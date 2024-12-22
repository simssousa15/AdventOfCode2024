#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

#define BLINKS 75

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
    while(line.find(' ') != string::npos){; 
        nums.push_back(stoll(line.substr(0, line.find(' '))));
        line = line.substr(line.find(' ')+1);
        
    }
    nums.push_back(stoll(line));
    
    for(auto n : nums){ cout << n << " "; }
    cout << endl;

    // num, cnt
    map<long long, long long> itr_map;
    for(auto n : nums){ itr_map[n]++; }

    for(int i = 0; i < BLINKS; i++){
        map<long long, long long> tmp;
        for(auto [num, cnt] : itr_map){
            if(num == 0){ 
                tmp[1] += cnt;
            }
            else if( to_string(num).length()%2 == 0){
                string n1 = to_string(num).substr(0, to_string(num).length()/2);
                string n2 = to_string(num).substr(to_string(num).length()/2);
                tmp[stoll(n1)] += cnt;
                tmp[stoll(n2)] += cnt;
            }else{
                tmp[num*2024] += cnt;
            }
        }
        itr_map = tmp;
    }

    long long total = 0;
    for(auto item : itr_map){ total += item.second; }

    cout << total << endl;
    
    return 0;
}