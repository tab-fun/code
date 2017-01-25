// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <cstdio>
#include <windows.h>


// TODO:  在此处引用程序需要的其他头文件

// 系统头文件
#include <conio.h>
#include <Windows.h>
#include <mmsystem.h>

#include <iostream>
#include <string>
#include <list>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include <memory>
#include <bass.h>
using namespace std;
#using "C:\外来文件\项目文件\一些小程序\M2\bin\Z_MailLib.dll"
using namespace Z_SendMailLib;
using namespace System;

// 本地头文件
#include "Music.h"
#include "ZException.h"
#include "WindowDataSourceInterface.h"
#include "EventInterface.h"
#include "MenuSettingControllerDelegate.h"

#include "xml\tinyxml.h"

#include "Others.h"
#include "ZObject.h"

#include "Controller.h"
#include "GameController.h"
#include "MainController.h"
#include "MenuController.h"

#include "ZView.h"
#include "ZWindow.h"
#include "MenuView.h"
#include "GameView.h"
#include "MenuItemView.h"
#include "GameSceneView.h"
#include "GameItemView.h"

#include "Data.h"
#include "WindowData.h"
#include "MenuData.h"
#include "GameData.h"



// using 声明
using namespace M2;

// 添加依赖库
#pragma comment(lib,"winmm.lib")

// 函数声明
int ConsoleApplicationMain(int _argc, char *_argv[]);
HANDLE GetConsoleOutputHandle();