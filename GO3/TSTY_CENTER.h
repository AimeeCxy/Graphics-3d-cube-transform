#pragma once


// TSTY_CENTER �Ի���

class TSTY_CENTER : public CDialog
{
	DECLARE_DYNAMIC(TSTY_CENTER)

public:
	TSTY_CENTER(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~TSTY_CENTER();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int center_x;
	int center_y;
	int center_z;
};
