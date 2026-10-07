#include "BaseProtocol.h"

#pragma once
class CTcpProtocol : public CBaseProtocol
{
public:
	CTcpProtocol();
	~CTcpProtocol();
	static int Thread(void *lpParam);
	int Open();
	int Init();
	int Loop();
	int Reply();
};

