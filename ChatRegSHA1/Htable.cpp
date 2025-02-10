#include "Htable.h"


HashTable::HashTable() {
    count = 0;
    mem_size = 10;
    array = new Pair[mem_size];
}

HashTable::~HashTable() {
    delete[] array;
}

int HashTable::hash_func(std::string _login, int offset) {
    int sum = 0; 
    const double d_value = 0.3;
    for (int i = 0; i < mem_size; i++)
    {
        sum += std::stoi(array[i]._login);
    }

    sum = int(mem_size * (d_value * sum - int(d_value * sum)));
    return (sum % mem_size + offset * offset) % mem_size;
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
            add(old_pair._login, old_pair._pasword);
        }
    }

    delete[] save;
}

void HashTable::add(std::string login, std::string pasword) {
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
        add(login, pasword);
    }
    else {
        array[index] = Pair(login, pasword);
        count++;
    }
}

void HashTable::del(std::string login) {
    int index = -1, i = 0;
    // берем пробы по всем i от 0 до размера массива
    for (; i < mem_size; i++) {
        index = hash_func(login, i);
        if (array[index]._status == enPairStatus::engaged && array[index]._login == login) {
            array[index]._status = enPairStatus::deleted;
            count--;
            return;
        }
        else if (array[index]._status == enPairStatus::free) {
            return;
        }
    }
}

std::string HashTable::find(std::string login) {

    for (int i = 0; i < mem_size; i++) {
        int index = hash_func(login, i);
        if (array[index]._status == enPairStatus::engaged && array[index]._login == login) {
            return array[index]._pasword;
        } 
        else if (array[index]._status == enPairStatus::free) {
            return "";
        }
    }
    return "";
}