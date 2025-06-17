//
// Created by Darius on 08.06.25.
//

#ifndef MESSAGE_H
#define MESSAGE_H
#define MAX_INPUT 512




struct Message {
    char functionName[100];
    char msg[100];
    char srcIP[15];
    char dstIP[15];
};
char* readLine();
char* readMessage(struct Message message);
struct Message buildMessage(char* functionName, char* msg,char* serverIP,char* clientIP);




#endif //MESSAGE_H
