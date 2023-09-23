#pragma once
#include <string>
#include <memory>

using namespace std;
class SetElem;

#include <vector>

class Set
{
private:

    vector<SetElem> elemsArray;

    void ParseFromString(string, int&);
    string PrintSet(bool)const;

public:
    Set();
   
    Set(string);

    bool operator==(const Set&) const;

    Set operator+=(const  Set&);

    Set operator*(const  Set&)const;

    Set operator*=(const  Set&);

    Set operator+(const  Set&)const;

    Set operator-=(const  Set&);

    Set operator-(const  Set&)const;

    int operator[](SetElem)const;
    int operator[]( const Set &)const;
    int operator[](char)const;


    void AddElement( char);
    void AddElement(const  Set&);
    void AddElement(SetElem);
   
    Set DeleteElem(int);
    Set DeleteElem(const  Set&);
    Set DeleteElem(char);

    string Print()const;
   
    int Count()const;

    Set Boolean()const;

    bool IsEmpty()const;
};
