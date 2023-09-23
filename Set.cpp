#include "Set.h"
#include "SetElem.h"
#include <iostream>
using namespace std;

bool Set::operator==(const Set & s) const {
    if (elemsArray.size() != s.elemsArray.size())
        return false;

    bool IsCompair = false;

    for (int i = 0; i < elemsArray.size(); i++) {
        for (int j = 0; j < s.elemsArray.size(); j++) {
            if (!elemsArray[i].CheckIsSet() && !s.elemsArray[j].CheckIsSet()) {
                if (elemsArray[i].GetCharElem() == s.elemsArray[j].GetCharElem()) {
                    IsCompair = true;
                    break;
                }
            }
            else if (elemsArray[i].CheckIsSet() && s.elemsArray[j].CheckIsSet()) {
                if (elemsArray[i].GetSetElem() == s.elemsArray[j].GetSetElem()) {
                    IsCompair = true;
                    break;
                }
            }
        }

        if (!IsCompair)
            return false;

        IsCompair = false;
    }

    return true;
}

void Set::AddElement(char input) {
    if ((*this)[input] != -1)
        return;

    SetElem newSL(input);
    elemsArray.push_back(newSL);
}

string Set::Print() const {
    return PrintSet(true);
}

string Set::PrintSet(bool mainSet) const {
    string rez = "{";
    if (mainSet) rez += "{},";
    SetElem CurentElem;
    Set CurentSet;
    for (int i = 0; i < elemsArray.size(); i++) {
        if (i != 0)
            rez += ",";
        CurentElem = elemsArray[i];
        if (CurentElem.CheckIsSet() == true) {
            rez += CurentElem.GetSetElem().PrintSet(false);
        }
        else {
            rez += CurentElem.GetCharElem();
        }
    }

    rez += "}";
    return rez;
}



void Set::AddElement(const Set& input) {
    if ((*this)[input] != -1)
        return;

    SetElem newSL(input);
    elemsArray.push_back(newSL);
}

void Set::AddElement(SetElem input) {
    if ((*this)[input] != -1)
        return;

    elemsArray.push_back(input);
}

bool isValid(string str) {
    int cnt = 0;
    for (char c : str) {
        if (c == '{')
            cnt++;
        else if (c == '}')
            cnt--;

        if (cnt < 0) {
            cout << "количество { и } не совпадает";
            return false;
        }
    }
    if (cnt != 0)
        cout << "количество { и } не совпадает";
    return cnt == 0;
}


Set Set::operator+=(const  Set&s) {
    for (int i = 0; i < s.elemsArray.size(); i++) {
        AddElement(s.elemsArray[i]);
    }
    return *this;
}

Set Set::operator+(const  Set&s)const {
    Set UnionSet;
    for (int i = 0; i < s.elemsArray.size(); i++)
        UnionSet.AddElement(s.elemsArray[i]);
    for (int j = 0; j < elemsArray.size(); j++)
        UnionSet.AddElement(elemsArray[j]);
    return UnionSet;
}

Set Set::DeleteElem(int number) {
    if (number >= 1 && number <= elemsArray.size()) {
        elemsArray.erase(elemsArray.begin() + (number - 1));
    }
    return *this;
}

Set Set::DeleteElem(const  Set&s) {
    int n = (*this)[s];
    if (n != -1)
        elemsArray.erase(elemsArray.begin() + n);
    return *this;
}

Set Set::DeleteElem(char s) {
    int n = (*this)[s];
    if (n != -1)
        elemsArray.erase(elemsArray.begin() + n);
    return *this;
}

Set Set::operator*(const  Set&s)const {
    Set IntersectionSet;
    for (int i = 0; i < s.elemsArray.size(); i++) {
        if ((*this)[s.elemsArray[i]] != -1) {
            IntersectionSet.AddElement(s.elemsArray[i]);
        }
    }
    return IntersectionSet;
}

Set Set::operator*=(const  Set&s) {
    Set NewSet;
    for (int i = 0; i < s.elemsArray.size(); i++) {
        if ((*this)[s.elemsArray[i]] != -1) {
            NewSet.AddElement(s.elemsArray[i]);
        }
    }
    elemsArray = NewSet.elemsArray;
    return *this;
}

Set Set::operator-=(const  Set&s) {
    Set DifferenceSet;
    for (int i = 0; i < elemsArray.size(); i++) {
        if (s[elemsArray[i]] == -1) {
            DifferenceSet.AddElement(elemsArray[i]);
        }
    }
    elemsArray = DifferenceSet.elemsArray;
    return *this;
}

Set Set::operator-(const  Set&s) const{
    Set DifferenceSet;
    for (int i = 0; i < elemsArray.size(); i++)
        if (s[elemsArray[i]] == -1)
            DifferenceSet.AddElement(elemsArray[i]);

    return DifferenceSet;
}

Set::Set(string input) : Set() {
    if (!input.empty() && input.front() == '{' && input.back() == '}' && isValid(input)) {
        int cur = 0;
        ParseFromString(input, cur);
    }
}

int Set::operator[](const Set& si)const {
    for (int i = 0; i < elemsArray.size(); i++) {
        if (elemsArray[i].CheckIsSet())
            if (elemsArray[i].GetSetElem() == si)
                return i;
    }
    return -1;
}


int Set::operator[](char si)const {
    for (int i = 0; i < elemsArray.size(); i++) {
        if (!elemsArray[i].CheckIsSet())
            if (elemsArray[i].GetCharElem() == si)
                return i;
    }
    return -1;
}



int Set::operator[](SetElem si)const {
    if (si.CheckIsSet())
        return (*this)[(const Set&)si.GetSetElem()];
    else
        return (*this)[si.GetCharElem()];
    return -1;
}

void Set::ParseFromString(string input, int& cur) {
    cur++;
    bool AddChar = false;
    char CurentChar = ' ';
    do {
        switch (input[cur]) {
        case '}':
            if (AddChar) {
                AddElement(CurentChar);
                AddChar = false;
            }
            return;
            break;
        case ',':
            if (AddChar) {
                AddElement(CurentChar);
                AddChar = false;
            }
            break;
        case '{': {
            Set* NewSet = new Set;
            NewSet->ParseFromString(input, cur);
            AddElement(*NewSet);
        } break;
        case ' ':
            break;
        default: {
            CurentChar = input[cur];
            AddChar = true;
        } break;
        }
        cur++;
    } while (cur != input.size());
}

int Set::Count()const {
    return elemsArray.size() + 1;
}

void intToBinaryArray(int n, int* binaryArray, int size) {
    for (int i = size - 1; i >= 0; i--) {
        binaryArray[i] = n & 1; // ѕолучаем младший бит числа n
        n >>= 1; // —двигаем число n вправо на 1 бит
    }
}

Set Set::Boolean()const {
    Set BooleanSet;
    int* binaryArray = new int[elemsArray.size()];
    for (int i = 1; i < pow(2, elemsArray.size()); i++) {
        Set NewSet;
        intToBinaryArray(i, binaryArray, elemsArray.size());
        for (int j = 0; j < elemsArray.size(); j++)
            if (binaryArray[j] == 1)
                NewSet.AddElement(elemsArray[j]);
        BooleanSet.AddElement(NewSet);
    }
    delete[] binaryArray;
    return BooleanSet;
}

bool Set::IsEmpty() const {
    return elemsArray.empty();
}

Set::Set() {
}
