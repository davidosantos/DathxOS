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
    inboxVar.Messages = new MessageAddrs();
    inboxVar.inboxCapacity = (pageSize / sizeof (MessageAddrs));
    return inboxVar;
}

void Messaging::broadcastMessage(MessageAddrs *Message) {
    //Console::clear();
    for (u32 taskIndex = 0; taskIndex <= Tasks::TaskCount; taskIndex++) {
        if (Tasks::getTask(taskIndex).MessageListener) {
            for (u16 messageIndex = 0; messageIndex <
                    Tasks::getTask(taskIndex).inboxAddrss.inboxCapacity; messageIndex++) {


                //Console::print("[messageIndex].type %i", Tasks::TasksList[taskIndex].inboxAddrss.Messages[messageIndex].type);
                if (Tasks::TasksList[taskIndex].inboxAddrss.Messages[messageIndex].type == Type_read ||
                        Tasks::TasksList[taskIndex].inboxAddrss.Messages[messageIndex].type == 0) {

                    Tasks::TasksList[taskIndex].inboxAddrss.Messages[messageIndex] = *Message;
                    break;
                }

            }
        }
    }
}

Messaging::MessageAddrs *Messaging::initMessaging(u32 pid) {
    Tasks::getTaskbyPid(pid)->MessageListener = true;
    Tasks::getTaskbyPid(pid)->inboxAddrss = getNewInbox();
    return Tasks::getTaskbyPid(pid)->inboxAddrss.Messages;
}

Messaging::MessageAddrs Messaging::readMessage(u32 pid) {
     for (u32 i = 0; i < Tasks::getTaskbyPid(pid)->inboxAddrss.inboxCapacity; i++) {
        if (Tasks::getTaskbyPid(pid)->inboxAddrss.Messages[i].type == Type_unread) {
            Tasks::getTaskbyPid(pid)->inboxAddrss.Messages[i].type = Type_read;
            return Tasks::getTaskbyPid(pid)->inboxAddrss.Messages[i];
        }
    }
    Messaging::MessageAddrs newMes;
    return newMes;
}

bool Messaging::isThereMessage(u32 pid) {
    for (u32 i = 0; i < Tasks::getTaskbyPid(pid)->inboxAddrss.inboxCapacity; i++) {
        if (Tasks::getTaskbyPid(pid)->inboxAddrss.Messages[i].type == Type_unread) {
            return true;
        }
    }
    return false;
}