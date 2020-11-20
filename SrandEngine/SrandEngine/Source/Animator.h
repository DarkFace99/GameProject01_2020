#pragma once

#include <string>
#include <vector>
#include <map>

#include "GameObject.h"
#include "Component.h"
#include "AssetManager.h"

class Animator : public Component {
private:
	int totalFrames = 0;
	float timeInterval = 1;

	std::map<std::string, Vector2D_Int> states;
	std::string currentState = "";
	std::string nextState = "";

	float* offSetX_Ptr = nullptr;

public:
	Animator(int totalFrames, float timeInterval) 
		:totalFrames(totalFrames), timeInterval(timeInterval){
		
		offSetX_Ptr = gameObject->GetComponent<SpriteRenderer>().GetOffSetX_Ptr();
	}

	

	void SetState(std::string stateName, int startFrame, int endFrame) {
		if (states.count(stateName) <= 0) {
			states[stateName] = Vector2D_Int(startFrame, endFrame);
			std::cout << "state: [" << stateName << "] created!" << std::endl;
		}
		else {
			std::cout << "Animator: //Error// state name [" << stateName << "] was already used!" << std::endl;
		}
	}
	
	void PlayState(std::string stateName) {
		if (states.count(stateName) > 0) {
			nextState = stateName;
		}
		else {
			std::cout << "Animator: //Error// state name [" << stateName << "] is not found!" << std::endl;
		}
	}

	void Update() override final {
		// detect change
		if (currentState != nextState){
			currentState = nextState;	//	update state
			*offSetX_Ptr = (float)(states[currentState].x /* start frame */ / totalFrames);
		}

		// TODO: Implement time acoording to timeInterval
		// increment offset
		//if...{
		*offSetX_Ptr += (float)(1.0f / totalFrames);
			if (*offSetX_Ptr > (float)(states[currentState].y /* end frame */ + 0.5f) / (float)totalFrames) {
				// reset to start frame
				*offSetX_Ptr = (float)(states[currentState].x /* start frame */ / totalFrames);
			}
		//}
	}
	
};
