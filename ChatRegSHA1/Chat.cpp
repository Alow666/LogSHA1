#include "Chat.h"
#include "iostream"
#include <string>

Chat::Chat() {
    data = new HashTable();
}

Chat::~Chat() {
    delete data;
}

void Chat::reg(char _login[LOGINLENGTH], char _pass[], int pass_length) {
    // Ваш код
    data->add(_login, sha1(_pass, pass_length));
}
bool Chat::login(char _login[LOGINLENGTH], char _pass[], int pass_length) {
   
    uint* digest = sha1(_pass, pass_length);
    bool cmpHashes = !memcmp(data->find(_login), digest, SHA1HASHLENGTHBYTES);

    delete[] digest;
    return cmpHashes;
}