#include "stdafx.h"

namespace M2
{
	bool operator!=(const Rect &_rect, const Rect &_rect1)
	{
		if (_rect.point.x != _rect1.point.x ||
			_rect.point.y != _rect1.point.y ||
			_rect.size.width != _rect1.size.width ||
			_rect.size.height != _rect1.size.height)
		{
			return true;
		}
		return false;
	}
	bool operator==(const Rect &_rect, const Rect &_rect1)
	{
		if (_rect.point.x == _rect1.point.x &&
			_rect.point.y == _rect1.point.y &&
			_rect.size.width == _rect1.size.width &&
			_rect.size.height == _rect1.size.height)
		{
			return true;
		}
		return false;
	}

	bool CMapRectItem::IsCollided(CMapRectItem *_item, bool _is)
	{
		if (_is)
		{
			if (m_type == 0)
			{
				return false;
			}

			auto point = (*_item).m_rect.point, point2 = point;

			switch ((*_item).m_direction)
			{
			case DirectionEnum::Up:
				point2.x += 2;
				if (point.x > m_rect.point.x && point.x <m_rect.point.x+m_rect.size.width && point.y > m_rect.point.y && point.y < m_rect.point.y + m_rect.size.height)
				{
					return true;
				}
				point = point2;
				if (point.x > m_rect.point.x && point.x <m_rect.point.x + m_rect.size.width && point.y > m_rect.point.y && point.y < m_rect.point.y + m_rect.size.height)
				{
					return true;
				}
				break;
			case DirectionEnum::Down:
				point.y++;
				point2.y++;
				point2.x += 2;
				if (point.x > m_rect.point.x && point.x <m_rect.point.x + m_rect.size.width && point.y > m_rect.point.y && point.y < m_rect.point.y + m_rect.size.height)
				{
					return true;
				}
				point = point2;
				if (point.x > m_rect.point.x && point.x <m_rect.point.x + m_rect.size.width && point.y > m_rect.point.y && point.y < m_rect.point.y + m_rect.size.height)
				{
					return true;
				}
				break;
			case DirectionEnum::Left:
				point2.y++;
				if (point.x > m_rect.point.x && point.x <m_rect.point.x + m_rect.size.width && point.y > m_rect.point.y && point.y < m_rect.point.y + m_rect.size.height)
				{
					return true;
				}
				point = point2;
				if (point.x > m_rect.point.x && point.x <m_rect.point.x + m_rect.size.width && point.y > m_rect.point.y && point.y < m_rect.point.y + m_rect.size.height)
				{
					return true;
				}
				break;
			case DirectionEnum::Right:
				point.x += 2;
				point2.x += 2;
				point2.y++;
				if (point.x > m_rect.point.x && point.x <m_rect.point.x + m_rect.size.width && point.y > m_rect.point.y && point.y < m_rect.point.y + m_rect.size.height)
				{
					return true;
				}
				point = point2;
				if (point.x > m_rect.point.x && point.x <m_rect.point.x + m_rect.size.width && point.y > m_rect.point.y && point.y < m_rect.point.y + m_rect.size.height)
				{
					return true;
				}
				break;
			default:
				break;
			}
		}
		else {
			if (m_type != 0) // 自身可以发生碰撞
			{
				if (_item->m_type == -1) // 玩家和自身发生了碰撞
				{
					if (_item->m_rect == m_rect)
					{
						return true;
					}
				}
			}

		}

		return false;
	}

	bool CMapRectItem::IsCollided(Point &_item)
	{
		if (m_rect.point.x == _item.x && m_rect.point.y == _item.y)
		{
			return true;
		}
		else {
			return false;
		}
	}

	bool Rect::IsCrossde(const Rect *_rect, bool _isOnlyCompareLeftPoint)
	{
		if (_isOnlyCompareLeftPoint)
		{
			if (point.x <= (*_rect).point.x && point.x + size.width >= (*_rect).point.x && point.y <= (*_rect).point.y && point.y + size.height >= (*_rect).point.y)
			{
				return true;
			}
		}
		else
		{
			Point point_2 = (*_rect).point, point_3 = point_2, point_4 = point_2;
			point_2.x += (*_rect).size.width;
			point_3.y += (*_rect).size.height;
			point_4.x += (*_rect).size.width;
			point_4.y += (*_rect).size.height;

			auto isLeftUp = false, isRightUp = false, isLeftDown = false, isRightDown = false;

			if (point.x < (*_rect).point.x && point.x + size.width > (*_rect).point.x && point.y < (*_rect).point.y && point.y + size.height > (*_rect).point.y)
			{
				return isLeftUp;
			}
			if (point.x < point_2.x && point.x + size.width > point_2.x && point.y < point_2.y && point.y + size.height > point_2.y)
			{
				return isRightUp;
			}
			if (point.x < point_3.x && point.x + size.width > point_3.x && point.y < point_3.y && point.y + size.height > point_3.y)
			{
				return isLeftDown;
			}
			if (point.x < point_4.x && point.x + size.width > point_4.x && point.y < point_4.y && point.y + size.height > point_4.y)
			{
				return isRightDown;
			}

			if (isLeftUp || isRightUp || isLeftDown || isRightUp)
			{
				return true;
			}
		}
		return false;
	}
}