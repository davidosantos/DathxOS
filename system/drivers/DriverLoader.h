/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DriveLoader.h
 * Author: david
 *
 * Created on 26 de Maio de 2016, 18:39
 */

#ifndef DRIVELOADER_H
#define DRIVELOADER_H

#include "../../util/util.h"
#include "../RunTime/ElfLoader.h"

extern "C" u32 intsStart;
extern "C" u32 intsEnd;

class DriverLoader {
public:
    
    DriverLoader();
    static void loadDriver(const s8 *file);
//    DriveLoader(const DriveLoader& orig);
//    virtual ~DriveLoader();
private:
    

};

#endif /* DRIVELOADER_H */

