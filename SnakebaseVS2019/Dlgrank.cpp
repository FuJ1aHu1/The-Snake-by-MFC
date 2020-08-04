// Dlgrank.cpp: 实现文件
//

#include "pch.h"
#include "MFCApplication1.h"
#include "Dlgrank.h"
#include "afxdialogex.h"


// Dlgrank 对话框

IMPLEMENT_DYNAMIC(Dlgrank, CDialog)

Dlgrank::Dlgrank(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_Dlgrank, pParent)
	, Name(_T(""))
{

}

Dlgrank::~Dlgrank()
{
}

void Dlgrank::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, Name);
}


BEGIN_MESSAGE_MAP(Dlgrank, CDialog)
END_MESSAGE_MAP()


// Dlgrank 消息处理程序
