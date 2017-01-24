#include "stdafx.h"
#include "DirectSound.h"

#define M_PI 3.14159265358979323846

CDirectSound::CDirectSound() {
	CoInitialize(NULL); // init COM-Interface
	lpds = 0; lpDSBPrimary = 0;
}

CDirectSound::~CDirectSound() {
	if (lpds) {
		lpDSBPrimary->Release();
		lpDSBPrimary = 0;
		lpds->Release(); lpds = 0;
	}
	// falls es das einzige COM-Interface ist
	// CoUninitialize();
}

bool CDirectSound::Create(CWnd* wnd) {
	if (!lpds) {
		// init DirectSound-Interface
		if (CoCreateInstance(CLSID_DirectSound, NULL, CLSCTX_ALL,
			IID_IDirectSound, (LPVOID*)&lpds) != DS_OK) {
			AfxMessageBox(L"DirectSound object not created.");
			return false;
		}
		if (lpds->Initialize(0) != DS_OK) {
			AfxMessageBox(L"Error: Initialize DirectSound-Interface");
			return false;
		}

		// be cooperativ
		if (lpds->SetCooperativeLevel(wnd->GetSafeHwnd(), DSSCL_NORMAL) != DS_OK) {
			AfxMessageBox(L"Application's Behavior not available");
			return false;
		}

		// init primary sound buffer
		memset(&dsbd, 0, sizeof(dsbd));
		dsbd.dwSize = sizeof(dsbd);
		dsbd.dwFlags = DSBCAPS_PRIMARYBUFFER;
		if (lpds->CreateSoundBuffer(&dsbd, &lpDSBPrimary, NULL) != DS_OK) {
			AfxMessageBox(L"Cannot create the primary buffer");
			return false;
		}
	}
	return true;
}

LPDIRECTSOUNDBUFFER CDirectSound::CreateSoundBuffer(WORD Channels, WORD BitsPerSample, DWORD SamplesPerSec, WORD seconds) {
	if (!lpds) return 0;
	WAVEFORMATEX pcmwf; LPDIRECTSOUNDBUFFER lpDSBuffer;
	memset(&pcmwf, 0, sizeof(PCMWAVEFORMAT));
	pcmwf.wFormatTag = WAVE_FORMAT_PCM;
	pcmwf.nChannels = Channels; pcmwf.wBitsPerSample = BitsPerSample;
	pcmwf.nSamplesPerSec = SamplesPerSec;
	pcmwf.nBlockAlign = Channels*(BitsPerSample / 8); // for example 4 Byte
	pcmwf.nAvgBytesPerSec = pcmwf.nSamplesPerSec * pcmwf.nBlockAlign;
	memset(&dsbd, 0, sizeof(dsbd)); dsbd.dwSize = sizeof(dsbd);
	dsbd.dwFlags = DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY |
		DSBCAPS_GLOBALFOCUS;
	dsbd.dwBufferBytes = seconds * pcmwf.nAvgBytesPerSec;
	dsbd.lpwfxFormat = &pcmwf;
	// create the sound buffer now
	if (lpds->CreateSoundBuffer(&dsbd, &lpDSBuffer, NULL) != DS_OK) {
		AfxMessageBox(L"Cannot create a secondary buffer");
		return 0;
	}
	return lpDSBuffer;
}

bool CDirectSound::GetWaveFormat(LPDIRECTSOUNDBUFFER buf, WAVEFORMATEX *pcmwf)
{
	if (!buf) return false;
	if (buf->GetFormat(pcmwf, sizeof *pcmwf, NULL) != DS_OK) {
		AfxMessageBox(L"Cannot get audio format");
		return false;
	}
	return true;
}

bool CDirectSound::LockBuffer(LPDIRECTSOUNDBUFFER buf, DWORD offset, DWORD size, void **ptr1, DWORD *bytes1, void **ptr2, DWORD *bytes2) {
	WAVEFORMATEX pcmwf;
	if (!buf) return false;
	if (!GetWaveFormat(buf, &pcmwf)) return false;
	if (buf->Lock(offset * pcmwf.nAvgBytesPerSec, // a offset of some seconds
		size * pcmwf.nAvgBytesPerSec, // write size seconds
		ptr1, // get pointer 1
		bytes1, // get bytes available there
		ptr2, // get pointer 2 (the buffer is circular)
		bytes2, // get bytes available there
		NULL) != DS_OK) {
		AfxMessageBox(L"Cannot lock the secondary buffer");
		return false;
	}
	return true;
}

bool CDirectSound::UnlockBuffer(LPDIRECTSOUNDBUFFER buf, void *ptr1, DWORD bytes1, void *ptr2, DWORD bytes2) {
	if (!buf) return false;
	if (buf->Unlock(ptr1, bytes1, ptr2, bytes2) != DS_OK) {
		AfxMessageBox(L"Cannot unlock the secondary buffer");
		return false;
	}
	return true;
}

bool CDirectSound::Play(LPDIRECTSOUNDBUFFER buf, bool looped)
{
	if (!buf) return false;
	if (buf->Play(0, 0, looped ? DSBPLAY_LOOPING : 0) != DS_OK) {
		AfxMessageBox(L"Cannot play the secondary buffer");
		return false;
	}
	return true;
}

bool CDirectSound::Stop(LPDIRECTSOUNDBUFFER buf)
{
	if (!buf) return false;
	if (buf->Stop() != DS_OK) {
		AfxMessageBox(L"Cannot stop our playback");
		return false;
	}
	return true;
}

bool CDirectSound::GenerateSound(LPDIRECTSOUNDBUFFER buf, DWORD offset, DWORD length, int f) {
	WAVEFORMATEX pcmwf;
	if (!buf) return false;
	if (!GetWaveFormat(buf, &pcmwf))
		return false;
	void *lpvPtr1, *lpvPtr2; DWORD dwBytes1, dwBytes2;
	if (!this->LockBuffer(buf, offset, length,
		&lpvPtr1, &dwBytes1, // get pointer 1
		&lpvPtr2, &dwBytes2)) // get pointer 2 (the buffer is circular)
		return false;
	// write a sinus sound now
	DWORD i; short int *t; // points to 16 Bit
	for (i = 0, t = (short int*)lpvPtr1; i<(dwBytes1 + dwBytes2); i += 4, t += 2) {
		if (i == dwBytes1)
			t = (short int*)lpvPtr2;
		*t = *(t + 1) = (short int)(sin(i / (pcmwf.nAvgBytesPerSec / (6.283185*f))) * 30000);
	}
	// unlock memory
	if (!this->UnlockBuffer(buf,
		lpvPtr1, dwBytes1, // pointer 1
		lpvPtr2, dwBytes2)) // pointer 2
		return false;
	return true;
}

bool CDirectSound::LoadPCMSound(LPDIRECTSOUNDBUFFER buf, DWORD offset, DWORD length, FILE *fileptr) {
	WAVEFORMATEX pcmwf;
	BOOL result;
	if (!buf) return false;
	if (!GetWaveFormat(buf, &pcmwf))
		return false;
	void *lpvPtr1, *lpvPtr2; DWORD dwBytes1, dwBytes2;
	if (!this->LockBuffer(buf, offset, length,
		&lpvPtr1, &dwBytes1, // get pointer 1
		&lpvPtr2, &dwBytes2)) // get pointer 2 (the buffer is circular)
		return false;
	// write a sinus sound now
	result = (fread(lpvPtr1, 1, dwBytes1, fileptr) == dwBytes1);

	// unlock memory
	if (!this->UnlockBuffer(buf,
		lpvPtr1, dwBytes1, // pointer 1
		lpvPtr2, dwBytes2)) // pointer 2
		return false;
	return result;
}

bool CDirectSound::SetPlaybackVolume(LPDIRECTSOUNDBUFFER buf, LONG db)
{
	if (!buf) return false;
	if (buf->SetVolume(db) != DS_OK) {
		AfxMessageBox(L"Cannot change volume");
		return false;
	}
	return true;
}

bool CDirectSound::SetBalance(LPDIRECTSOUNDBUFFER buf, LONG db)
{
	if (!buf) return false;
	if (buf->SetPan(db) != DS_OK) {
		AfxMessageBox(L"Cannot change balance");
		return false;
	}
	return true;
}

int CDirectSound::GetPlayPosition(LPDIRECTSOUNDBUFFER buf) {
	DSBCAPS caps;
	caps.dwSize = sizeof(DSBCAPS);
	if (buf->GetCaps(&caps) != DS_OK) {
		AfxMessageBox(L"Cannot get buffer caps");
		return -1;
	}
	DWORD playPos;
	if (buf->GetCurrentPosition(&playPos, 0) != DS_OK) {
		AfxMessageBox(L"Cannot get the secondary buffer positions");
		return -1;
	}
	return ((playPos * 100) / caps.dwBufferBytes);

void CDirectSound::smsFft(float *fftBuffer, long fftFrameSize, long sign) {
	this->fftFrameSize = fftFrameSize;
	float wr, wi, arg, *p1, *p2, temp;
	float tr, ti, ur, ui, *p1r, *p1i, *p2r, *p2i;
	long i, bitm, j, le, le2, k;
	for (i = 2; i < 2 * fftFrameSize - 2; i += 2) {
		for (bitm = 2, j = 0; bitm < 2 * fftFrameSize; bitm <<= 1) {
			if (i & bitm) j++; j <<= 1;
		}
		if (i < j) {
			p1 = fftBuffer + i; p2 = fftBuffer + j;
			temp = *p1; *(p1++) = *p2;
			*(p2++) = temp; temp = *p1; *p1 = *p2; *p2 = temp;
		}
	}
	for (k = 0, le = 2; k < log((double)fftFrameSize) / log(2.); k++) {
		le <<= 1; le2 = le >> 1; ur = 1.0; ui = 0.0;
		arg = M_PI / (le2 >> 1); wr = cos(arg); wi = sign*sin(arg);
		for (j = 0; j < le2; j += 2) {
			p1r = fftBuffer + j; p1i = p1r + 1;
			p2r = p1r + le2; p2i = p2r + 1;
			for (i = j; i < 2 * fftFrameSize; i += le) {
				tr = *p2r * ur - *p2i * ui;
				ti = *p2r * ui + *p2i * ur;
				*p2r = *p1r - tr; *p2i = *p1i - ti;
				*p1r += tr; *p1i += ti;
				p1r += le; p1i += le; p2r += le; p2i += le;
			}
			tr = ur*wr - ui*wi; ui = ur*wi + ui*wr; ur = tr;
		}
	}
}

void CDirectSound::calcParts(int transformLength)
{
	long bin, k;
	cosPart = new float[transformLength];
	sinPart = new float[transformLength];
	double arg, sign = -1.; /* sign = -1 -> FFT, 1 -> inverse FFT */
	for (bin = 0; bin < transformLength / 2; bin++) {
		cosPart[bin] = sinPart[bin] = 0.;
		for (k = 0; k < transformLength; k++) {
			arg = 2.*(float)bin*M_PI*(float)k / (float)transformLength;
			sinPart[bin] += inputData[k] * sign * sin(arg);
			cosPart[bin] += inputData[k] * cos(arg);
		}
	}
}

void CDirectSound::calcMagnitude(int transformLength, int sampleRate)
{
	long bin;
	for (bin = 0; bin < transformLength / 2; bin++) {
		/* frequency */
		frequency[bin] = (float)bin * sampleRate / (float)transformLength;
		/* magnitude */
		magnitude[bin] = 20. * log10(2. *
			sqrt(sinPart[bin] * sinPart[bin] +
				cosPart[bin] * cosPart[bin]) / (float)transformLength);
	}
}

void CDirectSound::DrawFFT(CDC *pdc, CRect r) {
	COLORREF c = RGB(0, 255, 0); CRgn rgn;
	pdc->FillSolidRect(&r, RGB(255, 255, 255));
	pdc->MoveTo(r.TopLeft()); // Rahmen zeichnen
	pdc->LineTo(r.right, r.top);
	pdc->LineTo(r.BottomRight());
	pdc->LineTo(r.left, r.bottom);
	pdc->LineTo(r.TopLeft());
	rgn.CreateRectRgn(r.left + 2, r.top + 2, r.right - 1, r.bottom - 1);
	pdc->SelectObject(&rgn);
	float bandwidth = (r.Width() / (fftFrameSize / 2.f)) - 1;
	float dbstep = (r.Height() - 2) / 40.f; // Schwellwert anwenden
	if (bandwidth < 1.0f) bandwidth = 1.0f; // 1 Pixel Balkenbreite
											// Frequenzanteile zeichnen
	for (int i = 0, x = r.left + 1; i < (fftFrameSize / 2); i++, x += (int)bandwidth + 1)
		pdc->FillSolidRect(x, (int)(r.top + 1 + dbstep*(-magnitude[i])),
		(int)bandwidth, r.Height() - 1, c);
}