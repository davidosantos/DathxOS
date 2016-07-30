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
u16 in::index = 0;
s8 in::String[1024];

/**
 * Get input from the keyboard from broadcasted by the driver
 * through the use o messaging.
 * @return s8
 */
s8 in::getChar() {
    if (isMassagingInit == false) {
        Messaging::initMessaging();
        isMassagingInit = true;
    }


    while (Messaging::isThereMessage() == false) {

    }
   
    return Messaging::readMessage().keychar;

}
/**
 * Get input from the keyboard from broadcasted by the driver
 * through the use o messaging until a Enter key is pressed
 * Max: 1024 characters.
 * @return 
 */
const s8 *in::getLine() {
    if (isMassagingInit == false) {
        Messaging::initMessaging();
        isMassagingInit = true;
    }

    u8 character = 0;
    index = 0;
    do {
        
        character = in::getChar();

        if (character != Key_Enter_Down) {
            String[index] = character;
            if (index >= 1024)
                index = 1024;
        } else {
            String[index] = 0;
            index = 0;
        }
        index++;
    } while (character != Key_Enter_Down);



    return (const s8*) &String;

}


