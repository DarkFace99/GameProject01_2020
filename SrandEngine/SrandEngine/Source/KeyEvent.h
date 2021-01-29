#pragma once

/* C Headers */
#include <sstream>

/* Custom Headers */
#include "Source/Event.h"

namespace Srand
{
	class KeyEvent : public Event
	{
	protected:
		KeyEvent(int keycode) : m_keycode(keycode) {}

		int m_keycode;

	public:
		inline int GetKeyCode() const { return m_keycode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	};

	class KeyPressedEvent : public KeyEvent
	{
	private:
		int m_repeateCount;

	public:
		KeyPressedEvent(int keycode, int repeateCount) : KeyEvent(keycode), m_repeateCount(repeateCount) {}

		inline int GetRepeatCount() const { return m_repeateCount; }
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_keycode << " (" << m_repeateCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_keycode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)

	};

	class KeyTypedEvent : public KeyEvent
	{
	private:


	public:
		KeyTypedEvent(int keycode) : KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_keycode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)

	};
}

