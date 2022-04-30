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
 * @file      driver_tsl2561_interrupt.c
 * @brief     driver tsl2561 interrupt source file
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

#include "driver_tsl2561_interrupt.h"

static tsl2561_handle_t gs_handle;        /**< tsl2561 handle */

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
                               uint16_t ch0_low_threshold, uint16_t ch0_high_threshold)
{
    uint8_t res;
    
    /* link interface function */
    DRIVER_TSL2561_LINK_INIT(&gs_handle, tsl2561_handle_t);
    DRIVER_TSL2561_LINK_IIC_INIT(&gs_handle, tsl2561_interface_iic_init);
    DRIVER_TSL2561_LINK_IIC_DEINIT(&gs_handle, tsl2561_interface_iic_deinit);
    DRIVER_TSL2561_LINK_IIC_READ(&gs_handle, tsl2561_interface_iic_read);
    DRIVER_TSL2561_LINK_IIC_WRITE(&gs_handle, tsl2561_interface_iic_write);
    DRIVER_TSL2561_LINK_DELAY_MS(&gs_handle, tsl2561_interface_delay_ms);
    DRIVER_TSL2561_LINK_DEBUG_PRINT(&gs_handle, tsl2561_interface_debug_print);
    
    /* set iic address */
    res = tsl2561_set_addr_pin(&gs_handle, addr_pin);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: set addr pin failed.\n");
        
        return 1;
    }
    
    /* tsl2561 init */
    res = tsl2561_init(&gs_handle);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: init failed.\n");
        
        return 1;
    }
    
    /* wake up */
    res = tsl2561_wake_up(&gs_handle);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: wake up failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set gain */
    res = tsl2561_set_gain(&gs_handle, TSL2561_INTERRUPT_DEFAULT_GAIN);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: set gain failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set integration time */
    res = tsl2561_set_integration_time(&gs_handle, TSL2561_INTERRUPT_DEFAULT_INTEGRATION_TIME);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: set integration time failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set interrupt mode */
    res =tsl2561_set_interrupt_mode(&gs_handle, mode);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: set interrupt mode failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set interrupt */
    res = tsl2561_set_interrupt(&gs_handle, TSL2561_BOOL_TRUE);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: disable interrupt failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set interrupt high threshold */
    res = tsl2561_set_interrupt_high_threshold(&gs_handle, ch0_high_threshold);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: set interrupt high threshold failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set interrupt low threshold */
    res = tsl2561_set_interrupt_low_threshold(&gs_handle, ch0_low_threshold);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: set interrupt low threshold failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    
    return 0;
}

/**
 * @brief      interrupt example read
 * @param[out] *lux points to a lux buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t tsl2561_interrupt_read(uint32_t *lux)
{
    uint16_t channel_0_raw;
    uint16_t channel_1_raw;
    
    /* read data */
    if (tsl2561_read(&gs_handle, (uint16_t *)&channel_0_raw, (uint16_t *)&channel_1_raw, lux) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief  interrupt example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t tsl2561_interrupt_deinit(void)
{
    /* close tsl2561 */
    if (tsl2561_deinit(&gs_handle) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
