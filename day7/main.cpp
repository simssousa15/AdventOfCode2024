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

    long long sum = 0;
    for(auto l : text){
        long long res = stoll(l.substr(0, l.find(':')));
        // cout << res << ": ";
        l = l.substr(l.find(' ')+1);

        vector<long long> num;
        while(!l.empty()){
            num.push_back(stoll(l.substr(0, l.find(' '))));
            // cout << *num.rbegin() << " ";
            l = l.substr(l.find(' ')+1);
            if(l.find(' ') == string::npos){ break; }
            
        }
        num.push_back(stoll(l));
        // cout << *num.rbegin() << " ";
        // cout << endl;

        // idx, total
        queue<pair<int, long long>> q;
        q.push({0, num[0]});

        bool pos = false;
        while(!q.empty()){
            auto [idx, total] = q.front();
            // cout << idx << " " << total << endl;
            q.pop();
            
            // #############################################
            // possible to check before adding to queue
            if(total == res && idx == num.size() - 1){ pos = true; break; }
            idx++;
            if(idx == num.size()){ continue; }
            // #############################################

            q.push({idx, total+num[idx]});
            q.push({idx, total*num[idx]});
            q.push({idx, stoll(to_string(total)+to_string(num[idx]))});
        }   

        if(pos){ sum += res; }
    }
    
    cout << sum << endl;

    return 0;
}