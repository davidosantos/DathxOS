/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   InputProvider.cpp
 * Author: david
 * 
 * Created on 28 de Maio de 2016, 13:44
 */

#include "InputProvider.h"

InputProvider::InputProvider() {
}

//InputProvider::InputProvider(const InputProvider& orig) {
//}
//
//InputProvider::~InputProvider() {
//}

InputProvider::RegistredListeners *InputProvider::registredListeners;

void InputProvider::setup() {
    registredListeners = new RegistredListeners[1024];
   // Console::print("registredListeners %i",sizeof(RegistredListeners[1024]));
}

void InputProvider::add(void (*listener)(s8 keyCode)) {

}

