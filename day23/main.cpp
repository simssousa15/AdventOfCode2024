#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

/* struct Three{
    string pc1, pc2, pc3;
    Three(string pc1, string pc2, string pc3) : pc1(pc1), pc2(pc2), pc3(pc3) {}
};

bool operator==(const Three A, const Three B){
    if(A.pc1 == B.pc1 || A.pc1 == B.pc2 || A.pc1 == B.pc3){
        if(A.pc2 == B.pc1 || A.pc2 == B.pc2 || A.pc2 == B.pc3){
            if(A.pc3 == B.pc1 || A.pc3 == B.pc2 || A.pc3 == B.pc3){
                return true;
            }
        }
    }

    return false;
}

struct  ThreeHasher
{
    size_t operator()const
}; */



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
    
    unordered_map<string, set<string>> og;
    for(auto l : text){
        og[l.substr(0,2)].insert(l.substr(3,2));
        og[l.substr(3,2)].insert(l.substr(0,2));
    }

    /* set<string> three_way;
    for(auto [pc1, cnect1] : og){
        for(auto pc2 : og[pc1]){
            for(auto pc3 : og[pc2]){
                for(auto pc4 : og[pc3]){
                    if(pc4 == pc1){
                        vector<string> tmp = {pc1, pc2, pc3};
                        sort(tmp.begin(), tmp.end());
                        three_way.insert(tmp[0]+","+tmp[1]+","+tmp[2]);
                    }
                }
            }
        }
    }

    cout << three_way.size() << endl;
    
    int t_cnt = 0;
    for(auto l : three_way){ 
        if( l[0] == 't' || l[3] == 't' || l[6] == 't' ){
            t_cnt ++;
        }
    } */

    queue<vector<string>> q;
    for(auto item : og){
        vector<string>tmp;
        tmp.push_back(item.first);
        q.push(tmp);
    }

    set<string> visited;
    int max_sz = 0;
    vector<string> max_vec;
    while(!q.empty()){
        auto pcs = q.front();
        q.pop();
        
        if(q.size()%10000 == 0){ cout << q.size() << endl; }

        if(pcs.size() > max_sz){ 
            max_sz = pcs.size();
            max_vec = pcs;
            cout << "Size: " << max_sz << endl;
            for( auto p : pcs ){ cout << p << " "; }
            cout << endl;
        }


        for(auto [n_pc, _] : og){
            bool ok = true;
            for(auto p : pcs){
                if(og[p].find(n_pc) == og[p].end()){
                    ok = false;
                    break;
                }
            }
            if(ok){
                auto tmp = pcs;
                tmp.push_back(n_pc);
                sort(tmp.begin(), tmp.end());

                string k = "";
                for(auto t : tmp){
                    k += t + ",";
                }

                if(visited.find(k) == visited.end()){
                    visited.insert(k);
                    q.push(tmp);
                }
            }
        }
    }
    
    //sort(max_vec.begin(), max_vec.end());

    cout << "##########################" << endl;
    cout << "Password: " << endl;
    for(auto pc : max_vec){ cout << pc << ","; }
    cout << endl;
    cout << "##########################" << endl;

    /* set<string> three_way;
    for(auto [pc1, cnect1] : cnect){
        for(auto pc2 : cnect[pc1]){
            for(auto pc3 : cnect[pc2]){
                for(auto pc4 : cnect[pc3]){
                    if(pc4 == pc1){
                        vector<string> tmp = {pc1, pc2, pc3};
                        sort(tmp.begin(), tmp.end());
                        three_way.insert(tmp[0]+","+tmp[1]+","+tmp[2]);
                    }
                }
            }
        }
    }

    cout << three_way.size() << endl;
    
    int t_cnt = 0;
    for(auto l : three_way){ 
        if( l[0] == 't' || l[3] == 't' || l[6] == 't' ){
            t_cnt ++;
        }
    }


    cout << t_cnt << endl; */


    return 0;
}