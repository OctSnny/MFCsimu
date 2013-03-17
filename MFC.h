#define BOOL int
#define TRUE 1
#define FALSE 0
#define LPCSTR LPSTR
typedef char* LPSTR;
#define UINT int
#define PASCAL _stdcall
#include <iostream>

class CObject;

struct CRuntimeClass
{
  //Attributes
	LPCSTR m_lpszClassName;
	int m_nObjectSize;
	UINT m_wSchema;		//schema number of the loaded class
	CObject* (PASCAL* m_pfnCreateObject) ();
	CRuntimeClass* m_pBaseClass;

	//CRuntimeClass objects linked together in simple list
	static CRuntimeClass* pFirstClass;	
	CRuntimeClass* m_pNextClass;	//linked list of registered classes
};

struct AFX_CLASSINIT
{
	AFX_CLASSINIT(CRuntimeClass* pNewClass);
};

#define RUNTIME_CLASS(class_name) \
	(&class_name::class##class_name)

#define DECLARE_DYNAMIC(class_name) \
public:	\
	static CRuntimeClass class##class_name; \
	virtual CRuntimeClass* GetRuntimeClass() const;

#define _IMPLEMENT_RUNTIMECLASS(class_name,base_class_name,wSchema,pfnNew) \
	static char _lpsz##class_name[] = #class_name; \
	CRuntimeClass class_name::class##class_name = { \
		_lpsz##class_name,sizeof(class_name),wSchema,pfnNew, \
			RUNTIME_CLASS(base_class_name),NULL}; \
	static AFX_CLASSINIT _init_##class_name(&class_name::class##class_name); \
	CRuntimeClass* class_name::GetRuntimeClass() const \
	{return &class_name::class##class_name;} \
	
#define  IMPLEMENT_DYNAMIC(class_name,base_class_name) \
	_IMPLEMENT_RUNTIMECLASS(class_name,base_class_name,0xFFFF,NULL)

class CObject
{
public:
	CObject::CObject()
	{
		//std::cout << "CObject constructor \n";
	}
	CObject::~CObject()
	{
		//std::cout << "CObject destructor \n";
	}
	virtual CRuntimeClass* GetRuntimeClass() const;

public:
	static CRuntimeClass classCObject;
private:

};

class CCmdTarget : public CObject
{
	DECLARE_DYNAMIC(CCmdTarget)
public:
	CCmdTarget::CCmdTarget()
	{
		//std::cout << "CCmdTarget constructor \n";
	}
	CCmdTarget::~CCmdTarget()
	{
		//std::cout << "CCmdTarget destructor \n";
	}

private:

};

class CWinThread : public CCmdTarget
{
	DECLARE_DYNAMIC(CWinThread)
public:
	CWinThread::CWinThread()
	{
		//std::cout << "CWinThread constructor \n";
	}
	CWinThread::~CWinThread()
	{
		//std::cout << "CWinThread destructor \n";
	}

	virtual BOOL InitInstance()
	{
		//std::cout << "CWinThread::InitInstance \n";
		return TRUE;
	}

	virtual int Run()
	{
		//std::cout << "CWinThread::Run \n";
		return 1;
	}
};

class CWnd;

class CWinApp : public CWinThread
{
	DECLARE_DYNAMIC(CWinApp)
public:
	CWinApp* m_pCurrentWinApp;
	CWnd* m_pMainWnd;
public:
	CWinApp::CWinApp()
	{
		m_pCurrentWinApp = this;
		//std::cout << "CWinApp constructor \n";
	}
	CWinApp::~CWinApp()
	{
		//std::cout << "CWinApp destructor \n";
	}
	virtual BOOL InitApplication()
	{
		//std::cout << "CWinApp::InitApplication \n";
		return TRUE;
	}
	virtual BOOL InitInstance()
	{
		//std::cout << "CWinApp::InitInstance \n";
		return TRUE;
	}
	virtual int Run()
	{
		//std::cout << "CWinApp::Run \n";
		return CWinThread::Run();
	}
private:

};

class CDocument : public CCmdTarget
{
	DECLARE_DYNAMIC(CDocument)
public:
	CDocument::CDocument()
	{
		//std::cout << "CDocument constructor \n";
	}
	CDocument::~CDocument()
	{
		//std::cout << "CDocument destructor \n";
	}
private:

};

class CWnd : public CCmdTarget
{
	DECLARE_DYNAMIC(CWnd)
public:
	CWnd::CWnd()
	{
		//std::cout << "CWnd constructor \n";
	}
	CWnd::~CWnd()
	{
		//std::cout << "CWnd destructor \n";
	}
	virtual BOOL Create();
	BOOL CreateEx();
	virtual BOOL PreCreateWindow();
private:

};

class CFrameWnd : public CWnd
{
	DECLARE_DYNAMIC(CFrameWnd)
public:
	CFrameWnd::CFrameWnd()
	{
		//std::cout << "CFrameWnd constructor \n";
	}
	CFrameWnd::~CFrameWnd()
	{
		//std::cout << "CFrameWnd destructor \n";
	}

	BOOL Create();
	virtual BOOL PreCreateWindow();
};

class CView : public CWnd
{
	DECLARE_DYNAMIC(CView)
public:
	CView::CView()
	{
		//std::cout << "CView constructor \n";
	}
	CView::~CView()
	{
		//std::cout << "CView destructor \n";
	}

private:

};

//global function

CWinApp* AfxGetApp();
