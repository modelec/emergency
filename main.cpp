#include <fstream>
#include <iostream>
#include "serialib.h"

#define SERIAL_PORT "/dev/USB_ARDUINO"
#define MAX_MESSAGE_LEN 1048
#define TIME_OUT 500
#define BAUDS 115200 //vitesse des données (bit/sec)

serialib init_serial(){
    serialib serial;
    char errorOpening = serial.openDevice(SERIAL_PORT, BAUDS);
    if (errorOpening!=1) exit(errorOpening);
    return serial;
}

int main(int argc, char *argv[]) {
    std::string filePath;

    if (argc == 2) {
        filePath = argv[1];
    } else {
        return 0;
    }

    std::ifstream file;
    file.open(filePath);
    std::string line;
    getline(file, line);

    serialib serial = init_serial();

    int errorCode;
    char myString[MAX_MESSAGE_LEN] = {0};

    std::string toSend = "G " + line + "\n";
    strcpy(myString, toSend.c_str());
    myString[strlen(myString)] = '\0';

    errorCode = serial.writeBytes(toSend.c_str(), toSend.length());

    std::cout << "Code received: " << errorCode << std::endl;

    serial.closeDevice();
    file.close();

    return 0;
}
