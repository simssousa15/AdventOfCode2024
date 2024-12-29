#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

#define ROBOT_KEYPADS 75
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

/* vector<string> directions(int di, int dj, int j){
    vector<string> ops;

    char c_v = dj < 0 ? 'v' : '^';
    char c_h = di < 0 ? '>' : '<';
    
    string i1="";
    string i2="";

    for(int i = 0; i < abs(di); i++){ i1 += c_h; }
    for(int i = 0; i < abs(dj); i++){ i1 += c_v; }
    
    for(int i = 0; i < abs(dj); i++){ i2 += c_v; }
    for(int i = 0; i < abs(di); i++){ i2 += c_h; }

    i1 += 'A';
    i2 += 'A';

    if(j != 0 && j+dj != 0){
        ops.push_back(i1);
        ops.push_back(i2);
    }else if(j == 0){
        ops.push_back(i2);   
    }else{
        ops.push_back(i1);
    }

    return ops;
}

 */

string decompose(string move){
    
    string ans = "";
    int i = 0, j = 0;

    for(char c : move){
        vector<string> nxt;
        auto[dest_i, dest_j] = dir_keyboard[c];

        int di = dest_i - i;
        int dj = dest_j - j;

        auto ops = directions(di, dj, i, j);
        ans += ops[0];

        i = dest_i;
        j = dest_j;
    }

    return ans;
}

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

    map<string, string> dir_combinations = {{"A", "A"}};
    vector<char> char_dirs = {'<', '>', '^', 'v'};
    
    string move = "";
    for(auto c1 : char_dirs){
        move = c1; move += "A";
        dir_combinations[move] = decompose(move);
        for(auto c2 : char_dirs){
            move = c1; move += c2; move += "A";
            dir_combinations[move] = decompose(move);
            for(auto c3 : char_dirs){
                move = c1; move += c2; move += c3; move += "A";
                dir_combinations[move] = decompose(move);
            }
        }
    }

    /* cout << dir_combinations.size() << endl;
    for(auto item : dir_combinations){
        cout << item.first << " : " << item.second << endl;
    }
    cout << endl;
    return 0;*/

    int sum = 0;
    for(auto &code : text){
        
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
        // cout << inputs.size() << endl;
        cout << inputs[0].size() << endl;

        for(int _ = 0; _<2; _++){
            vector<string> new_inputs;
            auto pos2 = dir_keyboard['A'];
            i = pos2.first;
            j = pos2.second;
            for(auto inp : inputs){
                vector<string> nxt_inps;
                nxt_inps.push_back("");
                for(auto c : inp){
                    vector<string> nxt;
                    auto[dest_i, dest_j] =  dir_keyboard[c];

                    int di = dest_i - i;
                    int dj = dest_j - j;

                    auto ops = directions(di, dj, i, j);
                    for(auto o : ops){
                        for(auto i_ : nxt_inps){
                            nxt.push_back(i_ + o);
                        }
                    }
                    i = dest_i;
                    j = dest_j;

                    nxt_inps = nxt;
                }
                for(auto nxt : nxt_inps){
                    new_inputs.push_back(nxt);
                }
            }
            inputs = new_inputs;

            // remove larger
            int minimum = INT_MAX; 
            for(auto inp : inputs){
                if(minimum > inp.length()){
                    minimum = inp.length();
                }
            }
            new_inputs.clear();
            for(auto inp : inputs){
                if(minimum == inp.length()){
                    new_inputs.push_back(inp);
                }
            }

            //store changes made
            inputs = new_inputs;

            // cout << inputs.size() << endl;
            cout << inputs[0].size() << endl;

        }

        string ans = inputs[0];
        for(int _ = 2; _<ROBOT_KEYPADS; _++){
            string new_ans = "";
            string tmp = "";
            for(char c : ans){
                tmp += c;
                if(c == 'A'){
                    if(dir_combinations.find(tmp) == dir_combinations.end()){ cout << "BOOM!" << endl;}
                    new_ans += dir_combinations[tmp];
                    tmp = "";
                }
            }
            ans = new_ans;
            cout << "iter: " << _ << " " << ans.size() << endl;
        }

        int complexity = stoi(code.substr(0, 3)) * ans.length();
        sum += complexity;
        cout << "Complexity: " << ans.length() << " * " << stoi(code.substr(0, 3)) << endl;
        

        cout << "##################################" << endl;
    }

    cout << "Total: " << sum << endl;

    return 0;
}



// high: 126384

/*
029A: 
<vA<AA>>^AvAA<^A>A<v<A>>^AvA^A<vA>^A<v<A>^A>AAvA^A<v<A>A>^AAAvA<^A>A


980A: 
<v<A>>^AAAvA^A<vA<AA>>^AvAA<^A>A<v<A>A>^AAAvA<^A>A<vA>^A<A>A
v<<A>>^AAAvA^Av<A<AA>>^AAvAA^<A>Av<A>^Av<<A>>^AAAvA^<A>Av<A>^A<A>A


179A: 
<v<A>>^A<vA<A>>^AAvAA<^A>A<v<A>>^AAvA^A<vA>^AA<A>A<v<A>A>^AAAvA<^A>A


456A: 
<v<A>>^AA<vA<A>>^AAvAA<^A>A<vA>^A<A>A<vA>^A<A>A<v<A>A>^AAvA<^A>A








379A:
A<AAv<AA>>^AvAA^Av<AAA>^A

^A<vA<AA>>^AAvA<^A>AAvA^A<vA>^AA<A>A<v<A>A>^AAAvA<^A>A
^Av<<A>>^AAv<A<A>>^AAvAA^<A>Av<A>^AA<A>Av<A<A>>^AAAvA^<A>A

^A^^<<A>>AvvvA
<A>A<AAv<AA>>^AvAA^Av<AAA>^A


*/