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

int main() {
    const s8 *name = "Test of System Calls %h";

    u32 value = 0;


    while (true) {
        value++;

        out::print(47, 0, name, value);
    }

    return 0;
}


