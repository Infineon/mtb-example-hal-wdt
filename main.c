/******************************************************************************
* File Name: main.c
*
* Description: This is the source code for the PSoC 6 MCU Watchdog Timer Example.
*              for ModusToolbox.
*
* Related Document: See README.md
*
*
*******************************************************************************
* Copyright 2019-2021, Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.  All rights reserved.
*
* This software, including source code, documentation and related
* materials ("Software") is owned by Cypress Semiconductor Corporation
* or one of its affiliates ("Cypress") and is protected by and subject to
* worldwide patent protection (United States and foreign),
* United States copyright laws and international treaty provisions.
* Therefore, you may use this Software only as provided in the license
* agreement accompanying the software package from which you
* obtained this Software ("EULA").
* If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
* non-transferable license to copy, modify, and compile the Software
* source code solely for use in connection with Cypress's
* integrated circuit products.  Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
* reserves the right to make changes to the Software without notice. Cypress
* does not assume any liability arising out of the application or use of the
* Software or any product or circuit described in the Software. Cypress does
* not authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
*******************************************************************************/

#include "cyhal.h"
#include "cybsp.h"

/*******************************************************************************
* Macros
********************************************************************************/

/* WDT time out for reset mode, in milliseconds. Max limit is given by CYHAL_WDT_MAX_TIMEOUT_MS */
#define WDT_TIME_OUT_MS                     4000
#define ENABLE_BLOCKING_FUNCTION            0

/*******************************************************************************
* Function Prototypes
********************************************************************************/
void initialize_wdt(void);

/*******************************************************************************
* Global Variables
********************************************************************************/

/* WDT object */
cyhal_wdt_t wdt_obj;

 
/*******************************************************************************
* Function Name: main
********************************************************************************
* Summary:
* This is the main function for CM4 CPU. It demonstrates the WDT reset 
* 
*
* Parameters:
*  void
*
* Return:
*  int
*
*******************************************************************************/
int main(void)
{
    cy_rslt_t result;

    /* Initialize the device and board peripherals */
    result = cybsp_init();
    
    /* Board init failed. Stop program execution */
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    /* Initialize the User LED */
    cyhal_gpio_init(CYBSP_USER_LED, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, CYBSP_LED_STATE_OFF);
    
    /* Check the reason for device restart */
    if (CYHAL_SYSTEM_RESET_WDT == cyhal_system_get_reset_reason())
    {
        /* It's WDT reset event - blink LED twice */
        cyhal_gpio_write(CYBSP_USER_LED, CYBSP_LED_STATE_ON);
        cyhal_system_delay_ms(100);
        cyhal_gpio_write(CYBSP_USER_LED, CYBSP_LED_STATE_OFF);
        cyhal_system_delay_ms(200);
        cyhal_gpio_write(CYBSP_USER_LED, CYBSP_LED_STATE_ON);
        cyhal_system_delay_ms(100);
        cyhal_gpio_write(CYBSP_USER_LED, CYBSP_LED_STATE_OFF);
    }
    else
    {
        /* It's Power-On reset or XRES event - blink LED once */
        cyhal_gpio_write(CYBSP_USER_LED, CYBSP_LED_STATE_ON);
        cyhal_system_delay_ms(100);
        cyhal_gpio_write(CYBSP_USER_LED, CYBSP_LED_STATE_OFF);;
        cyhal_system_delay_ms(100);
    }

    /* Initialize WDT */
    initialize_wdt();

    /* Enable global interrupt */
    __enable_irq();

    for (;;)
    {
        #if (ENABLE_BLOCKING_FUNCTION)
            while(1);            
        #else
            /* Reset WDT */
            cyhal_wdt_kick(&wdt_obj);

            /* Constant delay of 1000ms */
            cyhal_system_delay_ms(1000);

            /* Invert the state of LED */
            cyhal_gpio_toggle(CYBSP_USER_LED);
        #endif
      
    }
}

/*******************************************************************************
* Function Name: InitializeWDT
********************************************************************************
* Summary:
* This function initializes the WDT block
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void initialize_wdt()
{
    cy_rslt_t result;

    /* Initialize the WDT */
    result = cyhal_wdt_init(&wdt_obj, WDT_TIME_OUT_MS);

    /* WDT initialization failed. Stop program execution */
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }
}


/* [] END OF FILE */
