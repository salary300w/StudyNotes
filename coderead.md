- [CodeRead-xiangkongzhen](#coderead-xiangkongzhen)
  - [类](#类)
    - [```class USDevHandle ： public QObject```](#class-usdevhandle--public-qobject)
    - [```class USDevHandleProtect ： public QObject```](#class-usdevhandleprotect--public-qobject)
    - [```class SubWidget_ScanRule : public DataConfigSubWidget```](#class-subwidget_scanrule--public-dataconfigsubwidget)
    - [```class UTParaManagerPrivate```](#class-utparamanagerprivate)
    - [```class SubWidget_Gate : public DataConfigSubWidget```](#class-subwidget_gate--public-dataconfigsubwidget)
    - [```class UTParaManagerPrivate```](#class-utparamanagerprivate-1)
    - [```class UTPARAMANAGERSHARED_EXPORT UTParaManager```](#class-utparamanagershared_export-utparamanager)
    - [```class UTPARAMANAGERSHARED_EXPORT UtScanParameter```](#class-utparamanagershared_export-utscanparameter)
  - [函数](#函数)
    - [```void SubWidget_ScanRule::UpdateCurrentInfo();```](#void-subwidget_scanruleupdatecurrentinfo)
    - [```void SubWidget_USConf::UpdateCurrentInfo();```](#void-subwidget_usconfupdatecurrentinfo)
    - [```void SubWidget_Gate::UpdateCurrentInfo();```](#void-subwidget_gateupdatecurrentinfo)
    - [```void SubWidget_Scan::UpdateCurrentInfo();```](#void-subwidget_scanupdatecurrentinfo)
    - [```double UtScanParameter::GetScanRuleParam(SRPName param);```](#double-utscanparametergetscanruleparamsrpname-param)
  - [结构体](#结构体)
    - [```struct CScanParam```](#struct-cscanparam)
    - [```struct ScanRuleConfParam```](#struct-scanruleconfparam)
    - [```struct ScanRuleInspectParam```](#struct-scanruleinspectparam)
    - [```struct ScanRuleBeamParam```](#struct-scanrulebeamparam)
    - [```struct ScanRuleWedgeParam```](#struct-scanrulewedgeparam)
    - [```struct ScanRuleProbeParam```](#struct-scanruleprobeparam)
    - [```struct ScanRuleParam```](#struct-scanruleparam)
    - [```typedef struct InspectParam```](#typedef-struct-inspectparam)
  - [枚举类型](#枚举类型)
    - [```enum SRPName```](#enum-srpname)
# CodeRead-xiangkongzhen
## 类
### ```class USDevHandle ： public QObject```
* 作用:扫描相关参数
* 成员变量:```USDevHandleProtect *m_protect;```
* 成员函数:
  ```C++
  //虚函数
  virtual void UpdateScanXAxis(); //计算图像x方向端点值
  virtual void GenerateImageCoefficient(); //设置图像参数
  virtual void UpdateImageValidP1P2(); //计算图像最佳显示
  virtual void UpdateParameter(); //重新发送配置到硬件
  
  void SetScanStatus(QString status); //修改扫查状态
  double ChangeEncoderPercision(double step); //修改编码器精度
  //槽函数
  int GateCalibAmp(int gateIndex, AWaveform * const pWaveform); //计算pWaveform的闸门峰值和峰值位置，return 闸门峰值
  ```
### ```class USDevHandleProtect ： public QObject```
* 作用:存储参数设置
* 成员变量:
  ```C++
  BYTE m_dataBuffer[Pa22Support_PA::dataSize];
  BYTE *pAWaveBuff ;
  BYTE *pImageBuff ;
  UtScanParameter* param_;
  int m_height;
  int m_width;
  int m_width_frame;
  unsigned int m_encoderPluseFwd;
  unsigned int m_encoderPluseRvs;
  unsigned char m_beamLineMax[128];
  unsigned char m_horizontalMax[512];
  int m_horizontalMaxDataStart;
  int m_horizontalMaxDataEnd;
  QTime scanStartTime;
  QTime scanPauseTime;
  unsigned long m_scanPauseTimeMm;
  unsigned long m_scanTimeCountMs;
  int lastPx;
  unsigned int oldFwdCount;
  unsigned int oldRvsCount;
  double ix[400];
  double ox[400];
  double iy[400];
  double oy[400];
  ```
* 成员函数:无
### ```class SubWidget_ScanRule : public DataConfigSubWidget```
* 作用:存储参数设置
* 成员变量:```Ui::SubWidget_ScanRule *ui;```
* 成员函数
  ```C++
  //构造函数
  explicit SubWidget_ScanRule(QWidget *parent = 0);
  //槽函数
  void UpdateCurrentInfo();
  ```
### ```class UTParaManagerPrivate```
* 作用:存储参数设置
* 成员变量:
  ```C++
  //公共成员变量
  USDevHandle *pUtScanHandle;
  ```
* 成员函数
  ```C++
  //公共成员函数
  UTParaManagerPrivate(); //作用:堆区创建pUtScanHandle，调用其init函数初始化扫查方式为:A扫和线扫！
  ```
### ```class SubWidget_Gate : public DataConfigSubWidget```
* 作用:
* 成员变量:
  ```C++
  //私有
  int m_curGateIndex;
  Ui::SubWidget_ScanRule *ui;
  ```
* 成员函数
  ```C++
  //公有槽函数
  virtual void UpdateCurrentInfo();
  void updateGateInfo();
  //私有槽函数
  void onGateSwitch();
  void onGateStartChanged(double val);
  void onGateWidthChanged(double val);
  void onGateThrChanged(double val);
  void onGateIndexChanged(int index);

  void onVpaChanged(int val);
  ```
### ```class UTParaManagerPrivate```
* 作用:存储参数设置
* 成员变量:
  ```C++
  //公共成员变量
  USDevHandle *pUtScanHandle;
  ```
* 成员函数
  ```C++
  //公共成员函数
  UTParaManagerPrivate(); //作用:堆区创建pUtScanHandle，调用其init函数初始化扫查方式为:A扫和线扫！
  ```
### ```class UTPARAMANAGERSHARED_EXPORT UTParaManager```
* 作用:扫查参数管理设置
* 成员变量:
  ```C++
  //私有成员变量
  UTParaManagerPrivate *m_private;
  ```
* 成员函数
  ```C++
  //保护成员函数
  UTParaManager();
  //公共成员函数
  static UTParaManager &instance(); //作用:在全局区创建UTParaManager对象。(单例设计模式)
  USDevHandle *getUtScanHandle(); //直接return m_private->pUtScanHandle;
  ```
### ```class UTPARAMANAGERSHARED_EXPORT UtScanParameter```
* 作用:存储扫查参数
* 成员变量:
* 友元类:```USDevHandle```
  ```C++
  //保护成员变量
  int scan_type_;
  int gaind;  //数字增益
  int gs_smooth_ ;    //高斯平滑
  int sf_image_ ;     //软件成像,貌似没卵用
  ScanRuleParam scanrule_param_;  //扫描法则//由sb_api初始化
  GateInfoParam gateinfo_param_[GATE_COUNT];   //闸门信息
  InspectParam inspect_param_;    //不知道干嘛的//看起来相似存储当前配置的玩意
  USDevHandle *scan_;

  int m_eleAdjust;
  int eleAdjustIndex; //基线
  int countT; //收发孔径T,没怎么用上
  int countR; //收发孔径R,没怎么用上
  int m_avgtimes; //平均次数,没怎么用上
  int eleFilter;  //数字滤波器
  int TRTimeSequence; //发射时序选择
  CScanParam cscan_param_; //CScanParam 结构体类型
  CursorLineParam m_cursorLineParams[2];
  bool m_cursorLineSwitch[4];
  ```
* 成员函数
  ```C++
  //保护成员函数
  UTParaManager();
  //公共成员函数
  UtScanParameter();
  virtual ~UtScanParameter();
  ScanRuleParam* GetScanRulePtr();
  void SetUtScan(USDevHandle *scan);
  //int GetVelocity();
  //void SetVelocity(int val);
  double GetScanRuleParam(SRPName param);
  void SetScanRuleParam(SRPName param, double val);
  bool GetScanDoubleMode();
  //单双探头模式
  void SetScanDoubleMode(bool val);
  bool GetDynFocusEnable();
  void SetDynFocusEnable(bool val);
  bool GetWedgeUsed();
  //启用楔块
  void SetWedgeUsed(bool val);

  double GetCurrentBeamAngle();
  double GetBeamAngleByIndex(int index);
  bool SetDisplayRange(double val);
  double GetDisplayRange();
  bool SetUnidB(double val);
  double GetUnidB();
  bool SetDeltadB(double val);
  double GetDeltadB();

  void SetScanXAxisP1P2(double p1, double p2);
  void GetScanXAxisP1P2(double &p1, double &p2);
  void SetImageValidXP1P2(double p1, double p2);
  void GetImageValidXP1P2(double &p1, double &p2);
  void SetImageValidYP1P2(double p1, double p2);
  void GetImageValidYP1P2(double &p1, double &p2);

  bool SetProbeDelayUs(double val);
  double GetProbeDelayUs();
  int GetBeamCount();
  bool SetBeamLineIndex(int val);
  int GetBeamLineIndex();
  /*!
   * \brief SetHighVoltage 设置发射电压
   * \param val
   * \return
   */
  bool SetHighVoltage(int val);
  int GetHighVotage();
  bool SetPulseWidth(int val);
  int GetPulseWidth();
  bool SetRPF(int val);
  int GetRPF();
  bool SetFilter(int step);
  QString GetFilter();
  int GetFilterInt();
  bool SetSmooth(bool val);
  bool GetSmooth();
  //冻结
  bool SetFreeze(bool val);
  bool GetFreeze();

  void SetInterpolateEnable(bool val);
  bool GetInterpolateEnable();

  GateParameter GetGateParam(int index);
  GateParameter *GetGateParamPtr(int index);
  GateResultParam GetGateResultParam(int index);
  GateResultParam *GetGateResultParamPtr(int index);
  void SetGateParam(GateParameter par, int index);
  bool SetGateResultParam(GateResultParam par,int index);

  void AdjustGates();

  virtual void updateScanRule();
  void SetScanType(int type);
  int GetScanType();

  bool SetGainD(int val);
  int GetGainD();

  void SetEleAdjust(int val);
  int GetEleAdjust(int index = -1);
  void SetAdjustEleIndex(int val);
  int GetAdjustEleIndex(){return eleAdjustIndex;}
  void SetEleMultiple(int val);
  int GetEleMultiple(int index = -1);

  void SetSRPAperture(QString type, int index, bool val);
  bool GetSRPAperture(QString type, int index);
  void ClearAperture(QString type);
  int GetAvgTimes();
  void SetAvgTimes(int val);
  void SetEleFilter(int val);
  QString GetEleFilter();
  int GetEleFilterInt(){return eleFilter;}
  void SetTRTimeSequence(int val);
  int GetTRTimeSequence(){return TRTimeSequence;}
  void GetBatteryInfo(bool &isac, int &persent, double &tem);

  void SetSmoothGauss(int val);
  int GetSmoothGauss();
  void SetSfImage(int val);
  int GetSfImage();

  //for ImageCache
  void reset();
  //void Init();
  void SetCScanParam(CScanParam par);
  CScanParam GetCScanParam();
  CScanParam* GetCScanParamPtr();
  void SetCScanStatus(QString val);
  QString GetCScanStatus();
  void SetCScanMode(QString mode);
  QString GetCScanMode();
  void GetCScanRect(int &height, int &length, int &frameNum, int &frameLength);
  void GetCScanXAxisP1P2(double &p1, double &p2);
  void GetCScanYAxisP1P2(double &p1, double &p2);
  void GetCScanXAxisPixP1P2(int &p1, int &p2);
  void SetCScanEncoderPercisionCp(double val);
  void SetCScanEncoderPercision(double step);
  double GetCScanEncoderPercision();
  void SetCScanImagePercisionCp(double val);
  void SetCScanImagePercision(int step);
  double GetCScanImagePercision();
  void SetCScanYPercision(double val);
  double GetCScanYPercision();
  virtual void SetEncoderDir(int step);
  QString GetEncoderDir();
  double GetCurrentScanPos();

  //bool GetRecordEnable();
  //void SetRecordEnable(bool sw);
  //QString GetRecordStatus();
  //bool SetSaveRecord();
  //bool SetSaveRecord(QString dir);
  //QString GetFileName();

  //void SetCScanImageStartPos(int val);//pix
  void GetCScanImageArea(double &x1, double &x2, double &y1,double &y2);
  void SetCScanImageArea(double x1, double x2, double y1,double y2);
  double GetCScanLimitLength();
  void SetCScanLimitLength(double val);
  int GetCScanLimitTime();
  void SetCScanLimitTime(int val);
  CursorLineParam getCursorLineParam(int index);
  void setCursorLineParam(CursorLineParam par, int index);
  bool getCursorSwitch(int index);
  void setCursorSwitch(bool en,int index);
  enum CursorLineSwitchEnum
  {
      ACursorSwith,
      BCursorSwith,
      CCursorSwith,
      SCursorSwith,
  };
  ```
**--------------------------------------------**
## 函数
### ```void SubWidget_ScanRule::UpdateCurrentInfo();```
* 作用:
  * 更新当前关于扫查规则的配置信息
  * 获取扫查方式
  * 获取扫查角度的起点
  * 获取晶片数量
  * 获取孔径起点
  * 获取孔径重点
### ```void SubWidget_USConf::UpdateCurrentInfo();```
* 作用:
  * 设置InfoLE_Gain显示为InspectParam结构体的unidB值
  * 设置某InfoLE_DeltaGain显示为InspectParam结构体的deltadB值
  * 设置InfoLE_StartPos显示为0.0
  * 设置InfoLE_DisplayRange显示为扫描法则初始值为GetDisplayRange()
  * 设置InfoLE_WedgeDelay显示为0
  * 设置InfoLE_VS显示为工作声速
  * 设置InfoLE_Angle显示为扫查角度的起点
  * 设置InfoLabel_Pluse显示为孔径起点
  * 设置InfoLabel_ReciveAp显示为孔径终点
### ```void SubWidget_Gate::UpdateCurrentInfo();```
* 作用:
  * 设置GateEN_checkBox默认是否被选中
  * 设置GateStartPos_lineEdit开始位置的默认值
  * 设置GateWidth_lineEdit的默认值
  * 设置GateThr_lineEdit的默认值
  * 设置GateStartPos_lineEdit的范围上下限
  * 设置GateWidth_lineEdit的范围上下限
  * 设置spinBox_VPA的初始值
  * 设置spinBox_VPA的范围上下限
  * 更新各种光标的范围
    * Cursor_Pm
    * Cursor_Pr
    * Cursor_Um
    * Cursor_Ur
    * Cursor_Sm
    * Cursor_Sr
    * Cursor_Im
    * Cursor_Ir
### ```void SubWidget_Scan::UpdateCurrentInfo();```
* 作用:
  * mmPerCoder(编码器精度)<=0,设置为1
  * 设置InfoLE_ScanEndPos显示内容
  * 设置slider_ScanPos滑动条的最大值
  * 设置lineEdit_ScanPos的范围上下限
### ```double UtScanParameter::GetScanRuleParam(SRPName param);```
* 作用:根据枚举类型SRPName，获取扫查参数信息
* 函数内容:
  ```C++
  double UtScanParameter::GetScanRuleParam(SRPName param)
  {
    switch (param) {
    case SRPvelocity:
        return scanrule_param_.scanConf.velocity;
    case SRPapertureSize:
        return scanrule_param_.scanConf.apertureSize;
    case SRPapertureFrom:
        return scanrule_param_.scanConf.apertureFrom;
        /*
        .
        .
        .
        */
    default:
        return 0;
  }
  ```
**--------------------------------------------**
## 结构体
### ```struct CScanParam```
* 成员:
  ```C++
  CScanParam();

  QString scanStatus;
  QString encoderDir;
  QString scanMode ;//"enc","time"
  int height ;
  int frameLength ;
  int frameNum ;
  int length;
  int currentPos;
  int screenStartPos;
  int screenEndPos ;
  int limitScanTimeS ;
  int imageHeightPixel ; //c scan image height
  double mmPerCoder ;	//encoder percison
  double mmPerPixelX ; //image percison mm/pixel
  double mmPerPixelY ;
  double imageHeightMMY1 ;//
  double imageHeightMMY2 ;//y2 of c image,not view
  double imageLengthMMX1Adjustable ;//x1 of c image,menu adjustable
  double imageLengthMMX2Adjustable ;
  double imageHeightMMY1Adjustable ;//y1 of c image,menu adjustable
  double imageHeightMMY2Adjustable ;
  double limitScanLengthMM ;
  double scanByTimePixPerMS ;//pix/ms;
  //    bool recordEnable = false;
  ```
### ```struct ScanRuleConfParam```
* 作用:扫查参数具体设置
* 成员:
  ```C++
  int velocity = 2400;
  int apertureSize = 115;
  int apertureFrom = 1;
  int apertureTo = 128;
  double scanAngleFrom = -45;
  double scanAngleTo = 45;
  double scanAngleStep = 1;
  int focus = 10;
  bool dynFocusEnable = true;//false;

  int beamCount = 128;
  double maxCenterDelay = 0;	// in ns
  int focusDis = 10;
  bool scanDoubleMode = false;
  int apertureSizeR = 16;
  int apertureFromR = 1;
  int apertureToR = 16;
  int apertureSizeT = 16;
  int apertureFromT = 17;
  int apertureToT = 32;

  bool apertureT[/*64*/MAX_ELE_COUNT] = {false};
  bool apertureR[/*64*/MAX_ELE_COUNT] = {false};
  int delayTInterval = 0;
  int delayRInterval = 0;
  int delayT = 0;
  int delayR = 0;
  unsigned short dynFocusPos[ScanRuleBeamParam::DynFocusSegments];
  ```
### ```struct ScanRuleInspectParam```
* 成员:
  ```C++
  double dispRange = 25;
  ```
### ```struct ScanRuleBeamParam```
* 成员:
  ```C++
  //int				BeamIndex = 0;
  double          Angle = 0;
  int				CenterEle = 0;				// 中心阵元
  double		    RefractPoint = 0;
  double			WedgeDelay = 0;
  //bool            EleSelect[64] = {0};
  bool            RecEleSelect[/*64*/MAX_ELE_COUNT] = {0};
  bool            TransmitEleSelect[/*64*/MAX_ELE_COUNT] = {0};
  unsigned short	EleTDelay[/*64*/MAX_ELE_COUNT] = {0};
  unsigned short	EleRDelay[/*64*/MAX_ELE_COUNT] = {0};
  static const int DynFocusSegments = 100;
  //static const int DynFocusRange = 72;//150;//180;
  unsigned short  DynEleRDelay[DynFocusSegments][/*64*/MAX_ELE_COUNT];
  ```
### ```struct ScanRuleWedgeParam```
* 成员:
  ```C++
  bool wedgeUsed = false;
  double wedgeAngle = 0;			// 1/1000度
  int velocity = 2337;			// 楔块声速 m/s
  double eleHeight = 20;			//中心阵元高度
  ```
### ```struct ScanRuleProbeParam```
* 成员:
  ```C++
  unsigned int elementCount = 128;
  double elementDistance = 0.3;
  ```
### ```struct ScanRuleParam```
* 成员:
  ```C++
  ScanRuleConfParam scanConf;
  ScanRuleInspectParam inspect;
  ScanRuleBeamParam beam[128];
  ScanRuleWedgeParam wedge;
  ScanRuleProbeParam probe;
  ```
### ```typedef struct InspectParam```
* 作用:可能是参数检查的作用
* 成员:
  ```C++
  InspectParam();

  void reset();

  double unidB;
  double deltadB;            //22b
  //double dispRange{100};		// in mm
  //double dispStart{0};		// in mm
  int beamLineIndex;
  double compressRate;
  int filter;
  int RPF;
  int pulseWidth;
  int highVotage;
  bool smooth;
  QString gateAlarmSelect;
  double scanXAxisP1;
  double scanXAxisP2;
  double imageValidXP1;
  double imageValidXP2;
  double imageValidYP1;
  double imageValidYP2;
  EncoderParam encoder[2];
  bool freeze;
  double probeDelay;
  bool interpolateEnable;
  ```
**--------------------------------------------**
## 枚举类型
### ```enum SRPName```
* 成员:
  ```C++
  SRPvelocity, //工件声速
  SRPapertureSize,  //孔径大小
  SRPapertureFrom,  //孔径起点
  SRPapertureTo,    //孔径终点
  SRPapertureSizeR, SRPapertureFromR, SRPapertureToR, SRPapertureSizeT,
  SRPcountT, SRPcountR, //收发孔径T/R
  SRPapertureFromT, SRPapertureToT, SRPdelayTInterval, SRPdelayRInterval, SRPdelayT, SRPdelayR,
  SRPscanAngleFrom,  //扫查角度  //角度起点
  SRPscanAngleTo,   //角度终点
  SRPfocus,
  SRPfocusDis,      //焦距
  SRPbeamCount, SRPmaxCenterDelay,
  SRPdispRange,     //范围
  SRPelementCount,  //晶片数目
  SRPelementDistance,   //晶片间距
  SRPwedgeAngle,    //楔块角度
  SRPwedgeVelocity,     //楔块声速
  SRPeleHeight,     //中心晶片高
  ```