// GO3Doc.h : CGO3Doc ��Ľӿ�
//


#pragma once


class CGO3Doc : public CDocument
{
protected: // �������л�����
	CGO3Doc();
	DECLARE_DYNCREATE(CGO3Doc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CGO3Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


