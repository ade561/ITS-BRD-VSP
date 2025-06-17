#include "message.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>




char* readMessage(struct Message message) {
    char* functionName = message.functionName;

    if (strcmp(functionName, "functionOne") == 0) {
        //functionOne(message);
        fflush(stdout);
    } else if (strcmp(functionName, "functionTwo") == 0) {
        //functionTwo(message);
        fflush(stdout);
    } else {
        printf("Unbekannte Funktion: %s\n", functionName);
    }

    return NULL;
}

struct Message buildMessage(char* functionName, char* msgText, char* serverIP, char* clientIP) {
    struct Message m;
    strncpy(m.functionName, functionName, sizeof(m.functionName) - 1);
    m.functionName[sizeof(m.functionName) - 1] = '\0';

    strncpy(m.msg, msgText, sizeof(m.msg) - 1);
    m.msg[sizeof(m.msg) - 1] = '\0';

    strncpy(m.srcIP, clientIP, sizeof(m.srcIP) - 1);
    m.srcIP[sizeof(m.srcIP) - 1] = '\0';

    strncpy(m.dstIP, serverIP, sizeof(m.dstIP) - 1);
    m.dstIP[sizeof(m.dstIP) - 1] = '\0';

    return m;
}


char* readLine() {
    char buffer[MAX_INPUT];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) return NULL;

    buffer[strcspn(buffer, "\n")] = '\0';  // \n entfernen

    // Dynamischen Speicher reservieren für genau die Länge
    char* result = malloc(strlen(buffer) + 1);
    if (result != NULL) {
        strcpy(result, buffer);
    }
    return result;
}