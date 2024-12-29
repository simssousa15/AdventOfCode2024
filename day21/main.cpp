#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

#define ROBOT_KEYPADS 25
#define FILE_NAME "real.txt"

map<char, pair<int, int>> num_keyboard = {
    {'A', {0, 0}},
    {'0', {1, 0}},
    {'1', {2, 1}},
    {'2', {1, 1}},
    {'3', {0, 1}},
    {'4', {2, 2}},
    {'5', {1, 2}},
    {'6', {0, 2}},
    {'7', {2, 3}},
    {'8', {1, 3}},
    {'9', {0, 3}},
};

map<char, pair<int, int>> dir_keyboard = {
    {'A', {0, 0}},
    {'^', {1, 0}},
    {'<', {2, -1}},
    {'v', {1, -1}},
    {'>', {0, -1}},
};

vector<string> permuteRec(string& s, int idx)
{
    vector<string> perm;
    // Base case
    if (idx == s.size() - 1) {
        perm.push_back(s);
        return perm;
    }

    for (int i = idx; i < s.size(); i++) {
        // Swapping 
        swap(s[idx], s[i]);

        // First idx+1 characters fixed
        for(auto p : permuteRec(s, idx + 1)){
            perm.push_back(p);
        }

        // Backtrack
        swap(s[idx], s[i]);
    }

    //remove equals
    vector<string> fin;
    for(auto p : perm){
        if(find(fin.begin(), fin.end(), p) == fin.end()){
            fin.push_back(p);
        }
    }

    return fin;
}

vector<string> directions(int di, int dj, int i, int j){
    vector<string> ops;

    char c_v = dj < 0 ? 'v' : '^';
    char c_h = di < 0 ? '>' : '<';
    
    string i1="";

    for(int i = 0; i < abs(di); i++){ i1 += c_h; }
    for(int i = 0; i < abs(dj); i++){ i1 += c_v; }

    ops = permuteRec(i1, 0);
    
    map<char, pair<int, int>> char_to_dir = {
        {'>', {-1, 0}},
        {'<', {1, 0}},
        {'^', {0, 1}},
        {'v', {0, -1}}
    };
    
    auto new_ops = ops;
    new_ops.clear();

    for(auto op : ops){
        int tmp_i = i;
        int tmp_j = j;

        bool poss = true;
        for(char c : op){
            auto [di, dj] = char_to_dir[c];
            
            tmp_i += di;
            tmp_j += dj;

            if(tmp_i == 2 && tmp_j == 0){ 
                poss = false;
                // cout << "impossible" << endl;
                break;
            }
        }

        if(poss){ new_ops.push_back(op); }
    }

    ops = new_ops;

    for(auto &op : ops){
        op += 'A';
    }
    if(ops.empty()){ ops.push_back("A"); }

    return ops;
}

class CachedEval{

    public:
        map<pair<string, int>, long long> cache;

        long long eval(string instr, int depth=0){

            if(cache.find({instr, depth}) != cache.end()){
                return cache[{instr, depth}];
            }

            if(depth == 0){
                cache[{instr, depth}] = instr.length();
                return instr.length();
            }

            auto [i, j] = dir_keyboard['A'];

            long long cost = 0;
            for(char c : instr){
                auto [dest_i, dest_j] = dir_keyboard[c];
                int di = dest_i - i;
                int dj = dest_j - j;

                auto ops = directions(di, dj, i, j);

                long long min_cost = LONG_LONG_MAX;
                for(auto op : ops){
                    long long new_cost = eval(op, depth-1);
                    if(new_cost < min_cost){
                        min_cost = new_cost;
                    }
                }
                cost += min_cost;

                i = dest_i;
                j = dest_j;
            }

            // cout << depth << " Cost: " << cost << endl;
            cache[{instr, depth}] = cost;
            return cost;
        }
};

int main()
{

    ifstream inputFile(FILE_NAME);
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

    //first convertion
    vector<string> first;
    long long complexity = 0;
    for( auto code : text ){
        if(code.length() > 4){ code = code.substr(0, 4); }
        cout << code << endl;

        vector<string> inputs;
        inputs.push_back("");
        int i, j;
        auto pos = num_keyboard['A'];
        i = pos.first;
        j = pos.second; 
        for(auto c : code){
            vector<string> nxt;
            auto[dest_i, dest_j] = num_keyboard[c];

            int di = dest_i - i;
            int dj = dest_j - j;

            auto ops = directions(di, dj, i, j);
            for(auto o : ops){
                for(auto inp : inputs){
                    nxt.push_back(inp + o);
                }
            }
            i = dest_i;
            j = dest_j;

            inputs = nxt;
        }

        // remove larger
        int minimum = INT_MAX;
        for(auto inp : inputs){
            if(minimum > inp.length()){
                minimum = inp.length();
            }
        }
        vector<string> new_inputs;
        for(auto inp : inputs){
            if(minimum == inp.length()){
                new_inputs.push_back(inp);
            }
        }
        // #################
        // cout << "First itr: " << new_inputs[0].size() << endl;
        // cout << "First ops: " << new_inputs.size() << endl;

        CachedEval ce;
        long long min_cost = LONG_LONG_MAX;
        for(auto instr : new_inputs){
            // cout << instr << endl;
            long long cost = ce.eval(instr, 25);
            // cout << endl;
            if(cost < min_cost){ 
                min_cost = cost;
                // cout << cost << endl;
            }
        }
        cout << "Final Cost: " << min_cost << endl;
        complexity += min_cost * stoll(code.substr(0, 3));

    }
    
    cout << "Complexity: " << complexity << endl;

    return 0;
}


/*
029A

v<<A>>^A<A>AvA<^AA>A<vAAA>^A

<A^A>^^AvvvA
<v<Av<<AA<AAvA<A<AA<vAv<A<vAv<A<vAv<AA

*/