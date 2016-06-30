/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   in.cpp
 * Author: david
 * 
 * Created on 19 de Junho de 2016, 10:06
 */

#include "in.h"
#include "out.h"

in::in() {
}

//in::in(const in& orig) {
//}
//
//in::~in() {
//}

bool in::isMassagingInit = false;
Messaging::inbox in::inbox;
s8 in::String[1024];

s8 in::getChar() {
    if (isMassagingInit == false) {
         Messaging::initMessaging();
        isMassagingInit = true;
    }


    while (Messaging::isThereMessage() == false) {
    
    }
    static u32 teste;
    out::print(21, 0, "getChar %i", teste++);
    return Messaging::readMessage().keychar;

}

const s8 *in::getLine() {
    if (isMassagingInit == false) {
        Messaging::initMessaging();
        isMassagingInit = true;
    }
    u16 index = 0;
    u8 character = 0;
    ;
    do {

        character = in::getChar();

        if (character != Key_Enter_Down || character != Key_Enter_UP) {
            String[index++] = character;

        } else {
            String[index] = 0;
        }

        out::print(25, 0, "in %i", character);
        out::print(23, 0, "in %s", (const s8*) &String);

    } while (character != Key_Enter_Down);



    return (const s8*) &String;

}


