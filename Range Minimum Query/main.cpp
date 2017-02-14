//
//  main.cpp
//  RMQ
//
//  Created by Albastroiu Radu on 10/2/16.
//  Copyright © 2016 Albastroiu Radu. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;

ifstream fin("rmq.in");
ofstream fout("rmq.out");

long long i, j, n, m, tip, x, y, lg_dist, second_number;
long long v[100001], lg[100001], dinamica[19][100001];

// d[i + 2^j - 1][i]

int main()
{
    // read
    fin >> n >> m;
    for(i = 1; i <= n; ++i)
        fin >> v[i];
    
    // precalculation log
    for(i = 2; i <= n; ++i)
        lg[i] = lg[i >> 1] + 1;
    
    // precalculation dynamic matrix
    for(i = 1; i <= n; ++i)
        dinamica[0][i] = v[i];
    
    for(j = 1; 1 << j < n; ++j)
        for(i = 1; i <= n; ++i)
        {
            second_number = i + (1 << (j - 1));
            if( second_number > n)
                second_number = n - (1 << (j - 1));
            dinamica[j][i] = min(dinamica[j - 1][i], dinamica[j - 1][i + (1 << (j - 1))]);
        }
    
    // queries
    for(i = 1; i <= m; ++i)
    {
        fin >> x >> y;
        y++;
        lg_dist = lg[abs(x - y)];
        fout << min( dinamica[lg_dist][x], dinamica[lg_dist][y - (1 << lg_dist)] ) << "\n";
    }
    
    return 0;
}
