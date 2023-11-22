/*
 * IncFile1.h
 *
 * Created: 03.10.2023 13:22:45
 *  Author: erleness
 */ 


#ifndef MCP_H__
#define MCP_H__

#include "mcp2515.h"
#include <stdint.h>


int mcp2515_init();
void mcp2515_write(uint8_t address, uint8_t data);
uint8_t mcp2515_read(uint8_t address);
void mcp2515_reset();
void mcp2515_rts(int buffer);
uint8_t mcp2515_read_status();
void mcp2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data);
void mcp2515_mode_select(uint8_t mode);
#endif 