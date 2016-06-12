/* 
 * File:   util.h
 * Author: davidosantos
 *
 * Created on June 26, 2015, 12:39 PM
 */

#ifndef UTIL_H
#define	UTIL_H

#ifdef	__cplusplus
extern "C" {
#endif



#define u32 unsigned int
#define u16 unsigned short int
#define u8 unsigned char
#define s32 int
#define s16 short int
#define s8 char
#define cs8 const char
#define scs8 static const char
    

     enum returnCode {
        Error = -1,
        OK = 0,
     };
    
    enum vga_color {
        COLOR_BLACK = 0,
        COLOR_BLUE = 1,
        COLOR_GREEN = 2,
        COLOR_CYAN = 3,
        COLOR_RED = 4,
        COLOR_MAGENTA = 5,
        COLOR_BROWN = 6,
        COLOR_LIGHT_GREY = 7,
        COLOR_DARK_GREY = 8,
        COLOR_LIGHT_BLUE = 9,
        COLOR_LIGHT_GREEN = 10,
        COLOR_LIGHT_CYAN = 11,
        COLOR_LIGHT_RED = 12,
        COLOR_LIGHT_MAGENTA = 13,
        COLOR_LIGHT_BROWN = 14,
        COLOR_WHITE = 15,
    };
    

    void inline nop() {
        asm("nop");
    }

    void inline cli() {
        asm("cli");
    }

    void inline sti() {
        asm("sti");
    }

    union HMSValue {
        int i;
        char ch;
    };

    typedef struct Tstorage {
        HMSValue Hour;
        HMSValue Min;
        HMSValue Sec;

        const s8 *getValue() {
            s8 value[5];
            value[0] = Hour.ch;
            value[1] = ':';
            value[2] = Min.ch;
            value[3] = ':';
            value[4] = Sec.ch;
            value[5] = '\0';
            s8 *p = value;
            return p;
        }
    } Time;

    typedef struct Dstorage {
        HMSValue Day;
        HMSValue Month;
        HMSValue Year;
        HMSValue DayOfWeek;

        const s8 *getValue() {
            static s8 value[7];
            value[0] = Day.ch;
            value[1] = '/';
            value[2] = Month.ch;
            value[3] = '/';
            value[4] = Year.ch;
            value[5] = ':';
            value[6] = DayOfWeek.ch;
            value[7] = '\0';
            return value;;
        }
    } Date;
    
    typedef struct u512 {
        union{
        u16 data[256];
        u8 dataU8[512];
        };
    } sector;
    
    bool strcmp(const s8* str1, const s8 *str2);

#ifdef	__cplusplus
}
#endif

#endif	/* UTIL_H */

