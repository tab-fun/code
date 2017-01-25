#include "stdafx.h"
#include "MenuController.h"

namespace M2
{
	CMenuController::CMenuController()
	{
		if (!m_pGameData)
		{
			m_pGameData = new CGameData;
		}

		m_pMenuView = new CMenuView;
		m_pMenuView->m_title = MENU_ITEM_TITLE_MainMenu;
		m_pMenuView->m_isHaveBorder = true;
		m_pMenuView->m_pDelegate = this;
		m_pMenuView->LoadData();
		

		if (CData::doc.LoadFile())
		{
			auto ele = CData::doc.FirstChildElement("Player")->FirstChildElement("Archives");
			if (ele)
			{
				m_pGameData->m_playerName = ele->Attribute("name");
				m_pGameData->m_progress = stoi(ele->Attribute("progress"));
				ele->Attribute("difficulty", (int *)&m_pGameData->m_difficuty);
				m_userEmailAddress = ele->Attribute("userEmailAddress");
			}

		}
		else
		{
			throw CZException("xml文件加载失败！", nullptr, __LINE__, __FILE__);
		}


		OutputDebugString(_T(">>>>>> CMenuController::CMenuController()：菜单控制器被创建了！\n"));
	}

	void CMenuController::SetPlayerNewName(string _name)
	{
		m_pGameData->m_playerName = _name;
		m_pGameData->m_progress = 0;
		auto player = CData::doc.FirstChildElement("Player");
		auto ele = new TiXmlElement("Archives");
		player->LinkEndChild(ele);
		ele->SetAttribute("name", _name.c_str());
		ele->SetAttribute("difficulty", 0);
		ele->SetAttribute("progress", 0);
		CData::doc.SaveFile();
	}

	CMenuController::~CMenuController()
	{
		if (m_pGameController)
		{
			delete m_pGameController;
			m_pGameController = nullptr;
		}
		OutputDebugString(_T(">>>>>> CMenuController::~CMenuController()：菜单控制器被销毁了！\n"));
	}

	CMenuData CMenuController::LoadMenuData()
	{
		if (CData::doc.LoadFile())
		{
			if (m_pMenuView->m_title == MENU_ITEM_TITLE_MainMenu)
			{
				CMenuData data;
				auto ele = CData::doc.FirstChildElement("ConsoleWindow")->FirstChildElement("MainMenu");
				data.m_title = ele->Attribute("title");
				data.m_rect.point.x = stoi(ele->Attribute("x"));
				data.m_rect.point.y = stoi(ele->Attribute("y"));
				data.m_rect.size.width = stoi(ele->Attribute("width"));
				data.m_rect.size.height = stoi(ele->Attribute("height"));
				data.m_backgroundFillColor = stoi(ele->Attribute("color"));;
				data.m_borderColor = Color::Background_green | black;
				data.m_isHaveBorder = true;
				auto isAddOne = false;
				ele = CData::doc.FirstChildElement("Player")->FirstChildElement("Archives");
				if (ele && stoi(ele->Attribute("progress")) != 0)
				{
					m_pGameData->m_progress = stoi(ele->Attribute("progress"));

					isAddOne = true;
					data.m_rect.size.height += 3;
				}

				ele = CData::doc.FirstChildElement("ConsoleWindow")->FirstChildElement("MainMenu")->FirstChildElement("MenuItem");
				if (!isAddOne)
				{
					ele = ele->NextSiblingElement("MenuItem");
				}
				for (; ele != nullptr; ele = ele->NextSiblingElement("MenuItem"))
				{
					CMenuItemView *itemView = new CMenuItemView;
					itemView->m_title = ele->GetText();
					itemView->m_rect.point.x = stoi(ele->Attribute("x"));
					itemView->m_rect.point.y = stoi(ele->Attribute("y"));
					if (!isAddOne)
					{
						itemView->m_rect.point.y -= 3;
					}
					itemView->m_rect.size.width = stoi(ele->Attribute("width"));
					itemView->m_rect.size.height = stoi(ele->Attribute("height"));
					itemView->m_backgroundFillColor = data.m_backgroundFillColor;
					itemView->m_borderColor = Color::Background_darkWhite | Color::Foreground_red;
					m_pMenuView->AddSubview(itemView);
				}
				return data;
			}
			else if (m_pMenuView->m_title == "查看成就")
			{
				auto ele2 = CData::doc.FirstChildElement("Player")->FirstChildElement("Archives");
				vector<string> vec;
				m_pMenuView->m_looks.clear();
				for (; ele2 != nullptr; ele2 = ele2->NextSiblingElement("Archives"))
				{
					string s = ele2->Attribute("lookScore");
					if (s.empty())
					{
						s = "0 分";
					}
					else
					{
						s += " 分";
					}
					vec.push_back(s);

					s = ele2->Attribute("lookTime");
					if (s.empty())
					{
						s = "0 秒";
					}
					else
					{
						auto i = stoi(s);
						if (i<60)
						{
							s += " 秒";
						}
						else {
							s = to_string(i / 60) + " 分 " + to_string(i % 60) + " 秒";
						}
					}
					vec.push_back(s);

					s = ele2->Attribute("lookAchievements");
					if (s.empty())
					{
						s = "暂无";
					}
					vec.push_back(s);
					m_pMenuView->m_looks.push_back(vec);
					vec.clear();
				}

				CMenuData data;
				auto ele = CData::doc.FirstChildElement("ConsoleWindow")->FirstChildElement("LookAchievement");
				data.m_title = ele->Attribute("title");
				data.m_rect.point.x = stoi(ele->Attribute("x"));
				data.m_rect.point.y = stoi(ele->Attribute("y"));
				data.m_rect.size.width = stoi(ele->Attribute("width"));
				data.m_rect.size.height = stoi(ele->Attribute("height"));
				data.m_backgroundFillColor = stoi(ele->Attribute("color"));
				data.m_isHaveBorder = stoi(ele->Attribute("isHaveBorder"));
				data.m_borderColor = stoi(ele->Attribute("borderColor"));

				return data;
			}
			else if (m_pMenuView->m_title == "向作者反馈")
			{
				CMenuData data;
				auto ele = CData::doc.FirstChildElement("ConsoleWindow")->FirstChildElement("Feedback");
				data.m_title = ele->Attribute("title");
				data.m_rect.point.x = stoi(ele->Attribute("x"));
				data.m_rect.point.y = stoi(ele->Attribute("y"));
				data.m_rect.size.width = stoi(ele->Attribute("width"));
				data.m_rect.size.height = stoi(ele->Attribute("height"));
				data.m_backgroundFillColor = stoi(ele->Attribute("color"));
				data.m_isHaveBorder = stoi(ele->Attribute("isHaveBorder"));
				data.m_borderColor = stoi(ele->Attribute("borderColor"));

				ele = ele->FirstChildElement("MenuItem");
				for (; ele != nullptr; ele = ele->NextSiblingElement("MenuItem"))
				{
					CMenuItemView *itemView = new CMenuItemView;
					itemView->m_title = ele->GetText();
					itemView->m_rect.point.x = stoi(ele->Attribute("x"));
					itemView->m_rect.point.y = stoi(ele->Attribute("y"));
					itemView->m_rect.size.width = stoi(ele->Attribute("width"));
					itemView->m_rect.size.height = stoi(ele->Attribute("height"));
					itemView->m_backgroundFillColor = data.m_backgroundFillColor;
					itemView->m_borderColor = Color::Background_darkWhite | Color::Foreground_red;
					m_pMenuView->AddSubview(itemView);
				}
				return data;
			}
			else if (m_pMenuView->m_title == MENU_ITEM_TITLE_GameSetting)
			{
				CMenuData data;
				auto ele = CData::doc.FirstChildElement("ConsoleWindow")->FirstChildElement("GameSetting");
				data.m_title = ele->Attribute("title");
				data.m_rect.point.x = stoi(ele->Attribute("x"));
				data.m_rect.point.y = stoi(ele->Attribute("y"));
				data.m_rect.size.width = stoi(ele->Attribute("width"));
				data.m_rect.size.height = stoi(ele->Attribute("height"));
				data.m_backgroundFillColor = stoi(ele->Attribute("color"));
				data.m_isHaveBorder = stoi(ele->Attribute("isHaveBorder"));
				data.m_borderColor = stoi(ele->Attribute("borderColor"));

				ele = ele->FirstChildElement("MenuItem");
				for (; ele != nullptr; ele = ele->NextSiblingElement("MenuItem"))
				{
					CMenuItemView *itemView = new CMenuItemView;
					itemView->m_title = ele->GetText();
					itemView->m_rect.point.x = stoi(ele->Attribute("x"));
					itemView->m_rect.point.y = stoi(ele->Attribute("y"));
					itemView->m_rect.size.width = stoi(ele->Attribute("width"));
					itemView->m_rect.size.height = stoi(ele->Attribute("height"));
					itemView->m_backgroundFillColor = data.m_backgroundFillColor;
					itemView->m_borderColor = Color::Background_darkWhite | Color::Foreground_red;
					m_pMenuView->AddSubview(itemView);
				}

				return data;
			}
			else if (m_pMenuView->m_title == MENU_ITEM_TITLE_DifficultySetting)
			{
				CMenuData data;
				auto ele = CData::doc.FirstChildElement("ConsoleWindow")->FirstChildElement("SettingDifficulty");
				data.m_title = ele->Attribute("title");
				data.m_rect.point.x = stoi(ele->Attribute("x"));
				data.m_rect.point.y = stoi(ele->Attribute("y"));
				data.m_rect.size.width = stoi(ele->Attribute("width"));
				data.m_rect.size.height = stoi(ele->Attribute("height"));
				data.m_backgroundFillColor = stoi(ele->Attribute("color"));
				data.m_isHaveBorder = stoi(ele->Attribute("isHaveBorder"));
				data.m_borderColor = stoi(ele->Attribute("borderColor"));

				ele = ele->FirstChildElement("MenuItem");
				for (; ele != nullptr; ele = ele->NextSiblingElement("MenuItem"))
				{
					CMenuItemView *itemView = new CMenuItemView;
					itemView->m_title = ele->GetText();
					itemView->m_rect.point.x = stoi(ele->Attribute("x"));
					itemView->m_rect.point.y = stoi(ele->Attribute("y"));
					itemView->m_rect.size.width = stoi(ele->Attribute("width"));
					itemView->m_rect.size.height = stoi(ele->Attribute("height"));
					itemView->m_backgroundFillColor = data.m_backgroundFillColor;
					itemView->m_borderColor = Color::Background_darkWhite | Color::Foreground_red;
					m_pMenuView->AddSubview(itemView);
				}

				auto p = m_pMenuView->m_subviewsList.begin();
				switch (m_pGameData->m_difficuty)
				{
				case DifficultyEnum::Simple:
					(*p)->m_title += "(已设置)";
					break;
				case DifficultyEnum::General:
					p++;
					(*p)->m_title += "(已设置)";
					break;
				case DifficultyEnum::Hard:
					p++; p++;
					(*p)->m_title += "(已设置)";
					break;
				default:
					break;
				}

				return data;
			}
			else if (m_pMenuView->m_title == MENU_ITEM_TITLE_GameHelp)
			{
				CMenuData data;
				auto ele = CData::doc.FirstChildElement("ConsoleWindow")->FirstChildElement("GameHelp");
				data.m_title = ele->Attribute("title");
				data.m_rect.point.x = stoi(ele->Attribute("x"));
				data.m_rect.point.y = stoi(ele->Attribute("y"));
				data.m_rect.size.width = stoi(ele->Attribute("width"));
				data.m_rect.size.height = stoi(ele->Attribute("height"));
				data.m_backgroundFillColor = stoi(ele->Attribute("color"));
				data.m_isHaveBorder = stoi(ele->Attribute("isHaveBorder"));
				data.m_borderColor = stoi(ele->Attribute("borderColor"));

				ele = ele->FirstChildElement("MenuItem");
				for (; ele != nullptr; ele = ele->NextSiblingElement("MenuItem"))
				{
					CMenuItemView *itemView = new CMenuItemView;
					itemView->m_title = ele->GetText();
					itemView->m_rect.point.x = stoi(ele->Attribute("x"));
					itemView->m_rect.point.y = stoi(ele->Attribute("y"));
					itemView->m_rect.size.width = stoi(ele->Attribute("width"));
					itemView->m_rect.size.height = stoi(ele->Attribute("height"));
					itemView->m_backgroundFillColor = data.m_backgroundFillColor;
					itemView->m_borderColor = Color::Background_darkWhite | Color::Foreground_red;
					m_pMenuView->AddSubview(itemView);
				}

				return data;
			}
			else if (m_pMenuView->m_title == MENU_ITEM_TITLE_HowToPlay)
			{
				CMenuData data;
				auto ele = CData::doc.FirstChildElement("ConsoleWindow")->FirstChildElement("HowToPlay");
				data.m_title = ele->Attribute("title");
				data.m_rect.point.x = stoi(ele->Attribute("x"));
				data.m_rect.point.y = stoi(ele->Attribute("y"));
				data.m_rect.size.width = stoi(ele->Attribute("width"));
				data.m_rect.size.height = stoi(ele->Attribute("height"));
				data.m_backgroundFillColor = stoi(ele->Attribute("color"));
				data.m_isHaveBorder = stoi(ele->Attribute("isHaveBorder"));
				data.m_borderColor = stoi(ele->Attribute("borderColor"));
				data.m_text = ele->GetText();

				return data;
			}
			else if (m_pMenuView->m_title == MENU_ITEM_TITLE_AboutGame)
			{
				CMenuData data;
				auto ele = CData::doc.FirstChildElement("ConsoleWindow")->FirstChildElement("AboutGame");
				data.m_title = ele->Attribute("title");
				data.m_rect.point.x = stoi(ele->Attribute("x"));
				data.m_rect.point.y = stoi(ele->Attribute("y"));
				data.m_rect.size.width = stoi(ele->Attribute("width"));
				data.m_rect.size.height = stoi(ele->Attribute("height"));
				data.m_backgroundFillColor = stoi(ele->Attribute("color"));
				data.m_isHaveBorder = stoi(ele->Attribute("isHaveBorder"));
				data.m_borderColor = stoi(ele->Attribute("borderColor"));
				data.m_text = ele->GetText();

				return data;
			}
			else if (m_pMenuView->m_title == MENU_ITEM_TITLE_ArchiveSetting)
			{
				CMenuData data;
				
				auto ele = CData::doc.FirstChildElement("ConsoleWindow")->FirstChildElement("SettingArchives");
				data.m_title = ele->Attribute("title");
				data.m_rect.point.x = stoi(ele->Attribute("x"));
				data.m_rect.point.y = stoi(ele->Attribute("y"));
				data.m_rect.size.width = stoi(ele->Attribute("width"));
				data.m_rect.size.height = stoi(ele->Attribute("height"));
				data.m_backgroundFillColor = stoi(ele->Attribute("color"));
				data.m_isHaveBorder = stoi(ele->Attribute("isHaveBorder"));
				data.m_borderColor = stoi(ele->Attribute("borderColor"));

				ele = ele->FirstChildElement("MenuItem");
				for (; ele != nullptr; ele = ele->NextSiblingElement("MenuItem"))
				{
					CMenuItemView *itemView = new CMenuItemView;
					itemView->m_title = ele->GetText();
					itemView->m_rect.point.x = stoi(ele->Attribute("x"));
					itemView->m_rect.point.y = stoi(ele->Attribute("y"));
					itemView->m_rect.size.width = stoi(ele->Attribute("width"));
					itemView->m_rect.size.height = stoi(ele->Attribute("height"));
					itemView->m_backgroundFillColor = data.m_backgroundFillColor;
					itemView->m_borderColor = Color::Background_darkWhite | Color::Foreground_red;
					m_pMenuView->AddSubview(itemView);
				}

				auto isCurrentInited = true, isAllInitd = true;
				ele = CData::doc.FirstChildElement("Player")->FirstChildElement("Archives");

				for (; ele != nullptr; ele = ele->NextSiblingElement("Archives"))
				{
					if ((int)m_pGameData->m_difficuty == stoi(ele->Attribute("difficulty")))
					{
						if (stoi(ele->Attribute("progress")) != 0)
						{
							isCurrentInited = false;
						}
					}
					if (stoi(ele->Attribute("progress")) != 0)
					{
						isAllInitd = false;
					}
				}

				if (isCurrentInited)
				{
					auto p = m_pMenuView->m_subviewsList.begin();
					p++;
					(*p)->m_title += " √";
				}
				if (isAllInitd)
				{
					auto p = m_pMenuView->m_subviewsList.begin();
					p++; p++;
					(*p)->m_title += " √";
				}
				return data;
			}
			else if (m_pMenuView->m_title == MENU_ITEM_TITLE_ModificationArchivesName)
			{
				CMenuData data;

				auto ele = CData::doc.FirstChildElement("ConsoleWindow")->FirstChildElement("ModificationArchivesName");
				data.m_title = ele->Attribute("title");
				data.m_rect.point.x = stoi(ele->Attribute("x"));
				data.m_rect.point.y = stoi(ele->Attribute("y"));
				data.m_rect.size.width = stoi(ele->Attribute("width"));
				data.m_rect.size.height = stoi(ele->Attribute("height"));
				data.m_backgroundFillColor = stoi(ele->Attribute("color"));
				data.m_isHaveBorder = stoi(ele->Attribute("isHaveBorder"));
				data.m_borderColor = stoi(ele->Attribute("borderColor"));

				return data;
			}
			else if (m_pMenuView->m_title == "留邮箱地址")
			{
				CMenuData data;

				auto ele = CData::doc.FirstChildElement("ConsoleWindow")->FirstChildElement("leaveTheEmailAddress");
				data.m_title = ele->Attribute("title");
				data.m_rect.point.x = stoi(ele->Attribute("x"));
				data.m_rect.point.y = stoi(ele->Attribute("y"));
				data.m_rect.size.width = stoi(ele->Attribute("width"));
				data.m_rect.size.height = stoi(ele->Attribute("height"));
				data.m_backgroundFillColor = stoi(ele->Attribute("color"));
				data.m_isHaveBorder = stoi(ele->Attribute("isHaveBorder"));
				data.m_borderColor = stoi(ele->Attribute("borderColor"));

				return data;
			}
			
		}
		else
		{
			throw CZException("xml文件加载失败！", nullptr, __LINE__, __FILE__);
		}

		return CMenuData();
	}

	void CMenuController::ViewDidLoad()
	{
		m_pMenuView->m_subviewsList.front()->m_isHaveBorder = true;
		SetReceiveKeyboardEvent(true);
	}

	void CMenuController::DidReceiveKeyboardEvent(const INPUT_RECORD _keyMessage)
	{		
		// 处理按键：上下键、enter、space、esc 
		if (_keyMessage.EventType == KEY_EVENT && _keyMessage.Event.KeyEvent.bKeyDown == true)
		{
			String_ str = _T(">>>>>> CMenuController::DidReceiveKeyboardEvent(const INPUT_RECORD _keyMessage): 收到了键盘按下的事件信息\n");
			OutputDebugString(str.c_str());

			auto p = m_pMenuView->m_subviewsList.begin();
			for (; p != m_pMenuView->m_subviewsList.end(); p++)
			{
				if ((*p)->m_isHaveBorder)
				{
					break;
				}
			}

			if (_keyMessage.Event.KeyEvent.wVirtualKeyCode == 'M')
			{
				if (m_pMenuView->m_title == "进化蝴蝶：关于游戏")
				{
					int someting = 0;
				}
			}

			
			if (m_pMenuView->m_title == "进化蝴蝶：游戏玩法" || m_pMenuView->m_title == "进化蝴蝶：关于游戏")
			{
				auto controlKey = _keyMessage.Event.KeyEvent.dwControlKeyState;
				if (_keyMessage.Event.KeyEvent.wVirtualKeyCode == 'R')
				{
					if (controlKey &RIGHT_CTRL_PRESSED || controlKey & LEFT_CTRL_PRESSED)
					{
						int i = 2;
					}

				}
			}

			if (m_pMenuView->m_title == "进化蝴蝶：游戏玩法" || m_pMenuView->m_title == "进化蝴蝶：关于游戏")
			{
				auto controlKey = _keyMessage.Event.KeyEvent.dwControlKeyState;
				if (_keyMessage.Event.KeyEvent.wVirtualKeyCode == 'M')
				{
					if (controlKey &RIGHT_ALT_PRESSED || controlKey & LEFT_ALT_PRESSED)
					{
						int i = 2;
					}

				}
			}

			if (_keyMessage.Event.KeyEvent.wVirtualKeyCode == VK_SPACE || _keyMessage.Event.KeyEvent.wVirtualKeyCode == VK_RETURN)
			{
				if (m_pMenuView->m_title == "进化蝴蝶：游戏玩法"|| m_pMenuView->m_title == "进化蝴蝶：关于游戏" || m_pMenuView->m_title == "进化蝴蝶：查看成就")
				{
					return;
				}

				if ((*p)->m_title != MENU_ITEM_TITLE_QuitGame)
				{
					CMusic::Instance()->PlayEffect(2);
				}
				DidPressTheReturnKey((*p)->m_title);
			}

			if (_keyMessage.Event.KeyEvent.wVirtualKeyCode == 'W' || _keyMessage.Event.KeyEvent.wVirtualKeyCode == VK_UP)
			{
				if (m_pMenuView->m_title == "进化蝴蝶：游戏玩法" || m_pMenuView->m_title == "进化蝴蝶：关于游戏" || m_pMenuView->m_title == "进化蝴蝶：查看成就")
				{
					return;
				}
				CMusic::Instance()->PlayEffect(1);
				(*p)->m_isHaveBorder = false;

				if (p == m_pMenuView->m_subviewsList.begin())
					p = m_pMenuView->m_subviewsList.end();
				

				--p;
				(*p)->m_isHaveBorder = true;
			}

			if (_keyMessage.Event.KeyEvent.wVirtualKeyCode == 'S' || _keyMessage.Event.KeyEvent.wVirtualKeyCode == VK_DOWN)
			{
				if (m_pMenuView->m_title == "进化蝴蝶：游戏玩法" || m_pMenuView->m_title == "进化蝴蝶：关于游戏" || m_pMenuView->m_title == "进化蝴蝶：查看成就")
				{
					return;
				}
				CMusic::Instance()->PlayEffect(1);
				(*p)->m_isHaveBorder = false;

				if (p == --m_pMenuView->m_subviewsList.end())
					p = m_pMenuView->m_subviewsList.begin();
				else
					++p;


				(*p)->m_isHaveBorder = true;
			}

			if (_keyMessage.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE) 
			{
				if (m_pMenuView->m_title == "进化蝴蝶：主菜单")// 直接退出
				{
					CMainController::Instance()->m_isQuit = true;
				}
				else if(m_pMenuView->m_title == "进化蝴蝶：游戏设置" || m_pMenuView->m_title == "进化蝴蝶：游戏帮助" || m_pMenuView->m_title == "进化蝴蝶：查看成就" || m_pMenuView->m_title == "进化蝴蝶：向作者反馈"){
					m_SendingEmail = "";
					CMusic::Instance()->PlayEffect(5);
					m_pMenuView->RemoveSubviews();
					m_pMenuView->m_title = MENU_ITEM_TITLE_MainMenu;
					m_pMenuView->LoadData();
					ViewDidLoad();
				}
				else if (m_pMenuView->m_title == "进化蝴蝶：设置难度" || m_pMenuView->m_title == "进化蝴蝶：设置存档") {
					CMusic::Instance()->PlayEffect(5);
					m_pMenuView->RemoveSubviews();
					m_pMenuView->m_title = MENU_ITEM_TITLE_GameSetting;
					m_pMenuView->LoadData();
					ViewDidLoad();
				}
				else if (m_pMenuView->m_title == "进化蝴蝶：游戏玩法" || m_pMenuView->m_title == "进化蝴蝶：关于游戏") {
					CMusic::Instance()->PlayEffect(5);
					m_pMenuView->RemoveSubviews();
					m_pMenuView->m_title = MENU_ITEM_TITLE_GameHelp;
					m_pMenuView->LoadData();
					ViewDidLoad();
				}
				else if (m_pMenuView->m_title == "进化蝴蝶：修改存档名字") {
					CMusic::Instance()->PlayEffect(5);
					m_pMenuView->RemoveSubviews();
					m_pMenuView->m_title = MENU_ITEM_TITLE_ArchiveSetting;
					m_pMenuView->LoadData();
					ViewDidLoad();
				}
				else if (m_pMenuView->m_title == "进化蝴蝶：留邮箱地址") {
					CMusic::Instance()->PlayEffect(5);
					m_pMenuView->RemoveSubviews();
					m_pMenuView->m_title = "向作者反馈";
					m_pMenuView->LoadData();
					ViewDidLoad();
				}
				
			}
		}
	}
	void CMenuController::SendEmail()
	{
		auto obj = gcnew SendMailClass;
		auto s = gcnew String(m_pGameData->m_playerName.data());
		s += "提交的反馈——来自M2项目";
		auto s2 = gcnew String("提交的内容有：\n");
		for (const auto &view : m_pMenuView->m_subviewsList)
		{
			if (view->m_title == "留邮箱地址" || view->m_title == "提交反馈")
			{
				continue;
			}
			s2 += gcnew String(view->m_title.data()) + "\n";
		}
		auto isSuccess = obj->SendNow(s, s2);
		for (auto &view : m_pMenuView->m_subviewsList)
		{
			if (view->m_title == "提交反馈" || view->m_title == "请检查网络(发送失败)")
			{
				if (isSuccess)
				{
					view->m_title = "提交反馈(已发送)";
					m_SendingEmail = "邮件发送成功！";
					auto user = gcnew String(m_userEmailAddress.data());
					obj = gcnew SendMailClass(user);
					auto s = gcnew String("感谢玩家 ");
					s += gcnew String(m_pGameData->m_playerName.data()) + " 的反馈";

					auto s2 = gcnew String(s + "，我会努力修改这款游戏！");
					try
					{
						isSuccess = obj->SendNow(s, s2);
						if (isSuccess)
						{
							m_SendingEmail = "已向您的邮箱发送了感谢信，请查看。";
						}
					}
					catch (...)
					{
						// 不处理
					}

				}
				else {
					view->m_title = "请检查网络(发送失败)";
					m_SendingEmail = view->m_title;
				}
				break;
			}
		}
	}
	void CMenuController::DidPressTheReturnKey(const string _string)
	{
		OutputDebugString(_T(">>>>>> CMenuController::DidPressTheReturnKey(const CZView *_view): 已经按下了确定按键！\n"));

		if (_string == MENU_ITEM_TITLE_ContinueGame)
		{
			LoadGameView(false);
		}
		if (_string == MENU_ITEM_TITLE_StartGame)
		{
			LoadGameView(true);
		}

		if (_string == "查看成就")
		{
			m_pMenuView->RemoveSubviews();
			m_pMenuView->m_title = "查看成就";
			m_pMenuView->LoadData();
			SetReceiveKeyboardEvent(true);
		}
		if (_string == "向作者反馈")
		{
			m_pMenuView->RemoveSubviews();
			m_pMenuView->m_title = "向作者反馈";
			m_pMenuView->LoadData();
			ViewDidLoad();
		}
		if (_string == "提交反馈" || _string == "请检查网络(发送失败)")
		{
			m_SendingEmail = "请耐心等待，正在发送邮件...";
		}
		if (_string == MENU_ITEM_TITLE_GameSetting)
		{
			m_pMenuView->RemoveSubviews();
			m_pMenuView->m_title = MENU_ITEM_TITLE_GameSetting;
			m_pMenuView->LoadData();
			ViewDidLoad();
		}
		if (_string == MENU_ITEM_TITLE_GameHelp)
		{
			m_pMenuView->RemoveSubviews();
			m_pMenuView->m_title = MENU_ITEM_TITLE_GameHelp;
			m_pMenuView->LoadData();
			ViewDidLoad();
		}
		if (_string == MENU_ITEM_TITLE_DifficultySetting)
		{
			m_pMenuView->RemoveSubviews();
			m_pMenuView->m_title = MENU_ITEM_TITLE_DifficultySetting;
			m_pMenuView->LoadData();
			ViewDidLoad();
		}
		if (_string == MENU_ITEM_TITLE_Simple)
		{

			m_pGameData->m_difficuty = DifficultyEnum::Simple;
			m_pGameData->SaveDifficulty();

			for (auto view : m_pMenuView->m_subviewsList)
			{
				if (view->m_title.length() > (unsigned)8)
				{
					string str;
					for (size_t i = 0; i < 8; i++)
					{
						str += view->m_title[i];
					}
					view->m_title = str;
					break;
				}
			}

			for (auto &view : m_pMenuView->m_subviewsList)
			{
				if (view->m_title == _string)
				{
					view->m_title += "(已设置)";
					break;
				}
			}
		}
		if (_string == MENU_ITEM_TITLE_General)
		{


			m_pGameData->m_difficuty = DifficultyEnum::General;
			m_pGameData->SaveDifficulty();

			for (auto view : m_pMenuView->m_subviewsList)
			{
				if (view->m_title.length() > (unsigned)8)
				{
					string str;
					for (size_t i = 0; i < 8; i++)
					{
						str += view->m_title[i];
					}
					view->m_title = str;
					break;
				}
			}

			for (auto &view : m_pMenuView->m_subviewsList)
			{
				if (view->m_title == _string)
				{
					view->m_title += "(已设置)";
					break;
				}
			}
		}
		if (_string == MENU_ITEM_TITLE_Hard)
		{

			m_pGameData->m_difficuty = DifficultyEnum::Hard;
			m_pGameData->SaveDifficulty();

			for (auto view : m_pMenuView->m_subviewsList)
			{
				if (view->m_title.length() > (unsigned)8)
				{
					string str;
					for (size_t i = 0; i < 8; i++)
					{
						str += view->m_title[i];
					}
					view->m_title = str;
					break;
				}
			}

			for (auto &view : m_pMenuView->m_subviewsList)
			{
				if (view->m_title == _string)
				{
					view->m_title += "(已设置)";
					break;
				}
			}
		}
		if (_string == MENU_ITEM_TITLE_HowToPlay)
		{
			m_pMenuView->RemoveSubviews();
			m_pMenuView->m_title = MENU_ITEM_TITLE_HowToPlay;
			m_pMenuView->LoadData();
			SetReceiveKeyboardEvent(true);

		}
		if (_string == MENU_ITEM_TITLE_AboutGame)
		{
			m_pMenuView->RemoveSubviews();
			m_pMenuView->m_title = MENU_ITEM_TITLE_AboutGame;
			m_pMenuView->LoadData();
			SetReceiveKeyboardEvent(true);

		}
		if (_string == MENU_ITEM_TITLE_ArchiveSetting)
		{
			m_pMenuView->RemoveSubviews();
			m_pMenuView->m_title = MENU_ITEM_TITLE_ArchiveSetting;
			m_pMenuView->LoadData();
			ViewDidLoad();
			SetReceiveKeyboardEvent(true);

		}
		if (_string == "留邮箱地址")
		{
			m_pMenuView->RemoveSubviews();
			m_pMenuView->m_title = "留邮箱地址";
			m_pMenuView->LoadData();
			SetReceiveKeyboardEvent(true);
		}
		if (_string == "游戏不好玩儿" || _string == "游戏不好玩儿 √")
		{
			for (auto &view : m_pMenuView->m_subviewsList)
			{
				if (view->m_title == _string)
				{
					if (_string == "游戏不好玩儿")
					{
						view->m_title += " √";
						break;
					}
					else
					{
						view->m_title = "游戏不好玩儿";
						break;
					}
					
				}
			}
		}
		if (_string == "不稳定甚至崩溃" || _string == "不稳定甚至崩溃 √")
		{
			for (auto &view : m_pMenuView->m_subviewsList)
			{
				if (view->m_title == _string)
				{
					if (_string == "不稳定甚至崩溃")
					{
						view->m_title += " √";
						break;
					}
					else
					{
						view->m_title = "不稳定甚至崩溃";
						break;
					}
				}
			}
		}
		if (_string == "只为游戏点个赞！" || _string == "只为游戏点个赞！ √")
		{
			for (auto &view : m_pMenuView->m_subviewsList)
			{
				if (view->m_title == _string)
				{
					if (_string == "只为游戏点个赞！")
					{
						view->m_title += " √";
						break;
					}
					else
					{
						view->m_title = "只为游戏点个赞！";
						break;
					}
				}
			}
		}
		if (_string == "只为向作者咆哮！" || _string == "只为向作者咆哮！ √")
		{
			for (auto &view : m_pMenuView->m_subviewsList)
			{
				if (view->m_title == _string)
				{
					if (_string == "只为向作者咆哮！")
					{
						view->m_title += " √";
						break;
					}
					else
					{
						view->m_title = "只为向作者咆哮！";
						break;
					}
				}
			}
		}
		if (_string == MENU_ITEM_TITLE_InitCurrentArchive)
		{
			if (m_pGameData)
			{
				if (CData::doc.LoadFile())
				{
					auto ele = CData::doc.FirstChildElement("Player")->FirstChildElement("Archives");
					
					auto canInitArchive = false;
					for (; ele != nullptr; ele = ele->NextSiblingElement("Archives"))
					{
						if (stoi(ele->Attribute("difficulty")) == (int)m_pGameData->m_difficuty)
						{
							canInitArchive = true;
							break;
						}
					}
					if (canInitArchive)
					{
						ele->SetAttribute("progress", 0);
						CData::doc.SaveFile();
						m_pGameData->m_progress = 0;
						for (auto &view : m_pMenuView->m_subviewsList)
						{
							if (view->m_title == _string)
							{
								view->m_title += " √";
								break;
							}
						}
					}
				}
				else
				{
					throw CZException("xml文件加载失败！", nullptr, __LINE__, __FILE__);
				}
			}
		}
		if (_string == MENU_ITEM_TITLE_InitArchives)
		{
			if (m_pGameData)
			{
				if (CData::doc.LoadFile())
				{
					auto ele = CData::doc.FirstChildElement("Player")->FirstChildElement("Archives");
					for (; ele != nullptr; ele = ele->NextSiblingElement("Archives"))
					{
						ele->SetAttribute("progress", 0);
					}
					CData::doc.SaveFile();
					m_pGameData->m_progress = 0;
					for (auto &view : m_pMenuView->m_subviewsList)
					{
						if (view->m_title == _string)
						{
							view->m_title += " √";
							break;
						}
					}
				}
				else
				{
					throw CZException("xml文件加载失败！", nullptr, __LINE__, __FILE__);
				}
			}
		}
		if (_string == MENU_ITEM_TITLE_ModificationArchivesName)
		{
			m_pMenuView->RemoveSubviews();
			m_pMenuView->m_title = MENU_ITEM_TITLE_ModificationArchivesName;
			m_pMenuView->LoadData();
			SetReceiveKeyboardEvent(true);
		}
		if (_string == MENU_ITEM_TITLE_QuitGame)
		{
			SetReceiveKeyboardEvent(false);
			CMainController::Instance()->m_isQuit = true;
		}
	}

	void CMenuController::LoadGameView(bool _isNewGame)
	{
		OutputDebugString(_T(">>>>>> CMenuController::LoadGameView(bool _isNewGame): 将要加载游戏视图！\n"));

		if (!m_pGameController)
		{
			m_pGameController = new CGameController(_isNewGame);
		}
		m_pGameController->m_pGameData = m_pGameData;

		m_pMenuView->AddSubview(m_pGameController->m_pGameView);
		m_pGameController->ViewDidLoad();

		OutputDebugString(_T(">>>>>> CMenuController::LoadGameView(bool _isNewGame): 游戏视图加载完成！\n"));
	}
}

