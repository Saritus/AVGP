#pragma once

#include "stdafx.h"

class CDirectShow
{
public:
	CDirectShow();
	CDirectShow(OAHWND window);
	~CDirectShow();

	void Stop();
	void Resume();
	void Pause();
	void CleanUp();
	void Vollbild(bool v);
	void Run();

	void setCurrentPosition(REFERENCE_TIME pos);
	REFERENCE_TIME getCurrentPosition();
	REFERENCE_TIME getLenght();

	LONG GetIt(UINT wparam, LONG lparam);
	void setNotifyWindow(OAHWND window, UINT NEAR WM_GRAPHNOTIFY);
	void setVideoWindow(OAHWND window);

	CString filename = L"Confused.avi";

private:
	IGraphBuilder *pGraph; // ein Zeiger auf das COM-Interface
	IMediaControl *pMediaControl;
	IMediaEventEx *pEvent;
	IVideoWindow *pVidWin = NULL;
	IMediaSeeking *pSeek = NULL;
};

