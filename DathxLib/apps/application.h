/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   application.h
 * Author: david
 *
 * Created on 10 de Julho de 2016, 09:58
 */

#ifndef APPLICATION_H
#define APPLICATION_H
#include <system/RunTime/SysCallHandler.h>

/**
 * This function is defined inside application.cpp, it is declared as extern
 * so that the compiler doesn't change its name, so it can be referenced inside
 * link.ld script. This function will call main in the user application and
 * it is will do a system call do stop the running application when main returns.
 */
extern "C" void AppMain();

extern "C" int main();

class application {
public:
    
    static u32 getPid();
    
    static u32 PID;
    
    static void createTask(const s8 *String);
    
    application();
//    application(const application& orig);
//    virtual ~application();
private:

};

#endif /* APPLICATION_H */

