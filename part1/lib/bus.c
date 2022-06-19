#include <bus.h>

u8 bus_read(u16 address){   //reads from rom
    if (address < 0x8000){//ROM Data
        return cart_read(address);  // if less than addeess 0x8000 return the cartridge address
    }

    NO_IMPL //else no implemented yet
}
void bus_write(u16 address, u8 value){
    if(address < 0x8000){//wrtie to ROM
        cart_write(address,value);
        return;
    }

    NO_IMPL
}