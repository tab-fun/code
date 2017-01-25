#pragma once

#include "Controller.h"
#include "MenuDataSourceInterface.h"
#include "MenuSettingControllerDelegate.h"
#include "MenuItemInterface.h"
#include "EventInterface.h"
#include <vector>

namespace M2
{
	class CMenuView;
	class CData;
	class CZView;
	class CMenuController :
		public CController, public MenuDataSourceInterface, public EventInterface/*, public MenuSettingControllerDelegate*/ // �̳��Ի��ࡢ�˵�����Դ�ӿڡ��¼��ӿڡ��˵�����Э��
	{
	public:
		CMenuController();
		~CMenuController();

	public:
		CMenuView *m_pMenuView = nullptr;
		CGameData *m_pGameData = nullptr;
		CGameController *m_pGameController = nullptr;

		void SetPlayerNewName(string _name);
		
		void DidPressTheReturnKey(const string _string);
		void LoadGameView(bool _isNewGame);
		
		string m_userEmailAddress;
		string m_SendingEmail;
		void SendEmail();

		CMenuData LoadMenuData() override;
		void ViewDidLoad() override;
		void DidReceiveKeyboardEvent(const INPUT_RECORD _keyMessage) override;
	};
}
