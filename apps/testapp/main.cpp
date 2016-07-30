/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: david
 *
 * Created on 10 de Julho de 2016, 13:26
 */

#include <DathxLib/io/out.h>

using namespace std;

/*
 * 
 */
int main() {
    static u32 teste;
    teste++;
    out::print(45, 0, "Test App has Run %i",teste);
    
    return 0;
}

