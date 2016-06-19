/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "../../../../Dathx OS/system/Providers/Messaging.h"
#include "../../../../Dathx OS/util/util.h"
#include "../../Syscalls.h"

Messaging::Messaging() {
}

//Message::Message(const Message& orig) {
//}
//
//Message::~Message() {
//}

void Messaging::broadcastMessage(message *Message) {
    
    static CallsDirectives call, *callp;
    callp = &call;
   
    callp->Function = BroadCastMessage;
    callp->Value = (u32) Message;

    asm("movl %0,%%eax" ::"m" (callp) : "eax");
    asm("int $0x80");
}
