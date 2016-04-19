/* 
 * File:   pageManagment.h
 * Author: david
 *
 * Created on 7 de Novembro de 2015, 16:12
 */

#ifndef PAGEMANAGMENT_H
#define	PAGEMANAGMENT_H
#include "../../util/util.h"
#include "../monitor/Console.h"
#include "Memory.h"

#define byteSize 8
#define used 1
#define free 0

class pageManagment {

    struct byte {
        u8 b7 : 1,
        b6 : 1,
        b5 : 1,
        b4 : 1,
        b3 : 1,
        b2 : 1,
        b1 : 1,
        b0 : 1;

        void setBit(u8 index, u8 value) {
            switch (index) {
                case 0:
                    b0 = value;
                    break;
                case 1:
                    b1 = value;
                    break;
                case 2:
                    b2 = value;
                    break;
                case 3:
                    b3 = value;
                    break;
                case 4:
                    b4 = value;
                    break;
                case 5:
                    b5 = value;
                    break;
                case 6:
                    b6 = value;
                    break;
                case 7:
                    b7 = value;
                    break;
            }
        }

        u8 getBit(u8 index) {
            switch (index) {
                case 0:
                    return b0;
                    break;
                case 1:
                    return b1;
                    break;
                case 2:
                    return b2;
                    break;
                case 3:
                    return b3;
                    break;
                case 4:
                    return b4;
                    break;
                case 5:
                    return b5;
                    break;
                case 6:
                    return b6;
                    break;
                case 7:
                    return b7;
                    break;
            }
            return -1;
        }
    };

    struct bitMapPage {

        union {
            byte bytes[0x1000];
            u32 ints[0x400];
        };
    };

    static bitMapPage *bitMapPagePointer;

    static u32 totalPages;
    static u32 totalCount;
    static u32 lastPagesBitCount;

public:

    static void setup(u32 totalPages);
    static void setBusy(u32 *adrss);
    static void setRangeBusy(u32 *adrss,u32 *adrss2);
    static void setFree(u32 *adrss);
    static void clearPage(bitMapPage *adrss);
    static u32 *getFree();



    //    pageManagment();
    //    pageManagment(const pageManagment& orig);
    //    virtual ~pageManagment();
private:

};

#endif	/* PAGEMANAGMENT_H */

