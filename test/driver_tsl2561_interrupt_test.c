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
 * @file      driver_tsl2561_interrupt_test.c
 * @brief     driver tsl2561 interrupt test source file
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
 
#include "driver_tsl2561_interrupt_test.h"

static tsl2561_handle_t gs_handle;        /**< tsl2561 handle */

/**
 * @brief     interrupt test
 * @param[in] addr_pin is the iic device address
 * @param[in] mode is the interrupt mode
 * @param[in] ch0_low_threshold is the channel 0 interrupt low threshold
 * @param[in] ch0_high_threshold is the channel 0 interrupt high threshold
 * @param[in] times is the test times
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t tsl2561_interrupt_test(tsl2561_address_t addr_pin, tsl2561_interrupt_mode_t mode, 
                               uint16_t ch0_low_threshold, uint16_t ch0_high_threshold, uint32_t times)
{
    uint8_t res; 
    uint16_t channel_0_raw;
    uint16_t channel_1_raw;
    uint32_t lux;
    tsl2561_info_t info;
    
    /* link interface function */
    DRIVER_TSL2561_LINK_INIT(&gs_handle, tsl2561_handle_t);
    DRIVER_TSL2561_LINK_IIC_INIT(&gs_handle, tsl2561_interface_iic_init);
    DRIVER_TSL2561_LINK_IIC_DEINIT(&gs_handle, tsl2561_interface_iic_deinit);
    DRIVER_TSL2561_LINK_IIC_READ(&gs_handle, tsl2561_interface_iic_read);
    DRIVER_TSL2561_LINK_IIC_WRITE(&gs_handle, tsl2561_interface_iic_write);
    DRIVER_TSL2561_LINK_DELAY_MS(&gs_handle, tsl2561_interface_delay_ms);
    DRIVER_TSL2561_LINK_DEBUG_PRINT(&gs_handle, tsl2561_interface_debug_print);

    /* get chip information */
    res = tsl2561_info(&info);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print chip information */
        tsl2561_interface_debug_print("tsl2561: chip is %s.\n", info.chip_name);
        tsl2561_interface_debug_print("tsl2561: manufacturer is %s.\n", info.manufacturer_name);
        tsl2561_interface_debug_print("tsl2561: interface is %s.\n", info.interface);
        tsl2561_interface_debug_print("tsl2561: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        tsl2561_interface_debug_print("tsl2561: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        tsl2561_interface_debug_print("tsl2561: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        tsl2561_interface_debug_print("tsl2561: max current is %0.2fmA.\n", info.max_current_ma);
        tsl2561_interface_debug_print("tsl2561: max temperature is %0.1fC.\n", info.temperature_max);
        tsl2561_interface_debug_print("tsl2561: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* set iic address */
    res = tsl2561_set_addr_pin(&gs_handle, addr_pin);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: set addr pin failed.\n");
        
        return 1;
    }
    
    /* start interrupt test */
    tsl2561_interface_debug_print("tsl2561: start interrupt test.\n");
    
    /* tsl2561 init */
    res = tsl2561_init(&gs_handle);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: init failed.\n");
        
        return 1;
    }
    
    /* wake up chip */
    res = tsl2561_wake_up(&gs_handle);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: wake up failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set gain 16 */
    res = tsl2561_set_gain(&gs_handle, TSL2561_GAIN_16);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: set gain failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set integration time 101 */
    res = tsl2561_set_integration_time(&gs_handle, TSL2561_INTEGRATION_TIME_101MS);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: set integration time failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set interrupt mode */
    res = tsl2561_set_interrupt_mode(&gs_handle, mode);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: set interrupt mode failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    
    /* enable interrupt */
    res = tsl2561_set_interrupt(&gs_handle, TSL2561_BOOL_TRUE);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: enable interrupt failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set high_threshold */
    res = tsl2561_set_interrupt_high_threshold(&gs_handle, ch0_high_threshold);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: set interrupt high threshold failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set low threshold */
    res = tsl2561_set_interrupt_low_threshold(&gs_handle, ch0_low_threshold);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: set interrupt low threshold failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    while (times != 0)
    {
        tsl2561_interface_delay_ms(2000);
    
        /* read data */
        res = tsl2561_read(&gs_handle, (uint16_t *)&channel_0_raw, (uint16_t *)&channel_1_raw, (uint32_t *)&lux);
        if (res != 0)
        {
            tsl2561_interface_debug_print("tsl2561: read failed.\n");
            (void)tsl2561_deinit(&gs_handle);
            
            return 1;
        }
        tsl2561_interface_debug_print("tsl2561: read 0x%04X and check interrupt.\n", channel_0_raw);
        times--;
    }

    /* finish interrupt test */
    tsl2561_interface_debug_print("tsl2561: finish interrupt test.\n");
    (void)tsl2561_deinit(&gs_handle);
    
    return 0;
}
