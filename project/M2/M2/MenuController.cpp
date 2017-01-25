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
			throw CZException("xml�ļ�����ʧ�ܣ�", nullptr, __LINE__, __FILE__);
		}


		OutputDebugString(_T(">>>>>> CMenuController::CMenuController()���˵��������������ˣ�\n"));
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
		OutputDebugString(_T(">>>>>> CMenuController::~CMenuController()���˵��������������ˣ�\n"));
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
			else if (m_pMenuView->m_title == "�鿴�ɾ�")
			{
				auto ele2 = CData::doc.FirstChildElement("Player")->FirstChildElement("Archives");
				vector<string> vec;
				m_pMenuView->m_looks.clear();
				for (; ele2 != nullptr; ele2 = ele2->NextSiblingElement("Archives"))
				{
					string s = ele2->Attribute("lookScore");
					if (s.empty())
					{
						s = "0 ��";
					}
					else
					{
						s += " ��";
					}
					vec.push_back(s);

					s = ele2->Attribute("lookTime");
					if (s.empty())
					{
						s = "0 ��";
					}
					else
					{
						auto i = stoi(s);
						if (i<60)
						{
							s += " ��";
						}
						else {
							s = to_string(i / 60) + " �� " + to_string(i % 60) + " ��";
						}
					}
					vec.push_back(s);

					s = ele2->Attribute("lookAchievements");
					if (s.empty())
					{
						s = "����";
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
			else if (m_pMenuView->m_title == "�����߷���")
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
					(*p)->m_title += "(������)";
					break;
				case DifficultyEnum::General:
					p++;
					(*p)->m_title += "(������)";
					break;
				case DifficultyEnum::Hard:
					p++; p++;
					(*p)->m_title += "(������)";
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
					(*p)->m_title += " ��";
				}
				if (isAllInitd)
				{
					auto p = m_pMenuView->m_subviewsList.begin();
					p++; p++;
					(*p)->m_title += " ��";
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
			else if (m_pMenuView->m_title == "�������ַ")
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
			throw CZException("xml�ļ�����ʧ�ܣ�", nullptr, __LINE__, __FILE__);
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
		// �����������¼���enter��space��esc 
		if (_keyMessage.EventType == KEY_EVENT && _keyMessage.Event.KeyEvent.bKeyDown == true)
		{
			String_ str = _T(">>>>>> CMenuController::DidReceiveKeyboardEvent(const INPUT_RECORD _keyMessage): �յ��˼��̰��µ��¼���Ϣ\n");
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
				if (m_pMenuView->m_title == "����������������Ϸ")
				{
					int someting = 0;
				}
			}

			
			if (m_pMenuView->m_title == "������������Ϸ�淨" || m_pMenuView->m_title == "����������������Ϸ")
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

			if (m_pMenuView->m_title == "������������Ϸ�淨" || m_pMenuView->m_title == "����������������Ϸ")
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
				if (m_pMenuView->m_title == "������������Ϸ�淨"|| m_pMenuView->m_title == "����������������Ϸ" || m_pMenuView->m_title == "�����������鿴�ɾ�")
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
				if (m_pMenuView->m_title == "������������Ϸ�淨" || m_pMenuView->m_title == "����������������Ϸ" || m_pMenuView->m_title == "�����������鿴�ɾ�")
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
				if (m_pMenuView->m_title == "������������Ϸ�淨" || m_pMenuView->m_title == "����������������Ϸ" || m_pMenuView->m_title == "�����������鿴�ɾ�")
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
				if (m_pMenuView->m_title == "�������������˵�")// ֱ���˳�
				{
					CMainController::Instance()->m_isQuit = true;
				}
				else if(m_pMenuView->m_title == "������������Ϸ����" || m_pMenuView->m_title == "������������Ϸ����" || m_pMenuView->m_title == "�����������鿴�ɾ�" || m_pMenuView->m_title == "���������������߷���"){
					m_SendingEmail = "";
					CMusic::Instance()->PlayEffect(5);
					m_pMenuView->RemoveSubviews();
					m_pMenuView->m_title = MENU_ITEM_TITLE_MainMenu;
					m_pMenuView->LoadData();
					ViewDidLoad();
				}
				else if (m_pMenuView->m_title == "���������������Ѷ�" || m_pMenuView->m_title == "�������������ô浵") {
					CMusic::Instance()->PlayEffect(5);
					m_pMenuView->RemoveSubviews();
					m_pMenuView->m_title = MENU_ITEM_TITLE_GameSetting;
					m_pMenuView->LoadData();
					ViewDidLoad();
				}
				else if (m_pMenuView->m_title == "������������Ϸ�淨" || m_pMenuView->m_title == "����������������Ϸ") {
					CMusic::Instance()->PlayEffect(5);
					m_pMenuView->RemoveSubviews();
					m_pMenuView->m_title = MENU_ITEM_TITLE_GameHelp;
					m_pMenuView->LoadData();
					ViewDidLoad();
				}
				else if (m_pMenuView->m_title == "�����������޸Ĵ浵����") {
					CMusic::Instance()->PlayEffect(5);
					m_pMenuView->RemoveSubviews();
					m_pMenuView->m_title = MENU_ITEM_TITLE_ArchiveSetting;
					m_pMenuView->LoadData();
					ViewDidLoad();
				}
				else if (m_pMenuView->m_title == "�����������������ַ") {
					CMusic::Instance()->PlayEffect(5);
					m_pMenuView->RemoveSubviews();
					m_pMenuView->m_title = "�����߷���";
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
		s += "�ύ�ķ�����������M2��Ŀ";
		auto s2 = gcnew String("�ύ�������У�\n");
		for (const auto &view : m_pMenuView->m_subviewsList)
		{
			if (view->m_title == "�������ַ" || view->m_title == "�ύ����")
			{
				continue;
			}
			s2 += gcnew String(view->m_title.data()) + "\n";
		}
		auto isSuccess = obj->SendNow(s, s2);
		for (auto &view : m_pMenuView->m_subviewsList)
		{
			if (view->m_title == "�ύ����" || view->m_title == "��������(����ʧ��)")
			{
				if (isSuccess)
				{
					view->m_title = "�ύ����(�ѷ���)";
					m_SendingEmail = "�ʼ����ͳɹ���";
					auto user = gcnew String(m_userEmailAddress.data());
					obj = gcnew SendMailClass(user);
					auto s = gcnew String("��л��� ");
					s += gcnew String(m_pGameData->m_playerName.data()) + " �ķ���";

					auto s2 = gcnew String(s + "���һ�Ŭ���޸������Ϸ��");
					try
					{
						isSuccess = obj->SendNow(s, s2);
						if (isSuccess)
						{
							m_SendingEmail = "�����������䷢���˸�л�ţ���鿴��";
						}
					}
					catch (...)
					{
						// ������
					}

				}
				else {
					view->m_title = "��������(����ʧ��)";
					m_SendingEmail = view->m_title;
				}
				break;
			}
		}
	}
	void CMenuController::DidPressTheReturnKey(const string _string)
	{
		OutputDebugString(_T(">>>>>> CMenuController::DidPressTheReturnKey(const CZView *_view): �Ѿ�������ȷ��������\n"));

		if (_string == MENU_ITEM_TITLE_ContinueGame)
		{
			LoadGameView(false);
		}
		if (_string == MENU_ITEM_TITLE_StartGame)
		{
			LoadGameView(true);
		}

		if (_string == "�鿴�ɾ�")
		{
			m_pMenuView->RemoveSubviews();
			m_pMenuView->m_title = "�鿴�ɾ�";
			m_pMenuView->LoadData();
			SetReceiveKeyboardEvent(true);
		}
		if (_string == "�����߷���")
		{
			m_pMenuView->RemoveSubviews();
			m_pMenuView->m_title = "�����߷���";
			m_pMenuView->LoadData();
			ViewDidLoad();
		}
		if (_string == "�ύ����" || _string == "��������(����ʧ��)")
		{
			m_SendingEmail = "�����ĵȴ������ڷ����ʼ�...";
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
					view->m_title += "(������)";
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
					view->m_title += "(������)";
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
					view->m_title += "(������)";
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
		if (_string == "�������ַ")
		{
			m_pMenuView->RemoveSubviews();
			m_pMenuView->m_title = "�������ַ";
			m_pMenuView->LoadData();
			SetReceiveKeyboardEvent(true);
		}
		if (_string == "��Ϸ�������" || _string == "��Ϸ������� ��")
		{
			for (auto &view : m_pMenuView->m_subviewsList)
			{
				if (view->m_title == _string)
				{
					if (_string == "��Ϸ�������")
					{
						view->m_title += " ��";
						break;
					}
					else
					{
						view->m_title = "��Ϸ�������";
						break;
					}
					
				}
			}
		}
		if (_string == "���ȶ���������" || _string == "���ȶ��������� ��")
		{
			for (auto &view : m_pMenuView->m_subviewsList)
			{
				if (view->m_title == _string)
				{
					if (_string == "���ȶ���������")
					{
						view->m_title += " ��";
						break;
					}
					else
					{
						view->m_title = "���ȶ���������";
						break;
					}
				}
			}
		}
		if (_string == "ֻΪ��Ϸ����ޣ�" || _string == "ֻΪ��Ϸ����ޣ� ��")
		{
			for (auto &view : m_pMenuView->m_subviewsList)
			{
				if (view->m_title == _string)
				{
					if (_string == "ֻΪ��Ϸ����ޣ�")
					{
						view->m_title += " ��";
						break;
					}
					else
					{
						view->m_title = "ֻΪ��Ϸ����ޣ�";
						break;
					}
				}
			}
		}
		if (_string == "ֻΪ������������" || _string == "ֻΪ������������ ��")
		{
			for (auto &view : m_pMenuView->m_subviewsList)
			{
				if (view->m_title == _string)
				{
					if (_string == "ֻΪ������������")
					{
						view->m_title += " ��";
						break;
					}
					else
					{
						view->m_title = "ֻΪ������������";
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
								view->m_title += " ��";
								break;
							}
						}
					}
				}
				else
				{
					throw CZException("xml�ļ�����ʧ�ܣ�", nullptr, __LINE__, __FILE__);
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
							view->m_title += " ��";
							break;
						}
					}
				}
				else
				{
					throw CZException("xml�ļ�����ʧ�ܣ�", nullptr, __LINE__, __FILE__);
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
		OutputDebugString(_T(">>>>>> CMenuController::LoadGameView(bool _isNewGame): ��Ҫ������Ϸ��ͼ��\n"));

		if (!m_pGameController)
		{
			m_pGameController = new CGameController(_isNewGame);
		}
		m_pGameController->m_pGameData = m_pGameData;

		m_pMenuView->AddSubview(m_pGameController->m_pGameView);
		m_pGameController->ViewDidLoad();

		OutputDebugString(_T(">>>>>> CMenuController::LoadGameView(bool _isNewGame): ��Ϸ��ͼ������ɣ�\n"));
	}
}

