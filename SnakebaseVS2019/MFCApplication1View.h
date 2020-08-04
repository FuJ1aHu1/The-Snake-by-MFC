
// MFCApplication1View.h: CMFCApplication1View 类的接口
//

#pragma once
#include "Resource.h"
#include "mmsystem.h"
#include "windows.h"
#include "Dlgrank.h"

class CMFCApplication1View : public CView
{
	CString strFile;//声音文件字符串

	HWND m_hWnd;  //窗口句柄

	DWORD DeviceId;  //设备ID
	MCI_OPEN_PARMS mciopenparms;
	CRect r;
	CArray<CPoint, CPoint&> snake;
	CArray<CPoint, CPoint&> food;
	CBitmap bkbmp;
	CBitmap snakehead;
	CBitmap FoodEach;
	int bk_height;//背景size
	int bk_width;
	int food_height;//单个food size
	int food_width;
	int head_height;//蛇头size
	int head_width;
	int direction;
	int Scoresum;//得分
	CPoint temp;//用来记录吃到东西前最后一个点
	BOOL IsPause;
	int Level;//速度等级
protected: // 仅从序列化创建
	CMFCApplication1View() noexcept;
	DECLARE_DYNCREATE(CMFCApplication1View)

// 特性
public:
	CMFCApplication1Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMFCApplication1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int MakeFood();
	afx_msg void OnStart();
	afx_msg void OnPause();
	afx_msg void OnRestart();
	void playmusic(char *a);
	afx_msg void OnLevelEasy();
	afx_msg void OnLevelNormal();
	afx_msg void OnLevelCarzy();
	afx_msg void OnRank();
};

#ifndef _DEBUG  // MFCApplication1View.cpp 中的调试版本
inline CMFCApplication1Doc* CMFCApplication1View::GetDocument() const
   { return reinterpret_cast<CMFCApplication1Doc*>(m_pDocument); }
#endif

