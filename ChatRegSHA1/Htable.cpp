#include "Htable.h"


HashTable::HashTable() {
    count = 0;
    mem_size = 10;
    array = new Pair[mem_size];
}

HashTable::~HashTable() {
    delete[] array;
}

int HashTable::hash_func(const char login[], int offset) {
    int sum = 0; 
    const double d_value = 0.7;
    for (int i = 0; i < strlen(login); i++)
    {
        sum += login[i];
    }

    int f2 = int(mem_size * (d_value * sum - int(d_value * sum)));
    return (sum % mem_size + offset * f2) % mem_size;
}



void HashTable::resize() {

    Pair* save = array;
    int save_ms = mem_size;

    mem_size *= 2;
    array = new Pair[mem_size];
    count = 0;

    for (int i = 0; i < save_ms; i++) {
        Pair& old_pair = save[i];
        if (old_pair._status == enPairStatus::engaged) {
            add(old_pair._login, old_pair._pass_sha1_hash);
        }
    }

    delete[] save;
}

void HashTable::add(char login[], uint* sh1) {
    int index = -1, i = 0;
    // берем пробы по всем i от 0 до размера массива
    for (; i < mem_size; i++) {
        index = hash_func(login, i);
        if (array[index]._status == enPairStatus::free) {
            // найдена пустая ячейка, занимаем ее
            break;
        }
    }

    if (i >= mem_size) {
        resize();
        add(login, sh1);
    }
    else {
        array[index] = Pair(login, sh1);
        count++;
    }
}

void HashTable::del(char login[]) {
    int index = -1, i = 0;
    // берем пробы по всем i от 0 до размера массива
    for (; i < mem_size; i++) {
        index = hash_func(login, i);
        if (array[index]._status == enPairStatus::engaged && !strcmp(array[index]._login, login)) {
            array[index]._status = enPairStatus::deleted;
            count--;
            return;
        }
        else if (array[index]._status == enPairStatus::free) {
            return;
        }
    }
}

uint* HashTable::find(char login[]) {

    for (int i = 0; i < mem_size; i++) {
        int index = hash_func(login, i);
        if (array[index]._status == enPairStatus::engaged && !strcmp(array[index]._login, login)) {
            return array[index]._pass_sha1_hash;
        } 
        else if (array[index]._status == enPairStatus::free) {
            return nullptr;
        }
    }
    return nullptr;
}