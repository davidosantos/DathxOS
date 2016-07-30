/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: david
 *
 * Created on 19 de Junho de 2016, 08:29
 */

#include <DathxLib/io/out.h>
#include <DathxLib/io/in.h>
#include <system/Providers/Keyboard.h>
#include <DathxLib/apps/application.h>

#define maxInput 128

int main() {

    s8 input[maxInput];
    u32 inputIndex = 0;



    while (true) {
        char value = in::getChar();   

        if (value == Key_Enter_Down) {
            input[inputIndex] = 0;
            inputIndex = 0;
        } else {
            input[inputIndex++] = value;
            input[inputIndex] = 0;
        }
        
        out::print(0, 0, "                                                                                ", inputIndex);
        out::print(0, 0, "Command:> %s", (const s8 *) &input);
        out::print(2, 0, "                                                                                ", inputIndex);
        out::print(2, 0, "-------------------------------------------------------------------------%i/128", inputIndex);
        
        if( value == 'c'){
            application::createTask("bin/testapp");
        }
        
//        u32 eax;
//        u32 ebx;
//        u32 ecx;
//        u32 edx;
//        u32 ebp;
//        u32 esp;
//        u32 esi;
//        u32 edi;
//        asm("movl %%eax,%0\n" : "=m" (eax));
//        asm("movl %%ebx,%0\n" : "=m" (ebx));
//        asm("movl %%ecx,%0\n" : "=m" (ecx));
//        asm("movl %%edx,%0\n" : "=m" (edx));
//        asm("movl %%ebp,%0\n" : "=m" (ebp));
//        asm("movl %%esp,%0\n" : "=m" (esp));
//        asm("movl %%esi,%0\n" : "=m" (esi));
//        asm("movl %%edi,%0\n" : "=m" (edi));
//
//        out::print(11, 0, "eax:> %h", eax);
//        out::print(13, 0, "ebx:> %h", ebx);
//        out::print(15, 0, "ecx:> %h", ecx);
//        out::print(17, 0, "edx:> %h", edx);
//        out::print(19, 0, "ebp:> %h", ebp);
//        out::print(21, 0, "esp:> %h", esp);
//        out::print(23, 0, "esi:> %h", esi);
//        out::print(25, 0, "edi:> %h", edi);
//        out::print(27, 0, "value:> %h", value);


        if (inputIndex >= maxInput) {
            inputIndex = maxInput;
        }
    }

    return 0;
}


