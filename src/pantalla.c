/* Copyright 2022, Laboratorio de Microprocesadores, EITI 
 * Universidad Nacional de Tucuman
 * Hugo A. Lizarraga <lizarragahugo@gmail.com>
 * ============================================================================
 */

/** @file pantalla.c
 **
 ** @brief Pantalla de archivos fuente
 **
 ** Plantilla para los archivos de codigo fuente de prácticos de las 
 ** asignaturas Diseño Integrado de Sistemas Emebebidos y Sistemas Embebidos
 ** de Tiempo Real dictadas en de la Especialización en Integración de
 ** Sistemas Informaticos de la Univesidad Nacional de Tucumán
 ** 
 ** | RV | YYYY.MM.DD | Autor       | Descripción de los cambios              |
 ** |----|------------|-------------|-----------------------------------------|
 ** |  1 | 2022.11.29 | Lizarraga H.| Version inicial del archivo             |
 ** 
 ** @defgroup pantalla Plantilals de Archivos
 ** @brief Pantalla de archivos normalizadas
 ** @{ 
 */

/* === Inclusiones de cabeceras ============================================ */
#include "pantalla.h"
#include <string.h>

/* === Definicion y Macros privados ======================================== */
#ifndef DISPLAY_MAX_DIGITS
    #define DISPLAY_MAX_DIGITS 8
#endif
/* === Declaraciones de tipos de datos privados ============================ */
struct display_s {
    uint8_t digits;
    uint8_t active_digit;
    uint8_t flashing_from;
    uint8_t flashing_to;
    uint16_t flashing_frecuency;
    uint16_t flashing_count;
    uint8_t memory [DISPLAY_MAX_DIGITS];
    struct display_driver_s driver[1];
};

/* === Definiciones de variables privadas ================================== */
//static struct display_s instances[1];

static const uint8_t IMAGES[] = {
    SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F,              //! < 0
    SEGMENT_B | SEGMENT_C,                                                              //! < 1
    SEGMENT_A | SEGMENT_B | SEGMENT_D | SEGMENT_E | SEGMENT_G,                          //! < 2
    SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_G,                          //! < 3
    SEGMENT_B | SEGMENT_C | SEGMENT_F | SEGMENT_G,                                      //! < 4
    SEGMENT_A | SEGMENT_C | SEGMENT_D | SEGMENT_F | SEGMENT_G,                          //! < 5
    SEGMENT_A | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F | SEGMENT_G,              //! < 6
    SEGMENT_A | SEGMENT_B | SEGMENT_C,                                                  //! < 7
    SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F | SEGMENT_G,  //! < 8
    SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_F | SEGMENT_G,               //! < 9
};

/* === Definiciones de variables publicas ================================== */

/* === Declaraciones de funciones privadas ================================= */
static display_t DisplayAllocate(void);

/* === Definiciones de funciones privadas ================================== */
display_t DisplayAllocate(void){
    static struct display_s instances[1] = {0};

    return &instances[0];
}

/* === Definiciones de funciones publicas ================================== */
display_t DisplayCreate(uint8_t digits, display_driver_t driver){
    display_t display = DisplayAllocate();

    if (display){
        display->digits = digits;
        display->active_digit = digits-1;
        display->flashing_count = 0;
        display->flashing_from = 0;
        display->flashing_to = 0;
        display->flashing_frecuency = 0;
        memcpy (display->driver, driver,sizeof(display->driver));
        memset (display->memory, 0, sizeof(display->memory));
        display->driver->ScreenTurnOff();
    }

    return display;
}

void DisplayWriteBDC(display_t display, uint8_t * number, uint8_t size){
    memset (display->memory, 0, sizeof(display->memory));
    for(int index = 0; index < size; index++){
        if(index >= display->digits) break;
        display->memory[index] = IMAGES[number[index]];
    }
}

void DisplayRefresh(display_t display){
    uint8_t segments;
    display->driver->ScreenTurnOff();
    display->active_digit = (display->active_digit + 1) % display->digits;

    if (display->active_digit == 0){
        display->flashing_count++;
        if (display->flashing_count >= display->flashing_frecuency){
            display->flashing_count = 0;
        }
    }

    segments = display->memory[display->active_digit];
    if (display->flashing_frecuency > 0){
        if (display->flashing_count >= display->flashing_frecuency / 2){
            if ((display->active_digit >= display ->flashing_from) && (display->active_digit <= display->flashing_to)){
                segments = 0;
            }
        }
    }

    display->driver->SegmentsTurnOn(segments); //display->memory[display->active_digit]);

    display->driver->DigitTurnOn(display->active_digit);
}

void DisplayFlashDigits(display_t display, uint8_t from, uint8_t to, uint16_t frecuency){
    display->flashing_count = 0;
    display->flashing_from = from;
    display->flashing_to = to;
    display->flashing_frecuency = frecuency;
}

void DisplayToggleDots(display_t display, uint8_t from, uint8_t to){
    for(int index = from; index <= to; index++){
        display->memory[index] ^= (1 << 7);
    }
}


/* === Ciere de documentacion ============================================== */

/** @} Final de la definición del modulo para doxygen */

