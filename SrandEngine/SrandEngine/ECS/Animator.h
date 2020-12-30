#pragma once

#include <string>
#include <vector>
#include <map>

#include "GameObject.h"
#include "Component.h"
#include "Source/AssetManager.h"

class Animator : public Component {
private:
	int totalFrames = 1;
	float timeInterval = 1;

	std::map<std::string, Vector2D_Int> states;
	std::string currentState = "";
	std::string nextState = "";

	float* offSetX_Ptr = nullptr;
	float AccumulateTime = 0;

public:
	Animator(int totalFrames, float timeInterval) /* in ms */
		:totalFrames(totalFrames), timeInterval(timeInterval){
		
		/*offSetX_Ptr = gameObject->GetComponent<SpriteRenderer>().GetOffSetX();*/
	}

	

	void SetState(std::string stateName, int startFrame, int endFrame) {
		if (states.count(stateName) <= 0) {
			states[stateName] = Vector2D_Int(startFrame, endFrame);
			//std::cout << "state: [" << stateName << "] created!" << std::endl;
		}
		else {
			std::cout << "Animator: //Error// state name [" << stateName << "] was already used!" << std::endl;
		}
	}
	
	void PlayState(std::string stateName) {
		if (states.count(stateName) > 0) {
			if (nextState != stateName) { nextState = stateName; }
		}
		else {
			std::cout << "Animator: //Error// state name [" << stateName << "] is not found!" << std::endl;
		}
	}

	bool Init() override final {
		// for some reason
		offSetX_Ptr = gameObject->GetComponent<SpriteRenderer>().GetOffSetX();
		return true;
	}

	void Update() override final {
		

		// Update Acc Time
		AccumulateTime += TimeStep::get().GetMilliseconds();

		// detect change
		if (currentState != nextState){
			currentState = nextState;	//	update state
			*offSetX_Ptr = (float)states[currentState].x /* start frame */ / (float)totalFrames;
		}

		// increment offset in time step
		if(AccumulateTime >= timeInterval){
			AccumulateTime -= timeInterval;
			*offSetX_Ptr += (float)(1.0f / totalFrames); // increment frame
			
			if (*offSetX_Ptr > (float)(states[currentState].y /* end frame */ + 0.5f) / (float)totalFrames) {
					// reset to start frame
				*offSetX_Ptr = (float)states[currentState].x /* start frame */ / (float)totalFrames;
			}
		}
	}
	
};
