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
 * @file      driver_tsl2561_register_test.c
 * @brief     driver tsl2561 register test source file
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

#include "driver_tsl2561_register_test.h"
#include <stdlib.h>

static tsl2561_handle_t gs_handle;        /**< tsl2561 handle */

/**
 * @brief     register test
 * @param[in] addr is the iic device address
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t tsl2561_register_test(tsl2561_address_t addr)
{
    uint8_t res;
    uint16_t ch0, ch0_check;
    tsl2561_info_t info;
    tsl2561_address_t addr_pin;
    tsl2561_gain_t gain;
    tsl2561_interrupt_mode_t mode;
    tsl2561_integration_time_t t;
    tsl2561_bool_t enable;
    
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
    
    /* start register test */
    tsl2561_interface_debug_print("tsl2561: start register test.\n");
    
    /* tsl2561_set_addr_pin/tsl2561_get_addr_pin test */
    tsl2561_interface_debug_print("tsl2561: tsl2561_set_addr_pin/tsl2561_get_addr_pin test.\n");
    
    /* set ADDRESS_GND */
    res = tsl2561_set_addr_pin(&gs_handle, TSL2561_ADDRESS_GND);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: set addr pin failed.\n");
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: set addr pin ADDRESS_GND.\n");
    res = tsl2561_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: get addr pin failed.\n");
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: check addr pin %s.\n", addr_pin == TSL2561_ADDRESS_GND ? "ok" : "error");
    
    /* set ADDRESS_FLOAT */
    res = tsl2561_set_addr_pin(&gs_handle, TSL2561_ADDRESS_FLOAT);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: set addr pin failed.\n");
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: set addr pin ADDRESS_FLOAT.\n");
    res = tsl2561_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: get addr pin failed.\n");
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: check addr pin %s.\n", addr_pin == TSL2561_ADDRESS_FLOAT ? "ok" : "error");
    
    /* set ADDRESS_VCC */
    res = tsl2561_set_addr_pin(&gs_handle, TSL2561_ADDRESS_VCC);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: set addr pin failed.\n");
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: set addr pin ADDRESS_VCC.\n");
    res = tsl2561_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: get addr pin failed.\n");
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: check addr pin %s.\n", addr_pin == TSL2561_ADDRESS_VCC ? "ok" : "error");
    
    /* set iic address */
    res = tsl2561_set_addr_pin(&gs_handle, addr);
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
    
    /* tsl2561_power_down test */
    tsl2561_interface_debug_print("tsl2561: tsl2561_power_down test.\n");
    res = tsl2561_power_down(&gs_handle);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: set power down failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: check power down %s.\n", res == 0 ? "ok" : "error");
    
    /* tsl2561_wake_up test */
    tsl2561_interface_debug_print("tsl2561: tsl2561_wake_up test.\n");
    res = tsl2561_wake_up(&gs_handle);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: set wake up failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: check wake up %s.\n", res == 0 ? "ok" : "error");
    
    /* tsl2561_set_interrupt/tsl2561_get_interrupt test */
    tsl2561_interface_debug_print("tsl2561: tsl2561_set_interrupt/tsl2561_get_interrupt test.\n");
    
    /* enable interrupt */
    res = tsl2561_set_interrupt(&gs_handle, TSL2561_BOOL_TRUE);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: set interrupt failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    res = tsl2561_get_interrupt(&gs_handle, &enable);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: get interrupt failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: check interrupt %s.\n", enable == TSL2561_BOOL_TRUE ? "ok" : "error");
    
    /* disable interrupt */
    res = tsl2561_set_interrupt(&gs_handle, TSL2561_BOOL_FALSE);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: set interrupt failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    res = tsl2561_get_interrupt(&gs_handle, &enable);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: get interrupt failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: check interrupt %s.\n", enable == TSL2561_BOOL_FALSE ? "ok" : "error");
    
    /* tsl2561_set_gain/tsl2561_get_gain test */
    tsl2561_interface_debug_print("tsl2561: tsl2561_set_gain/tsl2561_get_gain test.\n");
    
    /* set gain 1 */
    res = tsl2561_set_gain(&gs_handle, TSL2561_GAIN_1);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: set gain failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: set gain 1.\n");
    res = tsl2561_get_gain(&gs_handle, &gain);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: get gain failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: check gain %s.\n", gain == TSL2561_GAIN_1 ? "ok" : "error");
    
    /* set gain 16 */
    res = tsl2561_set_gain(&gs_handle, TSL2561_GAIN_16);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: set gain failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: set gain 16.\n");
    res = tsl2561_get_gain(&gs_handle, &gain);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: get gain failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: check gain %s.\n", gain == TSL2561_GAIN_16 ? "ok" : "error");
    
    /* tsl2561_set_integration_time/tsl2561_get_integration_time test */
    tsl2561_interface_debug_print("tsl2561: tsl2561_set_integration_time/tsl2561_get_integration_time test.\n");
    
    /* set integration time 13 ms */
    res = tsl2561_set_integration_time(&gs_handle, TSL2561_INTEGRATION_TIME_13MS);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: set integration time failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: set integration time 13 ms.\n");
    res = tsl2561_get_integration_time(&gs_handle, &t);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: get integration time failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: check gain %s.\n", t == TSL2561_INTEGRATION_TIME_13MS ? "ok" : "error");
    
    /* set integration time 101 ms */
    res = tsl2561_set_integration_time(&gs_handle, TSL2561_INTEGRATION_TIME_101MS);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: set integration time failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: set integration time 101 ms.\n");
    res = tsl2561_get_integration_time(&gs_handle, &t);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: get integration time failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: check gain %s.\n", t == TSL2561_INTEGRATION_TIME_101MS ? "ok" : "error");
    
    /* set integration time 402 ms */
    res = tsl2561_set_integration_time(&gs_handle, TSL2561_INTEGRATION_TIME_402MS);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: set integration time failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: set integration time 402 ms.\n");
    res = tsl2561_get_integration_time(&gs_handle, &t);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: get integration time failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1; 
    }
    tsl2561_interface_debug_print("tsl2561: check gain %s.\n", t == TSL2561_INTEGRATION_TIME_402MS ? "ok" : "error");
    
    /* tsl2561_set_interrupt_mode/tsl2561_get_interrupt_mode test */
    tsl2561_interface_debug_print("tsl2561: tsl2561_set_interrupt_mode/tsl2561_get_interrupt_mode test.\n");
    
    /* set interrupt mode every adc cycle */
    res = tsl2561_set_interrupt_mode(&gs_handle, TSL2561_INTERRUPT_MODE_EVERY_ADC_CYCLE);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: set interrupt mode failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: set interrupt mode every adc cycle.\n");
    res = tsl2561_get_interrupt_mode(&gs_handle, &mode);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: get interrupt mode failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: check interrupt mode %s.\n", mode == TSL2561_INTERRUPT_MODE_EVERY_ADC_CYCLE ? "ok" : "error");
    
    /* set interrupt mode any value out of threshold range */
    res = tsl2561_set_interrupt_mode(&gs_handle, TSL2561_INTERRUPT_MODE_ANY_VALUE_OUT_OF_THRESHOLD_RANGE);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: set interrupt mode failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: set interrupt mode any value out of threshold range.\n");
    res = tsl2561_get_interrupt_mode(&gs_handle, &mode);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: get interrupt mode failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: check interrupt mode %s.\n", mode == TSL2561_INTERRUPT_MODE_ANY_VALUE_OUT_OF_THRESHOLD_RANGE ? "ok" : "error");
    
    /* set interrupt mode 2 integration time out of range */
    res = tsl2561_set_interrupt_mode(&gs_handle, TSL2561_INTERRUPT_MODE_2_INTEGRATION_TIME_OUT_OF_RANGE);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: set interrupt mode failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: set interrupt mode 2 integration time out of range.\n");
    res = tsl2561_get_interrupt_mode(&gs_handle, &mode);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: get interrupt mode failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: check interrupt mode %s.\n", mode == TSL2561_INTERRUPT_MODE_2_INTEGRATION_TIME_OUT_OF_RANGE ? "ok" : "error");
    
    /* set interrupt mode 3 integration time out of range */
    res = tsl2561_set_interrupt_mode(&gs_handle, TSL2561_INTERRUPT_MODE_3_INTEGRATION_TIME_OUT_OF_RANGE);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: set interrupt mode failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: set interrupt mode 3 integration time out of range.\n");
    res = tsl2561_get_interrupt_mode(&gs_handle, &mode);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: get interrupt mode failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: check interrupt mode %s.\n", mode == TSL2561_INTERRUPT_MODE_3_INTEGRATION_TIME_OUT_OF_RANGE ? "ok" : "error");
    
    /* set interrupt mode 4 integration time out of range */
    res = tsl2561_set_interrupt_mode(&gs_handle, TSL2561_INTERRUPT_MODE_4_INTEGRATION_TIME_OUT_OF_RANGE);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: set interrupt mode failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: set interrupt mode 4 integration time out of range.\n");
    res = tsl2561_get_interrupt_mode(&gs_handle, &mode);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: get interrupt mode failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: check interrupt mode %s.\n", mode == TSL2561_INTERRUPT_MODE_4_INTEGRATION_TIME_OUT_OF_RANGE ? "ok" : "error");
    
    /* set interrupt mode 5 integration time out of range */
    res = tsl2561_set_interrupt_mode(&gs_handle, TSL2561_INTERRUPT_MODE_5_INTEGRATION_TIME_OUT_OF_RANGE);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: set interrupt mode failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: set interrupt mode 5 integration time out of range.\n");
    res = tsl2561_get_interrupt_mode(&gs_handle, &mode);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: get interrupt mode failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: check interrupt mode %s.\n", mode == TSL2561_INTERRUPT_MODE_5_INTEGRATION_TIME_OUT_OF_RANGE ? "ok" : "error");
    
    /* set interrupt mode 6 integration time out of range */
    res = tsl2561_set_interrupt_mode(&gs_handle, TSL2561_INTERRUPT_MODE_6_INTEGRATION_TIME_OUT_OF_RANGE);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: set interrupt mode failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: set interrupt mode 6 integration time out of range.\n");
    res = tsl2561_get_interrupt_mode(&gs_handle, &mode);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: get interrupt mode failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: check interrupt mode %s.\n", mode == TSL2561_INTERRUPT_MODE_6_INTEGRATION_TIME_OUT_OF_RANGE ? "ok" : "error");
    
    /* set interrupt mode 7 integration time out of range */
    res = tsl2561_set_interrupt_mode(&gs_handle, TSL2561_INTERRUPT_MODE_7_INTEGRATION_TIME_OUT_OF_RANGE);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: set interrupt mode failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: set interrupt mode 7 integration time out of range.\n");
    res = tsl2561_get_interrupt_mode(&gs_handle, &mode);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: get interrupt mode failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: check interrupt mode %s.\n", mode == TSL2561_INTERRUPT_MODE_7_INTEGRATION_TIME_OUT_OF_RANGE ? "ok" : "error");
    
    /* set interrupt mode 8 integration time out of range */
    res = tsl2561_set_interrupt_mode(&gs_handle, TSL2561_INTERRUPT_MODE_8_INTEGRATION_TIME_OUT_OF_RANGE);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: set interrupt mode failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: set interrupt mode 8 integration time out of range.\n");
    res = tsl2561_get_interrupt_mode(&gs_handle, &mode);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: get interrupt mode failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: check interrupt mode %s.\n", mode == TSL2561_INTERRUPT_MODE_8_INTEGRATION_TIME_OUT_OF_RANGE ? "ok" : "error");
    
    /* set interrupt mode 9 integration time out of range */
    res = tsl2561_set_interrupt_mode(&gs_handle, TSL2561_INTERRUPT_MODE_9_INTEGRATION_TIME_OUT_OF_RANGE);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: set interrupt mode failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: set interrupt mode 9 integration time out of range.\n");
    res = tsl2561_get_interrupt_mode(&gs_handle, &mode);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: get interrupt mode failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: check interrupt mode %s.\n", mode == TSL2561_INTERRUPT_MODE_9_INTEGRATION_TIME_OUT_OF_RANGE ? "ok" : "error");
    
    /* set interrupt mode 10 integration time out of range */
    res = tsl2561_set_interrupt_mode(&gs_handle, TSL2561_INTERRUPT_MODE_10_INTEGRATION_TIME_OUT_OF_RANGE);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: set interrupt mode failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: set interrupt mode 10 integration time out of range.\n");
    res = tsl2561_get_interrupt_mode(&gs_handle, &mode);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: get interrupt mode failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: check interrupt mode %s.\n", mode == TSL2561_INTERRUPT_MODE_10_INTEGRATION_TIME_OUT_OF_RANGE ? "ok" : "error");
    
    /* set interrupt mode 11 integration time out of range */
    res = tsl2561_set_interrupt_mode(&gs_handle, TSL2561_INTERRUPT_MODE_11_INTEGRATION_TIME_OUT_OF_RANGE);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: set interrupt mode failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: set interrupt mode 11 integration time out of range.\n");
    res = tsl2561_get_interrupt_mode(&gs_handle, &mode);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: get interrupt mode failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: check interrupt mode %s.\n", mode == TSL2561_INTERRUPT_MODE_11_INTEGRATION_TIME_OUT_OF_RANGE ? "ok" : "error");
    
    /* set interrupt mode 12 integration time out of range */
    res = tsl2561_set_interrupt_mode(&gs_handle, TSL2561_INTERRUPT_MODE_12_INTEGRATION_TIME_OUT_OF_RANGE);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: set interrupt mode failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: set interrupt mode 12 integration time out of range.\n");
    res = tsl2561_get_interrupt_mode(&gs_handle, &mode);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: get interrupt mode failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: check interrupt mode %s.\n", mode == TSL2561_INTERRUPT_MODE_12_INTEGRATION_TIME_OUT_OF_RANGE ? "ok" : "error");
    
    /* set interrupt mode 13 integration time out of range */
    res = tsl2561_set_interrupt_mode(&gs_handle, TSL2561_INTERRUPT_MODE_13_INTEGRATION_TIME_OUT_OF_RANGE);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: set interrupt mode failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: set interrupt mode 13 integration time out of range.\n");
    res = tsl2561_get_interrupt_mode(&gs_handle, &mode);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: get interrupt mode failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: check interrupt mode %s.\n", mode == TSL2561_INTERRUPT_MODE_13_INTEGRATION_TIME_OUT_OF_RANGE ? "ok" : "error");
    
    /* set interrupt mode 14 integration time out of range */
    res = tsl2561_set_interrupt_mode(&gs_handle, TSL2561_INTERRUPT_MODE_14_INTEGRATION_TIME_OUT_OF_RANGE);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: set interrupt mode failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: set interrupt mode 14 integration time out of range.\n");
    res = tsl2561_get_interrupt_mode(&gs_handle, &mode);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: get interrupt mode failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: check interrupt mode %s.\n", mode == TSL2561_INTERRUPT_MODE_14_INTEGRATION_TIME_OUT_OF_RANGE ? "ok" : "error");
    
    /* set interrupt mode 15 integration time out of range */
    res = tsl2561_set_interrupt_mode(&gs_handle, TSL2561_INTERRUPT_MODE_15_INTEGRATION_TIME_OUT_OF_RANGE);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: set interrupt mode failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: set interrupt mode 15 integration time out of range.\n");
    res = tsl2561_get_interrupt_mode(&gs_handle, &mode);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: get interrupt mode failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: check interrupt mode %s.\n", mode == TSL2561_INTERRUPT_MODE_15_INTEGRATION_TIME_OUT_OF_RANGE ? "ok" : "error");
    
    /* tsl2561_set_interrupt_high_threshold/tsl2561_get_interrupt_high_threshold test */
    tsl2561_interface_debug_print("tsl2561: tsl2561_set_interrupt_high_threshold/tsl2561_get_interrupt_high_threshold test.\n");
    ch0 = rand()%65536;
    res = tsl2561_set_interrupt_high_threshold(&gs_handle, ch0);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: set interrupt high threshold failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: set interrupt high threshold %d.\n", ch0);
    res = tsl2561_get_interrupt_high_threshold(&gs_handle, (uint16_t *)&ch0_check);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: get interrupt high threshold failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: check interrupt high threshold %s.\n", ch0 == ch0_check ? "ok" : "error");
    
    /* tsl2561_set_interrupt_low_threshold/tsl2561_get_interrupt_low_threshold test */
    tsl2561_interface_debug_print("tsl2561: tsl2561_set_interrupt_low_threshold/tsl2561_get_interrupt_low_threshold test.\n");
    ch0 = rand()%65536;
    res = tsl2561_set_interrupt_low_threshold(&gs_handle, ch0);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: set interrupt low threshold failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: set interrupt low threshold %d.\n", ch0);
    res = tsl2561_get_interrupt_low_threshold(&gs_handle, (uint16_t *)&ch0_check);
    if (res != 0)
    {
        tsl2561_interface_debug_print("tsl2561: get interrupt low threshold failed.\n");
        (void)tsl2561_deinit(&gs_handle);
        
        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: check interrupt low threshold %s.\n", ch0 == ch0_check ? "ok" : "error");
    
    /* finished register test */
    tsl2561_interface_debug_print("tsl2561: finished register test.\n");
    (void)tsl2561_deinit(&gs_handle);
    
    return 0;
}
