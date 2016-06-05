/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   out.cpp
 * Author: david
 * 
 * Created on 5 de Junho de 2016, 12:45
 */

#include "out.h"

out::out() {
}

//out::out(const out& orig) {
//}
//
//out::~out() {
//}


 void out::print(const s8 *String){
    static CallsDirectives call, *callp;
    callp = &call;
    callp->Function = Print;
    callp->Subfunction = Print;
    callp->String = String;
    asm("movl %0,%%eax" ::"m" (callp) : "eax");
    asm("int $0x80");
 }
 
 void out::print(u16 y, u16 x, const s8 *String, u32 arg){
    static CallsDirectives call, *callp;
    callp = &call;
    callp->Function = Print;
    callp->Subfunction = PrintatXYwArgs;
    callp->y = y;
    callp->x = x;
    callp->String = String;
    callp->Value = arg;
    asm("movl %0,%%eax" ::"m" (callp) : "eax");
    asm("int $0x80");
 }