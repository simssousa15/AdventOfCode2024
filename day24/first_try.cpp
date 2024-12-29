#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

vector<unordered_set<int>> combinations_4pairs (int size){

    vector<unordered_set<int>> comb;
    for(int i = 0; i < size; i++){
        unordered_set<int> tmp;
        tmp.insert(i);
        comb.push_back(tmp);
    }

    while(comb[0].size() < 8){
        cout << comb[0].size() << " " << comb.size() << endl;
        vector<unordered_set<int>> new_comb;
        for(auto c : comb){
            for(int i = 0; i < size; i++){
                auto tmp = c;
                if( tmp.find(i) == tmp.end() ){
                    tmp.insert(i);
                    new_comb.push_back(tmp);
                }
            }
        }
        comb = new_comb;
    }

    return comb;
}

struct Operation{
    string el1, el2, op, ans;
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

    map<string, bool> wires;
    
    int i = 0;
    for(auto l : text){
        if(l.length() < 5){ break; }
        wires[l.substr(0,3)] = l[5] - '0';
        i++;
    }

    // find z
    long long x = 0;
    long long y = 0;
    for(int i = 0; i < wires.size() / 2; i++){
        string num = to_string(i);
        if(num.length() == 1){ num = "0" + num; }

        if(wires["x" + num]){ x += pow(2, i); }
        if(wires["y" + num]){ y += pow(2, i); }
    }

    vector<Operation> vec;

    for(int j = i+1; j < text.size(); j++){
        Operation op;
        auto  l = text[j];

        op.el1 = l.substr(0,3);
        l = l.substr(4);
        op.op = l.substr(0, l.find(' '));
        l = l.substr(l.find(' ')+1);
        op.el2 = l.substr(0,3);
        op.ans = l.substr(7,3);

        vec.push_back(op);
    }

    
    queue<Operation>q;
    while(!q.empty()){
        auto op = q.front();
        q.pop();

        if(wires.find(op.el1) != wires.end()
        && wires.find(op.el2) != wires.end() ){
            if(op.op == "AND"){
                wires[op.ans] = wires[op.el1] && wires[op.el2];
            }else if(op.op == "XOR"){
                wires[op.ans] = wires[op.el1] != wires[op.el2];
            }else if(op.op == "OR"){
                wires[op.ans] = wires[op.el1] || wires[op.el2];
            }else{
                cout << "Unrecognized operation: " << op.op << endl;
            }

            // cout << wires[op.el1] << " " << op.op << " " << wires[op.el2] << " = " << wires[op.ans]<< endl;
        }else{
            q.push(op);
        }
    }

    long long dec = 0;
    for(auto item : wires){
        // cout << item.first << ": " << item.second << endl;
        if(item.first[0] == 'z' && item.second){
            dec += pow(2, stoll(item.first.substr(1,2)));
        }
    }

    cout << dec << endl;

    return 0;
}