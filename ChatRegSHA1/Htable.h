#pragma once
#include <iostream>
#include "string.h"
#include "SHA1.h"

#define LOGINLENGTH 10

class HashTable { // хеш-таблица
public:

    HashTable();
    ~HashTable();
    void add(char login[], uint* sh1);
    void resize();
    void del(char login[]);
    uint* find(char login[]);

private:

    enum enPairStatus {
        free, // свободен
        engaged, //занят
        deleted //удален
    };

    struct Pair { 
    
        Pair() :
            _login(""),
            _pass_sha1_hash(0),
            _status(enPairStatus::free) {
        }

        ~Pair() {
            if (_pass_sha1_hash != 0)
                delete[] _pass_sha1_hash;
        }

        Pair(char login[LOGINLENGTH], uint* sh1) {
            std::copy_n(login, LOGINLENGTH, _login);
            _pass_sha1_hash = sh1;
            _status = enPairStatus::engaged;
        }

        Pair& operator = (const Pair& other) {
            std::copy_n(other._login, LOGINLENGTH, _login);
            _status = other._status;
            if (_pass_sha1_hash != 0)
                delete[] _pass_sha1_hash;
            _pass_sha1_hash = new uint[SHA1HASHLENGTHUINTS];
            memcpy(_pass_sha1_hash, other._pass_sha1_hash, SHA1HASHLENGTHBYTES);

            return *this;
        }
        
        char _login[LOGINLENGTH];
        uint* _pass_sha1_hash; // количество фрукта (значение)
        enPairStatus _status;
         
    };

    int hash_func(const char login[], int offset);

    Pair* array;
    int mem_size;
    int count;
};

