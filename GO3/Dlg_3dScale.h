#pragma once


// Dlg_3dScale 对话框

class Dlg_3dScale : public CDialog
{
	DECLARE_DYNAMIC(Dlg_3dScale)

public:
	Dlg_3dScale(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Dlg_3dScale();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double m_Sx;
	double m_Sy;
	double m_Sz;
};
