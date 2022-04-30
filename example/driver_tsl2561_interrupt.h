/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_tsl2561_interrupt.h
 * @brief     driver tsl2561 interrupt header file
 * @version   2.0.0
 * @author    Shifeng Li
 * @date      2021-02-26
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2021/02/26  <td>2.0      <td>Shifeng Li  <td>format the code
 * <tr><td>2020/10/28  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#ifndef DRIVER_TSL2561_INTERRUPT_H
#define DRIVER_TSL2561_INTERRUPT_H

#include <driver_tsl2561_interface.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @addtogroup tsl2561_example_driver
 * @{
 */

/**
 * @brief tsl2561 interrupt example default definition
 */
#define TSL2561_INTERRUPT_DEFAULT_GAIN                     TSL2561_GAIN_16                       /**< gain 16 */
#define TSL2561_INTERRUPT_DEFAULT_INTEGRATION_TIME         TSL2561_INTEGRATION_TIME_402MS        /**< 402ms integration time */

/**
 * @brief     interrupt example init
 * @param[in] addr_pin is the iic device address
 * @param[in] mode is the interrupt mode
 * @param[in] ch0_low_threshold is the channel 0 interrupt low threshold
 * @param[in] ch0_high_threshold is the channel 0 interrupt high threshold
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t tsl2561_interrupt_init(tsl2561_address_t addr_pin, tsl2561_interrupt_mode_t mode, 
                               uint16_t ch0_low_threshold, uint16_t ch0_high_threshold);

/**
 * @brief  interrupt example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t tsl2561_interrupt_deinit(void);

/**
 * @brief      interrupt example read
 * @param[out] *lux points to a lux buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t tsl2561_interrupt_read(uint32_t *lux);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
