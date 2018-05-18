
// DetectFeaturePointDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DetectFeaturePoint.h"
#include "DetectFeaturePointDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDetectFeaturePointDlg �Ի���




CDetectFeaturePointDlg::CDetectFeaturePointDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDetectFeaturePointDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDetectFeaturePointDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IMAGELIST, m_imgList);
	DDX_Control(pDX, IDC_COMBO1, m_FeatureType);
	DDX_Control(pDX, IDC_SLIDER1, m_slider);
}

BEGIN_MESSAGE_MAP(CDetectFeaturePointDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPENIMG, &CDetectFeaturePointDlg::OnBnClickedOpenimg)
	ON_BN_CLICKED(IDC_DETECT, &CDetectFeaturePointDlg::OnBnClickedDetect)
	ON_NOTIFY(NM_CLICK, IDC_IMAGELIST, &CDetectFeaturePointDlg::OnNMClickImagelist)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CDetectFeaturePointDlg::OnNMCustomdrawSlider1)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CDetectFeaturePointDlg ��Ϣ�������

BOOL CDetectFeaturePointDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
		//////////////////////////
	CRect rect;    
	m_imgList.GetClientRect(&rect);    // Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_imgList.SetExtendedStyle( m_imgList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);  
	m_imgList.InsertColumn(0,"ͼ��·��",LVCFMT_LEFT,600);
	m_FeatureType.InsertString(0,"SIFT");
	m_FeatureType.InsertString(1,"SURF");
	m_FeatureType.InsertString(2,"ORB");

	m_slider.SetRange(10,100,TRUE);//֡ʱ��
    m_slider.SetTicFreq(1);//m_slider.GetPos();
    m_slider.SetLineSize(10);
	MatchPointNum=10;
	//////////////////////////
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CDetectFeaturePointDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDetectFeaturePointDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CDetectFeaturePointDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


CString CDetectFeaturePointDlg::GetDirectory()//·���ļ���
{
	BROWSEINFO bi;
	char name[MAX_PATH];
	ZeroMemory(&bi,sizeof(BROWSEINFO));
	bi.hwndOwner = AfxGetMainWnd()->GetSafeHwnd();
	bi.pszDisplayName = name;
	bi.lpszTitle = "��ͼƬ·��";
	bi.ulFlags = BIF_RETURNFSANCESTORS;
	LPITEMIDLIST idl = SHBrowseForFolder(&bi);
	if(idl == NULL)
		return "";
	CString strDirectoryPath;
	SHGetPathFromIDList(idl, strDirectoryPath.GetBuffer(MAX_PATH));
	strDirectoryPath.ReleaseBuffer();
	if(strDirectoryPath.IsEmpty())
		return "";
	if(strDirectoryPath.Right(1)!="\\")
		strDirectoryPath+="\\";
	return strDirectoryPath;
}
void CDetectFeaturePointDlg::OnBnClickedOpenimg()//��ĳ��·���µ�ͼƬ
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	int ItemIndex=0;
	m_imgList.DeleteAllItems();
	CFileFind finder; 
	CString dirFileName=GetDirectory();
	BOOL bResult = FALSE;
	// SetDlgItemText(IDC_DETECTTIME,dirFileName);//.Replace("\\", "\\\\")
	BOOL bWorking =finder.FindFile(dirFileName+"\\*.jpg");
   while(bWorking)
   {
     bWorking = finder.FindNextFile();
     if (finder.IsDots())
        continue;
	 if(!finder.IsDirectory()) 
     { 
		 CString imgName=finder.GetFilePath(); 
		 m_imgList.InsertItem(ItemIndex,imgName);
     } 
   }
   bWorking =finder.FindFile(dirFileName+"\\*.bmp");
		
   while(bWorking)
   {
     bWorking = finder.FindNextFile();
     if (finder.IsDots())
        continue;
	 if(!finder.IsDirectory()) 
     { 
		 CString imgName=finder.GetFilePath(); 
		 m_imgList.InsertItem(ItemIndex,imgName);
		
     } 
   }
    bWorking =finder.FindFile(dirFileName+"\\*.png");//�����ַ�����*.*�������ļ�
  
   while(bWorking)
   {
     bWorking = finder.FindNextFile();
     if (finder.IsDots())
        continue;
	 if(!finder.IsDirectory()) 
     { 
		 CString imgName=finder.GetFilePath(); 
		 m_imgList.InsertItem(ItemIndex,imgName);
     } 
   }
  bWorking =finder.FindFile(dirFileName+"\\*.jpeg");//�����ַ�����*.*�������ļ�
   while(bWorking)
   {
     bWorking = finder.FindNextFile();
     if (finder.IsDots())
        continue;
	 if(!finder.IsDirectory()) 
     { 
		 CString imgName=finder.GetFilePath(); 
		 m_imgList.InsertItem(ItemIndex,imgName);
     } 
   }
}


void CDetectFeaturePointDlg::OnBnClickedDetect()//��ͼ�������������
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		////////////����������Ļ//////////
	GetDlgItem(IDC_PICWindow)->ShowWindow(FALSE);
	GetDlgItem(IDC_PICWindow)->ShowWindow(TRUE);
	if(m_images.size()!=2)
	{
		MessageBox("��ȷ��ѡ������ͼ��");
		return;
	}
	MatchPointNum=m_slider.GetPos();
	int Featureindex=0;
	CString strCBText1;
	if(m_FeatureType.GetCurSel()!=-1)
	{
		Featureindex=m_FeatureType.GetCurSel();
		m_FeatureType.GetLBText(Featureindex,strCBText1);
		m_FeatureType.SetCurSel(Featureindex); //ѡ����������������
	}
	   //�б��ѡ�е�������ƥ���ͼ��
		m_img1 = m_images[0];
		m_img2 = m_images[1];
		////////////////SIFT////////////
	if(Featureindex==0)
	{
		detecttime=0;
		detecttime =(double)getTickCount(); 
		SIFT sift1, sift2;
		Mat  mascara;
		// -- Step 1: ���ؼ��㣬����������������
		sift1(m_img1,mascara,key_points1,descriptors1);
		sift2(m_img2,mascara,key_points2,descriptors2);
		//������ʱ��
		detecttime= ((double)getTickCount() - detecttime)/getTickFrequency();  
		//-- Step 2: ƥ��
		//ʵ��������ƥ��������BruteForceMatcher
		BruteForceMatcher<L2<float>> matcher;  
		//����ƥ��������
		vector<DMatch>matches;  
		//ʵ��������֮���ƥ�䣬�õ�����matches
		matcher.match(descriptors1,descriptors2,matches);
		//��ʾ���ʱ��
		CString str="";
		str.Format("��������ʱ�䣺%f (s) \r\n ͼ1�ؼ��������%d \r\n ͼ2�ؼ��������%d \r\n ͼ1��ͼ2ƥ��ؼ��������%d\r\n ",detecttime,key_points1.size(),key_points2.size(),matches.size());
		GetDlgItem(IDC_TIME)->SetWindowText(str);
		//��ȡ��ǰk�����ƥ����
		if(matches.size()<=MatchPointNum)
		MatchPointNum=matches.size();

		std::nth_element(matches.begin(),     //ƥ�������ӵĳ�ʼλ��
			matches.begin()+MatchPointNum-1,     // ���������
			matches.end());       // ����λ��
		//�޳��������ƥ����
		matches.erase(matches.begin()+MatchPointNum, matches.end());
		// -- Step 3:��ƥ��㣬//�����ͼ���л���ƥ����
		drawMatches(m_img1,key_points1, //��һ��ͼ�������������
			m_img2,key_points2,      //�ڶ���ͼ�������������
			matches,       //ƥ��������
			img_matches,      //ƥ�����ͼ��
			Scalar::all(-1)/*CV_RGB(255,0,0)*/,CV_RGB(0,255,0),Mat(),2);    
		// drawMatches(m_img1,keypoints1,m_img2,keypoints2,goodMatches,img_matches,Scalar(255,255,255));//�ð�ɫֱ����������ͼ���е�������  
		// -- Step 4:��ʾƥ��������ͼ
		IplImage img_mathesP(img_matches);//Matת��ΪIplImage
		ShowImage(&img_mathesP,IDC_PICWindow);
		
	}
		///////////////SURF///////////////
	if(Featureindex==1)
	{
		detecttime=0;
		detecttime =(double)getTickCount(); 
		//��ȡ������  
		SURF surfDetector(4000);  //hessianThreshold,����������ֵ���������޶�������ĸ���  
		surfDetector.detect(m_img1, key_points1);  
		surfDetector.detect(m_img2, key_points2);  
		//������ʱ��
	    detecttime= ((double)getTickCount() - detecttime)/getTickFrequency(); 
	
		//����������  
		//drawKeypoints(m_img1, key_points1,m_img1,Scalar::all(-1),DrawMatchesFlags::DEFAULT);    
		//drawKeypoints(m_img2, key_points2,m_img2,Scalar::all(-1),DrawMatchesFlags::DRAW_RICH_KEYPOINTS);     
		//imshow("KeyPoints of m_img1",m_img1);  
		//imshow("KeyPoints of m_img2",m_img2);  
		//������������Ϊ�±ߵ�������ƥ����׼��  
		SURF SurfDescriptor;  
		SurfDescriptor.compute(m_img1, key_points1,descriptors1);  
		SurfDescriptor.compute(m_img2, key_points2,descriptors2);  
		//������ƥ�䲢��ʾƥ����  
		BruteForceMatcher<L2<float>> matcher;  
		//FlannBasedMatcher matcher;
		vector<DMatch> matches;  
		matcher.match(descriptors1,descriptors2,matches,Mat());
		//��ʾ���ʱ��
		CString str="";
		str.Format("��������ʱ�䣺%f (s) \r\n ͼ1�ؼ��������%d \r\n ͼ2�ؼ��������%d \r\n ͼ1��ͼ2ƥ��ؼ��������%d\r\n ",detecttime,key_points1.size(),key_points2.size(),matches.size());
		GetDlgItem(IDC_TIME)->SetWindowText(str);
		//��ȡ��ǰk�����ƥ����
		if(matches.size()<=MatchPointNum)
		MatchPointNum=matches.size();
		std::nth_element(matches.begin(),     //ƥ�������ӵĳ�ʼλ��
			matches.begin()+MatchPointNum-1,     // ���������
			matches.end());       // ����λ��
		//�޳��������ƥ����
		matches.erase(matches.begin()+MatchPointNum, matches.end());
		
	//��������ƥ���
	drawMatches(m_img1, key_points1,m_img2, key_points2,matches,img_matches,Scalar::all(-1),
   Scalar::all(-1),vector<char>(),DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS); 	
		

	IplImage img_mathesP(img_matches);//Matת��ΪIplImage
    ShowImage(&img_mathesP,IDC_PICWindow);
	
	}
	/////////////////ORB//////////////
	if(Featureindex==2)
	{
		// -- Step 1: ���ؼ���
		detecttime=0;
		detecttime =(double)getTickCount(); 
		ORB orb; 
		orb.detect(m_img1, key_points1); 
		orb.detect(m_img2, key_points2);
		//������ʱ��
	    detecttime= ((double)getTickCount() - detecttime)/getTickFrequency(); 
	   
		// -- Stpe 2: ����������
		orb.compute(m_img1, key_points1, descriptors1); 
		orb.compute(m_img2, key_points2, descriptors2);
		//-- Step 3: ƥ��
		BruteForceMatcher<L2<float>> matcher; 
		//BFMatcher matcher(NORM_HAMMING); 
		std::vector<DMatch> matches; 
		matcher.match(descriptors1, descriptors2, matches); 
		//��ʾ���ʱ��
		CString str="";
		str.Format("��������ʱ�䣺%f (s) \r\n ͼ1�ؼ��������%d \r\n ͼ2�ؼ��������%d \r\n ͼ1��ͼ2ƥ��ؼ��������%d\r\n ",detecttime,key_points1.size(),key_points2.size(),matches.size());
		GetDlgItem(IDC_TIME)->SetWindowText(str);
		//��ȡ��ǰk�����ƥ����
		if(matches.size()<=MatchPointNum)
		MatchPointNum=matches.size();
		std::nth_element(matches.begin(),     //ƥ�������ӵĳ�ʼλ��
			matches.begin()+MatchPointNum-1,     // ���������
			matches.end());       // ����λ��
		//�޳��������ƥ����
		matches.erase(matches.begin()+MatchPointNum,matches.end());
		// -- Step 4:��ƥ���
		drawMatches(m_img1, key_points1, m_img2, key_points2, matches, img_matches);
		// -- Step 5:��ʾƥ��������ͼ
		
		IplImage img_mathesP(img_matches);//Matת��ΪIplImage
		ShowImage(&img_mathesP,IDC_PICWindow);

	}
	
}
void CDetectFeaturePointDlg::ShowImage(IplImage* img, UINT ID)
{
	// �����ʾ�ؼ��� DC    
	CDC* pDC = GetDlgItem(ID)->GetDC(); 
	HDC hDC = pDC ->GetSafeHdc();            
	CRect rect;   
	GetDlgItem(ID)->GetClientRect( &rect ); 
	CvvImage cimg; 
	cimg.CopyOf( img );   
	cimg.DrawToHDC( hDC, &rect );   // ��ͼƬ���Ƶ���ʾ�ؼ���ָ��������  
	// ��ͼƬ���Ƶ���ʾ�ؼ���ָ�������� 
	//CopyOf()�����Ὺ��һ���µĿռ���ͼ�񣬲����Զ��ͷš�
    //�����ʹ��CopyOf()�����󣬱���Ҫʹ��Destroy()�����ֶ��ͷ��ڴ�
	cimg.Destroy(); //
	ReleaseDC( pDC );//�ͷ�CDC���ָ��
}

void CDetectFeaturePointDlg::OnNMClickImagelist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	m_images.clear();
	///////////////////
	POSITION  pos=NULL;
	int num=0;
	pos = m_imgList.GetFirstSelectedItemPosition();
	while(pos!=NULL)
	{
		int index = m_imgList.GetNextSelectedItem(pos);
		CString sFileName=m_imgList.GetItemText(index,0);
		num++;
		////////////////////////////////
		char* imgPath=sFileName.GetBuffer(sFileName.GetLength());
		Mat img=imread(imgPath);
		m_images.push_back(img);
		if(num==2)
			break;
	}
}

void CDetectFeaturePointDlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
	UpdateData(TRUE);
    CString str;
    int sldValue = m_slider.GetPos();    
    str.Format("%d", sldValue);
    GetDlgItem(IDC_STATICN)->SetWindowText(str);
    UpdateData(FALSE);
}



