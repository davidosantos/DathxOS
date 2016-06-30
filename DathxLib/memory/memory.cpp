/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   memory.cpp
 * Author: david
 * 
 * Created on 21 de Junho de 2016, 19:58
 */

#include <system/memory/Memory.h>
#include <system/RunTime/SysCallHandler.h>

void *operator new( unsigned int size) {
    u32 *retAddres;

    asm (
                "int $0x80;"
                : "=a"(retAddres) /* output */
                : "a"(sys_call_alloc), "c" (size) /* input */
                );

    return retAddres;

}

void *operator new[](unsigned int size) {
    u32 *retAddres;
    asm ("int $0x80;"
                : "=a"(retAddres) /* output */
                : "a"(sys_call_alloc), "c" (size) /* input */
                );
    return retAddres;
}
