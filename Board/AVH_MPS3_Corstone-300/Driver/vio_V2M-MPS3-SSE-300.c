/******************************************************************************
 * @file     vio.c
 * @brief    Virtual I/O implementation template
 * @version  V2.0.0
 * @date     18. October 2023
 ******************************************************************************/
/*
 * Copyright (c) 2019-2023 Arm Limited (or its affiliates).
 * All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*! \page vio_V2M-MPS3-SSE-300 Physical I/O Mapping
The table below lists the physical I/O mapping of this CMSIS-Driver VIO implementation.
Virtual Resource  | Variable       | Physical Resource on V2M-MPS3-SSE-300          |
:-----------------|:---------------|:-----------------------------------------------|
vioBUTTON0        | vioSignalIn.0  | User Button PB1                                |
vioBUTTON1        | vioSignalIn.1  | User Button PB1                                |
vioLED0           | vioSignalOut.0 | User LED UL0                                   |
vioLED1           | vioSignalOut.1 | User LED UL1                                   |
vioLED2           | vioSignalOut.2 | User LED UL2                                   |
vioLED3           | vioSignalOut.3 | User LED UL3                                   |
vioLED4           | vioSignalOut.4 | User LED UL4                                   |
vioLED5           | vioSignalOut.5 | User LED UL5                                   |
vioLED6           | vioSignalOut.6 | User LED UL6                                   |
vioLED7           | vioSignalOut.7 | User LED UL7                                   |
*/

/* History:
 *  Version 2.0.0
 *    Updated to API 1.0.0
 *  Version 1.0.0
 *    Initial release
 */

#include <string.h>
#include "cmsis_vio.h"

#include "RTE_Components.h"                 // Component selection
#include CMSIS_device_header

#if !defined CMSIS_VOUT || !defined CMSIS_VIN
#include "arm_mps3_io_drv.h"
#include "device_cfg.h"
#include "device_definition.h"
#endif

// VIO input, output definitions
#define VIO_VALUE_NUM           3U          // Number of values

// VIO input, output variables
__USED uint32_t vioSignalIn;                // Memory for incoming signal
__USED uint32_t vioSignalOut;               // Memory for outgoing signal
__USED int32_t  vioValue[VIO_VALUE_NUM];    // Memory for value used in vioGetValue/vioSetValue

#if !defined CMSIS_VOUT
// Add global user types, variables, functions here:

#endif

#if !defined CMSIS_VIN
// Add global user types, variables, functions here:

#endif

// Initialize test input, output.
void vioInit (void) {
#if !defined CMSIS_VOUT
// Add user variables here:

#endif
#if !defined CMSIS_VIN
// Add user variables here:

#endif

  vioSignalIn  = 0U;
  vioSignalOut = 0U;

  memset(vioValue, 0, sizeof(vioValue));

#if !defined CMSIS_VOUT
  // Turn off all LEDs
  arm_mps3_io_write_leds(&MPS3_IO_DEV, ARM_MPS3_IO_ACCESS_PORT, 0U, 0U);
#endif

#if !defined CMSIS_VIN
// Add user code here:

#endif
}

// Set signal output.
void vioSetSignal (uint32_t mask, uint32_t signal) {
#if !defined CMSIS_VOUT
  uint32_t n;
#endif

  vioSignalOut &= ~mask;
  vioSignalOut |=  mask & signal;

#if !defined CMSIS_VOUT
  for (n = 0U; n < 8U; n++) {
    if (mask & (1U << n)) {
      arm_mps3_io_write_leds(&MPS3_IO_DEV, ARM_MPS3_IO_ACCESS_PIN, n, signal & (1U << n));
    }
  }
#endif
}

// Get signal input.
uint32_t vioGetSignal (uint32_t mask) {
  uint32_t signal;
#if !defined CMSIS_VIN
// Add user variables here:

#endif

#if !defined CMSIS_VIN
  vioSignalIn = arm_mps3_io_read_buttons(&MPS3_IO_DEV, ARM_MPS3_IO_ACCESS_PORT, 0);
#endif

  signal = vioSignalIn & mask;

  return signal;
}

// Set value output.
void vioSetValue (uint32_t id, int32_t value) {
  uint32_t index = id;
#if !defined CMSIS_VOUT
// Add user variables here:

#endif

  if (index >= VIO_VALUE_NUM) {
    return;                             /* return in case of out-of-range index */
  }

  vioValue[index] = value;

#if !defined CMSIS_VOUT
// Add user code here:

#endif
}

// Get value input.
int32_t vioGetValue (uint32_t id) {
  uint32_t index = id;
  int32_t  value = 0;
#if !defined CMSIS_VIN
// Add user variables here:

#endif

  if (index >= VIO_VALUE_NUM) {
    return value;                       /* return default in case of out-of-range index */
  }

#if !defined CMSIS_VIN
// Add user code here:

//   vioValue[index] = ...;
#endif

  value = vioValue[index];

  return value;
}
