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

    vector<long long> reg;

    for(int i = 0; i < 3; i++){
        reg.push_back(stoll(text[i].substr(text[i].find(':')+1)));

        cout << *reg.rbegin() << " ";
    }
    cout << endl;

    vector<int>prog;

    string lin = text[4];
    lin = lin.substr(lin.find(':')+2);

    for(int i = 0; i < lin.length(); i+=2){
        prog.push_back(lin[i]-'0');
        cout << *prog.rbegin() << " ";
    }
    cout << endl;


    long long a = 0;
    while(true){

        if(a % 10000000 == 0){cout << a << endl;}

        reg[0] = a++;
        int out_idx = 0;

        int idx = 0;
        bool done = false;
        do{
            int lit = prog[idx+1];
            int combo = lit;
            if(combo > 3){
                combo = reg[combo%4];
            }

            switch (prog[idx])
            {
            case 0:
                reg[0] /= pow(2, combo);
                break;
            case 1:
                reg[1] ^= lit;
                break;
            case 2:
                reg[1] = combo%8;
                break;
            case 3:
                if(reg[0] != 0){ idx = lit; idx-=2;}
                break;
            case 4:
                reg[1] ^= reg[2];
                break;
            case 5:
                if(out_idx >= prog.size()){
                    cout << "Maybe ans: " << a-1 << endl;
                    done = true;
                }
                else{
                    if(prog[out_idx++] != combo%8){
                        done = true;
                    }
                }
                
                break;
            case 6:
                reg[1] = reg[0] / pow(2, combo);
                break;
            case 7:
                reg[2] = reg[0] / pow(2, combo);
                break;
            default:
                cout << "command not recognized" << endl;
                break;
            }

            idx+=2;
        }while(idx < prog.size() && !done);

        if(!done && out_idx == prog.size()){
            cout << "Ans: " << a - 1 << endl;
            break; 
        }
    }

    return 0;
}

// 720000000
// 2147483647