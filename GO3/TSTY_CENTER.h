#pragma once


// TSTY_CENTER 对话框

class TSTY_CENTER : public CDialog
{
	DECLARE_DYNAMIC(TSTY_CENTER)

public:
	TSTY_CENTER(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~TSTY_CENTER();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int center_x;
	int center_y;
	int center_z;
};
