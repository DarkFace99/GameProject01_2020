#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Srand
{
	class TimeStep {
	private:
		float m_Time;
		float lastFrameTime = 0.0f;
	public:
		float accumulator;

		static TimeStep* s_instance;
		static TimeStep& get() {
			if (s_instance == nullptr) {
				s_instance = new TimeStep();
			}
			return *s_instance;
		}

		TimeStep() = default;
		TimeStep(float time) : m_Time(time) {}

		void Update()
		{
			float time = (float)glfwGetTime();
			m_Time = time - lastFrameTime;
			if (m_Time > 0.25f)
				m_Time = 0.25f;
			lastFrameTime = time;
			accumulator += m_Time;
		}

		operator float() const { return m_Time; }

		float GetSeconds() const { return m_Time; }
		float GetMilliseconds() const { return m_Time * 1000.0f; }
	};
}