//
//  main.cpp
//  Rabin-Karp
//
//  Created by Albastroiu Radu on 11/26/16.
//  Copyright © 2016 Albastroiu Radu. All rights reserved.
//

#include <fstream>
#include <algorithm>
#include <vector>

#define BASE 128
#define HASH07 1000007
#define HASH09 1000009

using namespace std;

ifstream fin("strmatch.in");
ofstream fout("strmatch.out");

int main()
{
    string key_word, text;

    // read operations
    fin >> key_word;
    fin >> text;
    
    int power_mod_07 = 1;
    int power_mod_09 = 1;
    int first_hash_07 = 0;
    int first_hash_09 = 0;
    for (int i = 0; i < key_word.size(); i++)
    {
        // 'ab' -> 'abc' for the key_word
        first_hash_07 = (first_hash_07 * BASE + (key_word[i])) % HASH07;
        first_hash_09 = (first_hash_09 * BASE + (key_word[i])) % HASH09;
        
        // computing the power for lenght of the word
        if( i != 0 )
        {
            power_mod_07 = (power_mod_07 * BASE) % HASH07;
            power_mod_09 = (power_mod_09 * BASE) % HASH09;
        }
    }
    
    
    int second_hash_07 = 0;
    int second_hash_09 = 0;
    
    // creating a hash from the text of lenght key_word
    for (int i = 0; i < key_word.size(); i++)
    {
        // 'ab' -> 'abc'
        second_hash_07 = (second_hash_07 * BASE + (text[i])) % HASH07;
        second_hash_09 = (second_hash_09 * BASE + (text[i])) % HASH09;
    }
    
    int nr = 0;
    vector<int> positions;
    positions.reserve(1000);
    
    // check if the hash is the same with the key_word for the first key_word.size elements
    if(first_hash_07 == second_hash_07 &&
       first_hash_09 == second_hash_09)
    {
        nr++;
        positions.emplace_back(0);
    }
    
    for (int i = int(key_word.size()); i < text.size(); i++)
    {
        // 'abc' -> 'bcd' deleting a char from front and adding another one to the back in one operation
        second_hash_07 = ((second_hash_07 - (power_mod_07 * text[i - key_word.size()] ) % HASH07 + HASH07) * BASE + text[i]) % HASH07;
        second_hash_09 = ((second_hash_09 - (power_mod_09 * text[i - key_word.size()] ) % HASH09 + HASH09) * BASE + text[i]) % HASH09;
     
        // check if the hash is the same with the key_word
        if(first_hash_07 == second_hash_07 &&
           first_hash_09 == second_hash_09)
        {
            nr++;
            if(nr <= 1000)
                positions.emplace_back(int(i - key_word.size() + 1));
        }
    }
    
    // print operations
    fout << nr << "\n";
    
    // prints only the first 1000 appearances
    for( auto &element : positions)
        fout << element << " ";
    
    return 0;
}
