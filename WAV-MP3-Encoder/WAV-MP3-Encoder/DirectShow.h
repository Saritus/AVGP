#pragma once

#include "stdafx.h"

class CDirectShow
{
public:
	CDirectShow();
	~CDirectShow();

	void Init();
	void setWindow(OAHWND parentwindow);
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
	void setNotifyWindow(UINT NEAR WM_GRAPHNOTIFY);
	void setVideoWindow();
	void setFilename(CString filename);

	CString filename = L"Confused.avi";

private:
	OAHWND window;
	IGraphBuilder *pGraph; // ein Zeiger auf das COM-Interface
	IMediaControl *pMediaControl;
	IMediaEventEx *pEvent;
	IVideoWindow *pVidWin = NULL;
	IMediaSeeking *pSeek = NULL;
};

