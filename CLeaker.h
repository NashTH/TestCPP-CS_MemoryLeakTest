#pragma once
#include <afx.h>
class CLeaker :	public CObject
{
public:

	CLeaker();
	virtual ~CLeaker();

	void startLeaking();

};

