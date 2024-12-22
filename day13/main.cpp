#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>

#define GRID_SIZE 71
#define FALLEN_BYTES 1024
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
    for(int i = 0; i < text.size(); i++){
        
        auto l = text[i];

        l = l.substr(l.find('+')+1);
        long long ax = stol(l.substr(0, l.find(',')));
        l = l.substr(l.find('+')+1);
        long long ay = stol(l);

        l = text[++i];
        l = l.substr(l.find('+')+1);
        long long bx = stol(l.substr(0, l.find(',')));
        l = l.substr(l.find('+')+1);
        long long by = stol(l);

        l = text[++i];
        l = l.substr(l.find('=')+1);
        long long px = stoll(l.substr(0, l.find(',')));
        l = l.substr(l.find('=')+1);
        long long py = stoll(l);
        px += 10000000000000;
        py += 10000000000000;

        i++;

        cout << "A " << ax << ' ' << ay << endl;
        cout << "B " << bx << ' ' << by << endl;
        cout << "P "<< px << ' ' << py << endl;

        long long area_ab = ax*by - ay*bx;
        cout << "AB " << area_ab << endl;
        long long area_ap = ax*py - ay*px;
        cout << "AP " << area_ap << endl;
        long long area_pb = px*by - py*bx;
        cout << "PB " << area_pb << endl;

        long long la = area_pb / area_ab;
        if(area_pb % area_ab != 0){ la = -1; }
        cout << "La " << la << endl;
        long long lb = area_ap / area_ab;
        if(area_ap % area_ab != 0){ lb = -1; }
        cout << "Lb " << lb << endl;
        cout << endl;

        if(la != -1 & lb != - 1){
            sum += la*3 + lb;
        }
    }

    cout << "Cost: " << sum << endl;

    return 0;
}


// 10000000000000
// 2147483647
// 9,223,372,036,854,775,807