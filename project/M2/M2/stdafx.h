// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <cstdio>
#include <windows.h>


// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�

// ϵͳͷ�ļ�
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
#using "C:\�����ļ�\��Ŀ�ļ�\һЩС����\M2\bin\Z_MailLib.dll"
using namespace Z_SendMailLib;
using namespace System;

// ����ͷ�ļ�
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



// using ����
using namespace M2;

// ���������
#pragma comment(lib,"winmm.lib")

// ��������
int ConsoleApplicationMain(int _argc, char *_argv[]);
HANDLE GetConsoleOutputHandle();