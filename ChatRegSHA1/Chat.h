#pragma once
#include "SHA1.h"
#include "Htable.h"

#include <string>

#define SIZE 10
#define LOGINLENGTH 10

class Chat {
public:
    Chat();
    ~Chat();
    void reg(char _login[LOGINLENGTH], char _pass[], int pass_length);
    bool login(char _login[LOGINLENGTH], char _pass[], int pass_length);

private:
    HashTable* data;
};