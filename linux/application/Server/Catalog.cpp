// Catalog.cpp: implementation of the CCatalog class.
//
//////////////////////////////////////////////////////////////////////

#include "stdio.h"

#include "Catalog.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

int CCatalog::RegisterObject (int Id,void *p)
{
	if (Id>N_OBJECTS)
	{
		printf ("Invalid Object Id (%d)\n");
		return -1;
	}
	m_pObject[Id]=p;
	return 0;
}

void *CCatalog::GetObjectPtr (int Id)
{
	return m_pObject[Id];
}

CCatalog::CCatalog ()
{
	for (int i=0;i<N_OBJECTS;i++)
		m_pObject[i]=NULL;	
}
