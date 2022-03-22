/*
 *****************************************************************************
 *  @file   BME680_Lib.h
 *  @author Horst Rupp
 *  @brief  Created on: 21.11.2020
 *  @brief  Last Change : 28.11.2020
 *  @brief  These are the valid IDs for any data transfer on the CAN Bus.
 *****************************************************************************
 */


#ifndef  __BME680_Lib_h
  #define  __BME680_Lib_h

  #include "bme68x_defs.h"
  #include "bme68x.h"

  BME68X_INTF_RET_TYPE bme68x_i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr);
  BME68X_INTF_RET_TYPE bme68x_i2c_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len, void *intf_ptr);
  void bme68x_delay_us(uint32_t period, void *intf_ptr);
  int8_t bme68x_interface_init(struct bme68x_dev *bme, uint8_t intf);

#endif
// ****************************************************************************
//  EOF
// ****************************************************************************

