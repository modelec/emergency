#include <fstream>
#include <iostream>
#include "serialib.h"

#define SERIAL_PORT "/dev/USB_ARDUINO"
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

    std::string toSend = "G " + line + "\n";

    std::cout << toSend << std::endl;

    serial.writeBytes(toSend.c_str(), toSend.length());

    serial.closeDevice();
    file.close();

    return 0;
}
