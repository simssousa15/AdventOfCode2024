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

    vector<string> designs;

    line = text[0];
    while(true){
        designs.push_back(line.substr(0, line.find(',')));
        if(line.find(' ') == string::npos){ break; }
        line = line.substr(line.find(' ')+1);
    }
    
    /* for(auto d : designs){ if(d.size() == 0){ cout << d.size() << " "; } }
    cout << endl;
    return 0; */

    long long sum = 0;
    for(int i = 2; i < text.size(); i++){
        auto pat = text[i];
        cout << pat << endl;

        priority_queue<string, vector<string>, greater<string>> q;
        // size, pattern, count
        map<int, map<string, long long>> checked;
        q.push("");
        checked[0][""]++;

        while(!q.empty()){
            // cout << q.size() << endl;
            auto n = q.top();
            q.pop();
            // cout << n << endl;

            if(n == pat){ continue; }

            for( auto d : designs ){
                string temp = n + d;

                if(temp.length() > pat.length()){continue;}
                
                if(temp == pat.substr(0, temp.length())){
                    if(checked[temp.size()][temp] == 0){
                        q.push(temp);
                    }
                    checked[temp.size()][temp] += checked[n.size()][n];
                    if(checked[temp.size()][temp] < 0 ){ cout << "BOOM!" << endl; }
                }
            }
        }

        // cout << checked[pat.size()][pat] << endl;
        sum += checked[pat.size()][pat];
    }

    cout << sum << endl;

    return 0;
}