#ifndef BASE_H
#define BASE_H

#include <QString>

namespace gw {
struct GWConfigNetwork
{
    QString download_Sleep_Time;                             //下载等待时间
    QString download_Sleep_Interval;                     //下载等待间隔
    QString download_Thread_Count;                         //下载线程数目
};
struct GWConfigResource
{
    QString max_Memory_Size;                                   //限制进程内存大小
    QString max_Life_Time;                                       //资源（纹理、Mesh）的生命周期
    QString max_Tex_Size_Per_Batch;                     //最大纹理创建个数
    QString max_Mesh_Size_Per_Batch;                   //最大MESH创建个数
    QString max_Tex_Count_Per_Batch;                   //DOM数据
    QString max_Mesh_Count_Per_Batch;                 //创建MESH的个数
    QString max_Terrain_Count_Per_Batch;           //DEM数据
    QString max_Reclaim_Memory_Per_Frame;         //每一帧卸载内存大小
};
struct GWConfigRender
{
    QString max_FPS;                                                 //最大时间间隔
    QString computer_Performance;                       //模型性能高低中，模型的三种显示效果low、normal、high
    QString multi_Sample_Type;                             //多重采样类型
    QString hardware_Timer;                                   //定时器类型  0:WM_TIMER,1:HANDWARE_TIMER
    QString generate_Topologic;                           //usm数据有无拓扑结构
    QString remain_Raw_Buffer;                             //是否保留缓存
    QString light_Enable;                                      //是否开启灯光
    QString max_Frame_Time;                                   //每一帧渲染时间限制
    QString debug_Mode;                                           //显示小信息
    QString terrain_Render_Mode;                         //DEM渲染模式，0显示面，1显示网格
    QString update_Interval;                                 //更新时间限制，时间大则更新慢
};
struct GWConfigBuilding
{
    QString max_Vis_Range;                                    //建筑物最大可视范围
    QString min_Vis_Range;                                    //建筑物最小可视范围
    QString new_Building;                                      //与建筑物的阴影有无关系 1:考虑了光照
    QString transparent_Color;                            //透明的颜色1
    QString transparent_Color2;                          //透明的颜色2
    QString max_Visible_Height;                          //最大可视高度
    QString transparent_Begin;                            //透明起始值
    QString transparent_End;                                //透明终止值
    QString material_Levels;                                //材料水平
    QString texture_Bias;                                      //代码中无此项，只在config看到
    QString model_Render_Bios;                            //模型渲染
    QString lod_Sec_Distance;                              //模型第二级LOD显示距离
    QString use_Default_Texture;                        //是否默认纹理
};
struct GWConfigLink
{
    QString res_Folder;                                       //res的文件夹相对路径
    QString connection;                                       //连接的data.xml路径
    QString role_Res_Connection;                     //角色资源的连接路径
    QString AI_Server;                                         //服务器IP
    QString AI_Server_Port;                               //服务器端口号
    QString license_Server;                              //服务的license
    QString pipeline_Server;                            //服务licenseServer是否可用,实际中没用到
    QString debug_Log_Path;                              //日志路径
};
struct GWConfigRole
{
    QString role_Walk_Volocity;                     //角色走的速度
    QString role_Run_Volocity;                       //角色跑的速度
    QString underGround_Mode;                         //地下模式
};
struct GWConfigBrowse
{
    QString zoom_Center;                                 //是否显示中心点
    QString enable_Fly;                                   //是否允许飞行
};
struct GWConfigGui
{
    QString show_Navigator;                          //是否导航
    QString show_Logo;                                    //是否显示logo
    QString show_Information;                     //是否显示进度条
    QString information_Language;             //0：英文，1：中文
};
struct GWConfigParas
{
    GWConfigNetwork gwConfigNetwork;
    GWConfigResource gwConfigResource;
    GWConfigRender gwConfigRender;
    GWConfigBuilding gwConfigBuilding;
    GWConfigLink gwConfigLink;
    GWConfigRole gwConfigRole;
    GWConfigBrowse gwConfigBrowse;
    GWConfigGui gwConfigGui;
};
/*
 *Function       :NotEqualAndCopy
 *Description:判断两个字符串是否相等，不相等则复制
 *Parameters  :sSour-源字符串，sDes-目的字符串
 * Return:      :
 */
inline void NotEqualAndCopy(QString sSour, QString sDes)
{
    if(sSour != sDes) {
        sSour = sDes;
    }
}
}

#endif // BASE_H
