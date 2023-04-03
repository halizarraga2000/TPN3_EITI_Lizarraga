/* EITI - Universidad Nacional de Tucuman
 * Copyright 2022, Hugo Lizarraga <lizarragahugo@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/** \brief Simple sample of use LPC HAL gpio functions
 **
 ** \addtogroup samples Sample projects
 ** \brief Sample projects to use as a starting point
 ** @{ */

/* === Headers files inclusions =============================================================== */

#include "bsp.h"
#include "clock.h"
#include <stdbool.h>
#include <stddef.h>

//#include "pantalla.h"
//#include "poncho.h"
//#include "chip.h"

/* === Macros definitions ====================================================================== */

/* === Private data type declarations ========================================================== */

typedef enum{
    HORA_SIN_AJUSTAR,
    MOSTRANDO_HORA,
    AJUSTANDO_MINUTOS_ACTUAL,
    AJUSTANDO_HORAS_ACTUAL,
    AJUSTANDO_MINUTOS_ALARMA,
    AJUSTANDO_HORAS_ALARMA,
} modo_t;

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

static board_t board;

static modo_t modo;

static clock_t reloj;

/* === Private function implementation ========================================================= */

void CambiarModo(modo_t valor){
    modo = valor;
    switch (modo){
    case HORA_SIN_AJUSTAR:
        DisplayFlashDigits(board->display, 0, 3, 250);
        break;
    case MOSTRANDO_HORA:
        DisplayFlashDigits(board->display, 0, 0, 0);
        break;
    case AJUSTANDO_MINUTOS_ACTUAL:
        DisplayFlashDigits(board->display, 2, 3, 250);
        break;
    case AJUSTANDO_HORAS_ACTUAL:
        DisplayFlashDigits(board->display, 0, 1, 250);
        break;
    case AJUSTANDO_MINUTOS_ALARMA:
        DisplayFlashDigits(board->display, 2, 3, 250);
        break;
    case AJUSTANDO_HORAS_ALARMA:
        DisplayFlashDigits(board->display, 0, 1, 250);
        break;
    
    default:
        break;
    }
    
}

void SonarAlarma(clock_t clock){

}

/* === Public function implementation ========================================================= */

int main(void) {
    board_t board = BoardCreate();
    //board = BoardCreate();
    reloj = ClockCreate(1000, SonarAlarma); 

    SisTick_Init(10);  //10000
    CambiarModo(HORA_SIN_AJUSTAR);

    while (true) {
        if (DigitalInputHasActivated(board->accept)) {
            DisplayWriteBDC(board->display, (uint8_t[]){1,2,3,4},4);
            DisplayToggleDots(board->display, 1, 2);
        }

        if (DigitalInputHasActivated(board->cancel)) {
            DisplayWriteBDC(board->display, NULL, 0);
        }

        if (DigitalInputHasActivated(board->set_time)) {
        }

        if (DigitalInputHasActivated(board->set_alarm)) {
        }

        if (DigitalInputHasActivated(board->increment)) {
        }

        if (DigitalInputHasActivated(board->decrement)) {
        }
        
        for (int index = 0; index < 100; index++) {
            for (int delay = 0; delay < 25000; delay++) {
                __asm("NOP");
            }
        }
    }
}

void SysTick_Handler(void){
    uint8_t hora[4];

    DisplayRefresh(board->display);
    ClockNewTick(reloj);
    if (modo <= MOSTRANDO_HORA){
        ClockGetTime(reloj, hora, sizeof(hora));
        DisplayWriteBDC(board->display, hora, sizeof(hora));
    }
}


/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */
