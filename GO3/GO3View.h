// GO3View.h : CGO3View ��Ľӿ�
//


#pragma once
#include "atltypes.h"
#include "Point_3D.h"


class CGO3View : public CView
{
protected: // �������л�����
	CGO3View();
	DECLARE_DYNCREATE(CGO3View)

// ����
public:
	CGO3Doc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CGO3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
private:
	
	Point_3D* m_LBB;
	CPoint m_2dLbb;
	Point_3D* m_LBT;
	CPoint m_2dLbt;
	Point_3D* m_LFB;
	CPoint m_2dLfb;
	Point_3D* m_LFT;
	CPoint m_2dLft;
	Point_3D* m_RBB;
	CPoint m_2dRbb;
	Point_3D* m_RBT;
	CPoint m_2dRbt;
	Point_3D* m_RFB;
	CPoint m_2dRfb;
	Point_3D* m_RFT;
	CPoint m_2dRft;
public:
	double m_Proj_Matri[4][4];
	void DrawRect(CPoint P1, CPoint P2, CPoint P3, CPoint P4);
	void DrawCubic(void);
	void From3dTo2d(void);
	void ClearScreen(void);
	afx_msg void OnIsometric();
	int Left_Bd;
	int Right_Bd;
	int Bottom_Bd;
	int Top_Bd;
	int Back_Bd;
	int Front_Bd;
	afx_msg void OnPerspective();
	afx_msg void OnCabinet();
private:
	int m_type_transform;
	double m_xStep;
	double m_yStep;
	CPoint m_prevPoint;
	bool m_bLBDown;
	bool m_bRBDown;
	double m_RotateStep;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void On3drotate();
	afx_msg void On3dscale();
	afx_msg void On3dtranslate();
	afx_msg void OnTsty();
	// ͸��ͶӰ��From3dTo2d
	void TSTY_From3dTo2d(Point_3D* point_3, CPoint* point_2, double cx, double cy, double cz);
};

#ifndef _DEBUG  // GO3View.cpp �еĵ��԰汾
inline CGO3Doc* CGO3View::GetDocument() const
   { return reinterpret_cast<CGO3Doc*>(m_pDocument); }
#endif

