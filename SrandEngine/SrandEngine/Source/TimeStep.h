#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <srpch.h>

static float limitFPS = 1.0f / 60.0f;

namespace Srand
{
	class TimeStep {
	private:
		float m_Time;
	public:
		float lastFrameTime = 0.0f;
		float accumulator = 0.0f;
		float deltaTime = 0.0f;

		int frames = 0, updates = 0;

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
			deltaTime += (time - lastFrameTime) / limitFPS;
			m_Time = (time - lastFrameTime);
			lastFrameTime = time;

			SR_SYSTEM_TRACE("Time: {0}", m_Time);
		}

		operator float() const { return m_Time; }
		//operator double() const { return (double)m_Time; }

		float GetSeconds() const { return m_Time; }
		float GetMilliseconds() const { return m_Time * 1000.0f; }
	};
}