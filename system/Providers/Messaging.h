/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Message.h
 * Author: david
 *
 * Created on 18 de Junho de 2016, 14:22
 */

#ifndef MESSAGE_H
#define MESSAGE_H

#include "../../util/util.h"
#include "../../system/memory/Paging.h"
#include "../../system/memory/Memory.h"



class Messaging {
    
public:
    
    struct message{
        bool read;
        u8 type;
        s8 keychar;
        u8 keycode;
    }__attribute__((packed));
    
    struct inbox{
        u16 messageIndex;
        u16 inboxCapacity;
        bool full;
        message *Messages;
    }__attribute__((packed));
    
    static inbox getNewInbox();
    
    static void broadcastMessage(message *Message);
    
    static inbox readMessage(u16 messageIndex);
    
    static bool isThereMessage();
   
    Messaging();
//    Message(const Message& orig);
//    virtual ~Message();
private:

};
#include "../../system/Tasks/Tasks.h"
#endif /* MESSAGE_H */

