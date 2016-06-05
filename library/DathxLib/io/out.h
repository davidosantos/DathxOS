/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   out.h
 * Author: david
 *
 * Created on 5 de Junho de 2016, 12:45
 */

#ifndef OUT_H
#define OUT_H
#include "../Syscalls.h"

class out {
public:
    
    static void print(const s8 *String);

    static void print(const s8 *String, u32 arg);

    static void print(const s8 *String, const s8 *arg);

    static void print(u16 y, u16 x, const s8 *String);

    static void print(u16 y, u16 x, const s8 *String, u32 arg);

    static void print(u16 y, u16 x, const s8 *String, const s8 *arg);

    static void println(const char *String, ...);

    static void clear();

    static void scroll();

    static void paint(u8 color);

    static void input(s8 caracter);

    s8 *getInput();

    static void clearInput();

    /* static void update_cursor(int row, int col)
     * by Dark Fiber
     */
    static void update_cursor(int row, int col);
    
    out();
    //out(const out& orig);
    //virtual ~out();
private:

};

#endif /* OUT_H */

