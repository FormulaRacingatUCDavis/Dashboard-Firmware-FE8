/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.170.0
        Device            :  dsPIC33EP128GM604
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.61
        MPLAB 	          :  MPLAB X v5.45
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/mcc.h"
#define FCY _XTAL_FREQ
#include <libpic30.h>

/*
 * @Summary - writes a string to UART1
 * @Param str - char pointer for string to write to UART1
 * @Param size - size of string to write to UART1
 */
void UART1_Write_String(char * str, uint8_t size) {
    //uint8_t size = sizeof str / sizeof *str;
    uint8_t iter;
    for (iter = 0; iter < size; iter++) {
        UART1_Write(str[iter]);
    }
}

/*
 * @Summary - writes a byte to SPI1
 * @Param data - byte to write to SPI1
 */
void SPI1_Write_Byte(uint8_t data) {
    // selects device by pulling CS low
    IO_RB1_SetLow();
    
    // sends write instruction
    uint8_t WRITE_INSTR = 0x02;
    SPI1_Exchange8bitBuffer(&WRITE_INSTR, 1, NULL);

    // sends 24-bit address
    uint8_t address = 0;
    SPI1_Exchange8bitBuffer(&address, 1, NULL);
    SPI1_Exchange8bitBuffer(&address, 1, NULL);
    SPI1_Exchange8bitBuffer(&address, 1, NULL);

    // sends data
    SPI1_Exchange8bitBuffer(&data, 1, NULL);
    
    // terminates writing by pulling CS high
    IO_RB1_SetHigh();
}

/*
 * @Summary - reads a byte from SPI1
 * @Param read_data - byte to read data into from SPI1
 */
void SPI1_Read_Byte(uint8_t read_data) {
    // selects device by pulling CS low
    IO_RB1_SetLow();
    
    // sends read instruction
    uint8_t READ_INSTR = 0x03;
    SPI1_Exchange8bitBuffer(&READ_INSTR, 1, NULL);

    // sends 24-bit address
    uint8_t address = 0;
    SPI1_Exchange8bitBuffer(&address, 1, NULL);
    SPI1_Exchange8bitBuffer(&address, 1, NULL);
    SPI1_Exchange8bitBuffer(&address, 1, NULL);

    // reads data
    SPI1_Exchange8bitBuffer(NULL, 1, &read_data);
    
    // terminates reading by pulling CS high
    IO_RB1_SetHigh();
}

/*
 * @Summary - outputs an 8-bit color to GPIO pins as follows
 * r2 - RC8
 * r1 - RC7
 * r0 - RC6
 * g2 - RC5
 * g1 - RC4 // note RC3 is "skipped"
 * g0 - RC2
 * b1 - RC1
 * b0 - RC0
 * @Param data - byte for 8-bit color
 */
void color_to_GPIO(uint8_t data) {
    LATC = ((uint16_t)(data & 0b11111000) << 1) + (LATC & 0xFE08) + (data & 0b111);
}
/*
                         Main application
 */
int main(void) {
    // initialize the device
    SYSTEM_Initialize();
    /*
    char txData[8] = "V0.0.5\n";
    uint8_t size = 8;
    UART1_Write_String(txData, size);

    IO_RB1_SetHigh();
    while(1) {
        // write
        uint8_t data = 0x45; // E = 69
        SPI1_Write_Byte(data);
        
        // read
        uint8_t read_data = 0x46; // F = 70
        SPI1_Read_Byte(read_data);

        UART1_Write(read_data);
        __delay_ms(1000);
    }
    */

    while(1) {
        // turns off DE pin upon entering horizontal blanking interval
        TMR2_EndLine();

        /*
        color_to_GPIO(0xFF); //white
        __delay_ms(1000);
        
        color_to_GPIO(0b11100000); //red
        __delay_ms(500);
        
        color_to_GPIO(0b11110000); //orange
        __delay_ms(500);
        
        color_to_GPIO(0b11111100); //yellow
        __delay_ms(500);
        
        color_to_GPIO(0b11100); //green
        __delay_ms(500);
        
        color_to_GPIO(0b11); //blue
        __delay_ms(500);
        
        //purple
        IO_RC8_SetHigh();
        IO_RC7_SetHigh();
        IO_RC6_SetHigh();
        IO_RC5_SetLow();
        IO_RC4_SetLow();
        IO_RC2_SetLow();
        IO_RC1_SetHigh();
        IO_RC0_SetHigh();
        __delay_ms(500);
        */
    }
    
    /*
    while (1) {
        IO_RB1_SetHigh();
        IO_RB1_SetLow();
        uint8_t WRITE_INSTR = 0x02;
        SPI1_Exchange8bitBuffer(&WRITE_INSTR, 1, NULL);

        uint8_t address = 0;
        SPI1_Exchange8bitBuffer(&address, 1, NULL);
        SPI1_Exchange8bitBuffer(&address, 1, NULL);
        SPI1_Exchange8bitBuffer(&address, 1, NULL);

        uint8_t data = 0x45; // E = 69
        SPI1_Exchange8bitBuffer(&data, 1, NULL);


        IO_RB1_SetHigh();
        IO_RB1_SetLow();
        uint8_t READ_INSTR = 0x03;
        SPI1_Exchange8bitBuffer(&READ_INSTR, 1, NULL);

        SPI1_Exchange8bitBuffer(&address, 1, NULL);
        SPI1_Exchange8bitBuffer(&address, 1, NULL);
        SPI1_Exchange8bitBuffer(&address, 1, NULL);

        uint8_t read_data = 0x46; // F = 70
        SPI1_Exchange8bitBuffer(NULL, 1, &read_data);

        UART1_Write(read_data);
        __delay_ms(1000);
    }
    */

    while(1) {}
}
/**
 End of File
*/