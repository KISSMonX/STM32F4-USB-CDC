#include "Adc.h"
#include "IoMap.h"
#include "stm32f4xx.h"

uint16_t AdcChannels[ 16 ] ;

void AdcInit()
{
	ADC_InitTypeDef       ADC_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	DMA_InitTypeDef       DMA_InitStructure;

	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_DMA2, ENABLE );
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_ADC1, ENABLE );

	DMA_DeInit(DMA2_Stream0);
	DMA_InitStructure.DMA_Channel = DMA_Channel_0;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)AdcChannels;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_InitStructure.DMA_BufferSize = 16;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(DMA2_Stream0, &DMA_InitStructure);
	DMA_Cmd(DMA2_Stream0, ENABLE);

	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_20Cycles;
	ADC_CommonInit(&ADC_CommonInitStructure);

	ADC_StructInit( &ADC_InitStructure );
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = 16;
	ADC_Init(ADC1, &ADC_InitStructure);

	ADC_RegularChannelConfig( ADC1, ADC_Channel_1, 1, ADC_SampleTime_15Cycles );
	ADC_RegularChannelConfig( ADC1, ADC_Channel_2, 2, ADC_SampleTime_15Cycles );
	ADC_RegularChannelConfig( ADC1, ADC_Channel_3, 3, ADC_SampleTime_15Cycles );
	ADC_RegularChannelConfig( ADC1, ADC_Channel_4, 4, ADC_SampleTime_15Cycles );

	ADC_RegularChannelConfig( ADC1, ADC_Channel_5, 5, ADC_SampleTime_15Cycles );
	ADC_RegularChannelConfig( ADC1, ADC_Channel_6, 6, ADC_SampleTime_15Cycles );
	ADC_RegularChannelConfig( ADC1, ADC_Channel_7, 7, ADC_SampleTime_15Cycles );
	ADC_RegularChannelConfig( ADC1, ADC_Channel_8, 8, ADC_SampleTime_15Cycles );

	ADC_RegularChannelConfig( ADC1, ADC_Channel_9, 9, ADC_SampleTime_15Cycles );
	ADC_RegularChannelConfig( ADC1, ADC_Channel_10, 10, ADC_SampleTime_15Cycles );
	ADC_RegularChannelConfig( ADC1, ADC_Channel_11, 11, ADC_SampleTime_15Cycles );
	ADC_RegularChannelConfig( ADC1, ADC_Channel_12, 12, ADC_SampleTime_15Cycles );

	ADC_RegularChannelConfig( ADC1, ADC_Channel_13, 13, ADC_SampleTime_15Cycles );
	ADC_RegularChannelConfig( ADC1, ADC_Channel_14, 14, ADC_SampleTime_15Cycles );
	ADC_RegularChannelConfig( ADC1, ADC_Channel_15, 15, ADC_SampleTime_15Cycles );
	ADC_RegularChannelConfig( ADC1, ADC_Channel_16, 15, ADC_SampleTime_15Cycles );

	ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);
	ADC_DMACmd(ADC1, ENABLE);
	ADC_Cmd(ADC1, ENABLE);
	ADC_SoftwareStartConv(ADC1);
}

void AiUpdateMap()
{
	for( int i = 0; i < 16; ++i )
		IoMapAiSetPort( i, AdcChannels[ i ] );
}
