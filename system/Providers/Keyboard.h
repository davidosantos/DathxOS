/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Keyboard.h
 * Author: david
 *
 * Created on 25 de Junho de 2016, 18:41
 */

#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "../../util/util.h"

#define Key_Enter_UP        0x9c
#define Key_Enter_Down      0x1c   

#define Key_lShit_UP        0xaa
#define Key_lShit_Down      0x2a  

#define Key_rShit_UP        0xb6
#define Key_rShit_Down      0x36  

static u8 keys_ptbr[] = {
  //0  1    2    3    4    5    6    7    8    9   10   11   12    13  14
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', /* Backspace 14*/
  // 15  
    '\t', /* Tab 15*/
  //16   17   18    19 
    'q', 'w', 'e', 'r', /* 19 */
  //20    21   22   23   24   25  26   27    28
    't', 'y', 'u', 'i', 'o', 'p', '\"', '[', 0x1c, /* Enter key 28*/
    0, /* 29   - Control */
  //30   31   32   33   34   35   36   37   38   39   40  
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'c', '~',/* 40 */
  //41    42 
    '\'', 0, /* Left shift 42*/
  //43   44   45   46   47   48   49
    ']', 'z', 'x', 'c', 'v', 'b', 'n', /* 49 */
  //50   51   52   53  54
    'm', ',', '.', ';', 0, /* Right shift */
  //55  
    '*',
  //56  
    0, /* Alt */
  //57  
    ' ', /* Space bar */
  //58
    0, /* Caps lock */
    0, /* 59 - F1 key ... > */
    0, 0, 0, 0, 0, 0, 0, 0,
    0, /* < ... F10 */
    0, /* 69 - Num lock*/
    0, /* Scroll Lock */
    0, /* Home key */
    0, /* Up Arrow */
    0, /* Page Up */
    '-',
    0, /* Left Arrow */
    0,
    0, /* Right Arrow */
    '+',
    0, /* 79 - End key*/
    0, /* Down Arrow */
    0, /* Page Down */
    0, /* Insert Key */
    0, /* Delete Key */
    0, 0, 0,
    0, /* F11 Key */
    0, /* F12 Key */
    0, /* All other keys are undefined */
};

static u8 keys_ptbrShift[] = {
  //0  1    2    3    4    5    6    7    8    9   10   11   12    13  14
    0, 27, '!', '@', '#', '$', '%', '\0', '&', '*', '(', ')', '_', '+', '\b', /* Backspace 14*/
  // 15  
    '\t', /* Tab 15*/
  //16   17   18    19 
    'Q', 'W', 'E', 'R', /* 19 */
  //20    21   22   23   24   25  26   27    28
    'T', 'Y', 'U', 'I', 'O', 'P', '\"', '{', 0x1c, /* Enter key 28*/
    0, /* 29   - Control */
  //30   31   32   33   34   35   36   37   38   39   40  
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'C', '^',/* 40 */
  //41    42 
    '\'', 0, /* Left shift 42*/
  //43   44   45   46   47   48   49
    '}', 'Z', 'X', 'C', 'V', 'B', 'N', /* 49 */
  //50   51   52   53  54
    'M', '<', '>', ':', 0, /* Right shift */
  //55  
    '*',
  //56  
    0, /* Alt */
  //57  
    ' ', /* Space bar */
  //58
    0, /* Caps lock */
    0, /* 59 - F1 key ... > */
    0, 0, 0, 0, 0, 0, 0, 0,
    0, /* < ... F10 */
    0, /* 69 - Num lock*/
    0, /* Scroll Lock */
    0, /* Home key */
    0, /* Up Arrow */
    0, /* Page Up */
    '_',
    0, /* Left Arrow */
    0,
    0, /* Right Arrow */
    '=',
    0, /* 79 - End key*/
    0, /* Down Arrow */
    0, /* Page Down */
    0, /* Insert Key */
    0, /* Delete Key */
    0, 0, 0,
    0, /* F11 Key */
    0, /* F12 Key */
    0, /* All other keys are undefined */
};

class Keyboard {
public:
    Keyboard();
    //    Keyboard(const Keyboard& orig);
    //    virtual ~Keyboard();
private:

};

#endif /* KEYBOARD_H */

