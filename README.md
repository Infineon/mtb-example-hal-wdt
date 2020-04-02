# PSoC 6 MCU Watchdog Timer

This example explains two use cases of Watchdog Timer (WDT) – a watchdog that causes a device reset in the case of a malfunction and as a periodic interrupt source.

A few `#defines` in the Makefile determines the mode to be used. Out of the box, this example demonstrates the periodic interrupt. The user LED toggles on every interrupt at an interval of ~1 s.

For reset mode, change the `#define` and enable an infinite loop in the `main()` function to block the execution. The device resets in ~4 s. The user LED blinks twice after the device comes out of reset. If you use the reset mode without blocking the execution, the device does not reset. The user LED toggles every 1 s in the main loop to indicate that the CPU is in action. In addition, the user LED blinks once for power cycling or an external reset event.

## Requirements

- [ModusToolbox™ software](https://www.cypress.com/products/modustoolbox-software-environment) v2.1
- Programming Language: C
- Associated Parts: All [PSoC® 6 MCU](http://www.cypress.com/PSoC6) parts

## Supported Kits

- [PSoC 6 Wi-Fi BT Prototyping Kit](https://www.cypress.com/CY8CPROTO-062-4343W) (CY8CPROTO-062-4343W) - Default target
- [PSoC 6 WiFi-BT Pioneer Kit](https://www.cypress.com/CY8CKIT-062-WiFi-BT) (CY8CKIT-062-WiFi-BT)
- [PSoC 6 BLE Pioneer Kit](https://www.cypress.com/CY8CKIT-062-BLE) (CY8CKIT-062-BLE)
- [PSoC 6 BLE Prototyping Kit](https://www.cypress.com/CY8CPROTO-063-BLE) (CY8CPROTO-063-BLE)
- [PSoC 62S2 Wi-Fi BT Pioneer Kit](https://www.cypress.com/CY8CKIT-062S2-43012) (CY8CKIT-062S2-43012)
- [PSoC 62S1 Wi-Fi BT Pioneer Kit](https://www.cypress.com/CYW9P62S1-43438EVB-01) (CYW9P62S1-43438EVB-01)
- [PSoC 62S1 Wi-Fi BT Pioneer Kit](https://www.cypress.com/CYW9P62S1-43012EVB-01) (CYW9P62S1-43012EVB-01)
- [PSoC 62S3 Wi-Fi BT Prototyping Kit](https://www.cypress.com/CY8CPROTO-062S3-4343W) (CY8CPROTO-062S3-4343W)

## Hardware Setup

This example uses the board's default configuration. See the kit user guide to ensure that the board is configured correctly.

**Note**: The PSoC 6 BLE Pioneer Kit and the PSoC 6 WiFi-BT Pioneer Kit ship with KitProg2 installed. ModusToolbox software requires KitProg3. Before using this code example, make sure that the board is upgraded to KitProg3. The tool and instructions are available in the [Firmware Loader](https://github.com/cypresssemiconductorco/Firmware-loader) GitHub repository. If you do not upgrade, you will see an error like "unable to find CMSIS-DAP device" or "KitProg firmware is out of date".

## Software Setup
See the [Operation](#operation) section for information on how to modify the code for each demo.

## Using the Code Example

### In Eclipse IDE for ModusToolbox:

1. Click the **New Application** link in the Quick Panel (or, use **File** > **New** > **ModusToolbox Application**).

2. Pick a kit supported by the code example from the list shown in the **Project Creator - Choose Board Support Package (BSP)** dialog.

   When you select a supported kit, the example is reconfigured automatically to work with the kit. To work with a different supported kit later, use the **Library Manager** to choose the BSP for the supported kit. You can use the **Library Manager** to select or update the BSP and firmware libraries used in this application. To access the **Library Manager**, right-click the application name from the Project Workspace window in the IDE, and select **ModusToolbox** > **Library Manager**.

   You can also just start the application creation process again and select a different kit.

   If you want to use the application for a kit not listed here, you may need to update source files. If the kit does not have the required resources, the application may not work.

3. In the **Project Creator - Choose Board Support Package (BSP)** dialog, choose the example.

4. Optionally, update the **Application Name:** and **Location** fields with the application name and local path where application is created.

5. Click **Create** and complete the application creation process.

For more details, see the Eclipse IDE for ModusToolbox User Guide: *{ModusToolbox install directory}/ide_{version}/docs/mt_ide_user_guide.pdf*.

### In Command-line Interface (CLI):

1. Download and unzip this repository onto your local machine, or clone the repository.

2. Open a CLI terminal and navigate to the application folder. On Linux and macOS, you can use any terminal application. On Windows, navigate to the *modus-shell* directory (*{ModusToolbox install directory}/tools_\<version>/modus-shell*) and run Cygwin.bat.

3. Import required libraries by executing the `make getlibs` command.

### In Third-party IDEs:

1. Follow instructions from the CLI section to download or clone the repository, and import libraries using `make getlibs` command.

2. Export the application to a supported IDE using the `make <ide>` command.

3. Follow instructions displayed in the terminal to create or import the application as an IDE project.

For more details, see *Exporting to IDEs* section of the ModusToolbox User Guide: *{ModusToolbox install directory}/ide_{version}/docs/mtb_user_guide.pdf*.

## Operation

1. Connect the board to your PC using the provided USB cable through the USB connector.

2. Modify the makefile if you want to use RESET mode. By default, the example is in INTERRUPT mode.   
    1. Open the makefile from *mtb-example-psoc6-wdt* in the workspace.  
    
    2. Set `WDT_DEMO to WDT_RESET_DEMO` for reset demonstration as shown below:
    
       ```
       DEFINES=WDT_DEMO=WDT_RESET_DEMO            
       ```
    3. To demonstrate WDT reset, a blocking code `(while(1))` is introduced in the innermost `for` loop by enabling the define `DEFINES+=EXECUTION_BLOCK` in the makefile.    

3. When `WDT_INTERRUPT_DEMO` is selected, you can optionally put the device in Deep Sleep mode by enabling the define `DEFINES+=DEEPSLEEP_ENABLE` in the makefile. The device wakes up from Deep Sleep mode on a WDT
interrupt.

4. Program the board.

   ### Using Eclipse IDE for ModusToolbox:

   1. Select the application project in the Project Explorer.

   2. In the **Quick Panel**, scroll down, and click **\<Application Name> Program (KitProg3)**.

   ### Using CLI:

   1. From the terminal, execute the `make program` command to build and program the application using the default toolchain to the default target. You can specify a target and toolchain manually:
        ```
        make program TARGET=<BSP> TOOLCHAIN=<toolchain>
        ```
        Example:

        ```
        make program TARGET=CY8CKIT-062-WIFI-BT TOOLCHAIN=GCC_ARM
        ```
        **Note**:  Before building the application, ensure that the *deps* folder contains the BSP file (*TARGET_xxx.lib*) corresponding to the TARGET. Execute the `make getlibs` command to fetch the BSP contents before building the application.

5. Observe the status of the LEDs based on different events summarized as follows:

| Project Setting | LED Status |
| :----------------------------------------------------------- | :----------------------------------------------------------- |
| `WDT_DEMO` set to `WDT_INTERRUPT_DEMO` | User LED toggles on every WDT interrupt (interval of 1 s). |
| `WDT_DEMO` set to `WDT_RESET_DEMO` with the blocking function | After approximately 4 s, the device resets and the user LED blinks twice within a second to indicate a WDT reset. |
| `WDT_DEMO` set to `WDT_RESET_DEMO` without the blocking function| User LED toggles every 1 s to indicate that the CPU is in action. |

Note that user LED blinks once on a power cycle or an external reset event. 

## Design and Implementation

### Resources and Settings

[Table 1](#table-1-application-resources) lists the ModusToolbox resources used in this example, and how they are used in the design.

##### Table 1. Application Resources
| Resource  |  Alias/Object     |    Purpose     |
| :------- | :------------    | :------------ |
| WDT (PDL and HAL) | -          | WDT driver to configure the hardware resource |
| GPIO (HAL)    | CYBSP_USER_LED         | User LED                  |

The WDT in PSoC 6 MCU is a 16-bit timer and uses the Internal Low-Speed Oscillator (ILO) clock of 32 kHz. WDT is configured using different set of APIs, depending on whether interrupt mode is selected or the reset mode. 
Follow these steps, in the project, to configure WDT when `WDT_INTERRUPT_DEMO` is selected:

1. Unlock the WDT to enable configuration.

2. Set the 'ignore' bits for the match resolution. In the project, it is set to ‘0’; that means full 16-bit resolution for the match count, which gives an interval of 2.048 s (65536 ÷ 32kHz) for the match event.

3. Write the match value. The WDT can generate an interrupt (if enabled) when the WDT counter reaches the match count. The project configures the match count using the `WDT_MATCH_COUNT` macro. Note that the interrupt handler
modifies the match count to generate a periodic interrupt.

4. Clear the pending WDT interrupt.

5. Enable the ILO, which is the source for the WDT.

6. Enable interrupt generation and assign the handler.

7. Enable WDT.

8. Lock the WDT to prevent inadvertent changes.

For using `WDT_RESET_DEMO`, there are set of easy to use APIs to initialize the WDT hardware for a desired time out period. APIs configure the ignore bits and the match count for the desired time out period. Time out period comprises of three match events. To avoid WDT reset, firmware needs to clear the WDT before the third match event. 

**Notes:**

1. The WDT generates an interrupt on match. However, the counter is not reset on match. It continues to count across the full 16-bit resolution. For this reason, the match count is updated on every WDT interrupt when
`WDT_INTERRUPT_DEMO` is selected.

2. Interrupt should not be enabled when `WDT_RESET_DEMO` is being used. If interrupt is enabled, upon an interrupt, it needs to be cleared to avoid repeated execution of the WDT interrupt handler. This removes the actual purpose of the WDT. Thus, interrupt generation should never be enabled and the WDT match event should always be cleared in the main loop.

| Macro                  | Value          | Purpose                                                                           |
| :----------------------| :--------------| :-------------------------------------------------------------------------------- |
| `WDT_DEMO` | `WDT_RESET_DEMO` | In this mode of the WDT, interrupt generation is not enabled and the WDT match event is cleared in the main loop.|
| `WDT_DEMO` | `WDT_INTERRUPT_DEMO` (default) | In this mode of the WDT, interrupt generation is enabled and the match event is cleared in the interrupt handler. The match count is updated to get the next interrupt after the same interval. |
| `WDT_INTERRUPT_INTERVAL_MS` | `1000` (default) | Specifies the interrupt interval in milliseconds. In this case, it is set to 1000 millisecond. Change this value to get a different interrupt interval. The maximum interval can be 2047 millisecond |
| `WDT_TIME_OUT_MS` | `4000` (default) | Specifies the time out for reset event in milliseconds. Change this value to get a different time out. The maximum time out that can be set is given by `CYHAL_WDT_MAX_TIMEOUT_MS`.|

To simulate a malfunction, the main loop contains a blocking function (infinite `while` loop). Enabling this blocking function causes WDT match events not to be cleared. After three match events, the device resets. The firmware blinks the user LED twice when the device comes out of reset. 

## Related Resources

| **Application Notes**                                            |                                                              |
| :----------------------------------------------------------- | :----------------------------------------------------------- |
| [AN228571](https://www.cypress.com/AN228571) – Getting Started with PSoC 6 MCU on ModusToolbox | Describes PSoC 6 MCU devices and how to build your first application with ModusToolbox |
| [AN221774](https://www.cypress.com/AN221774) – Getting Started with PSoC 6 MCU on PSoC Creator | Describes PSoC 6 MCU devices and how to build your first application with PSoC Creator |
| [AN210781](https://www.cypress.com/AN210781) – Getting Started with PSoC 6 MCU with Bluetooth Low Energy (BLE) Connectivity on PSoC Creator | Describes PSoC 6 MCU with BLE Connectivity devices and how to build your first application with PSoC Creator |
| [AN215656](https://www.cypress.com/AN215656) – PSoC 6 MCU: Dual-CPU System Design | Describes the dual-CPU architecture in PSoC 6 MCU, and shows how to build a simple dual-CPU design |
| [AN219528](https://www.cypress.com/AN219528) – PSoC 6 MCU: Low-Power Modes and Power Reduction Techniques | Describes how to use the PSoC 6 MCU power modes to optimize power consumption | 
| **Code Examples**                                            |                                                              |
| [Using ModusToolbox](https://github.com/cypresssemiconductorco/Code-Examples-for-ModusToolbox-Software) | [Using PSoC Creator](https://www.cypress.com/documentation/code-examples/psoc-6-mcu-code-examples) |
| **Device Documentation**                                     |                                                              |
| [PSoC 6 MCU Datasheets](https://www.cypress.com/search/all?f[0]=meta_type%3Atechnical_documents&f[1]=resource_meta_type%3A575&f[2]=field_related_products%3A114026) | [PSoC 6 Technical Reference Manuals](https://www.cypress.com/search/all/PSoC%206%20Technical%20Reference%20Manual?f[0]=meta_type%3Atechnical_documents&f[1]=resource_meta_type%3A583) |
| **Development Kits**                                         | Buy at www.cypress.com                                       |
| [CY8CKIT-062-BLE](https://www.cypress.com/CY8CKIT-062-BLE) PSoC 6 BLE Pioneer Kit | [CY8CKIT-062-WiFi-BT](https://www.cypress.com/CY8CKIT-062-WiFi-BT) PSoC 6 WiFi-BT Pioneer Kit |
| [CY8CPROTO-063-BLE](https://www.cypress.com/CY8CPROTO-063-BLE) PSoC 6 BLE Prototyping Kit | [CY8CPROTO-062-4343W](https://www.cypress.com/CY8CPROTO-062-4343W) PSoC 6 Wi-Fi BT Prototyping Kit |
| [CY8CKIT-062S2-43012](https://www.cypress.com/CY8CKIT-062S2-43012) PSoC 62S2 Wi-Fi BT Pioneer Kit | [CY8CPROTO-062S3-4343W](https://www.cypress.com/CY8CPROTO-062S3-4343W) PSoC 62S3 Wi-Fi BT Prototyping Kit |
| [CYW9P62S1-43438EVB-01](https://www.cypress.com/CYW9P62S1-43438EVB-01) PSoC 62S1 Wi-Fi BT Pioneer Kit | [CYW9P62S1-43012EVB-01](https://www.cypress.com/CYW9P62S1-43012EVB-01) PSoC 62S1 Wi-Fi BT Pioneer Kit |                                                              |
| **Libraries**                                                 |                                                              |
| PSoC 6 Peripheral Driver Library (PDL) and docs                    | [psoc6pdl](https://github.com/cypresssemiconductorco/psoc6pdl) on GitHub |
| Cypress Hardware Abstraction Layer (HAL) Library and docs          | [psoc6hal](https://github.com/cypresssemiconductorco/psoc6hal) on GitHub |
| RetargetIO - A utility library to retarget the standard input/output (STDIO) messages to a UART port | [retarget-io](https://github.com/cypresssemiconductorco/retarget-io) on GitHub |
| **Middleware**                                               |                                                              |
| CapSense library and docs                                    | [capsense](https://github.com/cypresssemiconductorco/capsense) on GitHub |
| Links to all PSoC 6 MCU Middleware                           | [psoc6-middleware](https://github.com/cypresssemiconductorco/psoc6-middleware) on GitHub |
| **Tools**                                                    |                                                              |
| [Eclipse IDE for ModusToolbox](https://www.cypress.com/modustoolbox)     | The multi-platform, Eclipse-based Integrated Development Environment (IDE) that supports application configuration and development for PSoC 6 MCU and IoT designers.             |
| [PSoC Creator](https://www.cypress.com/products/psoc-creator-integrated-design-environment-ide) | The Cypress IDE for PSoC and FM0+ MCU development.            |

## Other Resources

Cypress provides a wealth of data at www.cypress.com to help you select the right device, and quickly and effectively integrate it into your design.

For PSoC 6 MCU devices, see [How to Design with PSoC 6 MCU - KBA223067](https://community.cypress.com/docs/DOC-14644) in the Cypress community.

## Document History

Document Title: CE220060 - PSoC 6 MCU Watchdog Timer 

| Version | Description of Change |
| ------- | --------------------- |
| 1.0.0   | New code example      |
| 1.1.0   | Updated to support ModusToolbox software v2.1, added new kits<br> Minor changes to code |

------

All other trademarks or registered trademarks referenced herein are the property of their respective owners.

![Banner](images/Banner.png)

-------------------------------------------------------------------------------

© Cypress Semiconductor Corporation, 2019-2020. This document is the property of Cypress Semiconductor Corporation and its subsidiaries ("Cypress"). This document, including any software or firmware included or referenced in this document ("Software"), is owned by Cypress under the intellectual property laws and treaties of the United States and other countries worldwide. Cypress reserves all rights under such laws and treaties and does not, except as specifically stated in this paragraph, grant any license under its patents, copyrights, trademarks, or other intellectual property rights. If the Software is not accompanied by a license agreement and you do not otherwise have a written agreement with Cypress governing the use of the Software, then Cypress hereby grants you a personal, non-exclusive, nontransferable license (without the right to sublicense) (1) under its copyright rights in the Software (a) for Software provided in source code form, to modify and reproduce the Software solely for use with Cypress hardware products, only internally within your organization, and (b) to distribute the Software in binary code form externally to end users (either directly or indirectly through resellers and distributors), solely for use on Cypress hardware product units, and (2) under those claims of Cypress's patents that are infringed by the Software (as provided by Cypress, unmodified) to make, use, distribute, and import the Software solely for use with Cypress hardware products. Any other use, reproduction, modification, translation, or compilation of the Software is prohibited.  
TO THE EXTENT PERMITTED BY APPLICABLE LAW, CYPRESS MAKES NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, WITH REGARD TO THIS DOCUMENT OR ANY SOFTWARE OR ACCOMPANYING HARDWARE, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. No computing device can be absolutely secure. Therefore, despite security measures implemented in Cypress hardware or software products, Cypress shall have no liability arising out of any security breach, such as unauthorized access to or use of a Cypress product. CYPRESS DOES NOT REPRESENT, WARRANT, OR GUARANTEE THAT CYPRESS PRODUCTS, OR SYSTEMS CREATED USING CYPRESS PRODUCTS, WILL BE FREE FROM CORRUPTION, ATTACK, VIRUSES, INTERFERENCE, HACKING, DATA LOSS OR THEFT, OR OTHER SECURITY INTRUSION (collectively, "Security Breach"). Cypress disclaims any liability relating to any Security Breach, and you shall and hereby do release Cypress from any claim, damage, or other liability arising from any Security Breach. In addition, the products described in these materials may contain design defects or errors known as errata which may cause the product to deviate from published specifications. To the extent permitted by applicable law, Cypress reserves the right to make changes to this document without further notice. Cypress does not assume any liability arising out of the application or use of any product or circuit described in this document. Any information provided in this document, including any sample design information or programming code, is provided only for reference purposes. It is the responsibility of the user of this document to properly design, program, and test the functionality and safety of any application made of this information and any resulting product. "High-Risk Device" means any device or system whose failure could cause personal injury, death, or property damage. Examples of High-Risk Devices are weapons, nuclear installations, surgical implants, and other medical devices. "Critical Component" means any component of a High-Risk Device whose failure to perform can be reasonably expected to cause, directly or indirectly, the failure of the High-Risk Device, or to affect its safety or effectiveness. Cypress is not liable, in whole or in part, and you shall and hereby do release Cypress from any claim, damage, or other liability arising from any use of a Cypress product as a Critical Component in a High-Risk Device. You shall indemnify and hold Cypress, its directors, officers, employees, agents, affiliates, distributors, and assigns harmless from and against all claims, costs, damages, and expenses, arising out of any claim, including claims for product liability, personal injury or death, or property damage arising from any use of a Cypress product as a Critical Component in a High-Risk Device. Cypress products are not intended or authorized for use as a Critical Component in any High-Risk Device except to the limited extent that (i) Cypress's published data sheet for the product explicitly states Cypress has qualified the product for use in a specific High-Risk Device, or (ii) Cypress has given you advance written authorization to use the product as a Critical Component in the specific High-Risk Device and you have signed a separate indemnification agreement.  
Cypress, the Cypress logo, Spansion, the Spansion logo, and combinations thereof, WICED, PSoC, CapSense, EZ-USB, F-RAM, and Traveo are trademarks or registered trademarks of Cypress in the United States and other countries. For a more complete list of Cypress trademarks, visit cypress.com. Other names and brands may be claimed as property of their respective owners.
