

#include <stdbool.h>
#include "uart.h"
#include "dc_motor_with_enc.h"
#include "decode_packet.h"
#include "main.h"

int current_check();
void sequence_start();
int motor_timeout_check();
