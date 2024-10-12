#ifndef __KEY_H
#define __KEY_H
#include "config.h"

// ¶¨Òå×´Ì¬Ã¶¾Ù
typedef enum {
    WAIT_PRESS,
    DEBOUNCE,
    KEY_PRESSED
} KeyState;

u8 read_jtkey(void);
u8 read_start_jtkey(void);

u8 read_insertion(void);
u8 read_start_insertion(void);

#endif
