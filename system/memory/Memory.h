/* 
 * File:   New.h
 * Author: davidosantos
 *
 * Created on June 25, 2015, 9:16 PM
 */

#ifndef NEW_H
#define	NEW_H

#include "../../util/util.h"
#include "Paging.h"

#ifdef	__cplusplus
extern "C" {
#endif





    void *operator new( unsigned int size);

    void *operator new[](unsigned int size);

    void operator delete(void *p);

    void operator delete[](void *p);

    u32 getUsedMemory();

    u32 getNewPage();

#ifdef	__cplusplus
}
#endif

#endif	/* NEW_H */

