#pragma once
#include "Set.h"

using namespace std;
class Set;
class SetElem {
private:
    char CharElem;
    Set SetElemValue;
    bool IsSet;

public:
    SetElem() : CharElem('\0'), IsSet(false) {}

    bool CheckIsSet() const {
        return IsSet;
    }

    SetElem(char value) : CharElem(value), IsSet(false) {}

    SetElem(const Set& value) : CharElem('\0'), SetElemValue(value), IsSet(true) {}

    char GetCharElem() const {
        return CharElem;
    }

    Set GetSetElem() const {
        return SetElemValue;
    }
};
