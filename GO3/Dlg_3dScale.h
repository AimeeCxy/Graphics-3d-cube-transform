#pragma once


// Dlg_3dScale �Ի���

class Dlg_3dScale : public CDialog
{
	DECLARE_DYNAMIC(Dlg_3dScale)

public:
	Dlg_3dScale(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Dlg_3dScale();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	double m_Sx;
	double m_Sy;
	double m_Sz;
};
