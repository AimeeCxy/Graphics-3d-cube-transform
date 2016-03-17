// GO3Doc.cpp : CGO3Doc 类的实现
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


// CGO3Doc 构造/析构

CGO3Doc::CGO3Doc()
{
	// TODO: 在此添加一次性构造代码

}

CGO3Doc::~CGO3Doc()
{
}

BOOL CGO3Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CGO3Doc 序列化

void CGO3Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CGO3Doc 诊断

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


// CGO3Doc 命令
