
// MFCApplication1View.cpp: CMFCApplication1View 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#pragma comment(lib, "winmm")
#ifndef SHARED_HANDLERS
#include "MFCApplication1.h"
#endif

#include "MFCApplication1Doc.h"
#include "MFCApplication1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication1View

IMPLEMENT_DYNCREATE(CMFCApplication1View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication1View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_COMMAND(ID_START, &CMFCApplication1View::OnStart)
	ON_COMMAND(ID_PAUSE, &CMFCApplication1View::OnPause)
	ON_COMMAND(ID_RESTART, &CMFCApplication1View::OnRestart)
	ON_COMMAND(ID_LEVEL_EASY, &CMFCApplication1View::OnLevelEasy)
	ON_COMMAND(ID_LEVEL_NORMAL, &CMFCApplication1View::OnLevelNormal)
	ON_COMMAND(ID_LEVEL_CARZY, &CMFCApplication1View::OnLevelCarzy)
	ON_COMMAND(ID_RANK, &CMFCApplication1View::OnRank)
END_MESSAGE_MAP()

// CMFCApplication1View 构造/析构

CMFCApplication1View::CMFCApplication1View() noexcept
{
	Level = 300;
	IsPause = FALSE;
	// TODO: 在此处添加构造代码
	direction = VK_RIGHT;
	snake.SetSize(1);
	snake.SetAt(0, CPoint(80, 20));
	CPoint p(60, 20);
	snake.Add(p);
	snake.InsertAt(2, CPoint(40, 20));
	snake.InsertAt(3, CPoint(20, 20));
	snake.InsertAt(4, CPoint(0, 20));
	/*CString str1;
	str1.Format("%d", snake.GetUpperBound());
	MessageBox(str1);*/

	bkbmp.LoadBitmap(IDB_BITMAP1);
	BITMAP BM;
	bkbmp.GetBitmap(&BM);
	bk_width = BM.bmWidth;
	bk_height = BM.bmHeight;

	snakehead.LoadBitmap(IDB_BITMAP2);
	BITMAP HEAD;
	snakehead.GetBitmap(&HEAD);
	head_width = HEAD.bmWidth;
	head_height = HEAD.bmHeight;

	FoodEach.LoadBitmap(IDB_BITMAP3);
	BITMAP FOOD;
	FoodEach.GetBitmap(&FOOD);
	food_width = HEAD.bmWidth;
	food_height = HEAD.bmHeight;
	playmusic(".\\res\\playing.mp3");
}

CMFCApplication1View::~CMFCApplication1View()
{
}

BOOL CMFCApplication1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCApplication1View 绘图

void CMFCApplication1View::OnDraw(CDC* pDC)
{
	CMFCApplication1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDC MemDC;
	MemDC.CreateCompatibleDC(NULL);
	MemDC.SelectObject(&bkbmp);
	CDC MemDC2;
	MemDC2.CreateCompatibleDC(NULL);
	MemDC2.SelectObject(&snakehead);
	
	pDC->BitBlt(0, 0, bk_width, bk_height, &MemDC, 0, 0, SRCCOPY);
	CDC MemDC3;
	MemDC3.CreateCompatibleDC(NULL);
	MemDC3.SelectObject(&FoodEach);
	if (food.GetUpperBound() < 2) {
		MakeFood();
	}
	for (int i = 0; i <= food.GetUpperBound(); i++)
	{
		TransparentBlt(pDC->m_hDC, food[i].x - 10, food[i].y - 10, 20, 20, MemDC3, 0, 0, 28, 25, RGB(255, 255, 255));
	}
	
	for (int i = 0; i <= snake.GetUpperBound(); i++)
	{
		if (i == 0)
			TransparentBlt(pDC->m_hDC, snake[i].x - 10, snake[i].y - 10, 20, 20, MemDC2,0,0,625,625,RGB(255,255,255));
		else
		{
			TransparentBlt(pDC->m_hDC, snake[i].x - 10, snake[i].y - 10, 20, 20, MemDC2, 0, 0, 625, 625, RGB(255,255,255));
		}
	}
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMFCApplication1View 打印

BOOL CMFCApplication1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCApplication1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFCApplication1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMFCApplication1View 诊断

#ifdef _DEBUG
void CMFCApplication1View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication1Doc* CMFCApplication1View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication1Doc)));
	return (CMFCApplication1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication1View 消息处理程序


void CMFCApplication1View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	int tempdir;
	tempdir = direction;
	direction = nChar;
	CPoint newhead;

	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nChar)
	{
	case VK_UP:
		newhead = snake.GetAt(0) + CPoint(0, -20);
		break;
	case VK_DOWN:
		newhead = snake.GetAt(0) + CPoint(0, 20);
		break;
	case VK_LEFT:
		newhead = snake.GetAt(0) + CPoint(-20, 0);
		break;
	case VK_RIGHT:
		newhead = snake.GetAt(0) + CPoint(20, 0);
		break;
	default:
		direction = tempdir;
		return;

	}
	for (int i = 0; i <= food.GetUpperBound(); i++)
	{
		if (snake.GetAt(0) == food.GetAt(i))
		{
			sndPlaySound("res\\coin.wav", SND_ASYNC);
			snake.InsertAt(snake.GetUpperBound(), temp);
			food.RemoveAt(i);
			return;
		}
	}
	SetTimer(1, Level, NULL);
	snake.InsertAt(0, newhead);
	snake.RemoveAt(snake.GetUpperBound());
	Invalidate();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CMFCApplication1View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect r;
	GetClientRect(&r);
	CPoint newhead;
	for (int i = 0; i <= food.GetUpperBound(); i++)
	{
		if (snake.GetAt(0) == food.GetAt(i))
		{
			sndPlaySound("res\\coin.wav", SND_ASYNC);
			snake.InsertAt(snake.GetUpperBound(), temp);
			food.RemoveAt(i);
			return;
		}
	}
	switch (direction)
	{
	case VK_UP:
		newhead = snake.GetAt(0) + CPoint(0, -20);
		break;
	case VK_DOWN:
		newhead = snake.GetAt(0) + CPoint(0, 20);
		break;
	case VK_LEFT:
		newhead = snake.GetAt(0) + CPoint(-20, 0);
		break;
	case VK_RIGHT:
		newhead = snake.GetAt(0) + CPoint(20, 0);
		break;
	default:
		break;
	}
	
	
	for (int i = 0; i <= snake.GetUpperBound()-1; i++)
	{
		for (int j = i+1; j <= snake.GetUpperBound(); j++)//待查
		{
	
			if (snake.GetAt(i) == snake.GetAt(j)|| snake.GetAt(0).x >=r.right || snake.GetAt(0).y >= r.bottom|| snake.GetAt(0).x <0||snake.GetAt(0).y<0)//未知bug 偶尔直接GG
			{
				Scoresum = snake.GetUpperBound() * 10-40;
				mciSendCommand(DeviceId, MCI_STOP, 0, 0);
				mciSendCommand(DeviceId, MCI_CLOSE, 0, 0);
				sndPlaySound("res\\dead.wav", SND_SYNC);
				KillTimer(1);
				Dlgrank dlg;
		
				if (dlg.DoModal() == IDOK)

				{
					CString str;
					str.Format("%d\t", Scoresum);
					str = str + dlg.Name +'\n';
					FILE *fp;
					fp = fopen(".\\res\\rank.txt", "a+");
					fputs(str, fp);
					fclose(fp);
					//此处增加对话框和程序数据交互代码
				}
				CString str;
				str.Format("%d\t", Scoresum);
				MessageBox("GG \t score:"+ str);
				OnRestart();
				return;
			}
		}
		
	}
	
	snake.InsertAt(0, newhead);
	temp = snake.GetAt(snake.GetUpperBound());
	snake.RemoveAt(snake.GetUpperBound());
	Invalidate();
	CView::OnTimer(nIDEvent);
}


int CMFCApplication1View::MakeFood()
{
	CClientDC dc(this);
	CRect r;
	srand(time(NULL));
	GetClientRect(&r);
	for (int i = 0; i < 10; i++)
	{
	
		food.InsertAt(i, CPoint(rand() % r.Width() / 20 * 20, rand() % r.Height() / 20 * 20));
	}
	return 0;
}
	/*// TODO: 在此处添加实现代码.
	CClientDC dc(this);
	CRect r;
	GetClientRect(&r);
	CDC MemDC3;
	MemDC3.CreateCompatibleDC(NULL);
	MemDC3.SelectObject(&FoodEach);
	//TransparentBlt(dc.m_hDC, rand()%r.right, rand()%r.bottom, food_width, food_height, MemDC3, rand()%7*food_width, 0, food_height, food_width, RGB(255, 255, 255));

	//TransparentBlt(dc.m_hDC, rand()%r.right, rand()%r.bottom, food_width, food_height, MemDC3, rand()%7*food_width, 0, food_height, food_width, RGB(255, 255, 255));
	//TransparentBlt(pDC->m_hDC, snake[i].x - 10, snake[i].y - 10, 20, 20, MemDC2, 0, 0, 625, 625, RGB(255, 255, 255));

	return 0;
}*/


void CMFCApplication1View::OnStart()
{
	SetTimer(1, Level, NULL);
	// TODO: 在此添加命令处理程序代码
}


void CMFCApplication1View::OnPause()
{
	IsPause = !IsPause;
	if (IsPause==TRUE)
	{
		KillTimer(1);
		mciSendCommand(DeviceId, MCI_STOP, 0, 0);
		mciSendCommand(DeviceId, MCI_CLOSE, 0, 0);
		sndPlaySound("res\\pause.wav", SND_SYNC);
	}
	else
	{
		OnStart();
		playmusic(".\\res\\playing.mp3");
	}
	// TODO: 在此添加命令处理程序代码
}


void CMFCApplication1View::OnRestart()
{
	direction = VK_RIGHT;
	snake.SetSize(1);
	snake.SetAt(0, CPoint(80, 20));
	CPoint p(60, 20);
	snake.Add(p);
	snake.InsertAt(2, CPoint(40, 20));
	snake.InsertAt(3, CPoint(20, 20));
	snake.InsertAt(4, CPoint(0, 20));

	bkbmp.LoadBitmap(IDB_BITMAP1);
	BITMAP BM;
	bkbmp.GetBitmap(&BM);
	bk_width = BM.bmWidth;
	bk_height = BM.bmHeight;

	snakehead.LoadBitmap(IDB_BITMAP2);
	BITMAP HEAD;
	snakehead.GetBitmap(&HEAD);
	head_width = HEAD.bmWidth;
	head_height = HEAD.bmHeight;

	FoodEach.LoadBitmap(IDB_BITMAP3);
	BITMAP FOOD;
	FoodEach.GetBitmap(&FOOD);
	food_width = HEAD.bmWidth;
	food_height = HEAD.bmHeight;
	Invalidate();
	playmusic(".\\res\\playing.mp3");
	// TODO: 在此添加命令处理程序代码
}


void CMFCApplication1View::playmusic(char* a)
{
	strFile = a;    //播放的声音文件

	//加载文件前先清空上一次播放的设备

	mciSendCommand(DeviceId, MCI_CLOSE, 0, 0);

	mciopenparms.lpstrElementName = strFile;  //将音乐文件路径传给设备  

	DWORD dwReturn;

	if (dwReturn = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_WAIT, (DWORD)(LPVOID)&mciopenparms))

	{

		//如果打开失败,将出错信息储存在buffer,并显示出错警告  

		char buffer[256];

		mciGetErrorString(dwReturn, buffer, 256);//获取错误码对应的错误信息  

		MessageBox(buffer, "出错警告！", MB_ICONHAND | MB_ICONERROR | MB_ICONSTOP);

	}

	DeviceId = mciopenparms.wDeviceID;  //打开文件成功就关联文件到设备  
	// TODO: Add your command handler code here

	MCI_PLAY_PARMS mciplayparms;  //MCI_PLAY需要的参数结构体

	mciplayparms.dwCallback = (DWORD)m_hWnd;

	mciplayparms.dwFrom = 0; //每次播放都是从0开始播放  

	mciSendCommand(DeviceId, MCI_PLAY, MCI_FROM | MCI_NOTIFY, (DWORD)(LPVOID)&mciplayparms);
	// TODO: 在此处添加实现代码.
}


void CMFCApplication1View::OnLevelEasy()
{
	Level = 300;
	SetTimer(1, Level, NULL);
	// TODO: 在此添加命令处理程序代码
}


void CMFCApplication1View::OnLevelNormal()
{
	Level = 100;
	SetTimer(1, Level, NULL);
	// TODO: 在此添加命令处理程序代码
}


void CMFCApplication1View::OnLevelCarzy()
{
	Level = 50;
	SetTimer(1, Level, NULL);
	// TODO: 在此添加命令处理程序代码
}


void CMFCApplication1View::OnRank()
{
	FILE* fp;
	fp = fopen(".\\res\\rank.txt", "r");
	char a[20], b[10], name[10], Maxname[10] = "";
	int Max = 0, temp, k = 0;
	fgets(a, 20, fp);
/*	for (int i = 0; i < 20; i++)//----------------------------------待查 数组越界
		{
			b[i] = a[i];
			if (a[i] == '\t')
			{
				b[i] = '\0';
				temp = i;
			}
		}
	for (int i = temp, j = 0; i < 20; i++, j++)
	{
		name[j] = a[i];
		if (a[i] == '\n')
		{
			name[j] = '\0';
		}
	}
	if ((int)(b) >= Max)
	{
		MessageBox(b);
		Max = (int)(b);
		strcpy(Maxname, name);

	}
	/*int Max=0,temp,k=0;
	while (k++!=3)
	{
		fgets(a, 20, fp);
		for (int i = 0; i < 20; i++)
		{
			b[i] = a[i];
			if (a[i] == '\t')
			{
				b[i] = '\0';
				temp = i;
			}
		}
		for (int i = temp, j = 0; i < 20; i++, j++)
		{
			name[j] = a[i];
			if (a[i] == '\n')
			{
				name[j] = '\0';
			}
		}
		if ((int)(b) >= Max)
		{
			MessageBox(b);
			Max = (int)(b);
			strcpy(Maxname, name);
			
		}
	}*/
	fclose(fp);
	CString str;
	//str.Format("no1:%d\t%s", Max,Maxname);
	str.Format("no1:%s",a);
	MessageBox(str);
	// TODO: 在此添加命令处理程序代码
}
