/* 
 * File:   main.cpp
 * Author: david
 *
 * Created on 14 de Novembro de 2015, 14:51
 */


//using namespace std;
#include "util.h"
#include "../../library/DathxLib/io/out.h"

/*
 * 
 */
int main() {

    const s8 *name = "Test of System Calls %h";

    u32 value = 0;


    while (true) {
        value++;

        out::print(47,0,name,value);
    }

    return 0;
}

