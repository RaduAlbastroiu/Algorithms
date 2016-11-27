//
//  main.cpp
//  Rabin-Karp
//
//  Created by Albastroiu Radu on 11/26/16.
//  Copyright © 2016 Albastroiu Radu. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <cstring>
#include <cmath>

#define BASE 128
#define HASH07 1000007
#define HASH09 1000009

using namespace std;

ifstream fin("strmatch.in");
ofstream fout("strmatch.out");

int first_hash_07, first_hash_09, second_hash_07, second_hash_09, power_mod_07, power_mod_09, size;
string a, b;
vector<int> positions;

int main()
{
    
    fin >> a;
    fin >> b;
    
    power_mod_07 = 1;
    power_mod_09 = 1;
    
    if ( a.size() > b.size())
    {
        fout << 0;
        return 0;
    }

    for (int i = 0; i < a.size(); i++)
    {
        first_hash_07 = (first_hash_07 * BASE + (a[i])) % HASH07;
        first_hash_09 = (first_hash_09 * BASE + (a[i])) % HASH09;
        
        if( i != 0 )
        {
            power_mod_07 = (power_mod_07 * BASE) % HASH07;
            power_mod_09 = (power_mod_09 * BASE) % HASH09;
        }
    }
    
    for (int i = 0; i < a.size(); i++)
    {
        second_hash_07 = (second_hash_07 * BASE + (b[i])) % HASH07;
        second_hash_09 = (second_hash_09 * BASE + (b[i])) % HASH09;
    }
    
    if(first_hash_07 == second_hash_07 &&
       first_hash_09 == second_hash_09)
        positions.push_back(0);
    
    for (int i = int(a.size()); i < b.size(); i++)
    {
        second_hash_07 = ((second_hash_07 - (power_mod_07 * (b[i - a.size()])) % HASH07 + HASH07) * BASE + (b[i])) % HASH07;
        second_hash_09 = ((second_hash_09 - (power_mod_09 * (b[i - a.size()])) % HASH09 + HASH09) * BASE + (b[i])) % HASH09;
        
        if(first_hash_07 == second_hash_07 &&
           first_hash_09 == second_hash_09)
            positions.push_back(int(i - a.size() + 1));
    }
    
    fout << positions.size() << "\n";
    
    if(positions.size() > 1000)
        size = 1000;
    else
        size = positions.size();
    
    for (int i = 0; i < size; i++)
        fout << positions[i] << " ";
    
    return 0;
}
