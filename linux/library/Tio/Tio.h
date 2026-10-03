typedef enum E_TIO_ERROR_CODE
{
	TIO_OK				= 0,
	TIO_NOT_FOUND			= 1,
	TIO_WAIT_FOR_INT_FAILED	=2
}E_TIO_ERROR_CODE;

int TioOpen (void);

int TioWaitForInterrupt (int Channel, int Timeout);

