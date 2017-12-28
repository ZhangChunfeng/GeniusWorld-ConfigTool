#include "MainConfigWnd.h"
#include "ui_MainConfigWnd.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QFile>

MainConfigWnd::MainConfigWnd(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainConfigWnd)
    ,mFileName("")
    ,isConfigApply(false)
    ,enableHigherConfig(false)
    ,enableCommonConfig(false)
{
    ui->setupUi(this);

    this->setWindowIcon(QIcon(":/res/resources/tool_icon.png"));
    this->setWindowTitle(QStringLiteral("参数配置"));

    SetDefaultConfigPath();
}

MainConfigWnd::~MainConfigWnd()
{
    delete ui;
}

/*
 * Function      :OpenConfigFilePath
 * Description:打开配置文件路径
 * Parameters  :
 * Return          :bool  -false选择文件失败，true选择文件成功
 */
bool MainConfigWnd::OpenConfigFilePath()
{
    QString captionStr = QStringLiteral("选择配置文件路径");
    QString dirStr = qApp->applicationFilePath();
    QString typeStr = "Ini file(*.ini)";
    QString warnTitle = QStringLiteral("提示");
    QString warnText = QStringLiteral("请选择配置文件路径！");
    QMessageBox::StandardButtons standBtns = QMessageBox::Cancel | QMessageBox::Ok;
    if(!mFileName.isEmpty()) {
        warnText = QStringLiteral("确定要更新配置文件路径？");
        if(QMessageBox::Cancel == QMessageBox::question(this, warnTitle, warnText, standBtns)) {
            return false;
        }
    }
    QString nameStr = QFileDialog::getOpenFileName(this,captionStr, dirStr, typeStr,0);
    if(!nameStr.isEmpty()) {
        mFileName = nameStr;
        ui->CurrentPathEdit->setText(nameStr);
        return true;
    } else {
        QMessageBox::warning(this, warnTitle, warnText, QMessageBox::Ok);
        return false;
    }
}

/*
 * Function      :ReadConfigFileContent
 * Description:读取配置文件内容
 * Parameters  :
 * Return          :bool  -false读取文件失败，true读取文件成功
 */
bool MainConfigWnd::ReadConfigFileContent()
{
    using namespace gw;
    GWConfigParas configIniContent;
    QString fileName = mFileName;
    if(fileName.isEmpty()) {
        return false;
    }
    QSettings* configIniRead = new  QSettings(fileName, QSettings::IniFormat);

    GWConfigNetwork tempNetwork;
    tempNetwork.download_Sleep_Time = configIniRead->value("/Network/DownloadSleepTime").toString();
    tempNetwork.download_Sleep_Interval = configIniRead->value("/Network/DownloadSleepInterval").toString();
    tempNetwork.download_Thread_Count = configIniRead->value("/Network/DownloadThreadCount").toString();
    configIniContent.gwConfigNetwork = tempNetwork;

    GWConfigRender tempRender;
    tempRender.max_FPS = configIniRead->value("/Render/MaxFPS").toString();
    tempRender.computer_Performance = configIniRead->value("/Render/ComputerPerformance").toString();
    tempRender.multi_Sample_Type = configIniRead->value("/Render/MultiSampleType").toString();
    tempRender.hardware_Timer = configIniRead->value("/Render/HardwareTimer").toString();
    tempRender.generate_Topologic = configIniRead->value("/Render/GenerateTopologic").toString();
    tempRender.remain_Raw_Buffer = configIniRead->value("/Render/RemainRawBuffer").toString();
    tempRender.light_Enable = configIniRead->value("/Render/LightEnable").toString();
    tempRender.max_Frame_Time = configIniRead->value("/Render/MaxFrameTime").toString();
    tempRender.debug_Mode = configIniRead->value("/Render/DebugMode").toString();
    tempRender.terrain_Render_Mode = configIniRead->value("/Render/TerrainRenderMode").toString();
    tempRender.update_Interval = configIniRead->value("/Render/UpdateInterval").toString();
    configIniContent.gwConfigRender = tempRender;

    GWConfigBuilding tempBuilding;
    tempBuilding.max_Vis_Range = configIniRead->value("/Building/MaxVisRange").toString();
    tempBuilding.min_Vis_Range = configIniRead->value("/Building/MinVisRange").toString();
    tempBuilding.new_Building = configIniRead->value("/Building/NewBuilding").toString();
    tempBuilding.transparent_Color = configIniRead->value("/Building/TransparentColor").toString();
    tempBuilding.transparent_Color2 = configIniRead->value("/Building/TransparentColor2").toString();
    tempBuilding.max_Visible_Height = configIniRead->value("/Building/MaxVisibleHeight").toString();
    tempBuilding.transparent_Begin = configIniRead->value("/Building/TransparentBegin").toString();
    tempBuilding.transparent_End = configIniRead->value("/Building/TransparentEnd").toString();
    tempBuilding.material_Levels = configIniRead->value("/Building/MaterialLevels").toString();
    tempBuilding.texture_Bias = configIniRead->value("/Building/TextureBias").toString();
    tempBuilding.model_Render_Bios = configIniRead->value("/Building/ModelRenderBios").toString();
    tempBuilding.lod_Sec_Distance = configIniRead->value("/Building/LodSecDistance").toString();
    tempBuilding.use_Default_Texture = configIniRead->value("/Building/UseDefaultTexture").toString();
    configIniContent.gwConfigBuilding = tempBuilding;

    GWConfigResource tempResource;
    tempResource.max_Memory_Size = configIniRead->value("/Resource/MaxMemorySize").toString();
    tempResource.max_Life_Time = configIniRead->value("/Resource/MaxLifeTime").toString();
    tempResource.max_Tex_Size_Per_Batch = configIniRead->value("/Resource/MaxTexSizePerBatch").toString();
    tempResource.max_Mesh_Size_Per_Batch = configIniRead->value("/Resource/MaxMeshSizePerBatch").toString();
    tempResource.max_Tex_Count_Per_Batch = configIniRead->value("/Resource/MaxTexCountPerBatch").toString();
    tempResource.max_Mesh_Count_Per_Batch = configIniRead->value("/Resource/MaxMeshCountPerBatch").toString();
    tempResource.max_Terrain_Count_Per_Batch = configIniRead->value("/Resource/MaxTerrainCountPerBatch").toString();
    tempResource.max_Reclaim_Memory_Per_Frame = configIniRead->value("/Resource/MaxReclaimMemoryPerFrame").toString();
    configIniContent.gwConfigResource = tempResource;

    GWConfigLink tempLink;
    tempLink.res_Folder = configIniRead->value("/Link/ResFolder").toString();
    tempLink.connection = configIniRead->value("/Link/Connection").toString();
    tempLink.role_Res_Connection = configIniRead->value("/Link/RoleResConnection").toString();
    tempLink.AI_Server = configIniRead->value("/Link/AIServer").toString();
    tempLink.AI_Server_Port = configIniRead->value("/Link/AIServerPort").toString();
    tempLink.license_Server = configIniRead->value("/Link/LicenseServer").toString();
    tempLink.pipeline_Server = configIniRead->value("/Link/PipelineServer").toString();
    tempLink.debug_Log_Path = configIniRead->value("/Link/DebugLogPath").toString();
    configIniContent.gwConfigLink = tempLink;

    GWConfigRole tempRole;
    tempRole.role_Walk_Volocity = configIniRead->value("/Role/RoleWalkVolocity").toString();
    tempRole.role_Run_Volocity = configIniRead->value("/Role/RoleRunVolocity").toString();
    tempRole.underGround_Mode = configIniRead->value("/Role/UnderGroundMode").toString();
    configIniContent.gwConfigRole = tempRole;

    GWConfigBrowse tempBrowse;
    tempBrowse.zoom_Center = configIniRead->value("/Browse/ZoomCenter").toString();
    tempBrowse.enable_Fly = configIniRead->value("/Browse/EnableFly").toString();
    configIniContent.gwConfigBrowse = tempBrowse;

    GWConfigGui tempGui;
    tempGui.show_Navigator = configIniRead->value("/Gui/ShowNavigator").toString();
    tempGui.show_Logo = configIniRead->value("/Gui/ShowLogo").toString();
    tempGui.show_Information = configIniRead->value("/Gui/ShowInformation").toString();
    tempGui.information_Language = configIniRead->value("/Gui/InformationLanguage").toString();
    configIniContent.gwConfigGui = tempGui;

    m_configParas = configIniContent;
    delete configIniRead;
    configIniRead = NULL;
    return true;
}

/*
 * Function      :WriteConfigFileContent
 * Description:写配置文件内容
 * Parameters  :
 * Return          :bool false-写文件内容失败，true-写文件内容成功
 */
bool MainConfigWnd::WriteConfigFileContent()
{
    using namespace gw;
    GWConfigParas configParas = m_configParas;
    QString fileName = mFileName;
    if(fileName.isEmpty()) {
        return false;
    }

    QSettings* writeIni = new  QSettings(fileName, QSettings::IniFormat);

    GWConfigNetwork configNetwork = configParas.gwConfigNetwork;
    writeIni->setValue("/Network/DownloadSleepTime", configNetwork.download_Sleep_Time);
    writeIni->setValue("/Network/DownloadSleepInterval", configNetwork.download_Sleep_Interval);
    writeIni->setValue("/Network/DownloadThreadCount", configNetwork.download_Thread_Count);

    GWConfigRender configRender = configParas.gwConfigRender;
    writeIni->setValue("/Render/MaxFPS", configRender.max_FPS);
    writeIni->setValue("/Render/ComputerPerformance", configRender.computer_Performance);
    writeIni->setValue("/Render/MultiSampleType", configRender.multi_Sample_Type);
    writeIni->setValue("/Render/HardwareTimer",configRender.hardware_Timer );
    writeIni->setValue("/Render/GenerateTopologic", configRender.generate_Topologic);
    writeIni->setValue("/Render/RemainRawBuffer", configRender.remain_Raw_Buffer);
    writeIni->setValue("/Render/LightEnable", configRender.light_Enable);
    writeIni->setValue("/Render/MaxFrameTime", configRender.max_Frame_Time);
    writeIni->setValue("/Render/DebugMode", configRender.debug_Mode);
    writeIni->setValue("/Render/TerrainRenderMode", configRender.terrain_Render_Mode);
    writeIni->setValue("/Render/UpdateInterval", configRender.update_Interval);

    GWConfigResource configRes = configParas.gwConfigResource;
    writeIni->setValue("/Resource/MaxMemorySize", configRes.max_Memory_Size);
    writeIni->setValue("/Resource/MaxLifeTime", configRes.max_Life_Time);
    writeIni->setValue("/Resource/MaxTexSizePerBatch", configRes.max_Tex_Size_Per_Batch);
    writeIni->setValue("/Resource/MaxMeshSizePerBatch", configRes.max_Mesh_Size_Per_Batch);
    writeIni->setValue("/Resource/MaxTexCountPerBatch", configRes.max_Tex_Count_Per_Batch);
    writeIni->setValue("/Resource/MaxMeshCountPerBatch", configRes.max_Mesh_Count_Per_Batch);
    writeIni->setValue("/Resource/MaxTerrainCountPerBatch", configRes.max_Terrain_Count_Per_Batch);
    writeIni->setValue("/Resource/MaxReclaimMemoryPerFrame", configRes.max_Reclaim_Memory_Per_Frame);

    GWConfigBuilding configBuild = configParas.gwConfigBuilding;
    writeIni->setValue("/Building/MaxVisRange", configBuild.max_Vis_Range);;
    writeIni->setValue("/Building/MinVisRange", configBuild.min_Vis_Range);
    writeIni->setValue("/Building/NewBuilding", configBuild.new_Building);
    writeIni->setValue("/Building/TransparentColor", configBuild.transparent_Color);
    writeIni->setValue("/Building/TransparentColor2", configBuild.transparent_Color2);
    writeIni->setValue("/Building/MaxVisibleHeight", configBuild.max_Visible_Height);
    writeIni->setValue("/Building/TransparentBegin", configBuild.transparent_Begin);
    writeIni->setValue("/Building/TransparentEnd", configBuild.transparent_End);
    writeIni->setValue("/Building/MaterialLevels", configBuild.material_Levels);
    writeIni->setValue("/Building/TextureBias",configBuild.texture_Bias );
    writeIni->setValue("/Building/ModelRenderBios", configBuild.model_Render_Bios);
    writeIni->setValue("/Building/LodSecDistance", configBuild.lod_Sec_Distance);
    writeIni->setValue("/Building/UseDefaultTexture", configBuild.use_Default_Texture);

    GWConfigLink configLink = configParas.gwConfigLink;
    writeIni->setValue("/Link/ResFolder", configLink.res_Folder);
    writeIni->setValue("/Link/Connection", configLink.connection);
    writeIni->setValue("/Link/RoleResConnection", configLink.role_Res_Connection);
    writeIni->setValue("/Link/AIServer", configLink.AI_Server);
    writeIni->setValue("/Link/AIServerPort", configLink.AI_Server_Port);
    writeIni->setValue("/Link/LicenseServer", configLink.license_Server);
    writeIni->setValue("/Link/PipelineServer", configLink.pipeline_Server);
    writeIni->setValue("/Link/DebugLogPath", configLink.debug_Log_Path);

    GWConfigRole configRole = configParas.gwConfigRole;
    writeIni->setValue("/Role/RoleWalkVolocity", configRole.role_Walk_Volocity);
    writeIni->setValue("/Role/RoleRunVolocity", configRole.role_Run_Volocity);
    writeIni->setValue("/Role/UnderGroundMode", configRole.underGround_Mode);

    GWConfigBrowse configBrowse = configParas.gwConfigBrowse;
    writeIni->setValue("/Browse/ZoomCenter", configBrowse.zoom_Center);
    writeIni->setValue("/Browse/EnableFly", configBrowse.enable_Fly);

    GWConfigGui configGui = configParas.gwConfigGui;
    writeIni->setValue("/Gui/ShowNavigator", configGui.show_Navigator);
    writeIni->setValue("/Gui/ShowLogo", configGui.show_Logo);
    writeIni->setValue("/Gui/ShowInformation", configGui.show_Information);
    writeIni->setValue("/Gui/InformationLanguage", configGui.information_Language);

    delete writeIni;
    writeIni = NULL;
    return true;
}

/*
 * Function      :SetDefaultConfigPath
 * Description:设置默认配置文件路径
 * Parameters  :
 * Return          :bool true-设置路径正确，false-设置路径失败
 */
bool MainConfigWnd::SetDefaultConfigPath()
{
    QDir currPath = qApp->applicationDirPath();
    QString dirString = currPath.dirName();
    QString parentPath = currPath.currentPath();
    bool ok = parentPath.endsWith(dirString);
    if(ok) {
        dirString = "/" + dirString;
        parentPath = parentPath.left(parentPath.size() - dirString.size());
    }
    currPath = parentPath;
    QString absPath = currPath.absolutePath() + "/config.ini";
    QFile currFile( absPath);
    if(currFile.exists()) {
        mFileName = absPath;
        ui->CurrentPathEdit->setText(absPath);
        initialize();
        return true;
    } else {
        return false;
    }
}

/*
 * Function      :initialize
 * Description:界面配置初始化
 * Parameters  :
 * Return          :
 */
void MainConfigWnd::initialize()
{
    if(ReadConfigFileContent()) {
        WriteCommonConfig();
        WriteRecommendConfig();
        WriteHigherConfig();
    }
}

/*
 * Function      :ReadCommonConfig
 * Description:读取常用配置内容
 * Parameters  :
 * Return          :
 */
void MainConfigWnd::ReadCommonConfig()
{
    m_configParas.gwConfigNetwork.download_Sleep_Time = ui->downloadSleepTime1Edit->text();
    m_configParas.gwConfigNetwork.download_Sleep_Interval = ui->downloadSleepInterval1Edit->text();
    m_configParas.gwConfigNetwork.download_Thread_Count = ui->downloadThreadCount1Edit->text();
    m_configParas.gwConfigResource.max_Memory_Size = ui->maxMemorySize1Edit->text();
    m_configParas.gwConfigResource.max_Life_Time = ui->maxLifeTime1Edit->text();
    m_configParas.gwConfigResource.max_Reclaim_Memory_Per_Frame = ui->maxReclaimMemoryPerFrame1Edit->text();
    m_configParas.gwConfigRender.computer_Performance = ui->computerPerformance1Edit->text();
    int debugIndex = ui->debugModel1ComboBox->currentIndex();
    m_configParas.gwConfigRender.debug_Mode = QString("%1").arg(debugIndex);
    int lightIndex = ui->lightEnable1ComboBox->currentIndex();
    m_configParas.gwConfigRender.light_Enable = QString("%1").arg(lightIndex);
    m_configParas.gwConfigBuilding.max_Visible_Height = ui->maxVisibleHeight1Edit->text();
    int useDefaultIndex = ui->useDefaultTexture1ComboBox->currentIndex();
    m_configParas.gwConfigBuilding.use_Default_Texture = QString("%1").arg(useDefaultIndex);
    int zoomIndex = ui->zoomCenter1ComboBox->currentIndex();
    m_configParas.gwConfigBrowse.zoom_Center = QString("%1").arg(zoomIndex);
    int enableFlyIndex = ui->enableFly1ComboBox->currentIndex();
    m_configParas.gwConfigBrowse.enable_Fly = QString("%1").arg(enableFlyIndex);
    int showNavIndex = ui->showNavigator1ComboBox->currentIndex();
    m_configParas.gwConfigGui.show_Navigator = QString("%1").arg(showNavIndex);
    int showLogoIndex = ui->showLogo1ComboBox->currentIndex();
    m_configParas.gwConfigGui.show_Logo = QString("%1").arg(showLogoIndex);
    int showInfoIndex = ui->showInformation1ComboBox->currentIndex();
    m_configParas.gwConfigGui.show_Information = QString("%1").arg(showInfoIndex);
    int infoLanIndex = ui->informationLanguage1ComboBox->currentIndex();
    m_configParas.gwConfigGui.information_Language = QString("%1").arg(infoLanIndex);
}

/*
 * Function      :ReadRecommendConfig
 * Description:读取推荐配置内容
 * Parameters  :
 * Return          :
 */
void MainConfigWnd::ReadRecommendConfig()
{
    m_configParas.gwConfigNetwork.download_Sleep_Time = ui->downloadSleepTimeEdit->text();
    m_configParas.gwConfigNetwork.download_Sleep_Interval = ui->downloadSleepIntervalEdit->text();
    m_configParas.gwConfigNetwork.download_Thread_Count = ui->downloadThreadCountEdit->text();

    m_configParas.gwConfigResource.max_Memory_Size = ui->maxMemorySizeEdit->text();
    m_configParas.gwConfigResource.max_Life_Time = ui->maxLifeTimeEdit->text();
    m_configParas.gwConfigResource.max_Tex_Size_Per_Batch = ui->maxTexSizePerBatchEdit->text();
    m_configParas.gwConfigResource.max_Mesh_Size_Per_Batch = ui->maxMeshSizePerBatchEdit->text();
    m_configParas.gwConfigResource.max_Tex_Count_Per_Batch = ui->maxTexCountPerBatchEdit->text();
    m_configParas.gwConfigResource.max_Mesh_Count_Per_Batch = ui->maxMeshCountPerBatchEdit->text();
    m_configParas.gwConfigResource.max_Terrain_Count_Per_Batch = ui->maxTerrianCountPerBatchEdit->text();
    m_configParas.gwConfigResource.max_Reclaim_Memory_Per_Frame = ui->maxReclaimMemoryPerFrameEdit->text();

    m_configParas.gwConfigRender.max_FPS = ui->maxFPSEdit->text();
    m_configParas.gwConfigRender.computer_Performance = ui->computerPerformanceEdit->text();
    m_configParas.gwConfigRender.multi_Sample_Type = ui->mutilSampleTypeEdit->text();
    int hardIndex = ui->hardwareTimerComboBox->currentIndex();
    m_configParas.gwConfigRender.hardware_Timer = QString("%1").arg(hardIndex);
    int generateIndex = ui->generateTopologicComboBox->currentIndex();
    m_configParas.gwConfigRender.generate_Topologic = QString("%1").arg(generateIndex);
    int remainIndex = ui->remainRawBufferComboBox->currentIndex();
    m_configParas.gwConfigRender.remain_Raw_Buffer = QString("%1").arg(remainIndex);
    int lightIndex = ui->lightEnableComboBox->currentIndex();
    m_configParas.gwConfigRender.light_Enable = QString("%1").arg(lightIndex);
    m_configParas.gwConfigRender.max_Frame_Time = ui->maxFrameTimeEdit->text();
    int debugIndex = ui->debugModeComboBox->currentIndex();
    m_configParas.gwConfigRender.debug_Mode = QString("%1").arg(debugIndex);
    int terrainIndex = ui->terrainRenderModeComboBox->currentIndex();
    m_configParas.gwConfigRender.terrain_Render_Mode = QString("%1").arg(terrainIndex);
    m_configParas.gwConfigRender.update_Interval = ui->updateIntervalEdit->text();

    m_configParas.gwConfigBuilding.max_Vis_Range = ui->maxVisRangeEdit->text();
    m_configParas.gwConfigBuilding.min_Vis_Range = ui->minVisRangeEdit->text();
    int newBuildIndex = ui->newBuildingComboBox->currentIndex();
    m_configParas.gwConfigBuilding.new_Building = QString("%1").arg(newBuildIndex);
    m_configParas.gwConfigBuilding.transparent_Color = ui->transparentColorEdit->text();
    m_configParas.gwConfigBuilding.transparent_Color2 = ui->transparentColor2Edit->text();
    m_configParas.gwConfigBuilding.max_Visible_Height = ui->maxVisibleHeightEdit->text();
    m_configParas.gwConfigBuilding.transparent_Begin = ui->transparentBeginEdit->text();
    m_configParas.gwConfigBuilding.transparent_End = ui->transparentEndEdit->text();
    m_configParas.gwConfigBuilding.material_Levels = ui->materialLevelsEdit->text();
    m_configParas.gwConfigBuilding.texture_Bias = ui->textureBiasEdit->text();
    m_configParas.gwConfigBuilding.model_Render_Bios = ui->modelRenderBiosEdit->text();
    m_configParas.gwConfigBuilding.lod_Sec_Distance = ui->lodSecDistanceEdit->text();
    int useDefaultIndex = ui->useDefaultTextureComboBox->currentIndex();
    m_configParas.gwConfigBuilding.use_Default_Texture = QString("%1").arg(useDefaultIndex);

    m_configParas.gwConfigLink.res_Folder = ui->resFolderEdit->text();
    m_configParas.gwConfigLink.connection = ui->connectionEdit->text();
    m_configParas.gwConfigLink.role_Res_Connection = ui->roleResConnectionEdit->text();
    m_configParas.gwConfigLink.AI_Server = ui->AIServerEdit->text();
    m_configParas.gwConfigLink.AI_Server_Port = ui->AIServerPortEdit->text();
    m_configParas.gwConfigLink.license_Server = ui->licenseServerEdit->text();
    m_configParas.gwConfigLink.pipeline_Server = ui->pipelineServerEdit->text();
    m_configParas.gwConfigLink.debug_Log_Path = ui->debugLogPathEdit->text();

    m_configParas.gwConfigRole.role_Walk_Volocity = ui->roleWalkVolocityEdit->text();
    m_configParas.gwConfigRole.role_Run_Volocity = ui->roleRunVolocityEdit->text();
    int underGrIndex = ui->underGroundModeComboBox->currentIndex();
    m_configParas.gwConfigRole.underGround_Mode = QString("%1").arg(underGrIndex);

    int zoomIndex = ui->zoomCenterComboBox->currentIndex();
    m_configParas.gwConfigBrowse.zoom_Center = QString("%1").arg(zoomIndex);
    int enableFlyIndex = ui->enableFlyComboBox->currentIndex();
    m_configParas.gwConfigBrowse.enable_Fly = QString("%1").arg(enableFlyIndex);

    int showNavIndex = ui->showNavigatorComboBox->currentIndex();
    m_configParas.gwConfigGui.show_Navigator = QString("%1").arg(showNavIndex);
    int showLoIndex = ui->showLogoComboBox->currentIndex();
    m_configParas.gwConfigGui.show_Logo =  QString("%1").arg(showLoIndex);
    int showInfoIndex = ui->showInformationComboBox->currentIndex();
    m_configParas.gwConfigGui.show_Information = QString("%1").arg(showInfoIndex);
    int infoLanIndex = ui->informationLanguageComboBox->currentIndex();
    m_configParas.gwConfigGui.information_Language = QString("%1").arg(infoLanIndex);
}

/*
 * Function      :ReadHigherConfig
 * Description:读取高级配置内容
 * Parameters  :
 * Return          :
 */
void MainConfigWnd::ReadHigherConfig()
{
    m_configParas.gwConfigRender.computer_Performance = ui->computerPerformance2Edit->text();
    m_configParas.gwConfigNetwork.download_Sleep_Time = ui->downloadSleepTime2Edit->text();
    m_configParas.gwConfigNetwork.download_Sleep_Interval = ui->downloadSleepInterval2Edit->text();
    m_configParas.gwConfigNetwork.download_Thread_Count = ui->downloadThreadCount2Edit->text();
    m_configParas.gwConfigResource.max_Life_Time = ui->maxLifeTime2Edit->text();
    m_configParas.gwConfigRender.max_Frame_Time = ui->maxFrameTime2Edit->text();
    m_configParas.gwConfigRender.update_Interval = ui->updateInterval2Edit->text();
}

/*
 * Function      :WriteCommonConfig
 * Description:写常用配置内容
 * Parameters  :
 * Return          :
 */
void MainConfigWnd::WriteCommonConfig()
{
    ui->downloadSleepTime1Edit->setText(m_configParas.gwConfigNetwork.download_Sleep_Time);
    ui->downloadSleepInterval1Edit->setText(m_configParas.gwConfigNetwork.download_Sleep_Interval);
    ui->downloadThreadCount1Edit->setText(m_configParas.gwConfigNetwork.download_Thread_Count);
    ui->maxMemorySize1Edit->setText(m_configParas.gwConfigResource.max_Memory_Size);
    ui->maxLifeTime1Edit->setText(m_configParas.gwConfigResource.max_Life_Time);
    ui->maxReclaimMemoryPerFrame1Edit->setText(m_configParas.gwConfigResource.max_Reclaim_Memory_Per_Frame);
    ui->computerPerformance1Edit->setText(m_configParas.gwConfigRender.computer_Performance);
    int debugModeIndex = m_configParas.gwConfigRender.debug_Mode.toInt();
    ui->debugModel1ComboBox->setCurrentIndex(debugModeIndex);
    int lightIndex = m_configParas.gwConfigRender.light_Enable.toInt();
    ui->lightEnable1ComboBox->setCurrentIndex(lightIndex);
    ui->maxVisibleHeight1Edit->setText(m_configParas.gwConfigBuilding.max_Visible_Height);
    int useDefaultIndex = m_configParas.gwConfigBuilding.use_Default_Texture.toInt();
    ui->useDefaultTexture1ComboBox->setCurrentIndex(useDefaultIndex);
    int zoomIndex = m_configParas.gwConfigBrowse.zoom_Center.toInt();
    ui->zoomCenter1ComboBox->setCurrentIndex(zoomIndex);
    int enableFlyIndex = m_configParas.gwConfigBrowse.enable_Fly.toInt();
    ui->enableFly1ComboBox->setCurrentIndex(enableFlyIndex);
    int showNavIndex = m_configParas.gwConfigGui.show_Navigator.toInt();
    ui->showNavigator1ComboBox->setCurrentIndex(showNavIndex);
    int showLogoIndex = m_configParas.gwConfigGui.show_Logo.toInt();
    ui->showLogo1ComboBox->setCurrentIndex(showLogoIndex);
    int showInfoIndex = m_configParas.gwConfigGui.show_Information.toInt();
    ui->showInformation1ComboBox->setCurrentIndex(showInfoIndex);
    int infoLanIndex = m_configParas.gwConfigGui.information_Language.toInt();
    ui->informationLanguage1ComboBox->setCurrentIndex(infoLanIndex);
}

/*
 * Function      :WriteRecommendConfig
 * Description:写推荐配置内容
 * Parameters  :
 * Return          :
 */
void MainConfigWnd::WriteRecommendConfig()
{
    //Network parameters init
    ui->downloadSleepTimeEdit->setText(m_configParas.gwConfigNetwork.download_Sleep_Time);
    ui->downloadSleepIntervalEdit->setText(m_configParas.gwConfigNetwork.download_Sleep_Interval);
    ui->downloadThreadCountEdit->setText(m_configParas.gwConfigNetwork.download_Thread_Count);
    //Resource parameters init
    ui->maxMemorySizeEdit->setText(m_configParas.gwConfigResource.max_Memory_Size);
    ui->maxLifeTimeEdit->setText(m_configParas.gwConfigResource.max_Life_Time);
    ui->maxTexSizePerBatchEdit->setText(m_configParas.gwConfigResource.max_Tex_Size_Per_Batch);
    ui->maxMeshSizePerBatchEdit->setText(m_configParas.gwConfigResource.max_Mesh_Size_Per_Batch);
    ui->maxTexCountPerBatchEdit->setText(m_configParas.gwConfigResource.max_Tex_Count_Per_Batch);
    ui->maxMeshCountPerBatchEdit->setText(m_configParas.gwConfigResource.max_Mesh_Count_Per_Batch);
    ui->maxTerrianCountPerBatchEdit->setText(m_configParas.gwConfigResource.max_Terrain_Count_Per_Batch);
    ui->maxReclaimMemoryPerFrameEdit->setText(m_configParas.gwConfigResource.max_Reclaim_Memory_Per_Frame);
    //Render parameters init
    ui->maxFPSEdit->setText(m_configParas.gwConfigRender.max_FPS);
    ui->computerPerformanceEdit->setText(m_configParas.gwConfigRender.computer_Performance);
    ui->mutilSampleTypeEdit->setText(m_configParas.gwConfigRender.multi_Sample_Type);
    int hardIndex = m_configParas.gwConfigRender.hardware_Timer.toInt();
    ui->hardwareTimerComboBox->setCurrentIndex(hardIndex);
    int geneateIndex = m_configParas.gwConfigRender.generate_Topologic.toInt();
    ui->generateTopologicComboBox->setCurrentIndex(geneateIndex);
    int remainIndex = m_configParas.gwConfigRender.remain_Raw_Buffer.toInt();
    ui->remainRawBufferComboBox->setCurrentIndex(remainIndex);
    int lightIndex = m_configParas.gwConfigRender.light_Enable.toInt();
    ui->lightEnableComboBox->setCurrentIndex(lightIndex);
    ui->maxFrameTimeEdit->setText(m_configParas.gwConfigRender.max_Frame_Time);
    int debugIndex = m_configParas.gwConfigRender.debug_Mode.toInt();
    ui->debugModeComboBox->setCurrentIndex(debugIndex);
    int terrainIndex = m_configParas.gwConfigRender.terrain_Render_Mode.toInt();
    ui->terrainRenderModeComboBox->setCurrentIndex(terrainIndex);
    ui->updateIntervalEdit->setText(m_configParas.gwConfigRender.update_Interval);
    //Building parameters init
    ui->maxVisRangeEdit->setText(m_configParas.gwConfigBuilding.max_Vis_Range);
    ui->minVisRangeEdit->setText(m_configParas.gwConfigBuilding.min_Vis_Range);
    int newBuildIndex = m_configParas.gwConfigBuilding.new_Building.toInt();
    ui->newBuildingComboBox->setCurrentIndex(newBuildIndex);
    ui->transparentColorEdit->setText(m_configParas.gwConfigBuilding.transparent_Color);
    ui->transparentColor2Edit->setText(m_configParas.gwConfigBuilding.transparent_Color2);
    ui->maxVisibleHeightEdit->setText(m_configParas.gwConfigBuilding.max_Visible_Height);
    ui->transparentBeginEdit->setText(m_configParas.gwConfigBuilding.transparent_Begin);
    ui->transparentEndEdit->setText(m_configParas.gwConfigBuilding.transparent_End);
    ui->materialLevelsEdit->setText(m_configParas.gwConfigBuilding.material_Levels);
    ui->textureBiasEdit->setText(m_configParas.gwConfigBuilding.texture_Bias);
    ui->modelRenderBiosEdit->setText(m_configParas.gwConfigBuilding.model_Render_Bios);
    ui->lodSecDistanceEdit->setText(m_configParas.gwConfigBuilding.lod_Sec_Distance);
    int useDefaultIndex = m_configParas.gwConfigBuilding.use_Default_Texture.toInt();
    ui->useDefaultTextureComboBox->setCurrentIndex(useDefaultIndex);
    //Link  parameters init
    ui->resFolderEdit->setText(m_configParas.gwConfigLink.res_Folder);
    ui->connectionEdit->setText(m_configParas.gwConfigLink.connection);
    ui->roleResConnectionEdit->setText(m_configParas.gwConfigLink.role_Res_Connection);
    ui->AIServerEdit->setText(m_configParas.gwConfigLink.AI_Server);
    ui->AIServerPortEdit->setText(m_configParas.gwConfigLink.AI_Server_Port);
    ui->licenseServerEdit->setText(m_configParas.gwConfigLink.license_Server);
    ui->pipelineServerEdit->setText(m_configParas.gwConfigLink.pipeline_Server);
    ui->debugLogPathEdit->setText(m_configParas.gwConfigLink.debug_Log_Path);
    //Role parameters init
    ui->roleWalkVolocityEdit->setText(m_configParas.gwConfigRole.role_Walk_Volocity);
    ui->roleRunVolocityEdit->setText(m_configParas.gwConfigRole.role_Run_Volocity);
    int underGrdIndex = m_configParas.gwConfigRole.underGround_Mode.toInt();
    ui->underGroundModeComboBox->setCurrentIndex(underGrdIndex);
    //Browse parameters init
    int zoomIndex = m_configParas.gwConfigBrowse.zoom_Center.toInt();
    ui->zoomCenterComboBox->setCurrentIndex(zoomIndex);
    int enableFlyIndex = m_configParas.gwConfigBrowse.enable_Fly.toInt();
    ui->enableFlyComboBox->setCurrentIndex(enableFlyIndex);
    //Gui parameters init
    int showNavIndex = m_configParas.gwConfigGui.show_Navigator.toInt();
    ui->showNavigatorComboBox->setCurrentIndex(showNavIndex);
    int showLogoIndex = m_configParas.gwConfigGui.show_Logo.toInt();
    ui->showLogoComboBox->setCurrentIndex(showLogoIndex);
    int showInfoIndex = m_configParas.gwConfigGui.show_Information.toInt();
    ui->showInformationComboBox->setCurrentIndex(showInfoIndex);
    int infoLanIndex = m_configParas.gwConfigGui.information_Language.toInt();
    ui->informationLanguageComboBox->setCurrentIndex(infoLanIndex);
}

/*
 * Function      :WriteHigherConfig
 * Description:写高级配置内容
 * Parameters  :
 * Return          :
 */
void MainConfigWnd::WriteHigherConfig()
{
    SYSTEM_INFO systemInfo;
    GetSystemInfo(&systemInfo);
//    qDebug() << QStringLiteral("处理器掩码:       " )  << systemInfo.dwActiveProcessorMask;
//    qDebug() << QStringLiteral("处理器个数:       " )  << systemInfo.dwNumberOfProcessors;
//    qDebug() << QStringLiteral("处理器分页大小:" ) << systemInfo.dwPageSize;
//    qDebug() << QStringLiteral("处理器类型:        " ) << systemInfo.dwProcessorType;
//    qDebug() << QStringLiteral("最大寻址单元:    " ) << systemInfo.lpMaximumApplicationAddress;
//    qDebug() << QStringLiteral("最小寻址单元:    " ) << systemInfo.lpMinimumApplicationAddress;
//    qDebug() << QStringLiteral("处理器等级:        " ) << systemInfo.wProcessorLevel;
//    qDebug() << QStringLiteral("处理器版本:        " ) << systemInfo.wProcessorRevision;
    ui->processorNumberEdit->setText(QString("%1").arg(systemInfo.dwNumberOfProcessors));
    const long int MB = 1024 * 1024;
    MEMORYSTATUSEX statusex;
    statusex.dwLength = sizeof(statusex);
    GlobalMemoryStatusEx(&statusex);
//    qDebug() << QStringLiteral("物理内存使用率:           ") << statusex.dwMemoryLoad;
//    qDebug() << QStringLiteral("物理内存总量:               ") << statusex.ullTotalPhys/MB;
//    qDebug() << QStringLiteral("可用的物理内存:           ") << statusex.ullAvailPhys/MB;
//    qDebug() << QStringLiteral("系统页面文件大小:       ") << statusex.ullTotalPageFile/MB;
//    qDebug() << QStringLiteral("系统可用页面文件大小:") << statusex.ullAvailPageFile/MB;
//    qDebug() << QStringLiteral("虚拟内存总量:               ") << statusex.ullTotalVirtual/MB;
//    qDebug() << QStringLiteral("可用的虚拟内存:           ") << statusex.ullAvailVirtual/MB;
//    qDebug() << QStringLiteral("保留（值为0）:             ") << statusex.ullAvailExtendedVirtual/MB;
    ui->availablePhysicalMemoryEdit->setText(QString("%1").arg(statusex.ullAvailPhys/(MB*1024)));
    ui->MemoryLoadEdit->setText(QString("%1").arg(statusex.dwMemoryLoad));
    ui->TotalPhysEdit->setText(QString("%1").arg(statusex.ullTotalPhys/MB));

    ui->computerPerformance2Edit->setText(m_configParas.gwConfigRender.computer_Performance);
    ui->downloadSleepTime2Edit->setText(m_configParas.gwConfigNetwork.download_Sleep_Time);
    ui->downloadSleepInterval2Edit->setText(m_configParas.gwConfigNetwork.download_Sleep_Interval);
    ui->downloadThreadCount2Edit->setText(m_configParas.gwConfigNetwork.download_Thread_Count);
    ui->maxLifeTime2Edit->setText(m_configParas.gwConfigResource.max_Life_Time);
    ui->maxFrameTime2Edit->setText(m_configParas.gwConfigRender.max_Frame_Time);
    ui->updateInterval2Edit->setText(m_configParas.gwConfigRender.update_Interval);
}

void MainConfigWnd::on_SelectFileBtn_clicked()
{
    OpenConfigFilePath();
    initialize();
}

void MainConfigWnd::on_configApplyBtn_clicked()
{
    ReadRecommendConfig();
    if(enableCommonConfig) {
        ReadCommonConfig();
        enableCommonConfig = false;
    }
    if(enableHigherConfig) {
        ReadHigherConfig();
        enableHigherConfig = false;
    }
    if(WriteConfigFileContent()) {
        isConfigApply = true;
    }
}

void MainConfigWnd::on_configCancelBtn_clicked()
{
    this->close();
}

void MainConfigWnd::on_configOKBtn_clicked()
{
    if(!isConfigApply) {
        on_configApplyBtn_clicked();
    }
    this->close();
}

void MainConfigWnd::on_enableHigherConfigBtn_clicked()
{
    enableHigherConfig = true;
}

void MainConfigWnd::on_enableCommonConfigBtn_clicked()
{
    enableCommonConfig = true;
}

/*
 * Function      :GetConfigParasList
 * Description:获取配置参数清单
 * Parameters  :
 * Return          :gw::GWConfigParas-配置参数清单内容
 */
gw::GWConfigParas MainConfigWnd::GetConfigParasList()
{
    return m_configParas;
}
