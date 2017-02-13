//
//  main.cpp
//  Evaluare unei expresii
//
//  Created by Albastroiu Radu on 12/29/16.
//  Copyright © 2016 Albastroiu Radu. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin("evaluare.in");
ofstream fout("evaluare.out");

/*
 First represent the addition and substraction
 Second represent the multiplication and dividing
 Third creates the number if there is no parenthesis otherwise it whill call again method first
 Call order First -> Second -> Third ->(when needed)-> First
*/

int first(int& it, string& expresion);
int second(int& it, string& expresion);
int third(int& it, string& expresion);


int third(int& it, string& expresion)
{
    int r = 0;
    if(expresion[it] == '(')
    {
        ++it;
        r = first(it, expresion);
        ++it;
    }
    else
    {
        while(expresion[it] >= '0' && expresion[it] <= '9')
        {
            r = r * 10 + expresion[it] - '0';
            it++;
        }
    }
    
    return r;
}

int second(int& it, string& expresion)
{
    int r = third(it, expresion);
    
    while(expresion[it] == '*' || expresion[it] == '/')
    {
        switch(expresion[it])
        {
            case '*': ++it; r *= third(it, expresion); break;
            case '/': ++it; r /= third(it, expresion); break;
        }
    }
    return r;
}

int first(int& it, string& expresion)
{
    int r = second(it, expresion);
    
    while(expresion[it] == '+' || expresion[it] == '-')
    {
        switch(expresion[it])
        {
            case '+': ++it; r += second(it, expresion); break;
            case '-': ++it; r -= second(it, expresion); break;
        }
    }
    return r;
}


int main()
{
    string expresie;
    getline(fin, expresie);
    int it = 0;
    int result = first(it, expresie);
    
    fout << result;
}


