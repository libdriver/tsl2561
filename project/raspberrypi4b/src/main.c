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
#include <getopt.h>
#include <stdlib.h>

/**
 * @brief global var definition
 */
volatile uint8_t g_flag;            /**< interrupt flag */

/**
 * @brief     tsl2561 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t tsl2561(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"addr", required_argument, NULL, 1},
        {"high-threshold", required_argument, NULL, 2},
        {"low-threshold", required_argument, NULL, 3},
        {"mode", required_argument, NULL, 4},
        {"times", required_argument, NULL, 5},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    uint32_t times = 3;
    tsl2561_address_t addr = TSL2561_ADDRESS_FLOAT;
    tsl2561_interrupt_mode_t mode = TSL2561_INTERRUPT_MODE_EVERY_ADC_CYCLE;
    uint16_t high_threshold = 100;
    uint16_t low_threshold = 10;
    
    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }
    
    /* init 0 */
    optind = 0;
    
    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);
        
        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");
                
                break;
            }
            
            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");
                
                break;
            }
            
            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");
                
                break;
            }
            
            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);
                
                break;
            }
            
            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);
                
                break;
            }
            
            /* addr */
            case 1 :
            {
                /* set the addr pin */
                if (strcmp("GND", optarg) == 0)
                {
                    addr = TSL2561_ADDRESS_GND;
                }
                else if (strcmp("VCC", optarg) == 0)
                {
                    addr = TSL2561_ADDRESS_VCC;
                }
                else if (strcmp("FLOAT", optarg) == 0)
                {
                    addr = TSL2561_ADDRESS_FLOAT;
                }
                else
                {
                    return 5;
                }
                
                break;
            }
            
            /* high threshold */
            case 2 :
            {
                high_threshold = atoi(optarg);
                
                break;
            }
             
            /* low threshold */
            case 3 :
            {
                low_threshold = atoi(optarg);
                
                break;
            }
            
            /* mode */
            case 4 :
            {
                /* set the mode */
                if (strcmp("00", optarg) == 0)
                {
                    mode = TSL2561_INTERRUPT_MODE_EVERY_ADC_CYCLE;
                    tsl2561_interface_debug_print("tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_EVERY_ADC_CYCLE.\n");
                }
                else if (strcmp("01", optarg) == 0)
                {
                    mode = TSL2561_INTERRUPT_MODE_ANY_VALUE_OUT_OF_THRESHOLD_RANGE;
                    tsl2561_interface_debug_print("tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_ANY_VALUE_OUT_OF_THRESHOLD_RANGE.\n");
                }
                else if (strcmp("02", optarg) == 0)
                {
                    mode = TSL2561_INTERRUPT_MODE_2_INTEGRATION_TIME_OUT_OF_RANGE;
                    tsl2561_interface_debug_print("tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_2_INTEGRATION_TIME_OUT_OF_RANGE.\n");
                }
                else if (strcmp("03", optarg) == 0)
                {
                    mode = TSL2561_INTERRUPT_MODE_3_INTEGRATION_TIME_OUT_OF_RANGE;
                    tsl2561_interface_debug_print("tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_3_INTEGRATION_TIME_OUT_OF_RANGE.\n");
                }
                else if (strcmp("04", optarg) == 0)
                {
                    mode = TSL2561_INTERRUPT_MODE_4_INTEGRATION_TIME_OUT_OF_RANGE;
                    tsl2561_interface_debug_print("tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_4_INTEGRATION_TIME_OUT_OF_RANGE.\n");
                }
                else if (strcmp("05", optarg) == 0)
                {
                    mode = TSL2561_INTERRUPT_MODE_5_INTEGRATION_TIME_OUT_OF_RANGE;
                    tsl2561_interface_debug_print("tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_5_INTEGRATION_TIME_OUT_OF_RANGE.\n");
                }
                else if (strcmp("06", optarg) == 0)
                {
                    mode = TSL2561_INTERRUPT_MODE_6_INTEGRATION_TIME_OUT_OF_RANGE;
                    tsl2561_interface_debug_print("tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_6_INTEGRATION_TIME_OUT_OF_RANGE.\n");
                }
                else if (strcmp("07", optarg) == 0)
                {
                    mode = TSL2561_INTERRUPT_MODE_7_INTEGRATION_TIME_OUT_OF_RANGE;
                    tsl2561_interface_debug_print("tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_7_INTEGRATION_TIME_OUT_OF_RANGE.\n");
                }
                else if (strcmp("08", optarg) == 0)
                {
                    mode = TSL2561_INTERRUPT_MODE_8_INTEGRATION_TIME_OUT_OF_RANGE;
                    tsl2561_interface_debug_print("tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_8_INTEGRATION_TIME_OUT_OF_RANGE.\n");
                }
                else if (strcmp("09", optarg) == 0)
                {
                    mode = TSL2561_INTERRUPT_MODE_9_INTEGRATION_TIME_OUT_OF_RANGE;
                    tsl2561_interface_debug_print("tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_9_INTEGRATION_TIME_OUT_OF_RANGE.\n");
                }
                else if (strcmp("10", optarg) == 0)
                {
                    mode = TSL2561_INTERRUPT_MODE_10_INTEGRATION_TIME_OUT_OF_RANGE;
                    tsl2561_interface_debug_print("tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_10_INTEGRATION_TIME_OUT_OF_RANGE.\n");
                }
                else if (strcmp("11", optarg) == 0)
                {
                    mode = TSL2561_INTERRUPT_MODE_11_INTEGRATION_TIME_OUT_OF_RANGE;
                    tsl2561_interface_debug_print("tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_11_INTEGRATION_TIME_OUT_OF_RANGE.\n");
                }
                else if (strcmp("12", optarg) == 0)
                {
                    mode = TSL2561_INTERRUPT_MODE_12_INTEGRATION_TIME_OUT_OF_RANGE;
                    tsl2561_interface_debug_print("tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_12_INTEGRATION_TIME_OUT_OF_RANGE.\n");
                }
                else if (strcmp("13", optarg) == 0)
                {
                    mode = TSL2561_INTERRUPT_MODE_13_INTEGRATION_TIME_OUT_OF_RANGE;
                    tsl2561_interface_debug_print("tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_13_INTEGRATION_TIME_OUT_OF_RANGE.\n");
                }
                else if (strcmp("14", optarg) == 0)
                {
                    mode = TSL2561_INTERRUPT_MODE_14_INTEGRATION_TIME_OUT_OF_RANGE;
                    tsl2561_interface_debug_print("tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_14_INTEGRATION_TIME_OUT_OF_RANGE.\n");
                }
                else if (strcmp("15", optarg) == 0)
                {
                    mode = TSL2561_INTERRUPT_MODE_15_INTEGRATION_TIME_OUT_OF_RANGE;
                    tsl2561_interface_debug_print("tsl2561: set interrupt mode TSL2561_INTERRUPT_MODE_15_INTEGRATION_TIME_OUT_OF_RANGE.\n");
                }
                else
                {
                    return 5;
                }
                
                break;
            }
            
            /* running times */
            case 5 :
            {
                /* set the times */
                times = atol(optarg);
                
                break;
            } 
            
            /* the end */
            case -1 :
            {
                break;
            }
            
            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_reg", type) == 0)
    {
        /* run reg test */
        if (tsl2561_register_test(addr) != 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (strcmp("t_read", type) == 0)
    {
        /* run read test */
        if (tsl2561_read_test(addr, times) != 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (strcmp("t_int", type) == 0)
    {
        uint8_t res;
        
        /* gpio init */
        res = gpio_interrupt_init();
        if (res != 0)
        {
            return 1;
        }
        
        /* run interrupt test */
        res = tsl2561_interrupt_test(addr, mode, low_threshold, high_threshold, times);
        if (res != 0)
        {
            (void)gpio_interrupt_deinit();
            
            return 1;
        }
        
        /* gpio deinit */
        (void)gpio_interrupt_deinit();
        
        return 0;
    }
    else if (strcmp("e_read", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        uint32_t lux;
        
        /* basic init */
        res = tsl2561_basic_init(addr);
        if (res != 0)
        {
            return 1;
        }
        
        /* loop */
        for (i = 0; i < times; i++)
        {
            /* delay 1000ms */
            tsl2561_interface_delay_ms(1000);
            
            /* read data */
            res = tsl2561_basic_read((uint32_t *)&lux);
            if (res != 0)
            {
                (void)tsl2561_basic_deinit();
                
                return 1;
            }
            
            /* output */
            tsl2561_interface_debug_print("tsl2561: %d/%d.\n", (uint32_t)(i + 1), (uint32_t)times);
            tsl2561_interface_debug_print("tsl2561: read is %d lux.\n", lux);
        }
        
        /* basic deinit */
        (void)tsl2561_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_int", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        uint32_t lux;
        
        /* interrupt init */
        res = tsl2561_interrupt_init(addr, mode, low_threshold, high_threshold);
        if (res != 0)
        {
            return 1;
        }
        
        /* gpio init */
        res = gpio_interrupt_init();
        if (res != 0)
        {
            (void)tsl2561_interrupt_deinit();
            
            return 1;
        }
        
        /* loop */
        g_flag = 0;
        for (i = 0; i < times; i++)
        {
            /* delay 1000ms */
            tsl2561_interface_delay_ms(1000);
            
            /* read data */
            res = tsl2561_interrupt_read((uint32_t *)&lux);
            if (res != 0)
            {
                (void)tsl2561_interrupt_deinit();
                (void)gpio_interrupt_deinit();
                
                return 1;
            }
            
            /* output */
            tsl2561_interface_debug_print("tsl2561: %d/%d.\n", (uint32_t)(i + 1), (uint32_t)times);
            tsl2561_interface_debug_print("tsl2561: read is %d lux.\n", lux);
            
            /* check interrupt */
            if (g_flag != 0)
            {
                tsl2561_interface_debug_print("tsl2561: find interrupt.\n");
                
                break;
            }
            
        }
        
        /* deinit */
        (void)tsl2561_interrupt_deinit();
        (void)gpio_interrupt_deinit();
        
        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        tsl2561_interface_debug_print("Usage:\n");
        tsl2561_interface_debug_print("  tsl2561 (-i | --information)\n");
        tsl2561_interface_debug_print("  tsl2561 (-h | --help)\n");
        tsl2561_interface_debug_print("  tsl2561 (-p | --port)\n");
        tsl2561_interface_debug_print("  tsl2561 (-t reg | --test=reg) [--addr=<VCC | GND | FLOAT>]\n");
        tsl2561_interface_debug_print("  tsl2561 (-t read | --test=read) [--addr=<VCC | GND | FLOAT>] [--times=<num>]\n");
        tsl2561_interface_debug_print("  tsl2561 (-t int | --test=int) [--addr=<VCC | GND | FLOAT>] [--times=<num>]\n");
        tsl2561_interface_debug_print("          [--mode=<m>] [--low-threshold=<low>] [--high-threshold=<high>]\n");
        tsl2561_interface_debug_print("  tsl2561 (-e read | --example=read) [--addr=<VCC | GND | FLOAT>] [--times=<num>]\n");
        tsl2561_interface_debug_print("  tsl2561 (-e int | --example=int) [--addr=<VCC | GND | FLOAT>] [--times=<num>]\n");
        tsl2561_interface_debug_print("          [--mode=<m>] [--low-threshold=<low>] [--high-threshold=<high>]\n");
        tsl2561_interface_debug_print("\n");
        tsl2561_interface_debug_print("Options:\n");
        tsl2561_interface_debug_print("      --addr=<VCC | GND | FLOAT>    Set the addr pin.([default: FLOAT])\n");
        tsl2561_interface_debug_print("  -e <read | int>, --example=<read | int>\n");
        tsl2561_interface_debug_print("                                    Run the driver example.\n");
        tsl2561_interface_debug_print("  -h, --help                        Show the help.\n");
        tsl2561_interface_debug_print("      --high-threshold=<high>       Set the interrupt high threshold.([default: 100])\n");
        tsl2561_interface_debug_print("  -i, --information                 Show the chip information.\n");
        tsl2561_interface_debug_print("      --low-threshold=<low>         Set the interrupt low threshold.([default: 10])\n");
        tsl2561_interface_debug_print("      --mode=<m>                    Set the interrupt mode and it can be \"00\" - \"15\".([default: 00])\n");
        tsl2561_interface_debug_print("  -p, --port                        Display the pin connections of the current board.\n");
        tsl2561_interface_debug_print("  -t <reg | read | int>, --test=<reg | read | int>\n");
        tsl2561_interface_debug_print("                                    Run the driver test.\n");
        tsl2561_interface_debug_print("      --times=<num>                 Set the running times.([default: 3])\n");
        
        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        tsl2561_info_t info;
        
        /* print tsl2561 info */
        tsl2561_info(&info);
        tsl2561_interface_debug_print("tsl2561: chip is %s.\n", info.chip_name);
        tsl2561_interface_debug_print("tsl2561: manufacturer is %s.\n", info.manufacturer_name);
        tsl2561_interface_debug_print("tsl2561: interface is %s.\n", info.interface);
        tsl2561_interface_debug_print("tsl2561: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        tsl2561_interface_debug_print("tsl2561: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        tsl2561_interface_debug_print("tsl2561: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        tsl2561_interface_debug_print("tsl2561: max current is %0.2fmA.\n", info.max_current_ma);
        tsl2561_interface_debug_print("tsl2561: max temperature is %0.1fC.\n", info.temperature_max);
        tsl2561_interface_debug_print("tsl2561: min temperature is %0.1fC.\n", info.temperature_min);
        
        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        tsl2561_interface_debug_print("tsl2561: SCL connected to GPIO3(BCM).\n");
        tsl2561_interface_debug_print("tsl2561: SDA connected to GPIO2(BCM).\n");
        tsl2561_interface_debug_print("tsl2561: INT connected to GPIO17(BCM).\n");
        
        return 0;
    }
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
        tsl2561_interface_debug_print("tsl2561: unknown status code.\n");
    }

    return 0;
}
