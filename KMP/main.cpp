//
//  main.cpp
//  KMP
//
//  Created by Albastroiu Radu on 10/16/16.
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

using namespace std;

ifstream fin("strmatch.in");
ofstream fout("strmatch.out");

int match_text[2000001];
int match_key_word[2000001];

int main()
{
    string key_word, text, aux;
    aux = " ";
    
    fin >> key_word;
    fin >> text;
    
    key_word = aux + key_word;
    text = aux + text;
    
    auto n = key_word.size();
    auto m = text.size();
    
    int k = 0;
    match_key_word[0] = 0;
    match_key_word[1] = 0;
    
    for(int i = 2; i < n; i++)
    {
        while(k && key_word[i] != key_word[k + 1])
            k = match_key_word[k];
        
        if(key_word[i] == key_word[k + 1])
            k++;
        
        match_key_word[i] = k;
    }
    
    k = 0;
    
    match_text[0] = 0;
    vector<int> positions;
    positions.reserve(1000);
    int nr = 0;
    for(int i = 1; i < m; i++)
    {
        while(k && text[i] != key_word[k + 1])
            k = match_key_word[k];
        
        if(text[i] == key_word[k + 1])
        {
            k++;
            if( k == n - 1 )
            {
                nr++;
                if(nr <= 1000)
                    positions.emplace_back(i - n + 1);
            }
        }
    
        match_text[i] = k;
    }
    
    fout << nr << "\n";
    
    for( auto &element : positions)
        fout << element << " ";
    
    return 0;
}
