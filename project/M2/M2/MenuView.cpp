#include "stdafx.h"
#include "MenuView.h"


namespace M2
{
	CMenuView::CMenuView()
	{
		OutputDebugString(_T(">>>>>> CMenuView::CMenuView()：菜单被创建了！\n"));
	}


	CMenuView::~CMenuView()
	{
		OutputDebugString(_T(">>>>>> CMenuView::CMenuView()：菜单被销毁了！\n"));
	}

	void CMenuView::LoadData()
	{
		auto data = m_pDelegate->LoadMenuData();
		m_title = data.m_title;
		m_rect = data.m_rect;
		m_backgroundFillColor = data.m_backgroundFillColor;
		m_isHaveBorder = data.m_isHaveBorder;
		m_borderColor = data.m_borderColor;
		m_text = data.m_text;

	}

	void CMenuView::Draw()
	{
		CZView::Draw();

		for (auto view : m_subviewsList)
		{
			string s = typeid(*view).name();
			if (s == "class M2::CGameView")
			{
				return;
			}
		}
		
		if (m_title == "进化蝴蝶：修改存档名字" || m_title == "进化蝴蝶：留邮箱地址")
		{
			SetConsoleTextAttribute(GetConsoleOutputHandle(), Color::Background_green | Color::Foreground_yellow);

			COORD coord;
			coord.Y = 1;
			string str = "当前存档：";
			str += CMainController::Instance()->m_pMenuController->m_pGameData->m_playerName;
			switch (CMainController::Instance()->m_pMenuController->m_pGameData->m_difficuty)
			{
			case DifficultyEnum::Simple:
				str += "(简单)";
				break;
			case DifficultyEnum::General:
				str += "(普通)";
				break;
			case DifficultyEnum::Hard:
				str += "(困难)";
				break;
			default:
				break;
			}
			coord.X = 2;
			SetConsoleCursorPosition(GetConsoleOutputHandle(), coord);
			WriteConsoleA(GetConsoleOutputHandle(), str.c_str(), str.length(), nullptr, nullptr);

			coord.X = 0;
			coord.Y = CMainController::Instance()->m_pWindow->m_rect.size.height - 3;

			SetConsoleTextAttribute(GetConsoleOutputHandle(), Color::Background_green | Color::Foreground_yellow);

			str = " 返回(Esc)";
			SetConsoleCursorPosition(GetConsoleOutputHandle(), coord);
			WriteConsoleA(GetConsoleOutputHandle(), str.c_str(), str.length(), nullptr, nullptr);

			str = "确定(Enter) ";
			coord.X = CMainController::Instance()->m_pWindow->m_rect.size.width - str.length();
			SetConsoleCursorPosition(GetConsoleOutputHandle(), coord);
			WriteConsoleA(GetConsoleOutputHandle(), str.c_str(), str.length(), nullptr, nullptr);


			string name = "请输入一个新的存档名：";
			if (m_title == "进化蝴蝶：留邮箱地址")
			{
				name = "请输入您的邮箱地址:";
			}
			coord.X = m_rect.point.x + 3;
			coord.Y = m_rect.point.y + 2;
			CONSOLE_CURSOR_INFO info = { 1,true };
			SetConsoleCursorInfo(GetConsoleOutputHandle(), &info);
			SetConsoleCursorPosition(GetConsoleOutputHandle(), coord);
			SetConsoleTextAttribute(GetConsoleOutputHandle(), m_backgroundFillColor);
			WriteConsoleA(GetConsoleOutputHandle(), name.c_str(), name.length(), nullptr, nullptr);
	
			if (m_title == "进化蝴蝶：留邮箱地址")
			{
				name = "作者会在您提交反馈后，给您发送一份回馈信。";
				coord.Y+=5;
				SetConsoleCursorPosition(GetConsoleOutputHandle(), coord);
				WriteConsoleA(GetConsoleOutputHandle(), name.c_str(), name.length(), nullptr, nullptr);
				name = "注意：网络连接正常时才能提交反馈。";
				coord.Y+=2;
				SetConsoleCursorPosition(GetConsoleOutputHandle(), coord);
				SetConsoleTextAttribute(GetConsoleOutputHandle(), m_backgroundFillColor|Color::Foreground_brightRed);
				WriteConsoleA(GetConsoleOutputHandle(), name.c_str(), name.length(), nullptr, nullptr);
				coord.Y -= 7;
				SetConsoleTextAttribute(GetConsoleOutputHandle(), m_backgroundFillColor);
			}

			coord.Y++; coord.Y++;
			SetConsoleCursorPosition(GetConsoleOutputHandle(), coord);
			::SetConsoleActiveScreenBuffer(CMainController::Instance()->m_pWindow->m_hBuffer);
			cin >> name;
			info.bVisible = false;
			SetConsoleCursorInfo(GetConsoleOutputHandle(), &info);

			if (m_title == "进化蝴蝶：留邮箱地址")
			{
				if (CData::doc.LoadFile())
				{
					auto ele = CData::doc.FirstChildElement("Player")->FirstChildElement("Archives");
					ele->SetAttribute("userEmailAddress", name.data());
					CData::doc.SaveFile();
				}
				else
				{
					throw CZException("xml文件加载失败！", nullptr, __LINE__, __FILE__);
				}

				CMainController::Instance()->m_pMenuController->m_userEmailAddress = name;
				RemoveSubviews();
				m_title = "向作者反馈";
				LoadData();
				CMainController::Instance()->m_pMenuController->ViewDidLoad();
			
			}
			else
			{
				if (CData::doc.LoadFile())
				{
					auto ele = CData::doc.FirstChildElement("Player")->FirstChildElement("Archives");
					string eleName = ele->Attribute("name");
					if (eleName != name)
					{
						for (; ele != nullptr; ele = ele->NextSiblingElement("Archives"))
						{
							ele->SetAttribute("name", name.data());
						}
						CData::doc.SaveFile();

						CMainController::Instance()->m_pMenuController->m_pGameData->m_playerName = name;
						RemoveSubviews();
						m_title = MENU_ITEM_TITLE_ArchiveSetting;
						LoadData();
						CMainController::Instance()->m_pMenuController->ViewDidLoad();
					}
				}
				else
				{
					throw CZException("xml文件加载失败！", nullptr, __LINE__, __FILE__);
				}
			}
		}
		else if (m_title == "进化蝴蝶：游戏玩法" || m_title == "进化蝴蝶：关于游戏" || m_title == "进化蝴蝶：查看成就")
		{
			COORD coord;
			coord = { 0,1 };
			string str = " 返回(ESC)";
			SetConsoleCursorPosition(GetConsoleOutputHandle(), coord);
			SetConsoleTextAttribute(GetConsoleOutputHandle(), Color::Background_green | Color::Foreground_yellow);
			WriteConsoleA(GetConsoleOutputHandle(), str.c_str(), str.length(), nullptr, nullptr);
		
			list<string> list;
			string strg;
			for (auto &ch : m_text)
			{
				if (ch != '|')
				{
					strg += ch;
				}
				else
				{
					list.push_back(strg);
					strg = "";
				}
			}
			list.push_back(strg);
			coord.X = m_rect.point.x + 6;
			coord.Y = m_rect.point.y + 2;
			int i = 0;
			for (auto str : list)
			{
				if (i == 0)
				{
					coord.X = m_rect.point.x + m_rect.size.width / 2 - str.length() / 2;
					SetConsoleCursorPosition(GetConsoleOutputHandle(), coord);
					SetConsoleTextAttribute(GetConsoleOutputHandle(), m_backgroundFillColor|Color::Foreground_red);
					WriteConsoleA(GetConsoleOutputHandle(), str.c_str(), str.length(), nullptr, nullptr);
					i++;

					continue;
				}

				vector<string> li;
				string strg;
				for (auto &ch : str)
				{
					if (ch != ':')
					{
						strg += ch;
					}
					else
					{
						li.push_back(strg);
						strg = "";
					}
				}
				li.push_back(strg);
				
				coord.X = m_rect.point.x + 4;
				coord.Y += 3;

				SetConsoleCursorPosition(GetConsoleOutputHandle(), coord);

				int j = 0;
				for (auto &s : li)
				{
					if (j == 0)
					{
						s += ":";
						SetConsoleTextAttribute(GetConsoleOutputHandle(), m_backgroundFillColor | Color::Foreground_green);
						WriteConsoleA(GetConsoleOutputHandle(), s.c_str(), s.length(), nullptr, nullptr);

					}
					else {
						SetConsoleTextAttribute(GetConsoleOutputHandle(), m_backgroundFillColor);
						WriteConsoleA(GetConsoleOutputHandle(), s.c_str(), s.length(), nullptr, nullptr);
					}

					j++;
				}

				i++;
			}


			if (m_title == "进化蝴蝶：查看成就")
			{
				vector<string> vec{"得分","时间","勋章"};
				coord.X = m_rect.point.x + 16;
				coord.Y = m_rect.point.y + 3;
				for (size_t i = 0; i < 3; i++)
				{
					if (i == 2)
					{
						coord.X += 4;
					}
					str = vec[i];
					SetConsoleCursorPosition(GetConsoleOutputHandle(), coord);
					SetConsoleTextAttribute(GetConsoleOutputHandle(), Color::Background_darkWhite | Color::Foreground_darkGreen);
					WriteConsoleA(GetConsoleOutputHandle(), str.c_str(), str.length(), nullptr, nullptr);

					coord.X += 12;
				}

				vector<string> vec2{ "简单","普通","困难" };
				coord.X = m_rect.point.x + 6;
				coord.Y = m_rect.point.y + 8;
				for (size_t i = 0; i < 3; i++)
				{
					auto color = Color::Foreground_green;
					if(i==1)
					{
						color = Color::Foreground_red;
					}
					else if (i == 2)
					{
						color = Color::Foreground_brightRed;
					}
					str = vec2[i];
					SetConsoleCursorPosition(GetConsoleOutputHandle(), coord);
					SetConsoleTextAttribute(GetConsoleOutputHandle(), Color::Background_darkWhite | color);
					WriteConsoleA(GetConsoleOutputHandle(), str.c_str(), str.length(), nullptr, nullptr);

					auto vec = m_looks[i];

					coord.X = m_rect.point.x + 15;
					for (auto s : vec)
					{
						SetConsoleCursorPosition(GetConsoleOutputHandle(), coord);
						WriteConsoleA(GetConsoleOutputHandle(), s.c_str(), s.length(), nullptr, nullptr);
						coord.X += 12;
					}
					coord.X = m_rect.point.x + 6;
					coord.Y+=5;
				}

				coord.X = m_rect.point.x + 2;
				coord.Y = m_rect.point.y + 6;
				str = "----------------------------------------------------";
				for (size_t i = 0; i < 3; i++)
				{
					SetConsoleCursorPosition(GetConsoleOutputHandle(), coord);
					SetConsoleTextAttribute(GetConsoleOutputHandle(), Color::Background_darkWhite | Color::black);
					WriteConsoleA(GetConsoleOutputHandle(), str.c_str(), str.length(), nullptr, nullptr);
					coord.Y += 5;
				}

				coord.X = m_rect.point.x + 12;
				coord.Y = m_rect.point.y + 1;
				str = "|";
				for (size_t i = 0; i < 3; i++)
				{
					for (int j = m_rect.point.y + 1; j < m_rect.size.height + m_rect.point.y - 1; j++)
					{
						coord.Y = j;
						SetConsoleCursorPosition(GetConsoleOutputHandle(), coord);
						SetConsoleTextAttribute(GetConsoleOutputHandle(), Color::Background_darkWhite | Color::black);
						WriteConsoleA(GetConsoleOutputHandle(), str.c_str(), str.length(), nullptr, nullptr);
					}
					coord.X += 12;
				}

				str = "难度";
				coord.X = m_rect.point.x + 6;
				coord.Y = m_rect.point.y + 5;
				SetConsoleCursorPosition(GetConsoleOutputHandle(), coord);
				SetConsoleTextAttribute(GetConsoleOutputHandle(), Color::Background_darkWhite | Color::black);
				WriteConsoleA(GetConsoleOutputHandle(), str.c_str(), str.length(), nullptr, nullptr);

				str = "项";
				coord.X = m_rect.point.x + 10;
				coord.Y = m_rect.point.y + 2;
				SetConsoleCursorPosition(GetConsoleOutputHandle(), coord);
				SetConsoleTextAttribute(GetConsoleOutputHandle(), Color::Background_darkWhite | Color::black);
				WriteConsoleA(GetConsoleOutputHandle(), str.c_str(), str.length(), nullptr, nullptr);
				str = "目";
				coord.Y++;
				SetConsoleCursorPosition(GetConsoleOutputHandle(), coord);
				SetConsoleTextAttribute(GetConsoleOutputHandle(), Color::Background_darkWhite | Color::black);
				WriteConsoleA(GetConsoleOutputHandle(), str.c_str(), str.length(), nullptr, nullptr);
			}
		}
		else
		{
			SetConsoleTextAttribute(GetConsoleOutputHandle(), Color::Background_green | Color::Foreground_yellow);


			COORD coord;
			coord.Y = 1;
			string str = "当前存档：";
			str += CMainController::Instance()->m_pMenuController->m_pGameData->m_playerName;
			switch (CMainController::Instance()->m_pMenuController->m_pGameData->m_difficuty)
			{
			case DifficultyEnum::Simple:
				str += "(简单)";
				break;
			case DifficultyEnum::General:
				str += "(普通)";
				break;
			case DifficultyEnum::Hard:
				str += "(困难)";
				break;
			default:
				break;
			}
			coord.X = 2;
			SetConsoleCursorPosition(GetConsoleOutputHandle(), coord);
			WriteConsoleA(GetConsoleOutputHandle(), str.c_str(), str.length(), nullptr, nullptr);


			coord.X = 0;
			coord.Y = CMainController::Instance()->m_pWindow->m_rect.size.height - 3;

			str = " 退出(Esc)";

			if (m_title != "进化蝴蝶：主菜单")
			{
				str = " 返回(Esc)";
			}
			SetConsoleCursorPosition(GetConsoleOutputHandle(), coord);
			WriteConsoleA(GetConsoleOutputHandle(), str.c_str(), str.length(), nullptr, nullptr);

			str = "确定(Enter) ";
	
			coord.X = CMainController::Instance()->m_pWindow->m_rect.size.width - str.length();
			SetConsoleCursorPosition(GetConsoleOutputHandle(), coord);
			WriteConsoleA(GetConsoleOutputHandle(), str.c_str(), str.length(), nullptr, nullptr);

			if (m_title == "进化蝴蝶：向作者反馈")
			{
				str = CMainController::Instance()->m_pMenuController->m_SendingEmail;
				coord.X = CMainController::Instance()->m_pWindow->m_rect.size.width - str.length();
				coord.Y = 3;
				SetConsoleCursorPosition(GetConsoleOutputHandle(), coord);
				WriteConsoleA(GetConsoleOutputHandle(), str.c_str(), str.length(), nullptr, nullptr);

				if (str == "请耐心等待，正在发送邮件...")
				{
					static auto i = 0;

					if (i < 2)
					{
						i++;
					}
					else {
						CMainController::Instance()->m_pMenuController->SendEmail();
						i = 0;
					}
				}
			}
		}

	}
}

