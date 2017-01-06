#pragma once
class CDIB {
public:
	CDIB();
	~CDIB();
	virtual bool Load(char* fname); // Load from file
	virtual bool Save(char* fname); // Save to file
	virtual void Draw(CDC* pDC, int x, int y);
	virtual int DibWidth();
	virtual int DibHeight();
	void* GetPixelAddress(int x, int y);
	int StorageWidth();
	void brighten(int value);
	void negative();
	void grey();
	void histogramm(float *h, float zoom);
protected:
	BITMAPFILEHEADER *m_pBMFH; // Pointer to BITMAPFILEHEADER
	BITMAPINFO* m_pBMI; // Pointer to BITMAPINFO struct
	BYTE* m_pBits; // Pointer to Pixelbits
	DWORD m_dwLength; // length of DIB (including headers)
};