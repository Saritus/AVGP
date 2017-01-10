#pragma once
class CAudioConverter
{
public:
	CAudioConverter();
	~CAudioConverter();

	void Init();

private:
	IGraphBuilder *m_Graph1;
	IMediaControl *m_Ctrl1;
	IMediaEventEx *m_Event1;
};

