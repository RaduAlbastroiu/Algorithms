//
//  main.cpp
//  ArboriDeIntervale
//
//  Created by Albastroiu Radu on 9/17/16.
//  Copyright © 2016 Albastroiu Radu. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include <vector>
#define MULTFOARTEMULT (1<<28)-1
using namespace std;

ifstream fin("arbint.in");
ofstream fout("arbint.out");

int i, j, n, m, tip, a, b, v[100001], arb[200001], Max;

void populateArb(int left, int right, int p)
{
    if(left == right)
    {
        arb[p] = v[left];
    }
    else
    {
        int mij = (left + right)/2;
        
        populateArb(left, mij, p * 2);
        populateArb(mij+1, right, p * 2 + 1);
        
        arb[p] = max( arb[p * 2], arb[p * 2 + 1] );
    }
}

void update(int left, int right, int a, int b, int p)
{
    if(left == right)
    {
        arb[p] = b;
    }
    else
    {
        int mij = (left + right)/2;
        
        if( a <= mij && a >= left  )
            update(left, mij, a, b, p * 2);
        if( a >  mij && a <= right )
            update(mij+1, right, a, b, p * 2 + 1);
        
        arb[p] = max( arb[p*2], arb[p * 2 + 1] );
    }
}

void query(int left, int right, int a, int b, int p)
{
    if( left >= a && right <= b )
    {
        Max = max(arb[p], Max);
    }
    else
    {
        int mij = (left + right)/2;
        
        if( mij >= a )
            query(left, mij, a, b, p * 2);
        
        if( mij + 1 <= b )
            query(mij + 1, right, a, b, p * 2 + 1);
    }
}

int main()
{
    fin >> n >> m;
    
    for(i = 1; i <= n; i++)
        fin >> v[i];
    
    populateArb(1, n, 1);
    
    for(i = 1; i <= m; i++)
    {
        fin >> tip >> a >> b;
        
        if(tip)
            update(1, n, a, b, 1);
        
        else
        {
            Max = 0;
            if(a>b)
                swap(a,b);
            
            query(1,n,a,b,1);
            fout << Max << "\n";
        }
    }
    return 0;
}
