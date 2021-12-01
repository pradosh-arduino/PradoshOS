#pragma once

#define PORT 0x2f8 // com2
#define COM1 0x3f8
#define COM3 0x3e8
#define COM4 0x2e8

class SerialCOM{
    public:
    bool serial_configure_baud_rate(unsigned short com, unsigned short divisor);
    uint8_t read_serial();
    void write_serial(char a);
};

extern SerialCOM* GlobalSerial;