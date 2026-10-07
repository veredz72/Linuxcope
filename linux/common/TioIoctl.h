#include <linux/ioctl.h>

#define TIO_IOC_MAGIC 0xE0

#define WRITE_WORD32_REQUEST_CODE			_IOW(TIO_IOC_MAGIC, 1, int)
#define READ_WORD32_REQUEST_CODE			_IOR(TIO_IOC_MAGIC, 2, int)
#define WAIT_FOR_INTERRUPT_REQUEST_CODE		_IOW(TIO_IOC_MAGIC, 3, int)
#define GET_N_INTERRUPTS_CODE				_IOW(TIO_IOC_MAGIC, 4, int)
#define REGISTER_PROCESS_REQUEST_CODE		_IOW(TIO_IOC_MAGIC, 5, int)


typedef struct WORD32_REQUEST
{
	uint32_t Bar;
	uint32_t Offset;
	uint32_t Data;
}WORD32_REQUEST;

typedef struct WAIT_FOR_INTERRUPT_REQUEST
{
	uint32_t Interrupt;
	uint32_t Timeout;
}WAIT_FOR_INTERRUPT_REQUEST;

typedef struct REGISTER_PROCESS_REQUEST
{
	uint32_t Interrupt;
	uint32_t pid;
}REGISTER_PROCESS_REQUEST;

typedef struct GET_N_INTERRUPTS_REQUEST
{
	uint32_t Pps;
	uint32_t Smc[4];
	uint32_t Nav[6];
	uint32_t Mas[4];
	uint32_t NearField;
	uint32_t Miss[4];
}GET_N_INTERRUPTS_REQUEST;



