// Dlg_3dScale.cpp : 实现文件
//

#include "stdafx.h"
#include "GO3.h"
#include "Dlg_3dScale.h"

// Dlg_3dScale 对话框

IMPLEMENT_DYNAMIC(Dlg_3dScale, CDialog)

Dlg_3dScale::Dlg_3dScale(CWnd* pParent /*=NULL*/)
	: CDialog(Dlg_3dScale::IDD, pParent)
	, m_Sx(0)
	, m_Sy(0)
	, m_Sz(0)
{

}

Dlg_3dScale::~Dlg_3dScale()
{
}

void Dlg_3dScale::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDT_3dScale_Sx, (CWnd &)m_Sx);
	//DDX_Control(pDX, IDT_3dScale_Sy, (CWnd &)m_Sy);
	//DDX_Control(pDX, IDT_3dScale_Sz, (CWnd &)m_Sz);

	DDX_Text(pDX,IDT_3dScale_Sx,m_Sx);
	DDV_MinMaxDouble(pDX,m_Sx,0,5);
	DDX_Text(pDX,IDT_3dScale_Sy,m_Sy);
	DDV_MinMaxDouble(pDX,m_Sy,0,5);
	DDX_Text(pDX,IDT_3dScale_Sz,m_Sz);
	DDV_MinMaxDouble(pDX,m_Sz,0,5);
}


BEGIN_MESSAGE_MAP(Dlg_3dScale, CDialog)
END_MESSAGE_MAP()


// Dlg_3dScale 消息处理程序
