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

int main() {
    const s8 *name = "Test of System Calls memory %h";

    u32 value = 0;
    u16 *teste1 = new u16;
    
    
    out::print(45, 0, name, (u32) teste1);
    
    
    
    
    
    while (true) {
        value++;
        //out::print(47, 0, name, value);
        out::print(39, 0,"get String %s", in::getLine());
        //if()
    }

    return 0;
}


