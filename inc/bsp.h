/* Copyright 2022, Laboratorio de Microprocesadores, EITI 
 * Universidad Nacional de Tucuman
 * Hugo A. Lizarraga <lizarragahugo@gmail.com>
 * ============================================================================
 */

#ifndef BSP_H   /*! @cond    */
#define BSP_H   /*! @endcond */

/** @file bsp.h
 **
 ** @brief Plantilla de archivos de cabecera 
 **
 ** Plantilla para los archivos de cabeceras de las prácticos de las 
 ** asignaturas Diseño Integrado de Sistemas Emebebidos y Sistemas Embebidos
 ** de Tiempo Real dictadas en de la Especialización en Integración de
 ** Sistemas Informaticos de la Univesidad Nacional de Tucumán
 ** 
 ** | RV | YYYY.MM.DD | Autor       | Descripción de los cambios              |
 ** |----|------------|-------------|-----------------------------------------|
 ** |  1 | 2022.11.23 | Lizarraga H.| Version inicial del archivo             |
 ** 
 ** @defgroup plantilla Plantilals de Archivos
 ** @brief Plantillas de archivos normalizadas
 ** @{ 
 */

/* === Inclusiones de archivos externos ==================================== */
#include "digital.h"

/* === Cabecera C++ ======================================================== */
#ifdef __cplusplus
extern "C" {
#endif

/* === Definicion y Macros publicos ======================================== */

/* == Declaraciones de tipos de datos publicos ============================= */
typedef struct board_s {
    digital_output_t led_azul;
    digital_output_t led_rojo;
    digital_output_t led_amarillo;
    digital_output_t led_verde;

    digital_input_t boton_prueba;
    digital_input_t boton_cambiar;
    digital_input_t boton_prender;
    digital_input_t boton_apagar;
} const * board_t;

/* === Declaraciones de variables publicas ================================= */

/* === Declaraciones de funciones publicas ================================= */
board_t BoardCreate (void);

/* === Ciere de documentacion ============================================== */
#ifdef __cplusplus
}
#endif

/** @} Final de la definición del modulo para doxygen */

#endif   /* BSP_H */
