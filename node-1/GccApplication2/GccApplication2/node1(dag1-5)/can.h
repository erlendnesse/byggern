#ifndef CAN_H_
#define CAN_H_


struct Message {
    uint16_t id;
    uint8_t length;
    uint8_t data[8];
};


void mcp2515_transmission(struct Message msg);
struct Message mcp2515_reception(); 
void mcp2515_print(char *str);


#endif