/* 
 * File:   Video.cpp
 * Author: davidosantos
 * 
 * Created on June 26, 2015, 4:40 PM
 */

#include "Console.h"
#include "../../util/util.h"


s8 Console::inputString[100];


//Video::Video() {
//}

//Video::Video(const Video& orig) {
//}

//Video::~Video() {
//}

void Console::print(u16 y, u16 x, const s8 *String) {

    u8 backColor = COLOR_BLACK;
    u8 textColor = COLOR_WHITE;

    for (; *String != '\0'; String++) {
        if (*String == '%') {
            String++;
            const s8 type = *String;

            switch (type) {
                case 'c':

                    break;

                case 'h':

                    break;
            }
        }

        writeCharacter(*String, backColor, textColor, x, y);
        if (y >= 80) {
            y = 0;
            x++;
        } else {
            x = x + 2;
        }
    }

}

void Console::print(const s8 *String) {

    Console::print(String, (u32) 0);

}

u16 Console::Posx = 0;
u16 Console::Posy = 0;

u16 Console::PosxInput = 0;
u16 Console::PosyInput = 0;
u16 Console::inputCount = 0;

void Console::print(const s8 *String, u32 arg) {
    Console::print(0, (Posx * 80 * 2), String, arg);
    if (Posx < 25) {
        Posx++;
    } else {
        Posx = 25;
        scroll();
    }
}

void Console::print(u16 y, u16 x, const s8 *String, const s8 *arg) {

    print(y, x, String, (u32) arg);

}

void Console::print(const s8 *String, const s8 *arg) {

    print(String, (u32) arg);

}

void Console::print(u16 y, u16 x, const s8 *String, u32 arg) {


    u8 backColor = COLOR_BLACK;
    u8 textColor = COLOR_WHITE;

    while (*String != 0) {
        if (*String == '%') {
            String++;
            const s8 type = *String;

            switch (type) {
                case 'c':
                    String++;
                    if (*String == 't') {
                        String++;
                        textColor = *String;
                        String++;
                    } else if (*String == 'b') {
                        String++;
                        backColor = *String;
                        String++;
                    }

                    break;

                case 'h':
                    String++;
                    x = writeHex(backColor, textColor, x, y, arg);
                    break;

                case 's':

                    String++;
                    // x = 
                    print(y, x, (const s8*) arg);
                    break;

                case 'i':

                    String++;
                    x = writeInt(backColor, textColor, x, y, arg);

                    break;

            }
        }
        if (*String == '%') { //if another command go to next loop
            continue;
        } else if (*String != 0) {
            writeCharacter(*String++, backColor, textColor, x, y);
        }
        if (y >= 80) {
            y = 0;
            x++;
        } else {
            x = x + 2;
        }

    }


}

void Console::clear() {
    u16 *videoMemory;
    videoMemory = (u16 *) 0xB8000;

    for (u16 i = 0; i < 25 * 80; i++)
        *videoMemory++ = 0;

    Posx = 0;
    Posy = 0;
    PosxInput = 0;
    PosyInput = 0;

}

void Console::scroll() {
    R80x25 *r80x25 = (R80x25*) 0xB8000;
    for (int i = 0; i <= 25; i++) {
  
        r80x25->lines[i] = r80x25->lines[i + 1];
    }

}

void Console::paint(u8 color) {
    u16 *videoMemory;
    videoMemory = (u16 *) 0xB8000;

    for (u16 i = 0; i < 25 * 80; i++)
        *videoMemory = color;
    videoMemory = videoMemory + 2;

}

void Console::input(s8 caracter) {
    update_cursor(PosyInput, PosxInput / 2 + 40 + 6);
    inputString[inputCount++] = caracter;
    inputString[inputCount + 1] = 0;
    if (PosyInput >= 80) {
        PosyInput = 0;
        PosxInput++;
    } else {
        PosxInput = PosxInput + 2;
    }
}

void Console::clearInput() {

    for (int i = 0; i <= inputCount; i++) {
        inputString[i] = 0;
    }
    inputCount = 0;
    PosxInput = 0;
    PosyInput = 0;
    update_cursor(PosyInput, PosxInput / 2 + 40 + 6);
}

s8 *Console::getInput() {
    //inputString[++inputCount] = 0;
    // inputCount = 0;
    return inputString;
}

//void Video::println(const s8 *String, ...) {

//}

/* void update_cursor(int row, int col)
 * by Dark Fiber
 */
void Console::update_cursor(int row, int col) {
    //   unsigned short position = (row * 80) + col;
    if (row && col) {

    }
    // cursor LOW port to vga INDEX register
    //    hardware->outb(0x3D4, 0x0F);
    //   hardware->outb(0x3D5, (unsigned char) (position & 0xFF));
    // cursor HIGH port to vga INDEX register
    //  hardware->outb(0x3D4, 0x0E);
    // hardware->outb(0x3D5, (unsigned char) ((position >> 8)&0xFF));
}

s8 Console::readCharacter(u16 x, u16 y) {
    s8 *videoMemory;
    videoMemory = (s8 *) (0xB8000 + 80 * y + x);
    return *videoMemory;
}

void Console::writeCharacter(s8 c, u8 backColour,
        u8 textColour, u16 x, u16 y) {
    u16 *videoMemory;
    videoMemory = (u16 *) (0xB8000 + 80 * y + x);

    u8 attribute = (backColour << 4) | (textColour & 0xF);

    *videoMemory = c | ((u16) attribute << 8);
    // update_cursor(y, x);
}

int Console::writeHex(u8 backColour,
        u8 textColour, u16 x, u16 y, u32 integer) {

    writeCharacter('0', backColour, textColour, x, y);
    x = x + 2;
    writeCharacter('x', backColour, textColour, x, y);
    x = x + 2;
    u32 temp = integer;

    u32 *pointer = &temp;

    s8 Chars[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', \
                    'D', 'E', 'F'};

    int n = 0;
    int d = 1;
    while (*pointer / d >= 16)
        d *= 16;
    while (d != 0) {
        int dgt = *pointer / d;
        *pointer %= d;
        d /= 16;
        if (n || dgt > 0 || d == 0) {
            writeCharacter(Chars[dgt], backColour, textColour, x, y);
            x = x + 2;
            ++n;
        }
    }
    return x;
}

int Console::writeInt(u8 backColour,
        u8 textColour, u16 x, u16 y, u32 integer) {

    u32 temp = integer;

    u32 *pointer = &temp;

    s8 Chars[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    int n = 0;
    int d = 1;
    while (*pointer / d >= 10)
        d *= 10;
    while (d != 0) {
        int dgt = *pointer / d;
        *pointer %= d;
        d /= 10;
        if (n || dgt > 0 || d == 0) {
            writeCharacter(Chars[dgt], backColour, textColour, x, y);
            x = x + 2;
            ++n;
        }
    }
    return x;
}
