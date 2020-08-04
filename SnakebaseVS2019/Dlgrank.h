#pragma once


// Dlgrank 对话框

class Dlgrank : public CDialog
{
	DECLARE_DYNAMIC(Dlgrank)

public:
	Dlgrank(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Dlgrank();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Dlgrank };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString Name;
};
