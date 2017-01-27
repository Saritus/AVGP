#pragma once
class CDIB {
public:
	CDIB();
	~CDIB();
	virtual bool Load(CString fname); // Load from file
	virtual bool Save(CString fname); // Save to file
	virtual void Draw(CDC* pDC, int x, int y);
	virtual void Draw(CDC* pDC, int x, int y, int width, int height);
	virtual void Draw(CDC* pDC, CRect rect);
	virtual int DibWidth();
	virtual int DibHeight();
	void* GetPixelAddress(int x, int y);
	int StorageWidth();
	void brighten(int value);
	void negative();
	void grey();
	void histogramm(float *h, float zoom);
	void contrast(float alpha);
	void rgb(char ch);
	void slur(int percentage);
	void oil(int radius, int intensityLevels);
	void mosaic();
	void fft();
	void matrix(int* matrix, int matrixsize, int koeff, char offset = 0);
	void flip(char c);
	bool SaveJpeg(CString pszFileName, int quality);
	bool LoadJpeg(CString pszFileName);
protected:
	BITMAPFILEHEADER *m_pBMFH; // Pointer to BITMAPFILEHEADER
	BITMAPINFO* m_pBMI; // Pointer to BITMAPINFO struct
	BYTE* m_pBits; // Pointer to Pixelbits
	DWORD m_dwLength; // length of DIB (including headers)
private:
	double dist(int x1, int y1, int x2, int y2);
};