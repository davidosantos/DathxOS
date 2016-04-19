/* 
 * File:   autoCheck.h
 * Author: david
 *
 * Created on 12 de Novembro de 2015, 20:23
 */

#ifndef AUTOCHECK_H
#define	AUTOCHECK_H

#include "memory/Paging.h"
#include "processor.h"
#include "monitor/Console.h"

#define notPresent 0

extern u32 totalMemoryAdress;

class autoCheck {
public:
    
    static void runCheck();
    
   // autoCheck();
    //autoCheck(const autoCheck& orig);
   // virtual ~autoCheck();
private:

};

#endif	/* AUTOCHECK_H */

