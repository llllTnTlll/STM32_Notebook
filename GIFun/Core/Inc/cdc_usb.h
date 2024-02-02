/*
 * cdc_usb.h
 *
 *  Created on: Jan 28, 2024
 *      Author: zhiyuan
 */

#ifndef INC_CDC_USB_H_
#define INC_CDC_USB_H_

#include "delay.h"
#include "usbd_cdc_if.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum{
	SHAKE_HAND = 0x00,
	SHAKE_HAND_BACK = 0x01,
	REQUEST_NEW_FREAM = 0x02,
}USB_CMD;

enum USB_DATA_LENGTH{
	CMD_LEN = 1,
	FRAME_DATA_LEN = 1024,
};

void ResetBuffer();
void RecvData(uint32_t Len);
void TransmitCMD(USB_CMD cmd);
void ShakeHand(uint32_t freq);

#ifdef __cplusplus
}
#endif

#endif /* INC_CDC_USB_H_ */
