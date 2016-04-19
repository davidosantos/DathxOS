/* 
 * File:   Video.h
 * Author: davidosantos
 
 * Created on June 26, 2015, 4:40 PM
 */

#ifndef VIDEO_H
#define	VIDEO_H

#include "Console.h"
#include "../../util/util.h"
//#include "../IO/HardwareIO.h"

class Console {
public:
    //  Video();
    //    Video(const Video& orig);
    //    virtual ~Video();

    static void print(const s8 *String);

    static void print(const s8 *String, u32 arg);

    static void print(const s8 *String, const s8 *arg);

    static void print(u16 y, u16 x, const s8 *String);

    static void print(u16 y, u16 x, const s8 *String, u32 arg);

    static void print(u16 y, u16 x, const s8 *String, const s8 *arg);

    static void println(const char *String, ...);

    static void clear();

    static void paint(u8 color);

    static void input(s8 caracter);

    s8 *getInput();

    static void clearInput();

    /* static void update_cursor(int row, int col)
     * by Dark Fiber
     */
    static void update_cursor(int row, int col);

private:

    static void writeCharacter(s8 c, u8 backColour,
            u8 textColour, u16 x, u16 y);

    static s8 readCharacter(u16 x, u16 y);

    static int writeHex(u8 backColour,
            u8 textColour, u16 x, u16 y, u32 integer);

    static int writeInt(u8 backColour,
            u8 textColour, u16 x, u16 y, u32 integer);
    static u16 Posx;
    static u16 Posy;

    static u16 PosxInput;
    static u16 PosyInput;

    static u16 inputCount;

    static s8 inputString[100];

};

#endif	/* VIDEO_H */

