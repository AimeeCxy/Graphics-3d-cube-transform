// TSTY_CENTER.cpp : 实现文件
//

#include "stdafx.h"
#include "GO3.h"
#include "TSTY_CENTER.h"


// TSTY_CENTER 对话框

IMPLEMENT_DYNAMIC(TSTY_CENTER, CDialog)

TSTY_CENTER::TSTY_CENTER(CWnd* pParent /*=NULL*/)
	: CDialog(TSTY_CENTER::IDD, pParent)
	, center_x(0)
	, center_y(0)
	, center_z(0)
{

}

TSTY_CENTER::~TSTY_CENTER()
{
}

void TSTY_CENTER::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CENTER_X, center_x);
	DDX_Text(pDX, IDC_CENTER_Y, center_y);
	DDX_Text(pDX, IDC_CENTER_Z, center_z);
}


BEGIN_MESSAGE_MAP(TSTY_CENTER, CDialog)
END_MESSAGE_MAP()


// TSTY_CENTER 消息处理程序
