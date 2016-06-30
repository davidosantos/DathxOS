/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "../../../../Dathx OS/system/Providers/Messaging.h"
#include "../../../../Dathx OS/util/util.h"
#include "system/RunTime/SysCallHandler.h"

Messaging::Messaging() {
}

//Message::Message(const Message& orig) {
//}
//
//Message::~Message() {
//}

void Messaging::broadcastMessage(MessageAddrs *Message) {
    
   

    asm (
                "int $0x80;"
                :
                : "a"(sys_call_broadCastMessage), "c" (Message->keycode), "d" (Message->keychar)  /* input */
                );
}
void Messaging::initMessaging() {

    asm ( "int $0x80;"
                :  /* output */
                : "a" (sys_call_initiateMessaging) /* input */
                );
    
}

Messaging::MessageAddrs Messaging::readMessage() {
    Messaging::MessageAddrs message;


    asm ( "int $0x80;"
                : "=a"(message.keycode), "=c" (message.keychar) /* output */
                : "a" (sys_call_readMessage) /* input */
                );
    return message;
}

bool Messaging::isThereMessage() {
    u32 value = 0;

    asm ( "int $0x80;"
                : "=a"(value) /* output */
                : "a" (sys_call_isThereMessage) /* input */
                );
    return value == 1 ? true : false;
}