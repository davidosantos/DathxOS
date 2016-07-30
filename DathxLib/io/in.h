/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   in.h
 * Author: david
 *
 * Created on 19 de Junho de 2016, 10:06
 */

#ifndef IN_H
#define IN_H
#include <system/Providers/Messaging.h>
#include <system/RunTime/SysCallHandler.h>
#include <system/Providers/Keyboard.h>
  

class in {
private:

    static bool isMassagingInit;


public:

    static Messaging::inbox inbox;
    static u16 index;

    in();
    //    in(const in& orig);
    //    virtual ~in();

    static s8 getChar();

    static const s8 *getLine();
    
   

private:

    static s8 String[1024];

};

#endif /* IN_H */

