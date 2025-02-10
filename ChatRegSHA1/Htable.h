#pragma once
#include<iostream>
#include <string>


class HashTable { // ���-�������
public:

    HashTable();
    ~HashTable();
    void add(std::string login, std::string pasword);
    void resize();
    void del(std::string login);
    std::string find(std::string login);

private:

    enum enPairStatus {
        free, // ��������
        engaged, //�����
        deleted //������
    };

    struct Pair { 

        Pair() : 
            _login(""),
            _pasword(""),
            _status(enPairStatus::free) {

        }
        Pair(std::string login, std::string pasword) :
            _pasword(pasword),
            _status(enPairStatus::engaged) {
            _login = login;
        }
        Pair& operator = (const Pair& other) { 
            _pasword = other._pasword;
            _login = other._login;
            _status = other._status;

            return *this;
        }

        std::string _login;
        std::string _pasword; // ���������� ������ (��������)

        enPairStatus _status; // ��������� ������
    };

    int hash_func(std::string login, int offset);

    Pair* array;
    int mem_size;
    int count;
};

