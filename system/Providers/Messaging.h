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

#define Type_unread       1
#define Type_read         2
#define Type_removed      3

class Messaging {
public:

    struct MessageAddrs {
        bool read;
        u8 type;
        s8 keychar;

        union {

            struct {
u8:
                7,
                upKey : 1;
            };
            u8 keycode;
        };
    } __attribute__((packed));

    struct inbox {
        u16 inboxCapacity;
        MessageAddrs *Messages;
    } __attribute__((packed));

    static inbox getNewInbox();

    static void broadcastMessage(MessageAddrs *Message);

    static MessageAddrs readMessage(u32 pid);

    static MessageAddrs readMessage();

    static bool isThereMessage(u32 pid);

    static bool isThereMessage();

    static MessageAddrs *initMessaging(u32 pid);

    static void initMessaging();

    Messaging();
    //    Message(const Message& orig);
    //    virtual ~Message();
private:

};
#include "../../system/Tasks/Tasks.h"
#endif /* MESSAGE_H */

