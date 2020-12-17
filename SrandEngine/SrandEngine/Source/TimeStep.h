#pragma once

class TimeStep {
private:
	float m_Time;
public:

	static TimeStep* s_instance;
	static TimeStep& get() {
		if (s_instance == nullptr) {
			s_instance = new TimeStep();
		}
		return *s_instance;
	}

	TimeStep() = default;
	TimeStep(float time): m_Time(time){}

	operator float() const { return m_Time; }

	float GetSeconds() const { return m_Time; }
	float GetMilliseconds() const { return m_Time * 1000.0f; }
};