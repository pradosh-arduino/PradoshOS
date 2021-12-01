#pragma once
#include <stdint.h>

void outb(uint16_t port, uint8_t value);
uint8_t inb(uint16_t port);
void outw(uint16_t portNumber, uint16_t data);
uint16_t inw(uint16_t portNumber);
uint32_t inl(uint16_t portNumber);
void outl(uint16_t portNumber, uint32_t data);
void io_wait();