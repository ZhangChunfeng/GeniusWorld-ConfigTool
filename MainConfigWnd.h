#ifndef MAINCONFIGWND_H
#define MAINCONFIGWND_H

#include <QMainWindow>
#include <QSettings>
#include <QDebug>

#include "base.h"
#include "BubbleForm.h"
#include "Windows.h"

namespace Ui {
class MainConfigWnd;
}

class MainConfigWnd : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainConfigWnd(QWidget *parent = 0);
    ~MainConfigWnd();

    /*******选择配置文件路径*********/
    bool OpenConfigFilePath();
    /*****读取配置文件内容***********/
    bool ReadConfigFileContent();
    /*******写配置文件内容**********/
    bool WriteConfigFileContent();

private:
    /*****设置默认配置文件路径******/
    bool SetDefaultConfigPath();
    /*****界面配置初始化***********/
    void initialize();
    /********读取常用配置*********/
    void ReadCommonConfig();
    /********读取推荐配置*********/
    void ReadRecommendConfig();
    /********读取高级配置*********/
    void ReadHigherConfig();
    /********写进常用配置*********/
    void WriteCommonConfig();
    /********写进常用配置*********/
    void WriteRecommendConfig();
    /********写进常用配置*********/
    void WriteHigherConfig();

private slots:
    void on_SelectFileBtn_clicked();
    void on_configApplyBtn_clicked();
    void on_configCancelBtn_clicked();
    void on_configOKBtn_clicked();
    void on_enableHigherConfigBtn_clicked();
    void on_enableCommonConfigBtn_clicked();

public:
    /********获取配置参数清单*********/
    gw::GWConfigParas GetConfigParasList();

private:
    Ui::MainConfigWnd *ui;
    gw::GWConfigParas m_configParas;
    bool isConfigApply;
    bool enableHigherConfig;
    bool enableCommonConfig;
    QString  mFileName;

};

#endif // MAINCONFIGWND_H
