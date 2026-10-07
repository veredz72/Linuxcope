
#define VENDOR_ID						0x1172 // 0x1957
#define DEVICE_ID						0x0004 // 0x0071

#define N_TIMING						4
#define N_INTERRUPTS					20

#define SIG_PPS							44

#define SIG_SMC1						45
#define SIG_SMC2						46
#define SIG_SMC3						47
#define SIG_SMC4						48

#define SIG_NAV1						49
#define SIG_NAV2						50
#define SIG_NAV3						51
#define SIG_NAV4						52
#define SIG_NAV5						53
#define SIG_NAV6						54

#define SIG_MAS1						55
#define SIG_MAS2						56
#define SIG_MAS3						57
#define SIG_MAS4						58

#define SIG_NEAR						59

#define SIG_MISS1						60
#define SIG_MISS2						61
#define SIG_MISS3						62
#define SIG_MISS4						63

#define MAX_VALUE_4_BITS				15

#define MAX_VALUE_5_BITS				31

#define MAX_VALUE_16_BITS				65535

#define PRI_LENGTH_DEFAULT_VALUE		0x0100
#define PRI_PER_SMC_DEFAULT_VALUE		0x0100
#define SMC_FPD_DEFAULT_VALUE			0x1
#define SMC_LPD_DEFAULT_VALUE			0x1
#define FCTX_REF_CONTROL_DEFAULT_VALUE	0x0
#define PULSE_DELAY_DEFAULT_VALUE		0x10
#define PULSE_WIDTH_DEFAULT_VALUE		0x10

#define N_BAR 2

/******************** BAR 0  - General settings ****************************/

// General

#define PART_NUMBER_MSW_OFFSET					0x0000	

#define PART_NUMBER_LSW_OFFSET					0x0004

#define FIRMWARE_VERSION_OFFSET					0x0008

#define FPGA_BUILD_NUMBER_OFFSET				0x000C

#define FIRMWARE_RELEASE_DATE_OFFSET			0x0010

#define TEST_REGISTER_OFFSET					0x0014

#define SOFTWARE_RESET_REGISTER_OFFSET			0x0018

#define SOFTWARE_RESET_MASK_CONTROL_OFFSET		0x001C

#define RADAR_ON_DISCRETE_STATUS_OFFSET			0x0024

#define TEST_POINT_SIGNALS_REGISTER_OFFSET		0x0028

#define ONE_PPS_SYNTHETIC_STATUS				0x002C

#define ONE_PPS_SYNC_STATUS_OFFSET				0x0030

#define ONE_PPS_LESS_1USEC_OFFSET				0x0034

#define ONE_PPS_TIMEOUT_OFFSET					0x0038

#define ONE_PPS_N_IGNORED_PULSES_OFFSET			0x003C

#define ONE_PPS_SELECT_OFFSET					0x0040

#define ONE_PPS_RESYNC_OFFSET					0x0044

#define EXTERNAL_TO_SYNTHETIC_PPS_OFFSET		0x0048

#define TRIGGER_SOURCE_OFFSET					0x004C

#define RTC_CONTROL_OFFSET						0x0050

#define RTC_RESOLUTION_OFFSET					0x0054

#define RTC_FREE_MSW_OFFSET						0x0058

#define RTC_FREE_LSW_OFFSET						0x005C

static const uint32_t RTC_LATCHED_MSW_OFFSET[5] = { 0x60, 0xF0, 0xF8, 0x100, 0x68 };

static const uint32_t SCHEDULED_SMC_EARLY_STATUS_OFFSET[N_TIMING] = {0x70, 0x94, 0xB0, 0xCC };

static const uint32_t SCHEDULED_SMC_LATE_STATUS_OFFSET[N_TIMING] = { 0x74, 0x98, 0xB4, 0xD0 };

static const uint32_t NEXT_SCHEDULED_SMC_TIME_MSW_OFFSET[N_TIMING] = {0x78, 0x9C, 0xB8, 0xD4 };

static const uint32_t NEXT_SCHEDULED_SMC_TIME_LSW_OFFSET[N_TIMING] = {0x7C, 0xA0, 0xBC, 0xD8 };

static const uint32_t EXTERNAL_SMC_LIMIT_TIME_MSW_OFFSET[N_TIMING] = { 0x80, 0xA4, 0xC0, 0xDC };

static const uint32_t EXTERNAL_SMC_LIMIT_TIME_LSW_OFFSET[N_TIMING] = { 0x84, 0xA8, 0xC4, 0xF0 };

#define ALARM_TIME_MSW_OFFFSET					0x0088

#define ALARAM_TIME_LSW_OFFSET					0x008C

static const uint32_t EARLY_SCHEDULED_SMC_TIME_OFFSET[N_TIMING] = { 0x90, 0xAC, 0xC8, 0xF4 };

#define RTC_INITIAL_VALUE_LSW_OFFSET			0xE8 

#define RTC_INITIAL_VALUE_MSW_OFFSET			0xEC 

#define RTC_UPDATE_OFFSET						0x108

#define SCHEDULED_SMC_PROTECT_OFFSET			0x10C

#define AS_BUILD_ENABLE_BIT_OFFSET				0x1400

#define AS_BUILD_PC_ASSY_OFFSET					0x1404

#define AS_BUILD_FINAL_ASSY_OFFSET				0x1408

#define TEMPERTURE_SENSOR_1_OFFSET				0x140C

#define HUMIDITY_SENSOR_1_OFFSET				0x1410

#define TEMPERTURE_SENSOR_2_OFFSET				0x1414

#define HUMIDITY_SENSOR_2_OFFSET				0x1418

#define VOLTAGE_MONITOR_12V_OFFSET				0x141C

#define VOLTAGE_MONITOR_5V_OFFSET				0x1420

#define VOLTAGE_MONITOR_3_3V_OFFSET				0x1424

#define VOLTAGE_MONITOR_3_3V_FPGA_OFFSET		0x1428

#define VOLTAGE_MONITOR_3_3V_CLK_OFFSET			0x142C

#define VOLTAGE_MONITOR_1_15V_CORE_OFFSET		0x1430

#define VOLTAGE_MONITOR_1_15V_OFFSET			0x1434

#define VOLTAGE_MONITOR_1_5V_OFFSET				0x1438

#define VOLTAGE_MONITOR_2_5V_OFFSET				0x143C

#define SMART_CARD_VERSION_OFFSET				0x1440

// Timing

#define ARTIFICIAL_SMC_REGISTER_OFFSET			0x0200

#define SMC_ASYNC_CONTROL_REGISTER_OFFSET		0x0204

#define SMC_RESET_REGISTER_OFFSET				0x020C

#define SMC_MODE_OFFSET							0x0210

#define SMC_CONTROL_REGISTER_OFFSET				0x0214

#define SMC_PULSE_WIDTH_OFFSET					0x0218

#define SMC_FIRST_PULSE_DELAY_OFFSET			0x021C

#define SMC_LAST_PULSE_DELAY_OFFSET				0x0220

#define FCTX_FIRST_PULSE_DELAY_OFFSET			0x0224

#define BATCH_PULSE_WIDTH_OFFSET				0x0228

#define N_BATCH_PER_SMC_OFFSET					0x022C

#define SUB_BATCH_PULSE_WIDTH_OFFSET			0x0230

#define N_SUB_BATCH_PER_SMC_OFFSET				0x0234

#define PRI_LENGTH_OFFSET						0x0238

#define PRI_PULSE_WIDTH_OFFSET					0x023C

#define PRI_PER_SMC_OFFSET						0x0240

#define SUB_BATCH_FIRST_PULSE_DELAY_OFFSET		0x0244

#define SUB_BATCH_FCTX_PRI_FPD_OFFSET			0x0248

#define FCTX_SYNC_PRI_WINDOW_START_OFFSET		0x024C

#define FCTX_ASYNC_PRI_WINDOW_CONTROL_OFFSET	0x025C

#define OTXU_SMC_WINDOW_START_OFFSET			0X0328

#define OTXU_ASYNC_SMC_CONTROL_OFFSET			0x0338

#define FCTX_REFERENCE_CONTROL_OFFSET			0x0400

#define MAS_OTXU_STATUS_OFFSET					0x0404

#define MAS_CONFIG_OFFSET						0x0408

#define MAS_DISCRETES_STATUS_OFFSET				0x040C
		
#define BLANKING_1_PULSE_WIDTH_OFFSET			0x041C

#define TX_CONTROL_OFFSET						0x042C

#define ANT_CAL_OFFSET							0x430

#define SMC_MUX_OFFSET							0x434

#define FIRST_PULSE_DELAY_OFFSET				0x438

#define CHUNK_LENGTH_OFFSET						0x43C

#define CHUNK_DELAY_OFFSET						0x440

#define N_SYNT_TX_RX_WINDOW_OFFSET				0x444

#define SYNC_RESET_OFFSET						0x448

#define TIO_N_OF_PRI_WINDOW						11

#define MAX_SYNT_TX_RX_WINDOW					4

#define TX_ENABLE_MUX_OFFSET					0x1200

#define TIMING_SOURCE_OFFSET					0x1204

#define WASKAR_MUX_OFFSET						0x1208

#define INTERRUPT_STATUS_OFFSET					0x120C

#define INTERRUPT_CLEAR_OFFSET					0x1210

#define INTERRUPT_MASK_OFFSET					0x1214

#define DSMC_UART_ANC_OFFSET					0x121C

const   uint32_t SMC_ID_UART_CONTROL_OFFSET[4] = { 0x1500, 0x1600, 0x1700, 0x1800 };

#define PCI_EXPRESS_INTERRUPT_CONTROL_OFFSET	0x8050 

const   uint32_t TIMING_BASE_OFFSET[4] = { 0x0, 0x400, 0x800, 0xC00 };

typedef struct FIRMWARE_VERSION
{
	uint32_t SubVersion		: 8;
	uint32_t MinorVersion	: 8;
	uint32_t MajorVersion	: 4;
	uint32_t Compilation	: 12;
}FIRMWARE_VERSION;


typedef union FIRMWARE_VERSION_U
{
	FIRMWARE_VERSION	Bits;
	uint32_t				Word;

}FIRMWARE_VERSION_U;	


typedef struct FIRMWARE_DATE
{
	uint32_t Year       : 16;
	uint32_t Month      : 8;
	uint32_t Day		: 8;
}FIRMWARE_DATE;


typedef union FIRMWARE_DATE_U
{
	FIRMWARE_DATE		Bits;
	uint32_t				Word;

}FIRMWARE_DATE_U;	


typedef struct RESET_MASK_CONTROL
{	
	uint32_t CSU_1		: 1;
	uint32_t Reserved1 : 3;
	uint32_t CSU_2 : 1;
	uint32_t Reserved2 : 3;
	uint32_t CSU_3 : 1;
	uint32_t Reserved3 : 3;
	uint32_t CSU_4 : 1;
	uint32_t Reserved4 : 3;
	uint32_t QUAD : 1;
	uint32_t Reserved5 : 3;
	uint32_t RSM : 1;
	uint32_t Reserved6 : 3;
	uint32_t ANC_1_2 : 1;
	uint32_t Reserved7 : 3;
	uint32_t ANC_3_4 : 1;
	uint32_t NOVA : 1;
	uint32_t TioTiming : 1;
	uint32_t Reserved8 : 1;
}RESET_MASK_CONTROL;

typedef union RESET_MASK_CONTROL_U
{
	RESET_MASK_CONTROL	Bits;
	uint32_t				Word;

}RESET_MASK_CONTROL_U;	


typedef struct INTERRUPT_STATUS
{
	uint32_t	PPS			: 1;
	uint32_t	SMC1		: 1;
	uint32_t	SMC2		: 1;
	uint32_t	SMC3		: 1;
	uint32_t	SMC4		: 1;
	uint32_t	NAV1	    : 1;
	uint32_t	NAV2		: 1;
	uint32_t	NAV3		: 1;
	uint32_t	NAV4		: 1;
	uint32_t	NAV5		: 1;
	uint32_t	NAV6		: 1;
	uint32_t	MAS1		: 1;
	uint32_t	MAS2		: 1;
	uint32_t	MAS3		: 1;
	uint32_t	MAS4		: 1;
	uint32_t	NearField	: 1;
	uint32_t	MISS1		: 1;
	uint32_t    MISS2		: 1;
	uint32_t	MISS3		: 1;
	uint32_t    MISS4		: 1;
	uint32_t	Reserved	: 12;
}INTERRUPT_STATUS;


typedef union INTERRUPT_STATUS_U
{
	uint32_t				Word;
	INTERRUPT_STATUS		Bits;

}INTERRUPT_STATUS_U;


typedef struct SCARD_VERSION
{
	uint32_t Major		: 8;
	uint32_t Minor		: 8;
	uint32_t Mini		: 8;
	uint32_t Unreleased	: 8;

}SCARD_VERSION;


typedef union SCARD_VERSION_U
{
	SCARD_VERSION		Bits;
	uint32_t				Word;

}SCARD_VERSION_U;	


typedef struct TEST_POINT
{
	uint32_t TestPoint1	: 6;
	uint32_t TestPoint2 : 6;
	uint32_t TestPoint3 : 6;
	uint32_t TestPoint4 : 6;
	uint32_t Reserved	: 8;

}TEST_POINT;


typedef union TEST_POINT_U
{
	TEST_POINT		Bits;
	uint32_t			Word;
}TEST_POINT_U;	


typedef struct RTC_CONTROL
{
	uint32_t RtcReset	: 1;
	uint32_t RtcEnable	: 1;
	uint32_t Unused		: 30;
}RTC_CONTROL;


typedef union RTC_CONTROL_U
{
	RTC_CONTROL		Bits;
	uint32_t		Word;
}RTC_CONTROL_U;	


typedef struct MAS_STATUS
{
	uint32_t MAS_1		: 1;
	uint32_t Reserved1	: 3;
	uint32_t MAS_2		: 1;
	uint32_t Reserved2	: 3;
	uint32_t MAS_3		: 1;
	uint32_t Reserved3	: 3;
	uint32_t MAS_4		: 1;
	uint32_t Reserved4	: 3;
	uint32_t Spare		: 16;
}MAS_STATUS;


typedef union MAS_STATUS_U
{
	MAS_STATUS			Bits;
	uint32_t			Word;
}MAS_STATUS_U;	


typedef struct MAS_CONFIG
{
	uint32_t Otxu1		: 4;
	uint32_t Reserved1	: 4;
	uint32_t Otxu2		: 4;
	uint32_t Reserved2	: 4;
	uint32_t Otxu3		: 4;
	uint32_t Reserved3	: 4;
	uint32_t Otxu4		: 4;
	uint32_t Reserved4	: 4;
}MAS_CONFIG;


typedef union MAS_CONFIG_U
{
	MAS_CONFIG		Bits;
	uint32_t		Word;
}MAS_CONFIG_U;

typedef struct ONE_PPS_CONTROL
{
	uint32_t		Filter		: 1;
	uint32_t		Reserved0	: 3;
	uint32_t		External	: 1;
	uint32_t		Reserved1	: 3;
	uint32_t		Synthetic	: 1;
	uint32_t		Reserved2	: 23;	
}ONE_PPS_CONTROL;

typedef union ONE_PPS_CONTROL_U
{
	ONE_PPS_CONTROL		Bits;
	uint32_t			Word;
}ONE_PPS_CONTROL_U;

typedef struct ANT_CAL
{
	uint32_t		Waskar1		: 1;
	uint32_t		Waskar2		: 1;
	uint32_t		Waskar3		: 1;
	uint32_t		Waskar4		: 1;
	uint32_t		Waskar5		: 1;
	uint32_t		Waskar6		: 1;
	uint32_t		Reserved	: 26;
}ANT_CAL;

typedef union ANT_CAL_U
{
	ANT_CAL		Bits;
	uint32_t	Word;
}ANT_CAL_U;

typedef struct WASKAR_MUX
{
	uint32_t Waskar0 : 2;
	uint32_t Waskar1 : 2;
	uint32_t Waskar2 : 2;
	uint32_t Waskar3 : 2;
	uint32_t Waskar4 : 2;
	uint32_t Waskar5 : 2;
	uint32_t Reserved : 20;
}WASKAR_MUX;

typedef union WASKAR_MUX_U
{
	WASKAR_MUX	Bits;
	uint32_t	Word;
}WASKAR_MUX_U;

typedef struct DSMC_UART_ANC
{
	uint32_t		Timing0		: 1;
	uint32_t		Reserved0	: 3;
	uint32_t		Timing1		: 1;
	uint32_t		Reserved1	: 3;
	uint32_t		Timing2		: 1;
	uint32_t		Reserved2	: 3;
	uint32_t		Timing3		: 1;
	uint32_t		Reserved3	: 19;
}DSMC_UART_ANC;

typedef union DSMC_UART_ANC_U
{
	DSMC_UART_ANC	Bits;
	uint32_t		Word;
}DSMC_UART_ANC_U;

/******************** BAR 1  - Power supply and DR settings ****************/

// Power supply

#define PS_STATUS_REGISTER_OFFSET					0x0000

#define PS_SYNC_FREQ_REGISTER_OFFSET				0x0004

#define POWER_SUPPLY_VOLTAGE_SENSOR_1_OFFSET		0x0008

#define POWER_SUPPLY_VOLTAGE_SENSOR_2_OFFSET		0x000C

#define POWER_SUPPLY_VOLTAGE_SENSOR_3_OFFSET		0x0010


#define ACM_UNIT_CONTROL_OFFSET						0x0020

#define BFC_UNIT_CONTROL_OFFSET						0x0024

#define EPU_DISCRETES_STATUS_OFFSET					0x002C

#define E2O_DISCRETES_STATUS_OFFSET					0x0048

#define SDU_CONTROL_OFFSET							0x004C

#define BFCU_1_RESET_OFFSET							0x005C

#define PPS1_IN_MUX_OFFSET							0x006C

#define EXCITER_COMM_RESET_REGISTER_OFFSET			0x0200

#define EXCITER_LOOPBACK_MODE_OFFSET				0x0204

#define TX_FIFO_EXCITER_REGISTER_OFFSET				0x0208

#define RX_FIFO_EXCITER_REGISTER_OFFSET				0x0208

#define EXCITER_FIFO_STATUS_OFFSET					0x020C

#define EXCITER_PLL_LOCK_SETTLING_TIME_OFFSET		0x0210

#define EXCITER_PLL_LOCK_RESET_COUNTERS_OFFSET		0x0214

#define EXCITER_PLL_LOCK_COUNTER_OFFSET				0x0218

#define EXCITER_PLL_LOCK_HIGH_STATE_COUNTER_OFFSET	0x0228

#define EXCITER_DISCRETE_REGISTER_OFFSET			0x0238

typedef struct PS_STATUS
{
	uint32_t LocalPsOk			: 1;
	uint32_t Reserved1 : 3;
	uint32_t PsVinFail : 1;
	uint32_t Reserved2 : 3;
	uint32_t PsLockedOnFrequency : 1;
	uint32_t Reserved3 : 3;
	uint32_t PsOverTemperature : 1;
	uint32_t Reserved4 : 3;
	uint32_t OtsdpFailure : 1;
	uint32_t Reserved5 : 3;
	uint32_t Unused : 12;
}PS_STATUS;


typedef union PS_STATUS_U
{
	PS_STATUS	Bits;
	uint32_t		Word;

}PS_STATUS_U;


typedef struct EXCITER_DISCRETE_STATUS
{
	uint32_t ExciterInd	: 1;
	uint32_t Spare1 : 3;
	uint32_t Sync : 1;
	uint32_t Spare2 : 3;
	uint32_t ProgramEna : 1;
	uint32_t Spare3 : 3;
	uint32_t Unused : 20;
}EXCITER_DISCRETE_STATUS;


typedef union EXCITER_DISCRETE_STATUS_U
{
	EXCITER_DISCRETE_STATUS		Bits;
	uint32_t						Word;

}EXCITER_DISCRETE_STATUS_U;


typedef struct FIFO_STATUS_CONTROL
{
	uint32_t TxFifoWordUsed		: 12;
	uint32_t TxFifoEmptyFlag	: 1;
	uint32_t TxFifoFullFlag		: 1;
	uint32_t TxBurstError		: 1;
	uint32_t TxSmcError			: 1;
	uint32_t NofDwordInRxFifo	: 12;
	uint32_t RxFifoEmptyFlag	: 1;
	uint32_t RxFifoFullFlag		: 1;
	uint32_t RxBurstError		: 1;
	uint32_t CrcError			: 1;

}FIFO_STATUS_CONTROL;


typedef union FIFO_STATUS_CONTROL_U
{
	FIFO_STATUS_CONTROL		Bits;
	uint32_t					Word;

}FIFO_STATUS_CONTROL_U;


typedef struct DISCRETE_STATUS
{
	uint32_t Discrete1	: 1;
	uint32_t Spare1 : 3;
	uint32_t Discrete2 : 1;
	uint32_t Spare2 : 3;
	uint32_t Discrete3 : 1;
	uint32_t Spare3 : 3;
	uint32_t Discrete4 : 1;
	uint32_t Spare4 : 3;
	uint32_t Discrete5 : 1;
	uint32_t Spare5 : 3;
	uint32_t Discrete6 : 1;
	uint32_t Spare6 : 3;
	uint32_t Discrete7 : 1;
	uint32_t Spare7 : 3;
	uint32_t Discrete8 : 1;
	uint32_t Spare8 : 3;
}DISCRETE_STATUS;

typedef union DISCRETE_STATUS_U
{
	DISCRETE_STATUS		Bits;
	uint32_t			Word;
}DISCRETE_STATUS_U;

typedef struct WORD_TO_BYTES
{
	uint32_t Byte1	: 8;
	uint32_t Byte2	: 8;
	uint32_t Byte3	: 8;
	uint32_t Byte4	: 8;
}WORD_TO_BYTES;

typedef union WORD_TO_BYTES_U
{
	uint32_t			Word;
	WORD_TO_BYTES	Bits;

}WORD_TO_BYTES_U;

/************************** UART Control ********************************/

#define BAUD_RATE_NUMERATOR							40.0E6

#define UART_BLOCK_SIZE								0x0080

#define UART_HEADER_TAIL_MAX_SIZE					5

#define ROUND(x) ((int)((x > 0.0) ? (x + 0.5) : (x - 0.5)))


#define NAV1_UART_CONTROL_OFFSET			0x0300

#define NAV1_UART_FIFO_TX_RESET_OFFSET		0x0304

#define NAV1_UART_FIFO_RX_RESET_OFFSET		0x0308

#define NAV1_UART_FIFO_STATUS_OFFSET		0x030C

#define NAV1_UART_TX_RX_FIFO_OFFSET			0x0310

#define NAV1_UART_COM_CONFIG_OFFSET			0x0314

typedef struct DWORD_TO_BYTE
{
	uint32_t Byte0		: 8;
	uint32_t Byte1		: 8;
	uint32_t Byte2		: 8;
	uint32_t Byte3		: 8;

}DWORD_TO_BYTE;

typedef union DWORD_TO_BYTE_U
{
	uint32_t Word;
	DWORD_TO_BYTE Bits;

}DWORD_TO_BYTE_U;


typedef struct UART_CONTROL
{
	uint32_t BaudRate		: 16;
	uint32_t ParityEnable : 1;
	uint32_t ParityType : 1;
	uint32_t Reserved : 14;
}UART_CONTROL;


typedef union UART_CONTROL_U
{
	uint32_t			Word;
	UART_CONTROL	Bits;

}UART_CONTROL_U;


typedef struct UART_STATUS
{
	uint32_t TxWordCount		: 12;
	uint32_t TxFifoStatus : 2;
	uint32_t Reserved1 : 2;
	uint32_t RxWordCount : 12;
	uint32_t RxFifoStatus : 2;
	uint32_t Reserved2 : 2;
}UART_STATUS;


typedef union UART_STATUS_U
{
	UART_STATUS		Bits;
	uint32_t			Word;

}UART_STATUS_U;


typedef struct UART_COM_CONFIG
{
	uint32_t HeaderSize		: 4;
	uint32_t TailSize : 4;
	uint32_t Reserved1 : 4;
	uint32_t AlertLocation : 8;
	uint32_t MessageSize : 8;
	uint32_t Reserved2 : 4;
}UART_COM_CONFIG;

typedef union UART_COM_CONFIG_U
{
	UART_COM_CONFIG		Bits;
	uint32_t				Word;
}UART_COM_CONFIG_U;

/***************************************************************/
#ifdef I2C
typedef int ALT_AVALON_I2C_STATUS_CODE; 
void	i2c_sysOutLong(int addr, int data) {};
int		i2c_sysInLong(int addr) { return 0; };

#define IOWR_ALT_AVALON_I2C_CTRL(base, data)                i2c_sysOutLong (base + ((int)I2C_TRANSFER_COMMAND_FIFO_OFFSET) + ((int)ALT_AVALON_I2C_CTRL_REG) * 4, data) 
#define IOWR_ALT_AVALON_I2C_ISER(base, data)                i2c_sysOutLong (base + ((int)I2C_TRANSFER_COMMAND_FIFO_OFFSET) + ((int)ALT_AVALON_I2C_ISER_REG) * 4, data) 
#define IORD_ALT_AVALON_I2C_RX_DATA(base)                   i2c_sysInLong (base + ((int)I2C_TRANSFER_COMMAND_FIFO_OFFSET) + ((int)ALT_AVALON_I2C_RX_DATA_REG) * 4) 
#define IOWR_ALT_AVALON_I2C_CTRL(base, data)                i2c_sysOutLong (base + ((int)I2C_TRANSFER_COMMAND_FIFO_OFFSET) + ((int)ALT_AVALON_I2C_CTRL_REG) * 4, data) 
#define IORD_ALT_AVALON_I2C_RX_DATA_FIFO_LVL(base)          i2c_sysInLong (base + ((int)I2C_TRANSFER_COMMAND_FIFO_OFFSET) + ((int)ALT_AVALON_I2C_RX_DATA_FIFO_LVL_REG) * 4) 
#define IOWR_ALT_AVALON_I2C_SCL_LOW(base, data)             i2c_sysOutLong (base + ((int)I2C_TRANSFER_COMMAND_FIFO_OFFSET) + ((int)ALT_AVALON_I2C_SCL_LOW_REG) * 4, data) 
#define IOWR_ALT_AVALON_I2C_SCL_HIGH(base, data)            i2c_sysOutLong (base + ((int)I2C_TRANSFER_COMMAND_FIFO_OFFSET) + ((int)ALT_AVALON_I2C_SCL_HIGH_REG) * 4, data) 
#define IOWR_ALT_AVALON_I2C_TFR_CMD(base, data)             i2c_sysOutLong(base + ((int)I2C_TRANSFER_COMMAND_FIFO_OFFSET) + ((int)ALT_AVALON_I2C_TFR_CMD_REG) * 4, data) 
#define IOWR_ALT_AVALON_I2C_SDA_HOLD(base, data)            i2c_sysOutLong (base + ((int)I2C_TRANSFER_COMMAND_FIFO_OFFSET) + ((int)ALT_AVALON_I2C_SDA_HOLD_REG) * 4, data) 
#define IOWR_ALT_AVALON_I2C_ISR(base, data)                 i2c_sysOutLong (base + ((int)I2C_TRANSFER_COMMAND_FIFO_OFFSET) + ((int)ALT_AVALON_I2C_ISR_REG) * 4, data) 
#define IORD_ALT_AVALON_I2C_ISR(base)                       i2c_sysInLong (base + ((int)I2C_TRANSFER_COMMAND_FIFO_OFFSET) + ((int)ALT_AVALON_I2C_ISR_REG) * 4) 
#define IORD_ALT_AVALON_I2C_SDA_HOLD(base)                  i2c_sysInLong (base + ((int)I2C_TRANSFER_COMMAND_FIFO_OFFSET) + ((int)ALT_AVALON_I2C_SDA_HOLD_REG) * 4) 
#define IOWR_ALT_AVALON_I2C_SDA_HOLD(base, data)            i2c_sysOutLong (base + ((int)I2C_TRANSFER_COMMAND_FIFO_OFFSET) + ((int)ALT_AVALON_I2C_SDA_HOLD_REG) * 4, data) 

#define ALT_AVALON_I2C_TFR_CMD_REG                          0
#define ALT_AVALON_I2C_RX_DATA_REG                          1
#define ALT_AVALON_I2C_CTRL_REG                             2
#define ALT_AVALON_I2C_ISER_REG                             3
#define ALT_AVALON_I2C_ISR_REG                              4
#define ALT_AVALON_I2C_RX_DATA_FIFO_LVL_REG                 7
#define ALT_AVALON_I2C_SCL_LOW_REG                          8
#define ALT_AVALON_I2C_SCL_HIGH_REG                         9
#define ALT_AVALON_I2C_SDA_HOLD_REG                         0xa

#define ALT_AVALON_I2C_NACK_ERR								(-5)
#define ALT_AVALON_I2C_TIMEOUT								(-2)

#define ALT_AVALON_I2C_NO_RESTART							(0)
#define ALT_AVALON_I2C_STOP									(1)
#define ALT_AVALON_I2C_RESTART								(1)

#define ALT_AVALON_I2C_WRITE								(0)
#define ALT_AVALON_I2C_READ									(1) 
#define ALT_AVALON_I2C_SUCCESS								(0)
#define ALT_AVALON_I2C_NO_STOP								(0)
#define I2C_BYTE_TIME_OUT_INTERVAL							10000

#define I2C_FIFO_POLLING_MILLI_INTERVAL						100
#define I2C_TRANSFER_COMMAND_FIFO_OFFSET					0x0C00

#define ALT_AVALON_I2C_ISR_TX_READY_OFST					(0)
#define ALT_AVALON_I2C_ISR_NACK_DET_OFST                    (2)
#define ALT_AVALON_I2C_TFR_CMD_STO_OFST                     (8)
#define ALT_AVALON_I2C_ISR_TX_READY_MSK						(1 << ALT_AVALON_I2C_ISR_TX_READY_OFST)
#define ALT_AVALON_I2C_TFR_CMD_STA_OFST                     (9)
#define ALT_AVALON_I2C_ISR_NACK_DET_MSK						(1 << ALT_AVALON_I2C_ISR_NACK_DET_OFST)
#endif
