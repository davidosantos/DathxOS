/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Message.cpp
 * Author: david
 * 
 * Created on 18 de Junho de 2016, 14:22
 */

#include "Messaging.h"

Messaging::Messaging() {
}

//Message::Message(const Message& orig) {
//}
//
//Message::~Message() {
//}

Messaging::inbox Messaging::getNewInbox() {
    inbox inboxVar;
    inboxVar.Messages = new message [pageSize / sizeof (message)];
    inboxVar.inboxCapacity = (pageSize / sizeof (message));
    return inboxVar;
}

void Messaging::broadcastMessage(message *Message) {
    for (u32 i = 0; i < Tasks::TaskCount; i++) {
        if (Tasks::getTask(i).MessageListener) {
            if (Tasks::getTask(i).inboxAddrss.messageIndex <=
                    Tasks::getTask(i).inboxAddrss.inboxCapacity){

                Tasks::getTask(i).inboxAddrss.Messages[
                    Tasks::getTask(i).inboxAddrss.messageIndex] = *Message;
                
                Tasks::TasksList[i].inboxAddrss.messageIndex++;
            } else {
                Tasks::TasksList[i].inboxAddrss.full = true;
            }
        }
    }
}
