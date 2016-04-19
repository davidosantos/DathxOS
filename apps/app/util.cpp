#include "util.h"

bool strcmp(const s8* str1, const s8 *str2) {

    while (*str1 != 0) {
        if (*str1++ == *str2++) {
            if(*str1 ==0){
               if(*str2 != 0)
                   return false;
            }
        } else {
            return false;
        }
    }
    return true;
}