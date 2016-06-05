/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   InputProvider.h
 * Author: david
 *
 * Created on 28 de Maio de 2016, 13:44
 */

#ifndef INPUTPROVIDER_H
#define INPUTPROVIDER_H

#include "../memory/Memory.h"

class InputProvider {

    struct RegistredListeners {
        void (*listener)(s8 keyCode);
    } __attribute__((packed));
    static RegistredListeners *registredListeners;
public:
    static void add(void (*listener)(s8 keyCode));
    static void setup();
    InputProvider();
    //    InputProvider(const InputProvider& orig);
    //    virtual ~InputProvider();
private:

};

#endif /* INPUTPROVIDER_H */

