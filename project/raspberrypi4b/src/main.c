/**
 * Copyright (C) LibDriver 2015-2021 All rights reserved
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
 * @file      main.c
 * @brief     main source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2021-02-26
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2021/02/26  <td>1.0      <td>Shifeng Li  <td>format the code
 * </table>
 */

#include "driver_tsl2561_interrupt_test.h"
#include "driver_tsl2561_read_test.h"
#include "driver_tsl2561_register_test.h"
#include "driver_tsl2561_interrupt.h"
#include "driver_tsl2561_basic.h"
#include "gpio.h"

/**
 * @brief global var definition
 */
uint8_t g_flag;            /**< interrupt flag */

/**
 * @brief     tsl2561 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 *             - 1 run failed
 *             - 5 param is invalid
 * @note      none
 */
uint8_t tsl2561(uint8_t argc, char **argv)
{
    if (argc == 1)
    {
        goto help;
    }
    else if (argc == 2)
    {
        if (strcmp("-i", argv[1]) == 0)
        {
            tsl2561_info_t info;
            
            /* print tsl2561 info */
            tsl2561_info(&info);
            tsl2561_interface_debug_print("tsl2561: chip is %s.\n", info.chip_name);
            tsl2561_interface_debug_print("tsl2561: manufacturer is %s.\n", info.manufacturer_name);
            tsl2561_interface_debug_print("tsl2561: interface is %s.\n", info.interface);
            tsl2561_interface_debug_print("tsl2561: driver version is %d.%d.\n", info.driver_version/1000, (info.driver_version%1000)/100);
            tsl2561_interface_debug_print("tsl2561: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
            tsl2561_interface_debug_print("tsl2561: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
            tsl2561_interface_debug_print("tsl2561: max current is %0.2fmA.\n", info.max_current_ma);
            tsl2561_interface_debug_print("tsl2561: max temperature is %0.1fC.\n", info.temperature_max);
            tsl2561_interface_debug_print("tsl2561: min temperature is %0.1fC.\n", info.temperature_min);
            
            return 0;
        }
        else if (strcmp("-p", argv[1]) == 0)
        {
            /* print pin connection */
            tsl2561_interface_debug_print("tsl2561: SCL connected to GPIO3(BCM).\n");
            tsl2561_interface_debug_print("tsl2561: SDA connected to GPIO2(BCM).\n");
            tsl2561_interface_debug_print("tsl2561: INT connected to GPIO17(BCM).\n");
            
            return 0;
        }
        else if (strcmp("-h", argv[1]) == 0)
        {
            /* show tsl2561 help */
            
            help:
            
            tsl2561_interface_debug_print("tsl2561 -i\n\tshow tsl2561 chip and driver information.\n");
            tsl2561_interface_debug_print("tsl2561 -h\n\tshow tsl2561 help.\n");
            tsl2561_interface_debug_print("tsl2561 -p\n\tshow tsl2561 pin connections of the current board.\n");
            tsl2561_interface_debug_print("tsl2561 -t reg -a (VCC | GND | FLOAT)\n\trun tsl2561 register test.\n");
            tsl2561_interface_debug_print("tsl2561 -t read <times> -a (VCC | GND | FLOAT)\n\trun tsl2561 read test.times is test times.\n");
            tsl2561_interface_debug_print("tsl2561 -t int <times> -a (VCC | GND | FLOAT) -m <mode> -th <lowthreshold> <highthreshold>\n\t"
                                          "run tsl2561 interrupt test.times is test times.mode is the interrupt mode and it can be \"0\"-\"15\".");
            tsl2561_interface_debug_print("lowthreshold is interrupt low threshold.highthreshold is interrupt high threshold.\n");
            tsl2561_interface_debug_print("tsl2561 -c read <times> -a (VCC | GND | FLOAT)\n\trun tsl2561 read function.times is read times.\n");
            tsl2561_interface_debug_print("tsl2561 -c int <times> -a (VCC | GND | FLOAT) -m <mode> -th <lowthreshold> <highthreshold>\n\t"
                                          "run tsl2561 interrupt function.times is read times.mode is the interrupt mode and it can be \"0\"-\"15\".");
            tsl2561_interface_debug_print("lowthreshold is interrupt low threshold.highthreshold is interrupt high threshold.\n");
            
            return 0;
        }
        else
        {
            return 5;
        }
    }
    else if (argc == 5)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
            /* reg test */
            if (strcmp("reg", argv[2]) == 0)
            {
                tsl2561_address_t addr;
                
                /* check iic address */
                if (strcmp("-a", argv[3]) != 0)
                {
                    return 5;
                }
                if (strcmp("GND", argv[4]) == 0)
                {
                    addr = TSL2561_ADDRESS_GND;
                }
                else if (strcmp("VCC", argv[4]) == 0)
                {
                    addr = TSL2561_ADDRESS_VCC;
                }
                else if (strcmp("FLOAT", argv[4]) == 0)
                {
                    addr = TSL2561_ADDRESS_FLOAT;
                }
                else
                {
                    return 5;
                }
                
                /* run reg test */
                if (tsl2561_register_test(addr))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 6)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
             /* read test */
            if (strcmp("read", argv[2]) == 0)
            {
                tsl2561_address_t addr;
                
                /* check iic address */
                if (strcmp("-a", argv[4]) != 0)
                {
                    return 5;
                }
                if (strcmp("GND", argv[5]) == 0)
                {
                    addr = TSL2561_ADDRESS_GND;
                }
                else if (strcmp("VCC", argv[5]) == 0)
                {
                    addr = TSL2561_ADDRESS_VCC;
                }
                else if (strcmp("FLOAT", argv[5]) == 0)
                {
                    addr = TSL2561_ADDRESS_FLOAT;
                }
                else
                {
                    return 5;
                }
                if (tsl2561_read_test(addr, atoi(argv[3])))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
        
            /* param is invalid */
            else
            {
                return 5;
            }
        }

        /* run function */
        else if (strcmp("-c", argv[1]) == 0)
        {
             /* read function */
            if (strcmp("read", argv[2]) == 0)
            {
                volatile uint8_t res;
                volatile uint32_t times;
                volatile uint32_t i;
                volatile uint32_t lux;
                tsl2561_address_t addr;
                
                /* check iic address */
                if (strcmp("-a", argv[4]) != 0)
                {
                    return 5;
                }
                if (strcmp("GND", argv[5]) == 0)
                {
                    addr = TSL2561_ADDRESS_GND;
                }
                else if (strcmp("VCC", argv[5]) == 0)
                {
                    addr = TSL2561_ADDRESS_VCC;
                }
                else if (strcmp("FLOAT", argv[5]) == 0)
                {
                    addr = TSL2561_ADDRESS_FLOAT;
                }
                else
                {
                    return 5;
                }
                res = tsl2561_basic_init(addr);
                if (res)
                {
                    return 1;
                }
                times = atoi(argv[3]);
                for (i=0; i<times; i++)
                {
                    tsl2561_interface_delay_ms(1000);
                    res = tsl2561_basic_read((uint32_t *)&lux);
                    if (res)
                    {
                        tsl2561_basic_deinit();
                        
                        return 1;
                    }
                    tsl2561_interface_debug_print("tsl2561: %d/%d.\n", (uint32_t)(i+1), (uint32_t)times);
                    tsl2561_interface_debug_print("tsl2561: read is %d lux.\n", lux);
                }
                tsl2561_basic_deinit();
                
                return 0;
            }

            /* param is invalid */
            else
            {
                return 5;
            }
        }

        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 11)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
             /* read test */
            if (strcmp("int", argv[2]) == 0)
            {
                volatile uint8_t res;
                volatile uint32_t i;
                volatile uint32_t times;
                volatile uint32_t lux;
                tsl2561_address_t addr;
                tsl2561_interrupt_mode_t mode;
                
                /* check iic address */
                if (strcmp("-a", argv[4]) != 0)
                {
                    return 5;
                }
                if (strcmp("GND", argv[5]) == 0)
                {
                    addr = TSL2561_ADDRESS_GND;
                }
                else if (strcmp("VCC", argv[5]) == 0)
                {
                    addr = TSL2561_ADDRESS_VCC;
                }
                else if (strcmp("FLOAT", argv[5]) == 0)
                {
                    addr = TSL2561_ADDRESS_FLOAT;
                }
                else
                {
                    return 5;
                }

                /* check interrupt mode */
                if (strcmp("-m", argv[6]) != 0)
                {
                    return 5;
                }
                if (strcmp("0", argv[7]) == 0)
                {
                    mode = TSL2561_INTERRUPT_MODE_EVERY_ADC_CYCLE;
                    tsl2561_interface_debug_print("tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_EVERY_ADC_CYCLE.\n");
                }
                else if (strcmp("1", argv[7]) == 0)
                {
                    mode = TSL2561_INTERRUPT_MODE_ANY_VALUE_OUT_OF_THRESHOLD_RANGE;
                    tsl2561_interface_debug_print("tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_ANY_VALUE_OUT_OF_THRESHOLD_RANGE.\n");
                }
                else if (strcmp("2", argv[7]) == 0)
                {
                    mode = TSL2561_INTERRUPT_MODE_2_INTEGRATION_TIME_OUT_OF_RANGE;
                    tsl2561_interface_debug_print("tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_2_INTEGRATION_TIME_OUT_OF_RANGE.\n");
                }
                else if (strcmp("3", argv[7]) == 0)
                {
                    mode = TSL2561_INTERRUPT_MODE_3_INTEGRATION_TIME_OUT_OF_RANGE;
                    tsl2561_interface_debug_print("tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_3_INTEGRATION_TIME_OUT_OF_RANGE.\n");
                }
                else if (strcmp("4", argv[7]) == 0)
                {
                    mode = TSL2561_INTERRUPT_MODE_4_INTEGRATION_TIME_OUT_OF_RANGE;
                    tsl2561_interface_debug_print("tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_4_INTEGRATION_TIME_OUT_OF_RANGE.\n");
                }
                else if (strcmp("5", argv[7]) == 0)
                {
                    mode = TSL2561_INTERRUPT_MODE_5_INTEGRATION_TIME_OUT_OF_RANGE;
                    tsl2561_interface_debug_print("tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_5_INTEGRATION_TIME_OUT_OF_RANGE.\n");
                }
                else if (strcmp("6", argv[7]) == 0)
                {
                    mode = TSL2561_INTERRUPT_MODE_6_INTEGRATION_TIME_OUT_OF_RANGE;
                    tsl2561_interface_debug_print("tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_6_INTEGRATION_TIME_OUT_OF_RANGE.\n");
                }
                else if (strcmp("7", argv[7]) == 0)
                {
                    mode = TSL2561_INTERRUPT_MODE_7_INTEGRATION_TIME_OUT_OF_RANGE;
                    tsl2561_interface_debug_print("tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_7_INTEGRATION_TIME_OUT_OF_RANGE.\n");
                }
                else if (strcmp("8", argv[7]) == 0)
                {
                    mode = TSL2561_INTERRUPT_MODE_8_INTEGRATION_TIME_OUT_OF_RANGE;
                    tsl2561_interface_debug_print("tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_8_INTEGRATION_TIME_OUT_OF_RANGE.\n");
                }
                else if (strcmp("9", argv[7]) == 0)
                {
                    mode = TSL2561_INTERRUPT_MODE_9_INTEGRATION_TIME_OUT_OF_RANGE;
                    tsl2561_interface_debug_print("tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_9_INTEGRATION_TIME_OUT_OF_RANGE.\n");
                }
                else if (strcmp("10", argv[7]) == 0)
                {
                    mode = TSL2561_INTERRUPT_MODE_10_INTEGRATION_TIME_OUT_OF_RANGE;
                    tsl2561_interface_debug_print("tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_10_INTEGRATION_TIME_OUT_OF_RANGE.\n");
                }
                else if (strcmp("11", argv[7]) == 0)
                {
                    mode = TSL2561_INTERRUPT_MODE_11_INTEGRATION_TIME_OUT_OF_RANGE;
                    tsl2561_interface_debug_print("tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_11_INTEGRATION_TIME_OUT_OF_RANGE.\n");
                }
                else if (strcmp("12", argv[7]) == 0)
                {
                    mode = TSL2561_INTERRUPT_MODE_12_INTEGRATION_TIME_OUT_OF_RANGE;
                    tsl2561_interface_debug_print("tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_12_INTEGRATION_TIME_OUT_OF_RANGE.\n");
                }
                else if (strcmp("13", argv[7]) == 0)
                {
                    mode = TSL2561_INTERRUPT_MODE_13_INTEGRATION_TIME_OUT_OF_RANGE;
                    tsl2561_interface_debug_print("tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_13_INTEGRATION_TIME_OUT_OF_RANGE.\n");
                }
                else if (strcmp("14", argv[7]) == 0)
                {
                    mode = TSL2561_INTERRUPT_MODE_14_INTEGRATION_TIME_OUT_OF_RANGE;
                    tsl2561_interface_debug_print("tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_14_INTEGRATION_TIME_OUT_OF_RANGE.\n");
                }
                else if (strcmp("15", argv[7]) == 0)
                {
                    mode = TSL2561_INTERRUPT_MODE_15_INTEGRATION_TIME_OUT_OF_RANGE;
                    tsl2561_interface_debug_print("tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_15_INTEGRATION_TIME_OUT_OF_RANGE.\n");
                }
                else
                {
                    return 5;
                }

                /* check threshold */
                if (strcmp("-th", argv[8]) != 0)
                {
                    return 5;
                }
                times = atoi(argv[3]);

                res = gpio_interrupt_init();
                if (res)
                {
                    return 1;
                }
                res = tsl2561_interrupt_test(addr, mode, atoi(argv[9]), atoi(argv[10]), times);
                if (res)
                {
                    gpio_interrupt_deinit();
                    
                    return 1;
                }
                gpio_interrupt_deinit();
                
                return 0;
            }

            /* param is invalid */
            else
            {
                return 5;
            }
        }

        /* run function */
        else if (strcmp("-c", argv[1]) == 0)
        {
             /* read function */
            if (strcmp("int", argv[2]) == 0)
            {
                volatile uint8_t res;
                volatile uint32_t i;
                volatile uint32_t times;
                volatile uint32_t lux;
                tsl2561_address_t addr;
                tsl2561_interrupt_mode_t mode;
                
                /* check iic address */
                if (strcmp("-a", argv[4]) != 0)
                {
                    return 5;
                }
                if (strcmp("GND", argv[5]) == 0)
                {
                    addr = TSL2561_ADDRESS_GND;
                }
                else if (strcmp("VCC", argv[5]) == 0)
                {
                    addr = TSL2561_ADDRESS_VCC;
                }
                else if (strcmp("FLOAT", argv[5]) == 0)
                {
                    addr = TSL2561_ADDRESS_FLOAT;
                }
                else
                {
                    return 5;
                }

                /* check interrupt mode */
                if (strcmp("-m", argv[6]) != 0)
                {
                    return 5;
                }
                if (strcmp("0", argv[7]) == 0)
                {
                    mode = TSL2561_INTERRUPT_MODE_EVERY_ADC_CYCLE;
                    tsl2561_interface_debug_print("tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_EVERY_ADC_CYCLE.\n");
                }
                else if (strcmp("1", argv[7]) == 0)
                {
                    mode = TSL2561_INTERRUPT_MODE_ANY_VALUE_OUT_OF_THRESHOLD_RANGE;
                    tsl2561_interface_debug_print("tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_ANY_VALUE_OUT_OF_THRESHOLD_RANGE.\n");
                }
                else if (strcmp("2", argv[7]) == 0)
                {
                    mode = TSL2561_INTERRUPT_MODE_2_INTEGRATION_TIME_OUT_OF_RANGE;
                    tsl2561_interface_debug_print("tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_2_INTEGRATION_TIME_OUT_OF_RANGE.\n");
                }
                else if (strcmp("3", argv[7]) == 0)
                {
                    mode = TSL2561_INTERRUPT_MODE_3_INTEGRATION_TIME_OUT_OF_RANGE;
                    tsl2561_interface_debug_print("tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_3_INTEGRATION_TIME_OUT_OF_RANGE.\n");
                }
                else if (strcmp("4", argv[7]) == 0)
                {
                    mode = TSL2561_INTERRUPT_MODE_4_INTEGRATION_TIME_OUT_OF_RANGE;
                    tsl2561_interface_debug_print("tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_4_INTEGRATION_TIME_OUT_OF_RANGE.\n");
                }
                else if (strcmp("5", argv[7]) == 0)
                {
                    mode = TSL2561_INTERRUPT_MODE_5_INTEGRATION_TIME_OUT_OF_RANGE;
                    tsl2561_interface_debug_print("tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_5_INTEGRATION_TIME_OUT_OF_RANGE.\n");
                }
                else if (strcmp("6", argv[7]) == 0)
                {
                    mode = TSL2561_INTERRUPT_MODE_6_INTEGRATION_TIME_OUT_OF_RANGE;
                    tsl2561_interface_debug_print("tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_6_INTEGRATION_TIME_OUT_OF_RANGE.\n");
                }
                else if (strcmp("7", argv[7]) == 0)
                {
                    mode = TSL2561_INTERRUPT_MODE_7_INTEGRATION_TIME_OUT_OF_RANGE;
                    tsl2561_interface_debug_print("tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_7_INTEGRATION_TIME_OUT_OF_RANGE.\n");
                }
                else if (strcmp("8", argv[7]) == 0)
                {
                    mode = TSL2561_INTERRUPT_MODE_8_INTEGRATION_TIME_OUT_OF_RANGE;
                    tsl2561_interface_debug_print("tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_8_INTEGRATION_TIME_OUT_OF_RANGE.\n");
                }
                else if (strcmp("9", argv[7]) == 0)
                {
                    mode = TSL2561_INTERRUPT_MODE_9_INTEGRATION_TIME_OUT_OF_RANGE;
                    tsl2561_interface_debug_print("tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_9_INTEGRATION_TIME_OUT_OF_RANGE.\n");
                }
                else if (strcmp("10", argv[7]) == 0)
                {
                    mode = TSL2561_INTERRUPT_MODE_10_INTEGRATION_TIME_OUT_OF_RANGE;
                    tsl2561_interface_debug_print("tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_10_INTEGRATION_TIME_OUT_OF_RANGE.\n");
                }
                else if (strcmp("11", argv[7]) == 0)
                {
                    mode = TSL2561_INTERRUPT_MODE_11_INTEGRATION_TIME_OUT_OF_RANGE;
                    tsl2561_interface_debug_print("tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_11_INTEGRATION_TIME_OUT_OF_RANGE.\n");
                }
                else if (strcmp("12", argv[7]) == 0)
                {
                    mode = TSL2561_INTERRUPT_MODE_12_INTEGRATION_TIME_OUT_OF_RANGE;
                    tsl2561_interface_debug_print("tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_12_INTEGRATION_TIME_OUT_OF_RANGE.\n");
                }
                else if (strcmp("13", argv[7]) == 0)
                {
                    mode = TSL2561_INTERRUPT_MODE_13_INTEGRATION_TIME_OUT_OF_RANGE;
                    tsl2561_interface_debug_print("tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_13_INTEGRATION_TIME_OUT_OF_RANGE.\n");
                }
                else if (strcmp("14", argv[7]) == 0)
                {
                    mode = TSL2561_INTERRUPT_MODE_14_INTEGRATION_TIME_OUT_OF_RANGE;
                    tsl2561_interface_debug_print("tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_14_INTEGRATION_TIME_OUT_OF_RANGE.\n");
                }
                else if (strcmp("15", argv[7]) == 0)
                {
                    mode = TSL2561_INTERRUPT_MODE_15_INTEGRATION_TIME_OUT_OF_RANGE;
                    tsl2561_interface_debug_print("tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_15_INTEGRATION_TIME_OUT_OF_RANGE.\n");
                }
                else
                {
                    return 5;
                }

                /* check threshold */
                if (strcmp("-th", argv[8]) != 0)
                {
                    return 5;
                }
                times = atoi(argv[3]);
                res = tsl2561_interrupt_init(addr, mode, atoi(argv[9]), atoi(argv[10]));
                if (res)
                {
                    return 1;
                }
                res = gpio_interrupt_init();
                if (res)
                {
                    tsl2561_interrupt_deinit();
                    
                    return 1;
                }
                g_flag = 0;
                for (i=0; i<times; i++)
                {
                    /* read data */
                    tsl2561_interface_delay_ms(1000);
                    res = tsl2561_interrupt_read((uint32_t *)&lux);
                    if (res)
                    {
                        tsl2561_interrupt_deinit();
                        gpio_interrupt_deinit();
                        
                        return 1;
                    }
                    tsl2561_interface_debug_print("tsl2561: %d/%d.\n", (uint32_t)(i+1), (uint32_t)times);
                    tsl2561_interface_debug_print("tsl2561: read is %d lux.\n", lux);

                    /* check interrupt */
                    if (g_flag)
                    {
                        tsl2561_interface_debug_print("tsl2561: find interrupt.\n");
                        
                        break;
                    }
                    
                }
                tsl2561_interrupt_deinit();
                gpio_interrupt_deinit();
                
                return 0;
            }

            /* param is invalid */
            else
            {
                return 5;
            }
        }

        /* param is invalid */
        else
        {
            return 5;
        }
    }

    /* param is invalid */
    else
    {
        return 5;
    }
}

/**
 * @brief     main function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 * @note      none
 */
int main(uint8_t argc, char **argv)
{
    uint8_t res;

    res = tsl2561(argc, argv);
    if (res == 0)
    {
        /* run success */
    }
    else if (res == 1)
    {
        tsl2561_interface_debug_print("tsl2561: run failed.\n");
    }
    else if (res == 5)
    {
        tsl2561_interface_debug_print("tsl2561: param is invalid.\n");
    }
    else
    {
        tsl2561_interface_debug_print("tsl2561: unknow status code.\n");
    }

    return 0;
}
