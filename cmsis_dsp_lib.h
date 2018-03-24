/**
  * cmsis_dsp_lib.h - Using CMSIS DSP software library.
  *
  * Written in 2017 by Nattapong W. <https://github.com/jazzpiano1004>.
  *
  * To the extent possible under law, the author(s) have dedicated all
  * copyright and related and neighboring rights to this software to
  * the public domain worldwide. This software is distributed without
  * any warranty.
  *
  */

#ifndef  CMSIS_DSP_LIB_H
#define  CMSIS_DSP_LIB_H

/** Define which ARM cortex core that will be used in CMSIS DSP software library.
  * Note : Un-comment only one type of ARM cortex core which you're using.
  */
//#define         ARM_MATH_CM0
//#define         ARM_MATH_CM0PLUS
//#define         ARM_MATH_CM3
#define         ARM_MATH_CM4
//#define         ARM_MATH_CM7

//#include "stm32f7xx_hal.h"
#include "stm32f4xx_hal.h"
#include "arm_math.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifndef M_PI
#define M_PI           3.14159265358979323846
#endif

/**************************** FFT & IFFT section - start *****************************/
#define		REAL_FFT_SIZE_DEFAULT		512
#define   	REAL_FFT_SIZE              	REAL_FFT_SIZE_DEFAULT
#define 	REAL_MAG_FFT_SIZE		REAL_FFT_SIZE/2

typedef struct
{
    arm_rfft_fast_instance_f32 	arm_struct;
    uint16_t  			length;         //rfft size
    float32_t			*tmpBuffer_1;	//any pointer of temporary buffer which is used in FFT and IFFT calculation. 					 Size of buffer must equal to rFFT size
    float32_t			*tmpBuffer_2;	//any pointer of temporary buffer which is used in FFT and IFFT magnitude calculation. Size of buffer must equal to rFFT size

}rfft_f32_TypeDef;

typedef enum
{
		REAL_FFT_SELECT_VAL = 0,
		REAL_IFFT_SELECT_VAL

}rfft_functionSelectFlag;

/* function prototype */
int8_t  CMSIS_DSP_real_FFT_f32_blockInit	(rfft_f32_TypeDef *realFFT_struct,
                                              	float32_t *set_tmp1,
                                             	float32_t *set_tmp2,
                                              	uint16_t setLength);

void    CMSIS_DSP_real_FFT_f32_apply		(rfft_f32_TypeDef *user_RFFT_struct,
                                              	float32_t *rDataIn,
                                              	float32_t *fftOut);

void    CMSIS_DSP_real_IFFT_f32_apply		(rfft_f32_TypeDef *user_RFFT_struct,
                                           	float32_t *fftIn,
                                           	float32_t *ifftOut);

void    CMSIS_DSP_magnitude_FFT_f32_apply	(rfft_f32_TypeDef *realFFT_struct,
                                              	float32_t *rDataIn,
                                               	float32_t *magFFTOut);

void    CMSIS_DSP_magnitudeSquare_FFT_f32_apply	(rfft_f32_TypeDef *realFFT_struct,
                                              	float32_t *rDataIn,
                                              	float32_t *magSqFFTOut);

/****************************  FFT & IFFT section - end  *****************************/



/**************************** Window functions section - start ****************************/
#define   WINDON_MAX_LENGTH          DSP_FRAME_SIZE
typedef struct
{
    float32_t *value;   	   //any pointer of floating-point array which is used to store window's value (with maximum length = REAL_FFT_SIZE)
    uint16_t  length;        //window size
    int8_t    type;          //type of window (hanning, hamming etc.)

}window_TypeDef;

typedef enum
{
	WINDOW_TYPE_RECTANGULAR = 0,
	WINDOW_TYPE_HANNING,
	WINDOW_TYPE_HAMMING

}windowFunctionTypeList;

/* function prototype */
void    CMSIS_DSP_windowFunction_blockInit	(window_TypeDef *w,
                                            	float32_t *set_valueBuf,
                                           	uint8_t setWindowType,
                                            	uint16_t setLength);

void    CMSIS_DSP_windowFunciton_apply		(window_TypeDef *w,
                                            	float32_t *pInput,
                                            	float32_t *pOutput);

/****************************  Window functions section - end  ****************************/



/********************************* FIR filter section - start *********************************/
typedef struct
{
        arm_fir_instance_f32	arm_struct;
	uint16_t 		numTap;		//number of filter's tap
        float32_t		*pCoeff;	//any pointer of floating-point array which is used to store filter coefficient
        float32_t   		*pState;	//any pointer of floating-point array which is used to store filter's state
	float32_t		*tmpBuffer;	//any pointer of temporary buffer which is used in FIR filter calculation.
	uint16_t		blockSize;  	//number of samples that are processed per call

}fir_f32_TypeDef;

/* function prototype */
void	CMSIS_DSP_FIR_f32_blockInit	(fir_f32_TypeDef *user_FIR_struct,
                                   	float32_t *set_pCoeff,
                                   	float32_t *set_pState,
                                   	float32_t *set_tmp,
                                    	uint16_t setNumTap,
                                    	uint32_t setBlockSize);

void	CMSIS_DSP_FIR_f32_apply		(fir_f32_TypeDef *user_FIR_struct,
                               		float32_t *pInput,
                               		float32_t *pOutput);

/********************************* FIR filter section - end *********************************/


#endif
