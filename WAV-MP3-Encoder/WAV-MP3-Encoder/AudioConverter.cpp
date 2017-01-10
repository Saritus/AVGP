#include "stdafx.h"
#include "AudioConverter.h"


CAudioConverter::CAudioConverter()
{
}


CAudioConverter::~CAudioConverter()
{
}

void CAudioConverter::Init() {
	CoInitialize(NULL);
	CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
		IID_IGraphBuilder, (void **)&m_Graph1);
}
