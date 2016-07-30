/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   application.cpp
 * Author: david
 * 
 * Created on 10 de Julho de 2016, 09:58
 */

#include "application.h"

application::application() {
}

//application::application(const application& orig) {
//}
//
//application::~application() {
//}

u32 application::PID;

void AppMain() {
    
    asm (""
                : "=a"(application::PID) /* output */
                :  /* input */
                );
    //asm("movl %%eax,%0\n;" "=m" (application::PID));

    main();

    asm (
                "int $0x80;"
                :
                : "a"(sys_call_killTask), "c" (application::PID) /* input */
                );
}

u32 application::getPid(){
    return PID;
}

 void application::createTask(const s8 *String){
     
      static CallsDirectives call, *callp;
    callp = &call;
    callp->String = String;
 
     
     asm (
                "int $0x80;"
                :
                : "a"(sys_call_startTask), "c" (application::PID) /* input */
                );
 }