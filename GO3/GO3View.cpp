// GO3View.cpp : CGO3View 类的实现
//

#include "stdafx.h"
#include "GO3.h"

#include "GO3Doc.h"
#include "GO3View.h"
#include "Point_3D.h"
#include "math.h"
#include "Dlg_3dScale.h"
#include "TSTY_CENTER.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGO3View

IMPLEMENT_DYNCREATE(CGO3View, CView)

BEGIN_MESSAGE_MAP(CGO3View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(IDP_ISOMETRIC, &CGO3View::OnIsometric)
	ON_COMMAND(IDP_PERSPECTIVE, &CGO3View::OnPerspective)
	ON_COMMAND(IDP_CABINET, &CGO3View::OnCabinet)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_COMMAND(IDP_3DROTATE, &CGO3View::On3drotate)
	ON_COMMAND(IDP_3DSCALE, &CGO3View::On3dscale)
	ON_COMMAND(IDP_3DTRANSLATE, &CGO3View::On3dtranslate)
	ON_COMMAND(IDP_TSTY, &CGO3View::OnTsty)
END_MESSAGE_MAP()

// CGO3View 构造/析构

CGO3View::CGO3View()
:m_2dLbb(0)
, m_2dLbt(0)
, m_2dLfb(0)
, m_2dLft(0)
, m_2dRbb(0)
, m_2dRbt(0)
, m_2dRfb(0)
, m_2dRft(0)
, Left_Bd(0)
, Right_Bd(0)
, Bottom_Bd(0)
, Top_Bd(0)
, Back_Bd(0)
, Front_Bd(0)
, m_LBB(NULL)
, m_LBT(NULL)
, m_LFT(NULL)
, m_LFB(NULL)
, m_RBB(NULL)
, m_RBT(NULL)
, m_RFB(NULL)
, m_RFT(NULL)
, m_xStep(0)
, m_yStep(0)
, m_prevPoint(0)
, m_bLBDown(false)
, m_bRBDown(false)
, m_RotateStep(0)
{
	// TODO: 在此处添加构造代码
	Left_Bd = 100;
	Right_Bd = 200;
	Bottom_Bd = 100;
	Top_Bd = 200;
	Back_Bd = 100;
	Front_Bd = 200;

	m_LBB = new Point_3D(Left_Bd,Back_Bd,Bottom_Bd);
	m_LBT = new Point_3D(Left_Bd,Back_Bd,Top_Bd);
	m_LFB = new Point_3D(Left_Bd,Front_Bd,Bottom_Bd);
	m_LFT = new Point_3D(Left_Bd,Front_Bd,Top_Bd);

	m_RBB = new Point_3D(Right_Bd,Back_Bd,Bottom_Bd);
	m_RBT = new Point_3D(Right_Bd,Back_Bd,Top_Bd);
	m_RFB = new Point_3D(Right_Bd,Front_Bd,Bottom_Bd);
	m_RFT = new Point_3D(Right_Bd,Front_Bd,Top_Bd);
	
	m_type_transform = 0;
	m_xStep = 1.5;
	m_yStep = 1.5;
	m_prevPoint = 0;
	m_bLBDown = false;
	m_bRBDown = false;
	m_RotateStep = 0.05;
}

CGO3View::~CGO3View()
{
}

BOOL CGO3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CGO3View 绘制

void CGO3View::OnDraw(CDC* /*pDC*/)
{
	CGO3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CGO3View 打印

BOOL CGO3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CGO3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CGO3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CGO3View 诊断

#ifdef _DEBUG
void CGO3View::AssertValid() const
{
	CView::AssertValid();
}

void CGO3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGO3Doc* CGO3View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGO3Doc)));
	return (CGO3Doc*)m_pDocument;
}
#endif //_DEBUG


// CGO3View 消息处理程序

void CGO3View::DrawRect(CPoint P1, CPoint P2, CPoint P3, CPoint P4)
{
	CClientDC dc(this);
	dc.MoveTo(P1);
	dc.LineTo(P2);
	dc.LineTo(P3);
	dc.LineTo(P4);
	dc.LineTo(P1);
}

void CGO3View::DrawCubic(void)
{
	DrawRect(m_2dLbb,m_2dLbt,m_2dLft,m_2dLfb);//左面

	DrawRect(m_2dRbb,m_2dRbt,m_2dRft,m_2dRfb);//右面
	
	DrawRect(m_2dLbb,m_2dLbt,m_2dRbt,m_2dRbb);//后面
	
	DrawRect(m_2dLfb,m_2dLft,m_2dRft,m_2dRfb);//前面
	
	DrawRect(m_2dLbb,m_2dLfb,m_2dRfb,m_2dRbb);//下面
	
	DrawRect(m_2dLbt,m_2dLft,m_2dRft,m_2dRbt);//上面
}

void CGO3View::From3dTo2d(void)
{
	m_2dLbb.x = m_LBB->x * m_Proj_Matri[0][0] + m_LBB->y *  m_Proj_Matri[0][1] + m_LBB->z * m_Proj_Matri[0][2] + m_Proj_Matri[0][3] ; 
	m_2dLbb.y = m_LBB->x * m_Proj_Matri[1][0] + m_LBB->y *  m_Proj_Matri[1][1] + m_LBB->z * m_Proj_Matri[1][2] + m_Proj_Matri[1][3] ; 

	m_2dLbt.x = m_LBT->x * m_Proj_Matri[0][0] + m_LBT->y *  m_Proj_Matri[0][1] + m_LBT->z * m_Proj_Matri[0][2] + m_Proj_Matri[0][3] ; 
	m_2dLbt.y = m_LBT->x * m_Proj_Matri[1][0] + m_LBT->y *  m_Proj_Matri[1][1] + m_LBT->z * m_Proj_Matri[1][2] + m_Proj_Matri[1][3] ; 

	m_2dLfb.x = m_LFB->x * m_Proj_Matri[0][0] + m_LFB->y *  m_Proj_Matri[0][1] + m_LFB->z * m_Proj_Matri[0][2] + m_Proj_Matri[0][3] ; 
	m_2dLfb.y = m_LFB->x * m_Proj_Matri[1][0] + m_LFB->y *  m_Proj_Matri[1][1] + m_LFB->z * m_Proj_Matri[1][2] + m_Proj_Matri[1][3] ; 

	m_2dLft.x = m_LFT->x * m_Proj_Matri[0][0] + m_LFT->y *  m_Proj_Matri[0][1] + m_LFT->z * m_Proj_Matri[0][2] + m_Proj_Matri[0][3] ; 
	m_2dLft.y = m_LFT->x * m_Proj_Matri[1][0] + m_LFT->y *  m_Proj_Matri[1][1] + m_LFT->z * m_Proj_Matri[1][2] + m_Proj_Matri[1][3] ; 

	m_2dRbb.x = m_RBB->x * m_Proj_Matri[0][0] + m_RBB->y *  m_Proj_Matri[0][1] + m_RBB->z * m_Proj_Matri[0][2] + m_Proj_Matri[0][3] ; 
	m_2dRbb.y = m_RBB->x * m_Proj_Matri[1][0] + m_RBB->y *  m_Proj_Matri[1][1] + m_RBB->z * m_Proj_Matri[1][2] + m_Proj_Matri[1][3] ; 

	m_2dRbt.x = m_RBT->x * m_Proj_Matri[0][0] + m_RBT->y *  m_Proj_Matri[0][1] + m_RBT->z * m_Proj_Matri[0][2] + m_Proj_Matri[0][3] ; 
	m_2dRbt.y = m_RBT->x * m_Proj_Matri[1][0] + m_RBT->y *  m_Proj_Matri[1][1] + m_RBT->z * m_Proj_Matri[1][2] + m_Proj_Matri[1][3] ; 

	m_2dRfb.x = m_RFB->x * m_Proj_Matri[0][0] + m_RFB->y *  m_Proj_Matri[0][1] + m_RFB->z * m_Proj_Matri[0][2] + m_Proj_Matri[0][3] ; 
	m_2dRfb.y = m_RFB->x * m_Proj_Matri[1][0] + m_RFB->y *  m_Proj_Matri[1][1] + m_RFB->z * m_Proj_Matri[1][2] + m_Proj_Matri[1][3] ; 

	m_2dRft.x = m_RFT->x * m_Proj_Matri[0][0] + m_RFT->y *  m_Proj_Matri[0][1] + m_RFT->z * m_Proj_Matri[0][2] + m_Proj_Matri[0][3] ; 
	m_2dRft.y = m_RFT->x * m_Proj_Matri[1][0] + m_RFT->y *  m_Proj_Matri[1][1] + m_RFT->z * m_Proj_Matri[1][2] + m_Proj_Matri[1][3] ; 
	
	/*if(m_type_transform == 1)
	{
		double L = 2/1.7320508075;
		double Alpha = 20;
		Alpha *= 3.1415926/180;
		double c = cos(Alpha);
		double s = sin(Alpha);

		m_2dLbb.x += L*c/m_2dLbb.x;
		m_2dLbb.y += L*s/m_2dLbb.y;

		m_2dLbt.x += L*c/m_2dLbt.x;
		m_2dLbt.y += L*s/m_2dLbt.y;

		m_2dLfb.x += L*c/m_2dLfb.x;
		m_2dLfb.y += L*s/m_2dLfb.y;

		m_2dLft.x += L*c/m_2dLft.x;
		m_2dLft.y += L*s/m_2dLft.y;

		m_2dRbb.x += L*c/m_2dRbb.x;
		m_2dRbb.y += L*s/m_2dRbb.y;

		m_2dRbt.x += L*c/m_2dRbt.x;
		m_2dRbt.y += L*s/m_2dRbt.y;

		m_2dRfb.x += L*c/m_2dRfb.x;
		m_2dRfb.y += L*s/m_2dRfb.y;

		m_2dRft.x += L*c/m_2dRft.x;
		m_2dRft.y += L*s/m_2dRft.y;
	}*/
}

void CGO3View::ClearScreen(void)
{
	CClientDC dc(this);
	CRect window;
	GetClientRect(window);
	dc.SelectStockObject(WHITE_PEN);
	dc.SelectStockObject(WHITE_BRUSH);
	dc.Rectangle(window);
}

void CGO3View::OnIsometric()
{
	// TODO: 在此添加命令处理程序代码

	/*
	  CMenu menu;
      menu.LoadMenuW(IDR_MENU1);//加载资源菜单栏，IDR_MENU1为资源视图里菜单的ID
      this->SetMenu(&menu);     //这个函数将当前菜单设为指定的菜单。
      //它使窗口被重画以反映菜单的变化。参数必须是指针型的。
      menu.Detach();// 窗口销毁时，局部变量menu同时销毁 
	*/

	ClearScreen();
	m_Proj_Matri[0][0] = 0.70710678118655;m_Proj_Matri[0][1] = 0.70710678118655;m_Proj_Matri[0][2] = 0;m_Proj_Matri[0][3] = 0;
	m_Proj_Matri[1][0] = -0.408244829046386;m_Proj_Matri[1][1] = 0.408244829046386;m_Proj_Matri[1][2] = 0.81649658092773;m_Proj_Matri[1][3] = 0;
	m_Proj_Matri[2][0] = 0;m_Proj_Matri[2][1] = 0;m_Proj_Matri[2][2] = 0;m_Proj_Matri[2][3] = 0;
	m_Proj_Matri[3][0] = 0;m_Proj_Matri[3][1] = 0;m_Proj_Matri[3][2] = 0;m_Proj_Matri[3][3] = 1;
	From3dTo2d();
	DrawCubic();
}

void CGO3View::OnPerspective()
{
	// TODO: 在此添加命令处理程序代码
	ClearScreen();
	double x0 = 2;
	double y0 = 1;
	double d = 1;
	m_Proj_Matri[0][0]=1;m_Proj_Matri[0][1]=0;m_Proj_Matri[0][2]=x0/d;m_Proj_Matri[0][3]=0;
	m_Proj_Matri[1][0]=0;m_Proj_Matri[1][1]=1;m_Proj_Matri[1][2]=y0/d;m_Proj_Matri[1][3]=0;
    m_Proj_Matri[2][0]=0;m_Proj_Matri[2][1]=0;m_Proj_Matri[2][2]=0;m_Proj_Matri[2][3]=0;
	m_Proj_Matri[3][0]=0;m_Proj_Matri[3][1]=0;m_Proj_Matri[3][2]=1.0/d;m_Proj_Matri[3][3]=0;
	From3dTo2d();
	DrawCubic();
}

void CGO3View::OnCabinet()
{
	// TODO: 斜二侧投影
	ClearScreen();
	double L = 2/1.7320508075;
	double Alpha = 20;
	double c = cos(Alpha);
	double s = sin(Alpha);
	m_Proj_Matri[0][0]=1;m_Proj_Matri[0][1]=0;m_Proj_Matri[0][2]=L * c;m_Proj_Matri[0][3]=0;
	m_Proj_Matri[1][0]=0;m_Proj_Matri[1][1]=1;m_Proj_Matri[1][2]=L * s;m_Proj_Matri[1][3]=0;
    m_Proj_Matri[2][0]=0;m_Proj_Matri[2][1]=0;m_Proj_Matri[2][2]=0;m_Proj_Matri[2][3]=0;
	m_Proj_Matri[3][0]=0;m_Proj_Matri[3][1]=0;m_Proj_Matri[3][2]=0;m_Proj_Matri[3][3]=1;
	From3dTo2d();
	DrawCubic();
}

void CGO3View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bLBDown = true;
	m_prevPoint = point;

	CView::OnLButtonDown(nFlags, point);
}

void CGO3View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bLBDown = false;
	m_prevPoint = point;

	CView::OnLButtonUp(nFlags, point);
}

void CGO3View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int delta = 0;
	double c;
	double s;
	double x;
	double y;
	double z;
	switch(m_type_transform)
	{
	case 1:
		if(m_bLBDown)
		{
			ClearScreen();
			delta = point.x - m_prevPoint.x;
			m_prevPoint = point;
			m_LBB->x += delta * (int)m_xStep,0;
			m_LBT->x += delta * (int)m_xStep,0;
			m_LFB->x += delta * (int)m_xStep,0;
			m_LFT->x += delta * (int)m_xStep,0;
			m_RBB->x += delta * (int)m_xStep,0;
			m_RBT->x += delta * (int)m_xStep,0;
			m_RFB->x += delta * (int)m_xStep,0;
			m_RFT->x += delta * (int)m_xStep,0;
			From3dTo2d();
			
			TSTY_From3dTo2d(m_LBB,&m_2dLbb,80,50,90);
			TSTY_From3dTo2d(m_LBT,&m_2dLbt,80,50,90);
			TSTY_From3dTo2d(m_LFB,&m_2dLfb,80,50,90);
			TSTY_From3dTo2d(m_LFT,&m_2dLft,80,50,90);
			TSTY_From3dTo2d(m_RBB,&m_2dRbb,80,50,90);
			TSTY_From3dTo2d(m_RBT,&m_2dRbt,80,50,90);
			TSTY_From3dTo2d(m_RFB,&m_2dRfb,80,50,90);
			TSTY_From3dTo2d(m_RFT,&m_2dRft,80,50,90);

			DrawCubic();
		}
		if(m_bRBDown)
		{
			ClearScreen();
			delta = point.y - m_prevPoint.y;
			m_prevPoint = point;
			m_LBB->y += delta * (int)m_yStep,0;
			m_LBT->y += delta * (int)m_yStep,0;
			m_LFB->y += delta * (int)m_yStep,0;
			m_LFT->y += delta * (int)m_yStep,0;
			m_RBB->y += delta * (int)m_yStep,0;
			m_RBT->y += delta * (int)m_yStep,0;
			m_RFB->y += delta * (int)m_yStep,0;
			m_RFT->y += delta * (int)m_yStep,0;
			From3dTo2d();
			TSTY_From3dTo2d(m_LBB,&m_2dLbb,80,50,90);
			TSTY_From3dTo2d(m_LBT,&m_2dLbt,80,50,90);
			TSTY_From3dTo2d(m_LFB,&m_2dLfb,80,50,90);
			TSTY_From3dTo2d(m_LFT,&m_2dLft,80,50,90);
			TSTY_From3dTo2d(m_RBB,&m_2dRbb,80,50,90);
			TSTY_From3dTo2d(m_RBT,&m_2dRbt,80,50,90);
			TSTY_From3dTo2d(m_RFB,&m_2dRfb,80,50,90);
			TSTY_From3dTo2d(m_RFT,&m_2dRft,80,50,90);
			DrawCubic();
		}
		break;
	case 0:
		break;
	case 2:
		break;
	case 3:
		if(m_bLBDown&&(!m_bRBDown))//绕z轴旋转
		{
			ClearScreen();
			delta = point.y - m_prevPoint.y;
			m_prevPoint = point;
			c = cos(delta * m_RotateStep);
			s = sin(delta * m_RotateStep);
			x = m_LBB->x;y = m_LBB->y;
			m_LBB->x = x * c - y * s;m_LBB->y = x * s + y * c;
			
			x = m_LBT->x;y = m_LBT->y;
			m_LBT->x = x * c - y * s;m_LBT->y = x * s + y * c;
			
			x = m_LFB->x;y = m_LFB->y;
			m_LFB->x = x * c - y * s;m_LFB->y = x * s + y * c;
			
			x = m_LFT->x;y = m_LFT->y;
			m_LFT->x = x * c - y * s;m_LFT->y = x * s + y * c;

			x = m_RBB->x;y = m_RBB->y;
			m_RBB->x = x * c - y * s;m_RBB->y = x * s + y * c;
			
			x = m_RBT->x;y = m_RBT->y;
			m_RBT->x = x * c - y * s;m_RBT->y = x * s + y * c;
			
			x = m_RFB->x;y = m_RFB->y;
			m_RFB->x = x * c - y * s;m_RFB->y = x * s + y * c;
			
			x = m_RFT->x;y = m_RFT->y;
			m_RFT->x = x * c - y * s;m_RFT->y = x * s + y * c;
			double L = 2/1.7320508074;
			double Alpha = 20;
			Alpha *= 3.1415926/180;
			double c = cos(Alpha);
			double s = sin(Alpha);
			m_Proj_Matri[0][0]=1;m_Proj_Matri[0][1]=0;m_Proj_Matri[0][2]=L * c;m_Proj_Matri[0][3]=0;
			m_Proj_Matri[1][0]=0;m_Proj_Matri[1][1]=1;m_Proj_Matri[1][2]=L * s;m_Proj_Matri[1][3]=0;
			m_Proj_Matri[2][0]=0;m_Proj_Matri[2][1]=0;m_Proj_Matri[2][2]=0;m_Proj_Matri[2][3]=0;
			m_Proj_Matri[3][0]=0;m_Proj_Matri[3][1]=0;m_Proj_Matri[3][2]=0;m_Proj_Matri[3][3]=1;
			From3dTo2d();
			DrawCubic();
		}
		if(m_bRBDown&&(!m_bLBDown))//绕y轴旋转
		{
			ClearScreen();
		
			delta = point.y - m_prevPoint.y;
			m_prevPoint = point;
			c = cos(delta * m_RotateStep);
			s = sin(delta * m_RotateStep);
			x = m_LBB->x;z = m_LBB->z;
			m_LBB->x = x * c + z * s;m_LBB->z = - x * s + z * c;
			
			x = m_LBT->x;z = m_LBT->z;
			m_LBT->x = x * c + z * s;m_LBT->z = - x * s + z * c;
			
			x = m_LFB->x;z = m_LFB->z;
			m_LFB->x = x * c + z * s;m_LFB->z = - x * s + z * c;
			
			x = m_LFT->x;z = m_LFT->z;
			m_LFT->x = x * c + z * s;m_LFT->z = - x * s + z * c;

			x = m_RBB->x;z = m_RBB->z;
			m_RBB->x = x * c + z * s;m_RBB->z = - x * s + z * c;
			
			x = m_RBT->x;z = m_RBT->z;
			m_RBT->x = x * c + z * s;m_RBT->z = - x * s + z * c;
			
			x = m_RFB->x;z = m_RFB->z;
			m_RFB->x = x * c + z * s;m_RFB->z = - x * s + z * c;
			
			x = m_RFT->x;z = m_RFT->z;
			m_RFT->x = x * c + z * s;m_RFT->z = - x * s + z * c;

			double L = 2/1.7320508074;
			double Alpha = 20;
			Alpha *= 3.1415926/180;
			double c = cos(Alpha);
			double s = sin(Alpha);
			m_Proj_Matri[0][0]=1;m_Proj_Matri[0][1]=0;m_Proj_Matri[0][2]=L * c;m_Proj_Matri[0][3]=0;
			m_Proj_Matri[1][0]=0;m_Proj_Matri[1][1]=1;m_Proj_Matri[1][2]=L * s;m_Proj_Matri[1][3]=0;
			m_Proj_Matri[2][0]=0;m_Proj_Matri[2][1]=0;m_Proj_Matri[2][2]=0;m_Proj_Matri[2][3]=0;
			m_Proj_Matri[3][0]=0;m_Proj_Matri[3][1]=0;m_Proj_Matri[3][2]=0;m_Proj_Matri[3][3]=1;
			From3dTo2d();
			DrawCubic();
		}
		if(m_bLBDown && m_bLBDown)//绕x轴旋转
		{
			ClearScreen();

			delta = point.y - m_prevPoint.y;
			m_prevPoint = point;
			c = cos(delta * m_RotateStep);
			s = sin(delta * m_RotateStep);
			y = m_LBB->y;z = m_LBB->z;
			m_LBB->y = y * c - z * s;m_LBB->z = y * s + z * c;
			
			y = m_LBT->y;z = m_LBT->z;
			m_LBT->y = y * c - z * s;m_LBT->z = y * s + z * c;
			
			y = m_LFB->y;z = m_LFB->z;
			m_LFB->y = y * c - z * s;m_LFB->z = y * s + z * c;
			
			y = m_LFT->y;z = m_LFT->z;
			m_LFT->y = y * c - z * s;m_LFT->z = y * s + z * c;

			y = m_RBB->y;z = m_RBB->z;
			m_RBB->y = y * c - z * s;m_RBB->z = y * s + z * c;
			
			y = m_RBT->y;z = m_RBT->z;
			m_RBT->y = y * c - z * s;m_RBT->z = y * s + z * c;
			
			y = m_RFB->y;z = m_RFB->z;
			m_RFB->y = y * c - z * s;m_RFB->z = y * s + z * c;
			
			y = m_RFT->y;z = m_RFT->z;
			m_RFT->y = y * c - z * s;m_RFT->z = y * s + z * c;

			
			double L = 2/1.7320508074;
			double Alpha = 20;
			Alpha *= 3.1415926/180;
			double c = cos(Alpha);
			double s = sin(Alpha);
			m_Proj_Matri[0][0]=1;m_Proj_Matri[0][1]=0;m_Proj_Matri[0][2]=L * c;m_Proj_Matri[0][3]=0;
			m_Proj_Matri[1][0]=0;m_Proj_Matri[1][1]=1;m_Proj_Matri[1][2]=L * s;m_Proj_Matri[1][3]=0;
			m_Proj_Matri[2][0]=0;m_Proj_Matri[2][1]=0;m_Proj_Matri[2][2]=0;m_Proj_Matri[2][3]=0;
			m_Proj_Matri[3][0]=0;m_Proj_Matri[3][1]=0;m_Proj_Matri[3][2]=0;m_Proj_Matri[3][3]=1;
			From3dTo2d();
			DrawCubic();
		}
		break;
	}

	CView::OnMouseMove(nFlags, point);
}

void CGO3View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bRBDown = true;
	m_prevPoint = point;

	CView::OnRButtonDown(nFlags, point);
}

void CGO3View::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bRBDown = false;
	m_prevPoint = point;

	CView::OnRButtonUp(nFlags, point);
}

void CGO3View::On3drotate()
{
	// TODO: 旋转变换
	ClearScreen();
	m_type_transform = 3;
	double L = 2/1.7320508074;
	double Alpha = 20;
	Alpha *= 3.1415926/180;
	double c = cos(Alpha);
	double s = sin(Alpha);
	m_Proj_Matri[0][0]=1;m_Proj_Matri[0][1]=0;m_Proj_Matri[0][2]=L * c;m_Proj_Matri[0][3]=0;
	m_Proj_Matri[1][0]=0;m_Proj_Matri[1][1]=1;m_Proj_Matri[1][2]=L * s;m_Proj_Matri[1][3]=0;
    m_Proj_Matri[2][0]=0;m_Proj_Matri[2][1]=0;m_Proj_Matri[2][2]=0;m_Proj_Matri[2][3]=0;
	m_Proj_Matri[3][0]=0;m_Proj_Matri[3][1]=0;m_Proj_Matri[3][2]=0;m_Proj_Matri[3][3]=1;
	From3dTo2d();
	DrawCubic();
}

void CGO3View::On3dscale()
{
	// TODO: 比例变换
	ClearScreen();
	m_type_transform = 2;
	double Sx;
	double Sy;
	double Sz;
	Dlg_3dScale dlg = new Dlg_3dScale();
	/*dlg.DoModal();
	Sx = dlg.m_Sx;
	Sy = dlg.m_Sy;
	Sz = dlg.m_Sz;*/
	dlg.DoModal();
	if(dlg.m_Sx!=0 && dlg.m_Sy!=0 && dlg.m_Sz!=0)
	{
		Sx = dlg.m_Sx;
		Sy = dlg.m_Sy;
		Sz = dlg.m_Sz;
	}
	else
	{
		MessageBox(_T("没有正确输入比例因子，退出"),_T("警告"), MB_OK | MB_ICONHAND);
		exit(0);
	}
	m_LBB->x *= Sx;m_LBB->y *= Sy;m_LBB->z *= Sz;
	m_LBT->x *= Sx;m_LBT->y *= Sy;m_LBT->z *= Sz;
	m_LFB->x *= Sx;m_LFB->y *= Sy;m_LFB->z *= Sz;
	m_LFT->x *= Sx;m_LFT->y *= Sy;m_LFT->z *= Sz;

	m_RBB->x *= Sx;m_RBB->y *= Sy;m_RBB->z *= Sz;
	m_RBT->x *= Sx;m_RBT->y *= Sy;m_RBT->z *= Sz;
	m_RFB->x *= Sx;m_RFB->y *= Sy;m_RFB->z *= Sz;
	m_RFT->x *= Sx;m_RFT->y *= Sy;m_RFT->z *= Sz;
	double L = 2/1.7320508074;
	double Alpha = 20;
	Alpha *= 3.1415926/180;
	double c = cos(Alpha);
	double s = sin(Alpha);
	m_Proj_Matri[0][0]=1;m_Proj_Matri[0][1]=0;m_Proj_Matri[0][2]=L * c;m_Proj_Matri[0][3]=0;
	m_Proj_Matri[1][0]=0;m_Proj_Matri[1][1]=1;m_Proj_Matri[1][2]=L * s;m_Proj_Matri[1][3]=0;
    m_Proj_Matri[2][0]=0;m_Proj_Matri[2][1]=0;m_Proj_Matri[2][2]=0;m_Proj_Matri[2][3]=0;
	m_Proj_Matri[3][0]=0;m_Proj_Matri[3][1]=0;m_Proj_Matri[3][2]=0;m_Proj_Matri[3][3]=1;
	From3dTo2d();
	DrawCubic();
}

void CGO3View::On3dtranslate()
{
	// TODO: 平移变换
	ClearScreen();
	m_type_transform = 1;
	double L = 2/1.7320508075;
	double Alpha = 20;
	Alpha *= 3.1415926/180;
	double c = cos(Alpha);
	double s = sin(Alpha);
	m_Proj_Matri[0][0]=1;m_Proj_Matri[0][1]=0;m_Proj_Matri[0][2]=L * c;m_Proj_Matri[0][3]=0;
	m_Proj_Matri[1][0]=0;m_Proj_Matri[1][1]=1;m_Proj_Matri[1][2]=L * s;m_Proj_Matri[1][3]=0;
    m_Proj_Matri[2][0]=0;m_Proj_Matri[2][1]=0;m_Proj_Matri[2][2]=0;m_Proj_Matri[2][3]=0;
	m_Proj_Matri[3][0]=0;m_Proj_Matri[3][1]=0;m_Proj_Matri[3][2]=0;m_Proj_Matri[3][3]=1;
	From3dTo2d();
	
	TSTY_From3dTo2d(m_LBB,&m_2dLbb,80,50,90);
	TSTY_From3dTo2d(m_LBT,&m_2dLbt,80,50,90);
	TSTY_From3dTo2d(m_LFB,&m_2dLfb,80,50,90);
	TSTY_From3dTo2d(m_LFT,&m_2dLft,80,50,90);
	TSTY_From3dTo2d(m_RBB,&m_2dRbb,80,50,90);
	TSTY_From3dTo2d(m_RBT,&m_2dRbt,80,50,90);
	TSTY_From3dTo2d(m_RFB,&m_2dRfb,80,50,90);
	TSTY_From3dTo2d(m_RFT,&m_2dRft,80,50,90);
	DrawCubic();
}

void CGO3View::OnTsty()
{
	// TODO: 透视投影
	ClearScreen();
	double Cx;
	double Cy;
	double Cz;
	TSTY_CENTER cen = new TSTY_CENTER();
	cen.DoModal();
	Cx = cen.center_x;
	Cy = cen.center_y;
	Cz = cen.center_z;

	/*m_Proj_Matri[0][0] = 1;m_Proj_Matri[0][1] = 0;m_Proj_Matri[0][2] = -(Cx / Cz);m_Proj_Matri[0][3] = 0;
	m_Proj_Matri[1][0] = 0;m_Proj_Matri[1][1] = 1;m_Proj_Matri[1][2] = -(Cy / Cz);m_Proj_Matri[1][3] = 0;
	m_Proj_Matri[2][0] = 0;m_Proj_Matri[2][1] = 0;m_Proj_Matri[2][2] = 0;m_Proj_Matri[2][3] = 0;
	m_Proj_Matri[3][0] = 0;m_Proj_Matri[3][1] = 0;m_Proj_Matri[3][2] = -(1 / Cz);m_Proj_Matri[3][3] = 1;
	From3dTo2d();*/

	TSTY_From3dTo2d(m_LBB,&m_2dLbb,Cx,Cy,Cz);
	TSTY_From3dTo2d(m_LBT,&m_2dLbt,Cx,Cy,Cz);
	TSTY_From3dTo2d(m_LFB,&m_2dLfb,Cx,Cy,Cz);
	TSTY_From3dTo2d(m_LFT,&m_2dLft,Cx,Cy,Cz);
	TSTY_From3dTo2d(m_RBB,&m_2dRbb,Cx,Cy,Cz);
	TSTY_From3dTo2d(m_RBT,&m_2dRbt,Cx,Cy,Cz);
	TSTY_From3dTo2d(m_RFB,&m_2dRfb,Cx,Cy,Cz);
	TSTY_From3dTo2d(m_RFT,&m_2dRft,Cx,Cy,Cz);
	
	DrawCubic();
}



// 透视投影的From3dTo2d
void CGO3View::TSTY_From3dTo2d(Point_3D* point_3, CPoint* point_2, double cx, double cy, double cz)
{
	point_2->x = (point_3->x - cx) * cz /(point_3->z +cz) + cx;

	point_2->y = (point_3->y - cy) * cz /(point_3->z +cz) + cy;
}
