//
//  main.cpp
//  Euclid Extins
//
//  Created by Albastroiu Radu on 11/12/16.
//  Copyright © 2016 Albastroiu Radu. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include <bitset>
#include <vector>
#include <queue>

using namespace std;

ifstream fin("euclid3.in");
ofstream fout("euclid3.out");

int k, x, y, T, a, b, c;

int euclid_extended(int a, int b, int& x, int& y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    else
    {
        int x0, y0;
        int d = euclid_extended(b, a % b, x0, y0);
        x = y0;
        y = x0 - (a / b) * y0;
        return d;
    }
}

int main()
{
    fin >> T;
    while(T--)
    {
        fin >> a >> b >> c;
        
        k = euclid_extended(a, b, x, y);
        
        if (c % k == 0)
            fout << x * (c / k) << " " << y * (c / k) << "\n";
        else
            fout << "0 0\n";
        
    }
    
    return 0;
}
