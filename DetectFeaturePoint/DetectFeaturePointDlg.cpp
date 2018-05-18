
// DetectFeaturePointDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DetectFeaturePoint.h"
#include "DetectFeaturePointDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CDetectFeaturePointDlg 对话框




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


// CDetectFeaturePointDlg 消息处理程序

BOOL CDetectFeaturePointDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
		//////////////////////////
	CRect rect;    
	m_imgList.GetClientRect(&rect);    // 为列表视图控件添加全行选中和栅格风格   
	m_imgList.SetExtendedStyle( m_imgList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);  
	m_imgList.InsertColumn(0,"图像路径",LVCFMT_LEFT,600);
	m_FeatureType.InsertString(0,"SIFT");
	m_FeatureType.InsertString(1,"SURF");
	m_FeatureType.InsertString(2,"ORB");

	m_slider.SetRange(10,100,TRUE);//帧时间
    m_slider.SetTicFreq(1);//m_slider.GetPos();
    m_slider.SetLineSize(10);
	MatchPointNum=10;
	//////////////////////////
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDetectFeaturePointDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDetectFeaturePointDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


CString CDetectFeaturePointDlg::GetDirectory()//路径文件夹
{
	BROWSEINFO bi;
	char name[MAX_PATH];
	ZeroMemory(&bi,sizeof(BROWSEINFO));
	bi.hwndOwner = AfxGetMainWnd()->GetSafeHwnd();
	bi.pszDisplayName = name;
	bi.lpszTitle = "打开图片路径";
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
void CDetectFeaturePointDlg::OnBnClickedOpenimg()//打开某个路径下的图片
{
	// TODO: 在此添加控件通知处理程序代码

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
    bWorking =finder.FindFile(dirFileName+"\\*.png");//过滤字符串，*.*是所有文件
  
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
  bWorking =finder.FindFile(dirFileName+"\\*.jpeg");//过滤字符串，*.*是所有文件
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


void CDetectFeaturePointDlg::OnBnClickedDetect()//对图像进行特征点检测
{
	// TODO: 在此添加控件通知处理程序代码
		////////////重新设置屏幕//////////
	GetDlgItem(IDC_PICWindow)->ShowWindow(FALSE);
	GetDlgItem(IDC_PICWindow)->ShowWindow(TRUE);
	if(m_images.size()!=2)
	{
		MessageBox("请确保选择两幅图像！");
		return;
	}
	MatchPointNum=m_slider.GetPos();
	int Featureindex=0;
	CString strCBText1;
	if(m_FeatureType.GetCurSel()!=-1)
	{
		Featureindex=m_FeatureType.GetCurSel();
		m_FeatureType.GetLBText(Featureindex,strCBText1);
		m_FeatureType.SetCurSel(Featureindex); //选择主码流，子码流
	}
	   //列表框选中的两幅带匹配的图像
		m_img1 = m_images[0];
		m_img2 = m_images[1];
		////////////////SIFT////////////
	if(Featureindex==0)
	{
		detecttime=0;
		detecttime =(double)getTickCount(); 
		SIFT sift1, sift2;
		Mat  mascara;
		// -- Step 1: 检测关键点，计算特征点描述子
		sift1(m_img1,mascara,key_points1,descriptors1);
		sift2(m_img2,mascara,key_points2,descriptors2);
		//计算检测时间
		detecttime= ((double)getTickCount() - detecttime)/getTickFrequency();  
		//-- Step 2: 匹配
		//实例化暴力匹配器——BruteForceMatcher
		BruteForceMatcher<L2<float>> matcher;  
		//定义匹配器算子
		vector<DMatch>matches;  
		//实现描述符之间的匹配，得到算子matches
		matcher.match(descriptors1,descriptors2,matches);
		//显示检测时间
		CString str="";
		str.Format("特征点检测时间：%f (s) \r\n 图1关键点个数：%d \r\n 图2关键点个数：%d \r\n 图1和图2匹配关键点个数：%d\r\n ",detecttime,key_points1.size(),key_points2.size(),matches.size());
		GetDlgItem(IDC_TIME)->SetWindowText(str);
		//提取出前k个最佳匹配结果
		if(matches.size()<=MatchPointNum)
		MatchPointNum=matches.size();

		std::nth_element(matches.begin(),     //匹配器算子的初始位置
			matches.begin()+MatchPointNum-1,     // 排序的数量
			matches.end());       // 结束位置
		//剔除掉其余的匹配结果
		matches.erase(matches.begin()+MatchPointNum, matches.end());
		// -- Step 3:画匹配点，//在输出图像中绘制匹配结果
		drawMatches(m_img1,key_points1, //第一幅图像和它的特征点
			m_img2,key_points2,      //第二幅图像和它的特征点
			matches,       //匹配器算子
			img_matches,      //匹配输出图像
			Scalar::all(-1)/*CV_RGB(255,0,0)*/,CV_RGB(0,255,0),Mat(),2);    
		// drawMatches(m_img1,keypoints1,m_img2,keypoints2,goodMatches,img_matches,Scalar(255,255,255));//用白色直线连接两幅图像中的特征点  
		// -- Step 4:显示匹配后的两幅图
		IplImage img_mathesP(img_matches);//Mat转化为IplImage
		ShowImage(&img_mathesP,IDC_PICWindow);
		
	}
		///////////////SURF///////////////
	if(Featureindex==1)
	{
		detecttime=0;
		detecttime =(double)getTickCount(); 
		//提取特征点  
		SURF surfDetector(4000);  //hessianThreshold,海塞矩阵阈值，并不是限定特征点的个数  
		surfDetector.detect(m_img1, key_points1);  
		surfDetector.detect(m_img2, key_points2);  
		//计算检测时间
	    detecttime= ((double)getTickCount() - detecttime)/getTickFrequency(); 
	
		//绘制特征点  
		//drawKeypoints(m_img1, key_points1,m_img1,Scalar::all(-1),DrawMatchesFlags::DEFAULT);    
		//drawKeypoints(m_img2, key_points2,m_img2,Scalar::all(-1),DrawMatchesFlags::DRAW_RICH_KEYPOINTS);     
		//imshow("KeyPoints of m_img1",m_img1);  
		//imshow("KeyPoints of m_img2",m_img2);  
		//特征点描述，为下边的特征点匹配做准备  
		SURF SurfDescriptor;  
		SurfDescriptor.compute(m_img1, key_points1,descriptors1);  
		SurfDescriptor.compute(m_img2, key_points2,descriptors2);  
		//特征点匹配并显示匹配结果  
		BruteForceMatcher<L2<float>> matcher;  
		//FlannBasedMatcher matcher;
		vector<DMatch> matches;  
		matcher.match(descriptors1,descriptors2,matches,Mat());
		//显示检测时间
		CString str="";
		str.Format("特征点检测时间：%f (s) \r\n 图1关键点个数：%d \r\n 图2关键点个数：%d \r\n 图1和图2匹配关键点个数：%d\r\n ",detecttime,key_points1.size(),key_points2.size(),matches.size());
		GetDlgItem(IDC_TIME)->SetWindowText(str);
		//提取出前k个最佳匹配结果
		if(matches.size()<=MatchPointNum)
		MatchPointNum=matches.size();
		std::nth_element(matches.begin(),     //匹配器算子的初始位置
			matches.begin()+MatchPointNum-1,     // 排序的数量
			matches.end());       // 结束位置
		//剔除掉其余的匹配结果
		matches.erase(matches.begin()+MatchPointNum, matches.end());
		
	//绘制最优匹配点
	drawMatches(m_img1, key_points1,m_img2, key_points2,matches,img_matches,Scalar::all(-1),
   Scalar::all(-1),vector<char>(),DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS); 	
		

	IplImage img_mathesP(img_matches);//Mat转化为IplImage
    ShowImage(&img_mathesP,IDC_PICWindow);
	
	}
	/////////////////ORB//////////////
	if(Featureindex==2)
	{
		// -- Step 1: 检测关键点
		detecttime=0;
		detecttime =(double)getTickCount(); 
		ORB orb; 
		orb.detect(m_img1, key_points1); 
		orb.detect(m_img2, key_points2);
		//计算检测时间
	    detecttime= ((double)getTickCount() - detecttime)/getTickFrequency(); 
	   
		// -- Stpe 2: 计算描述子
		orb.compute(m_img1, key_points1, descriptors1); 
		orb.compute(m_img2, key_points2, descriptors2);
		//-- Step 3: 匹配
		BruteForceMatcher<L2<float>> matcher; 
		//BFMatcher matcher(NORM_HAMMING); 
		std::vector<DMatch> matches; 
		matcher.match(descriptors1, descriptors2, matches); 
		//显示检测时间
		CString str="";
		str.Format("特征点检测时间：%f (s) \r\n 图1关键点个数：%d \r\n 图2关键点个数：%d \r\n 图1和图2匹配关键点个数：%d\r\n ",detecttime,key_points1.size(),key_points2.size(),matches.size());
		GetDlgItem(IDC_TIME)->SetWindowText(str);
		//提取出前k个最佳匹配结果
		if(matches.size()<=MatchPointNum)
		MatchPointNum=matches.size();
		std::nth_element(matches.begin(),     //匹配器算子的初始位置
			matches.begin()+MatchPointNum-1,     // 排序的数量
			matches.end());       // 结束位置
		//剔除掉其余的匹配结果
		matches.erase(matches.begin()+MatchPointNum,matches.end());
		// -- Step 4:画匹配点
		drawMatches(m_img1, key_points1, m_img2, key_points2, matches, img_matches);
		// -- Step 5:显示匹配后的两幅图
		
		IplImage img_mathesP(img_matches);//Mat转化为IplImage
		ShowImage(&img_mathesP,IDC_PICWindow);

	}
	
}
void CDetectFeaturePointDlg::ShowImage(IplImage* img, UINT ID)
{
	// 获得显示控件的 DC    
	CDC* pDC = GetDlgItem(ID)->GetDC(); 
	HDC hDC = pDC ->GetSafeHdc();            
	CRect rect;   
	GetDlgItem(ID)->GetClientRect( &rect ); 
	CvvImage cimg; 
	cimg.CopyOf( img );   
	cimg.DrawToHDC( hDC, &rect );   // 将图片绘制到显示控件的指定区域内  
	// 将图片绘制到显示控件的指定区域内 
	//CopyOf()函数会开辟一个新的空间存放图像，不会自动释放。
    //因此在使用CopyOf()函数后，必须要使用Destroy()函数手动释放内存
	cimg.Destroy(); //
	ReleaseDC( pDC );//释放CDC类的指针
}

void CDetectFeaturePointDlg::OnNMClickImagelist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
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



