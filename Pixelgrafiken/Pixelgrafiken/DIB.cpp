#include "stdafx.h"
#include "DIB.h"

CDIB::CDIB() {
	m_pBMFH = 0;
	m_pBMI = 0;
	m_pBits = 0;
	m_dwLength = 0L; // init by Zero
}

CDIB::~CDIB() {
	if (m_pBMFH != 0)
		delete[] m_pBMFH; // free the memory.
}

int CDIB::DibWidth() {
	if (m_pBMFH)
		return m_pBMI->bmiHeader.biWidth;
	else return 0;
}

int CDIB::DibHeight() {
	if (m_pBMFH)
		return m_pBMI->bmiHeader.biHeight;
	else return 0;
}

bool CDIB::Load(char* fname) {
	if (m_pBMFH != 0) delete[] m_pBMFH; // DIB must be empty
	FILE* fp;
	if ((fp = fopen(fname, "rb")) == NULL) {
		AfxMessageBox(L"Unable to open CDIB-File");
		return false;
	}
	fseek(fp, 0L, SEEK_END); // Länge der Datei ermitteln
	m_dwLength = ftell(fp); rewind(fp);
	if ((m_pBMFH = (BITMAPFILEHEADER*) new char[m_dwLength]) == 0) {
		AfxMessageBox(L"Unable to allocate DIB-Memory"); fclose(fp);
		return false;
	}
	if (fread(m_pBMFH, m_dwLength, 1, fp) != 1) {
		AfxMessageBox(L"Read error");
		delete[] m_pBMFH; m_pBMFH = 0; fclose(fp);
		return false;
	}
	if (m_pBMFH->bfType != 0x4d42) {
		AfxMessageBox(L"Invalid bitmap file");
		delete[] m_pBMFH; m_pBMFH = 0; fclose(fp);
		return false;
	}
	m_pBMI = (BITMAPINFO*)(m_pBMFH + 1);
	m_pBits = (BYTE*)m_pBMFH + m_pBMFH->bfOffBits;
	fclose(fp); return true;
}

bool CDIB::Save(char* fname) {
	if (!m_pBMFH) return false;
	FILE* fp;
	if ((fp = fopen(fname, "wb")) == NULL) {
		AfxMessageBox(L"Unable to open CDIB-File");
		return false;
	}
	if (fwrite(m_pBMFH, m_dwLength, 1, fp) != 1) {
		AfxMessageBox(L"Write error");
		delete[] m_pBMFH; m_pBMFH = 0; fclose(fp);
		return false;
	}
	fclose(fp); return true;
}

// Draw the DIB to a given DC
void CDIB::Draw(CDC* pDC, int x, int y) {
	if (m_pBMFH != 0)
		StretchDIBits(pDC->GetSafeHdc(),
			x, // Destination x
			y, // Destination y
			DibWidth(), // Destination width
			DibHeight(), // Destination height
			0, // Source x
			0, // Source y
			DibWidth(), // Source width
			DibHeight(), // Source height
			m_pBits, // Pointer to bits
			m_pBMI, // BITMAPINFO
			DIB_RGB_COLORS, // Options
			SRCCOPY); // Raster operation code (ROP)
}

void* CDIB::GetPixelAddress(int x, int y) {
	int iWidth;
	if ((x >= DibWidth()) || (y >= DibHeight())) {
		return NULL; // pixel is out of range
	}
	iWidth = StorageWidth(); // Bytes pro Bildzeile
	if (m_pBMI->bmiHeader.biBitCount == 24)
		return m_pBits + (DibHeight() - y - 1) * iWidth +
		x*(m_pBMI->bmiHeader.biBitCount / 8);
	return m_pBits + (DibHeight() - y - 1) * iWidth + x;
}

int CDIB::StorageWidth() {
	return (m_pBMI ? ((m_pBMI->bmiHeader.biWidth*
		(m_pBMI->bmiHeader.biBitCount / 8) + 3) & ~3) : 0);
}

void CDIB::brighten(int value) {
	if ((m_pBMFH == 0) || (m_pBMI->bmiHeader.biBitCount != 24)
		|| (value < 1) || (value > 100))
		return; // do nothing (not supported)
	BYTE *t; int sw = StorageWidth();
	for (int i = 0; i < DibHeight(); i++) {
		t = (BYTE*)GetPixelAddress(0, i);
		for (int j = 0; j < sw; j += 3) {
			*(t + j) += (BYTE)((255 - *(t + j))*(value / 100.f));
			*(t + j + 1) += (BYTE)((255 - *(t + j + 1))*(value / 100.f));
			*(t + j + 2) += (BYTE)((255 - *(t + j + 2))*(value / 100.f));
		}
	}
}

void CDIB::negative() {
	if ((m_pBMFH == 0) || (m_pBMI->bmiHeader.biBitCount != 24))
		return;
	BYTE *t; int sw = StorageWidth();
	for (int i = 0; i < DibHeight(); i++) {
		t = (BYTE*)GetPixelAddress(0, i);
		for (int j = 0; j < sw; j += 3) {
			*(t + j) = 255 - (*(t + j));
			*(t + j + 1) = 255 - (*(t + j + 1));
			*(t + j + 2) = 255 - (*(t + j + 2));
		}
	}
}