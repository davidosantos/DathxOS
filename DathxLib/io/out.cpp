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

void out::print(const s8 *String) {
    static CallsDirectives call, *callp;
    callp = &call;
    callp->Function = sys_call_print;
    callp->Subfunction = sys_call_print;
    callp->String = String;
    asm (
                "int $0x80;"
                :
                : "a"(sys_call_print), "c" (callp) /* input */
                );
}

void out::print(u16 y, u16 x, const s8 *String, u32 arg) {
    static CallsDirectives call, *callp;
    callp = &call;
    callp->Function = sys_call_print;
    callp->Subfunction = sys_call_printatXYwArgs;
    callp->y = y;
    callp->x = x;
    callp->String = String;
    callp->Value = arg;
    asm (
                "int $0x80;"
                :
                : "a"(sys_call_print), "c" (callp) /* input */
                );
}

void out::print(u16 y, u16 x, const s8 *String, const s8 *arg) {
    static CallsDirectives call, *callp;
    callp = &call;
    callp->Function = sys_call_print;
    callp->Subfunction = sys_call_printatXYwString;
    callp->y = y;
    callp->x = x;
    callp->String = String;
    callp->Value = (u32) arg;

    asm (
                "int $0x80;"
                :
                : "a"(sys_call_print), "c" (callp) /* input */
                );
}

void out::print(const s8 *String, u32 arg){
    static CallsDirectives call, *callp;
    callp = &call;
    callp->Function = sys_call_print;
    callp->Subfunction = sys_call_printwArgs;
    callp->String = String;
    callp->Value = (u32) arg;
     asm (
                "int $0x80;"
                :
                : "a"(sys_call_print), "c" (callp) /* input */
                );
     
}

void out::clear(){
    static CallsDirectives call, *callp;
    callp = &call;
    callp->Function = sys_call_print;
    callp->Subfunction = sys_call_printClear;

     asm (
                "int $0x80;"
                :
                : "a"(sys_call_print), "c" (callp) /* input */
                );
}