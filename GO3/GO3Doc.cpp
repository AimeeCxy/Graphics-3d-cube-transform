// GO3Doc.cpp : CGO3Doc ���ʵ��
//

#include "stdafx.h"
#include "GO3.h"

#include "GO3Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGO3Doc

IMPLEMENT_DYNCREATE(CGO3Doc, CDocument)

BEGIN_MESSAGE_MAP(CGO3Doc, CDocument)
END_MESSAGE_MAP()


// CGO3Doc ����/����

CGO3Doc::CGO3Doc()
{
	// TODO: �ڴ����һ���Թ������

}

CGO3Doc::~CGO3Doc()
{
}

BOOL CGO3Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CGO3Doc ���л�

void CGO3Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CGO3Doc ���

#ifdef _DEBUG
void CGO3Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGO3Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGO3Doc ����
