#ifndef 	GPIO_H_
#define 	GPIO_H_

/*ENUM FOR ERROR STATUS*/
typedef enum
{
	GPIO_Ok,
	GPIO_InvalidArgument,
	GPIO_errorNullPtr
}GPIO_ErrorStatus_t;

typedef struct
{
	void* Port;								// specifying  channel
	u32 Mode;								// (MODER - OTYPER- PUPDR)
	u16 Pin;								// ( Variable that holds Channel Selected Pins to be configured )
	u16 Speed;								// (frequency of pin )
}GPIO_ChannelPinCfg_t;


/*Pin status*/
#define 	GPIO_HIGH							((u8)1)
#define 	GPIO_LOW							((u8)0)


#define 	GPIO_PORTA 		                     ((void*)0x40020000)
#define 	GPIO_PORTB 		                     ((void*)0x40020400)
#define 	GPIO_PORTC 		                     ((void*)0x40020800)
#define 	GPIO_PORTD 		                     ((void*)0x40020C00)
#define 	GPIO_PORTE 		                     ((void*)0x40021000)
#define 	GPIO_PORTH 		                     ((void*)0x40021C00)

#define 	GPIO_PIN_00 	                     ((u16)0x0001)
#define 	GPIO_PIN_01 	                     ((u16)0x0002)
#define 	GPIO_PIN_02 	                     ((u16)0x0004)
#define 	GPIO_PIN_03 	                     ((u16)0x0008)
#define 	GPIO_PIN_04 	                     ((u16)0x0010)
#define 	GPIO_PIN_05 	                     ((u16)0x0020)
#define 	GPIO_PIN_06 	                     ((u16)0x0040)
#define 	GPIO_PIN_07 	                     ((u16)0x0080)
#define 	GPIO_PIN_08 	                     ((u16)0x0100)
#define 	GPIO_PIN_09 	                     ((u16)0x0200)
#define 	GPIO_PIN_10 	                     ((u16)0x0400)
#define 	GPIO_PIN_11 	                     ((u16)0x0800)
#define 	GPIO_PIN_12 	                     ((u16)0x1000)
#define 	GPIO_PIN_13 	                     ((u16)0x2000)
#define 	GPIO_PIN_14 	                     ((u16)0x4000)
#define 	GPIO_PIN_15 	                     ((u16)0x8000)

/*  MODER Reg macros*/
#define 	GPIO_MODER_INPUT		             ((u32)0x00000000)
#define 	GPIO_MODER_OUTPUT		             ((u32)0x00000001)
#define 	GPIO_MODER_AF			             ((u32)0x00000002)
#define 	GPIO_MODER_ANALOG			         ((u32)0x00000003)

/*  OTYPER Reg macros*/
#define 	GPIO_OTYPER_PP			             ((u32)0x00000000)
#define 	GPIO_OTYPER_OD			             ((u32)0x00000100)

/*  PUPDR Reg macros*/
#define 	GPIO_PUPDR_NORMAL		             ((u32)0x00000000)
#define 	GPIO_PUPDR_PU		                 ((u32)0x00000010)
#define 	GPIO_PUPDR_PD		                 ((u32)0x00000020)
#define 	GPIO_PUPDR_RES			             ((u32)0x00000030)


/*  OSPEEDER Reg macros*/
#define 	GPIO_OSPEEDR_LS				         ((u32)0x00000000)
#define 	GPIO_OSPEEDR_MS                      ((u32)0x00000001)
#define 	GPIO_OSPEEDR_HS                      ((u32)0x00000002)
#define 	GPIO_OSPEEDR_VHS                     ((u32)0x00000003)

/* Alternate functions Macros for AFRL for GPIO pins from (0 ~ 7)*/
#define 	GPIO_AFRL_PIN0_AF0_SYSTEM	         ((u32)0x00000000)
#define 	GPIO_AFRL_PIN0_AF1_TIM_1_2	         ((u32)0x00000001)
#define 	GPIO_AFRL_PIN0_AF2_TIM_3_4_5	     ((u32)0x00000002)
#define 	GPIO_AFRL_PIN0_AF3_TIM_9_10_11	     ((u32)0x00000003)
#define 	GPIO_AFRL_PIN0_AF4_I2C_1_2_3	     ((u32)0x00000004)
#define 	GPIO_AFRL_PIN0_AF5_SPI_1_2_3_4	     ((u32)0x00000005)
#define 	GPIO_AFRL_PIN0_AF6_SPI3		         ((u32)0x00000006)
#define 	GPIO_AFRL_PIN0_AF7_USART_1_2         ((u32)0x00000007)
#define 	GPIO_AFRL_PIN0_AF8_USART6	         ((u32)0x00000008)
#define 	GPIO_AFRL_PIN0_AF9_I2C_2_3	         ((u32)0x00000009)
#define 	GPIO_AFRL_PIN0_AF10_OTGFS	         ((u32)0x0000000A)
#define 	GPIO_AFRL_PIN0_AF11			         ((u32)0x0000000B)
#define 	GPIO_AFRL_PIN0_AF12_SDIO	         ((u32)0x0000000C)
#define 	GPIO_AFRL_PIN0_AF13      	         ((u32)0x0000000D)
#define 	GPIO_AFRL_PIN0_AF14      	         ((u32)0x0000000E)
#define 	GPIO_AFRL_PIN0_AF15_EVENTOUT         ((u32)0x0000000F)

#define 	GPIO_AFRL_PIN1_AF0_SYSTEM	         ((u32)0x00000000)
#define 	GPIO_AFRL_PIN1_AF1_TIM_1_2	         ((u32)0x00000010)
#define 	GPIO_AFRL_PIN1_AF2_TIM_3_4_5	     ((u32)0x00000020)
#define 	GPIO_AFRL_PIN1_AF3_TIM_9_10_11	     ((u32)0x00000030)
#define 	GPIO_AFRL_PIN1_AF4_I2C_1_2_3	     ((u32)0x00000040)
#define 	GPIO_AFRL_PIN1_AF5_SPI_1_2_3_4	     ((u32)0x00000050)
#define 	GPIO_AFRL_PIN1_AF6_SPI3		         ((u32)0x00000060)
#define 	GPIO_AFRL_PIN1_AF7_USART_1_2         ((u32)0x00000070)
#define 	GPIO_AFRL_PIN1_AF8_USART6	         ((u32)0x00000080)
#define 	GPIO_AFRL_PIN1_AF9_I2C_2_3	         ((u32)0x00000090)
#define 	GPIO_AFRL_PIN1_AF10_OTGFS	         ((u32)0x000000A0)
#define 	GPIO_AFRL_PIN1_AF11			         ((u32)0x000000B0)
#define 	GPIO_AFRL_PIN1_AF12_SDIO	         ((u32)0x000000C0)
#define 	GPIO_AFRL_PIN1_AF13      	         ((u32)0x000000D0)
#define 	GPIO_AFRL_PIN1_AF14      	         ((u32)0x000000E0)
#define 	GPIO_AFRL_PIN1_AF15_EVENTOUT         ((u32)0x000000F0)

#define 	GPIO_AFRL_PIN2_AF0_SYSTEM	         ((u32)0x00000000)
#define 	GPIO_AFRL_PIN2_AF1_TIM_1_2	         ((u32)0x00000100)
#define 	GPIO_AFRL_PIN2_AF2_TIM_3_4_5	     ((u32)0x00000200)
#define 	GPIO_AFRL_PIN2_AF3_TIM_9_10_11	     ((u32)0x00000300)
#define 	GPIO_AFRL_PIN2_AF4_I2C_1_2_3	     ((u32)0x00000400)
#define 	GPIO_AFRL_PIN2_AF5_SPI_1_2_3_4	     ((u32)0x00000500)
#define 	GPIO_AFRL_PIN2_AF6_SPI3		         ((u32)0x00000600)
#define 	GPIO_AFRL_PIN2_AF7_USART_1_2         ((u32)0x00000700)
#define 	GPIO_AFRL_PIN2_AF8_USART6	         ((u32)0x00000800)
#define 	GPIO_AFRL_PIN2_AF9_I2C_2_3	         ((u32)0x00000900)
#define 	GPIO_AFRL_PIN2_AF10_OTGFS	         ((u32)0x00000A00)
#define 	GPIO_AFRL_PIN2_AF11			         ((u32)0x00000B00)
#define 	GPIO_AFRL_PIN2_AF12_SDIO	         ((u32)0x00000C00)
#define 	GPIO_AFRL_PIN2_AF13      	         ((u32)0x00000D00)
#define 	GPIO_AFRL_PIN2_AF14      	         ((u32)0x00000E00)
#define 	GPIO_AFRL_PIN2_AF15_EVENTOUT         ((u32)0x00000F00)

#define 	GPIO_AFRL_PIN3_AF0_SYSTEM	         ((u32)0x00000000)
#define 	GPIO_AFRL_PIN3_AF1_TIM_1_2	         ((u32)0x00001000)
#define 	GPIO_AFRL_PIN3_AF2_TIM_3_4_5	     ((u32)0x00002000)
#define 	GPIO_AFRL_PIN3_AF3_TIM_9_10_11	     ((u32)0x00003000)
#define 	GPIO_AFRL_PIN3_AF4_I2C_1_2_3	     ((u32)0x00004000)
#define 	GPIO_AFRL_PIN3_AF5_SPI_1_2_3_4	     ((u32)0x00005000)
#define 	GPIO_AFRL_PIN3_AF6_SPI3		         ((u32)0x00006000)
#define 	GPIO_AFRL_PIN3_AF7_USART_1_2         ((u32)0x00007000)
#define 	GPIO_AFRL_PIN3_AF8_USART6	         ((u32)0x00008000)
#define 	GPIO_AFRL_PIN3_AF9_I2C_2_3	         ((u32)0x00009000)
#define 	GPIO_AFRL_PIN3_AF10_OTGFS	         ((u32)0x0000A000)
#define 	GPIO_AFRL_PIN3_AF11			         ((u32)0x0000B000)
#define 	GPIO_AFRL_PIN3_AF12_SDIO	         ((u32)0x0000C000)
#define 	GPIO_AFRL_PIN3_AF13      	         ((u32)0x0000D000)
#define 	GPIO_AFRL_PIN3_AF14      	         ((u32)0x0000E000)
#define 	GPIO_AFRL_PIN3_AF15_EVENTOUT         ((u32)0x0000F000)

#define 	GPIO_AFRL_PIN4_AF0_SYSTEM	         ((u32)0x00000000)
#define 	GPIO_AFRL_PIN4_AF1_TIM_1_2	         ((u32)0x00010000)
#define 	GPIO_AFRL_PIN4_AF2_TIM_3_4_5	     ((u32)0x00020000)
#define 	GPIO_AFRL_PIN4_AF3_TIM_9_10_11	     ((u32)0x00030000)
#define 	GPIO_AFRL_PIN4_AF4_I2C_1_2_3	     ((u32)0x00040000)
#define 	GPIO_AFRL_PIN4_AF5_SPI_1_2_3_4	     ((u32)0x00050000)
#define 	GPIO_AFRL_PIN4_AF6_SPI3		         ((u32)0x00060000)
#define 	GPIO_AFRL_PIN4_AF7_USART_1_2         ((u32)0x00070000)
#define 	GPIO_AFRL_PIN4_AF8_USART6	         ((u32)0x00080000)
#define 	GPIO_AFRL_PIN4_AF9_I2C_2_3	         ((u32)0x00090000)
#define 	GPIO_AFRL_PIN4_AF10_OTGFS	         ((u32)0x000A0000)
#define 	GPIO_AFRL_PIN4_AF11			         ((u32)0x000B0000)
#define 	GPIO_AFRL_PIN4_AF12_SDIO	         ((u32)0x000C0000)
#define 	GPIO_AFRL_PIN4_AF13      	         ((u32)0x000D0000)
#define 	GPIO_AFRL_PIN4_AF14      	         ((u32)0x000E0000)
#define 	GPIO_AFRL_PIN4_AF15_EVENTOUT         ((u32)0x000F0000)

#define 	GPIO_AFRL_PIN5_AF0_SYSTEM	         ((u32)0x00000000)
#define 	GPIO_AFRL_PIN5_AF1_TIM_1_2	         ((u32)0x00100000)
#define 	GPIO_AFRL_PIN5_AF2_TIM_3_4_5	     ((u32)0x00200000)
#define 	GPIO_AFRL_PIN5_AF3_TIM_9_10_11	     ((u32)0x00300000)
#define 	GPIO_AFRL_PIN5_AF4_I2C_1_2_3	     ((u32)0x00400000)
#define 	GPIO_AFRL_PIN5_AF5_SPI_1_2_3_4	     ((u32)0x00500000)
#define 	GPIO_AFRL_PIN5_AF6_SPI3		         ((u32)0x00600000)
#define 	GPIO_AFRL_PIN5_AF7_USART_1_2         ((u32)0x00700000)
#define 	GPIO_AFRL_PIN5_AF8_USART6	         ((u32)0x00800000)
#define 	GPIO_AFRL_PIN5_AF9_I2C_2_3	         ((u32)0x00900000)
#define 	GPIO_AFRL_PIN5_AF10_OTGFS	         ((u32)0x00A00000)
#define 	GPIO_AFRL_PIN5_AF11			         ((u32)0x00B00000)
#define 	GPIO_AFRL_PIN5_AF12_SDIO	         ((u32)0x00C00000)
#define 	GPIO_AFRL_PIN5_AF13      	         ((u32)0x00D00000)
#define 	GPIO_AFRL_PIN5_AF14      	         ((u32)0x00E00000)
#define 	GPIO_AFRL_PIN5_AF15_EVENTOUT         ((u32)0x00F00000)

#define 	GPIO_AFRL_PIN6_AF0_SYSTEM	         ((u32)0x00000000)
#define 	GPIO_AFRL_PIN6_AF1_TIM_1_2	         ((u32)0x01000000)
#define 	GPIO_AFRL_PIN6_AF2_TIM_3_4_5	     ((u32)0x02000000)
#define 	GPIO_AFRL_PIN6_AF3_TIM_9_10_11	     ((u32)0x03000000)
#define 	GPIO_AFRL_PIN6_AF4_I2C_1_2_3	     ((u32)0x04000000)
#define 	GPIO_AFRL_PIN6_AF5_SPI_1_2_3_4	     ((u32)0x05000000)
#define 	GPIO_AFRL_PIN6_AF6_SPI3		         ((u32)0x06000000)
#define 	GPIO_AFRL_PIN6_AF7_USART_1_2         ((u32)0x07000000)
#define 	GPIO_AFRL_PIN6_AF8_USART6	         ((u32)0x08000000)
#define 	GPIO_AFRL_PIN6_AF9_I2C_2_3	         ((u32)0x09000000)
#define 	GPIO_AFRL_PIN6_AF10_OTGFS	         ((u32)0x0A000000)
#define 	GPIO_AFRL_PIN6_AF11			         ((u32)0x0B000000)
#define 	GPIO_AFRL_PIN6_AF12_SDIO	         ((u32)0x0C000000)
#define 	GPIO_AFRL_PIN6_AF13      	         ((u32)0x0D000000)
#define 	GPIO_AFRL_PIN6_AF14      	         ((u32)0x0E000000)
#define 	GPIO_AFRL_PIN6_AF15_EVENTOUT         ((u32)0x0F000000)

#define 	GPIO_AFRL_PIN7_AF0_SYSTEM	         ((u32)0x00000000)
#define 	GPIO_AFRL_PIN7_AF1_TIM_1_2	         ((u32)0x10000000)
#define 	GPIO_AFRL_PIN7_AF2_TIM_3_4_5	     ((u32)0x20000000)
#define 	GPIO_AFRL_PIN7_AF3_TIM_9_10_11	     ((u32)0x30000000)
#define 	GPIO_AFRL_PIN7_AF4_I2C_1_2_3	     ((u32)0x40000000)
#define 	GPIO_AFRL_PIN7_AF5_SPI_1_2_3_4	     ((u32)0x50000000)
#define 	GPIO_AFRL_PIN7_AF6_SPI3		         ((u32)0x60000000)
#define 	GPIO_AFRL_PIN7_AF7_USART_1_2         ((u32)0x70000000)
#define 	GPIO_AFRL_PIN7_AF8_USART6	         ((u32)0x80000000)
#define 	GPIO_AFRL_PIN7_AF9_I2C_2_3	         ((u32)0x90000000)
#define 	GPIO_AFRL_PIN7_AF10_OTGFS	         ((u32)0xA0000000)
#define 	GPIO_AFRL_PIN7_AF11			         ((u32)0xB0000000)
#define 	GPIO_AFRL_PIN7_AF12_SDIO	         ((u32)0xC0000000)
#define 	GPIO_AFRL_PIN7_AF13      	         ((u32)0xD0000000)
#define 	GPIO_AFRL_PIN7_AF14      	         ((u32)0xE0000000)
#define 	GPIO_AFRL_PIN7_AF15_EVENTOUT         ((u32)0xF0000000)



/* Alternate functions Macros for AFRH for GPIO pins from (8 ~ 15)*/
#define 	GPIO_AFRH_PIN8_AF0_SYSTEM	         ((u32)0x00000000)
#define 	GPIO_AFRH_PIN8_AF1_TIM_1_2	         ((u32)0x00000001)
#define 	GPIO_AFRH_PIN8_AF2_TIM_3_4_5	     ((u32)0x00000002)
#define 	GPIO_AFRH_PIN8_AF3_TIM_9_10_11	     ((u32)0x00000003)
#define 	GPIO_AFRH_PIN8_AF4_I2C_1_2_3	     ((u32)0x00000004)
#define 	GPIO_AFRH_PIN8_AF5_SPI_1_2_3_4	     ((u32)0x00000005)
#define 	GPIO_AFRH_PIN8_AF6_SPI3		         ((u32)0x00000006)
#define 	GPIO_AFRH_PIN8_AF7_USART_1_2         ((u32)0x00000007)
#define 	GPIO_AFRH_PIN8_AF8_USART6	         ((u32)0x00000008)
#define 	GPIO_AFRH_PIN8_AF9_I2C_2_3	         ((u32)0x00000009)
#define 	GPIO_AFRH_PIN8_AF10_OTGFS	         ((u32)0x0000000A)
#define 	GPIO_AFRH_PIN8_AF11			         ((u32)0x0000000B)
#define 	GPIO_AFRH_PIN8_AF12_SDIO	         ((u32)0x0000000C)
#define 	GPIO_AFRH_PIN8_AF13      	         ((u32)0x0000000D)
#define 	GPIO_AFRH_PIN8_AF14      	         ((u32)0x0000000E)
#define 	GPIO_AFRH_PIN8_AF15_EVENTOUT         ((u32)0x0000000F)

#define 	GPIO_AFRH_PIN9_AF0_SYSTEM	         ((u32)0x00000000)
#define 	GPIO_AFRH_PIN9_AF1_TIM_1_2	         ((u32)0x00000010)
#define 	GPIO_AFRH_PIN9_AF2_TIM_3_4_5	     ((u32)0x00000020)
#define 	GPIO_AFRH_PIN9_AF3_TIM_9_10_11	     ((u32)0x00000030)
#define 	GPIO_AFRH_PIN9_AF4_I2C_1_2_3	     ((u32)0x00000040)
#define 	GPIO_AFRH_PIN9_AF5_SPI_1_2_3_4	     ((u32)0x00000050)
#define 	GPIO_AFRH_PIN9_AF6_SPI3		         ((u32)0x00000060)
#define 	GPIO_AFRH_PIN9_AF7_USART_1_2         ((u32)0x00000070)
#define 	GPIO_AFRH_PIN9_AF8_USART6	         ((u32)0x00000080)
#define 	GPIO_AFRH_PIN9_AF9_I2C_2_3	         ((u32)0x00000090)
#define 	GPIO_AFRH_PIN9_AF10_OTGFS	         ((u32)0x000000A0)
#define 	GPIO_AFRH_PIN9_AF11			         ((u32)0x000000B0)
#define 	GPIO_AFRH_PIN9_AF12_SDIO	         ((u32)0x000000C0)
#define 	GPIO_AFRH_PIN9_AF13      	         ((u32)0x000000D0)
#define 	GPIO_AFRH_PIN9_AF14      	         ((u32)0x000000E0)
#define 	GPIO_AFRH_PIN9_AF15_EVENTOUT         ((u32)0x000000F0)

#define 	GPIO_AFRH_PIN10_AF0_SYSTEM	         ((u32)0x00000000)
#define 	GPIO_AFRH_PIN10_AF1_TIM_1_2	         ((u32)0x00000100)
#define 	GPIO_AFRH_PIN10_AF2_TIM_3_4_5	     ((u32)0x00000200)
#define 	GPIO_AFRH_PIN10_AF3_TIM_9_10_11	     ((u32)0x00000300)
#define 	GPIO_AFRH_PIN10_AF4_I2C_1_2_3	     ((u32)0x00000400)
#define 	GPIO_AFRH_PIN10_AF5_SPI_1_2_3_4	     ((u32)0x00000500)
#define 	GPIO_AFRH_PIN10_AF6_SPI3		     ((u32)0x00000600)
#define 	GPIO_AFRH_PIN10_AF7_USART_1_2        ((u32)0x00000700)
#define 	GPIO_AFRH_PIN10_AF8_USART6	         ((u32)0x00000800)
#define 	GPIO_AFRH_PIN10_AF9_I2C_2_3	         ((u32)0x00000900)
#define 	GPIO_AFRH_PIN10_AF10_OTGFS	         ((u32)0x00000A00)
#define 	GPIO_AFRH_PIN10_AF11			     ((u32)0x00000B00)
#define 	GPIO_AFRH_PIN10_AF12_SDIO	         ((u32)0x00000C00)
#define 	GPIO_AFRH_PIN10_AF13      	         ((u32)0x00000D00)
#define 	GPIO_AFRH_PIN10_AF14      	         ((u32)0x00000E00)
#define 	GPIO_AFRH_PIN10_AF15_EVENTOUT        ((u32)0x00000F00)

#define 	GPIO_AFRH_PIN11_AF0_SYSTEM	         ((u32)0x00000000)
#define 	GPIO_AFRH_PIN11_AF1_TIM_1_2	         ((u32)0x00001000)
#define 	GPIO_AFRH_PIN11_AF2_TIM_3_4_5	     ((u32)0x00002000)
#define 	GPIO_AFRH_PIN11_AF3_TIM_9_10_11	     ((u32)0x00003000)
#define 	GPIO_AFRH_PIN11_AF4_I2C_1_2_3	     ((u32)0x00004000)
#define 	GPIO_AFRH_PIN11_AF5_SPI_1_2_3_4	     ((u32)0x00005000)
#define 	GPIO_AFRH_PIN11_AF6_SPI3		     ((u32)0x00006000)
#define 	GPIO_AFRH_PIN11_AF7_USART_1_2        ((u32)0x00007000)
#define 	GPIO_AFRH_PIN11_AF8_USART6	         ((u32)0x00008000)
#define 	GPIO_AFRH_PIN11_AF9_I2C_2_3	         ((u32)0x00009000)
#define 	GPIO_AFRH_PIN11_AF10_OTGFS	         ((u32)0x0000A000)
#define 	GPIO_AFRH_PIN11_AF11			     ((u32)0x0000B000)
#define 	GPIO_AFRH_PIN11_AF12_SDIO	         ((u32)0x0000C000)
#define 	GPIO_AFRH_PIN11_AF13      	         ((u32)0x0000D000)
#define 	GPIO_AFRH_PIN11_AF14      	         ((u32)0x0000E000)
#define 	GPIO_AFRH_PIN11_AF15_EVENTOUT        ((u32)0x0000F000)

#define 	GPIO_AFRH_PIN12_AF0_SYSTEM	         ((u32)0x00000000)
#define 	GPIO_AFRH_PIN12_AF1_TIM_1_2	         ((u32)0x00010000)
#define 	GPIO_AFRH_PIN12_AF2_TIM_3_4_5	     ((u32)0x00020000)
#define 	GPIO_AFRH_PIN12_AF3_TIM_9_10_11	     ((u32)0x00030000)
#define 	GPIO_AFRH_PIN12_AF4_I2C_1_2_3	     ((u32)0x00040000)
#define 	GPIO_AFRH_PIN12_AF5_SPI_1_2_3_4	     ((u32)0x00050000)
#define 	GPIO_AFRH_PIN12_AF6_SPI3		     ((u32)0x00060000)
#define 	GPIO_AFRH_PIN12_AF7_USART_1_2        ((u32)0x00070000)
#define 	GPIO_AFRH_PIN12_AF8_USART6	         ((u32)0x00080000)
#define 	GPIO_AFRH_PIN12_AF9_I2C_2_3	         ((u32)0x00090000)
#define 	GPIO_AFRH_PIN12_AF10_OTGFS	         ((u32)0x000A0000)
#define 	GPIO_AFRH_PIN12_AF11			     ((u32)0x000B0000)
#define 	GPIO_AFRH_PIN12_AF12_SDIO	         ((u32)0x000C0000)
#define 	GPIO_AFRH_PIN12_AF13      	         ((u32)0x000D0000)
#define 	GPIO_AFRH_PIN12_AF14      	         ((u32)0x000E0000)
#define 	GPIO_AFRH_PIN12_AF15_EVENTOUT        ((u32)0x000F0000)

#define 	GPIO_AFRH_PIN13_AF0_SYSTEM	         ((u32)0x00000000)
#define 	GPIO_AFRH_PIN13_AF1_TIM_1_2	         ((u32)0x00100000)
#define 	GPIO_AFRH_PIN13_AF2_TIM_3_4_5	     ((u32)0x00200000)
#define 	GPIO_AFRH_PIN13_AF3_TIM_9_10_11	     ((u32)0x00300000)
#define 	GPIO_AFRH_PIN13_AF4_I2C_1_2_3	     ((u32)0x00400000)
#define 	GPIO_AFRH_PIN13_AF5_SPI_1_2_3_4	     ((u32)0x00500000)
#define 	GPIO_AFRH_PIN13_AF6_SPI3		     ((u32)0x00600000)
#define 	GPIO_AFRH_PIN13_AF7_USART_1_2        ((u32)0x00700000)
#define 	GPIO_AFRH_PIN13_AF8_USART6	         ((u32)0x00800000)
#define 	GPIO_AFRH_PIN13_AF9_I2C_2_3	         ((u32)0x00900000)
#define 	GPIO_AFRH_PIN13_AF10_OTGFS	         ((u32)0x00A00000)
#define 	GPIO_AFRH_PIN13_AF11			     ((u32)0x00B00000)
#define 	GPIO_AFRH_PIN13_AF12_SDIO	         ((u32)0x00C00000)
#define 	GPIO_AFRH_PIN13_AF13      	         ((u32)0x00D00000)
#define 	GPIO_AFRH_PIN13_AF14      	         ((u32)0x00E00000)
#define 	GPIO_AFRH_PIN13_AF15_EVENTOUT        ((u32)0x00F00000)

#define 	GPIO_AFRH_PIN14_AF0_SYSTEM	         ((u32)0x00000000)
#define 	GPIO_AFRH_PIN14_AF1_TIM_1_2	         ((u32)0x01000000)
#define 	GPIO_AFRH_PIN14_AF2_TIM_3_4_5	     ((u32)0x02000000)
#define 	GPIO_AFRH_PIN14_AF3_TIM_9_10_11	     ((u32)0x03000000)
#define 	GPIO_AFRH_PIN14_AF4_I2C_1_2_3	     ((u32)0x04000000)
#define 	GPIO_AFRH_PIN14_AF5_SPI_1_2_3_4	     ((u32)0x05000000)
#define 	GPIO_AFRH_PIN14_AF6_SPI3		     ((u32)0x06000000)
#define 	GPIO_AFRH_PIN14_AF7_USART_1_2        ((u32)0x07000000)
#define 	GPIO_AFRH_PIN14_AF8_USART6	         ((u32)0x08000000)
#define 	GPIO_AFRH_PIN14_AF9_I2C_2_3	         ((u32)0x09000000)
#define 	GPIO_AFRH_PIN14_AF10_OTGFS	         ((u32)0x0A000000)
#define 	GPIO_AFRH_PIN14_AF11			     ((u32)0x0B000000)
#define 	GPIO_AFRH_PIN14_AF12_SDIO	         ((u32)0x0C000000)
#define 	GPIO_AFRH_PIN14_AF13      	         ((u32)0x0D000000)
#define 	GPIO_AFRH_PIN14_AF14      	         ((u32)0x0E000000)
#define 	GPIO_AFRH_PIN14_AF15_EVENTOUT        ((u32)0x0F000000)

#define 	GPIO_AFRH_PIN15_AF0_SYSTEM	         ((u32)0x00000000)
#define 	GPIO_AFRH_PIN15_AF1_TIM_1_2	         ((u32)0x10000000)
#define 	GPIO_AFRH_PIN15_AF2_TIM_3_4_5	     ((u32)0x20000000)
#define 	GPIO_AFRH_PIN15_AF3_TIM_9_10_11	     ((u32)0x30000000)
#define 	GPIO_AFRH_PIN15_AF4_I2C_1_2_3	     ((u32)0x40000000)
#define 	GPIO_AFRH_PIN15_AF5_SPI_1_2_3_4	     ((u32)0x50000000)
#define 	GPIO_AFRH_PIN15_AF6_SPI3		     ((u32)0x60000000)
#define 	GPIO_AFRH_PIN15_AF7_USART_1_2        ((u32)0x70000000)
#define 	GPIO_AFRH_PIN15_AF8_USART6	         ((u32)0x80000000)
#define 	GPIO_AFRH_PIN15_AF9_I2C_2_3	         ((u32)0x90000000)
#define 	GPIO_AFRH_PIN15_AF10_OTGFS	         ((u32)0xA0000000)
#define 	GPIO_AFRH_PIN15_AF11			     ((u32)0xB0000000)
#define 	GPIO_AFRH_PIN15_AF12_SDIO	         ((u32)0xC0000000)
#define 	GPIO_AFRH_PIN15_AF13      	         ((u32)0xD0000000)
#define 	GPIO_AFRH_PIN15_AF14      	         ((u32)0xE0000000)
#define 	GPIO_AFRH_PIN15_AF15_EVENTOUT        ((u32)0xF0000000)




/* ----------------------------Function Prototypes section ---------------------------------------------- */

extern GPIO_ErrorStatus_t Gpio_Init (GPIO_ChannelPinCfg_t* Add_pstrPinCfg);

extern GPIO_ErrorStatus_t Gpio_setPinValue (void * GPIO_pvPort, u16 Copy_u16Pin , u8 Copy_u8Value);

extern GPIO_ErrorStatus_t Gpio_ReadPinValue(GPIO_ChannelPinCfg_t * Add_strGpioCfg, pu8 Add_pu8Value);

extern GPIO_ErrorStatus_t Gpio_SetPinAlternateFunc(void * GPIO_pvPort, u16 Copy_u16Pin, u32 Copy_u32AlternateFunction);

extern GPIO_ErrorStatus_t Gpio_setPortValue (void * GPIO_pvPort, u16 Copy_u16Value);

/* ----------------------------------------Configuration Section -------------------------------------------------- */

#define 	GPIO_INPUT_FLOATING					(GPIO_MODER_INPUT  | GPIO_PUPDR_NORMA)
#define 	GPIO_INPUT_PU					    (GPIO_MODER_INPUT  | GPIO_PUPDR_PU)
#define 	GPIO_INPUT_PD					    (GPIO_MODER_INPUT  | GPIO_PUPDR_PD)


#define 	GPIO_OUTPUT_PP						(GPIO_MODER_OUTPUT | GPIO_PUPDR_NORMAL | GPIO_OTYPER_PP)
#define 	GPIO_OUTPUT_PP_PU					(GPIO_MODER_OUTPUT | GPIO_PUPDR_PU     | GPIO_OTYPER_PP)
#define 	GPIO_OUTPUT_PP_PD					(GPIO_MODER_OUTPUT | GPIO_PUPDR_PD     | GPIO_OTYPER_PP)

#define 	GPIO_OUTPUT_OD						(GPIO_MODER_OUTPUT | GPIO_PUPDR_NORMAL | GPIO_OTYPER_OD)
#define 	GPIO_OUTPUT_OD_PU					(GPIO_MODER_OUTPUT | GPIO_PUPDR_PU     | GPIO_OTYPER_OD)
#define 	GPIO_OUTPUT_OD_PD					(GPIO_MODER_OUTPUT | GPIO_PUPDR_PD     | GPIO_OTYPER_OD)


#define 	GPIO_AF_PP						    (GPIO_MODER_AF     | GPIO_PUPDR_NORMAL | GPIO_OTYPER_PP)
#define 	GPIO_AF_PP_PU					    (GPIO_MODER_AF     | GPIO_PUPDR_PU     | GPIO_OTYPER_PP)
#define 	GPIO_AF_PP_PD					    (GPIO_MODER_AF     | GPIO_PUPDR_PD     | GPIO_OTYPER_PP)

#define 	GPIO_AF_OD						    (GPIO_MODER_AF     | GPIO_PUPDR_NORMAL | GPIO_OTYPER_OD)
#define 	GPIO_AF_OD_PU					    (GPIO_MODER_AF     | GPIO_PUPDR_PU     | GPIO_OTYPER_OD)
#define 	GPIO_AF_OD_PD					    (GPIO_MODER_AF     | GPIO_PUPDR_PD     | GPIO_OTYPER_OD)


#define 	GPIO_PIN_ANALOG						(GPIO_MODER_ANALOG)





#endif
