#pragma once

#include <srpch.h>

#include "Source/ObjectManager.h"
#include "Entity/Benny.h"
#include "Entity/Macho.h"
#include "Entity/Cherry.h"
#include "Entity/Pear.h"
#include "Entity/Barter.h"
#include "Entity/UI_Box.h"

#include "Source/GUI_Selector.h"

namespace Srand
{
	class LevelManager
	{
	private:
		std::vector<GameObject*> cc_List;
		std::vector<CC::ccTag> cc_Tag;

		std::vector<GameObject*> inRange_List;
		std::vector<CC::ccTag> inRange_Tag;

		LevelManager() {}
		static LevelManager* s_instance;
		GameObject* bennyObj = nullptr;
		GameObject* machoObj = nullptr;
		GameObject* cherryObj = nullptr;
		GameObject* pearObj = nullptr;
		GameObject* barterObj = nullptr;
		GameObject* ui_BoxObj = nullptr;

		GameObject* goalObj = nullptr;
		BoxCollider2D* goalCollider = nullptr;
		
		bool isSwitchCC_Down = false;
		bool isCancel = false;
		bool delay = false;

	protected:
		Transform* bennyTransform = nullptr;
		Benny* benny = nullptr;
		Transform* machoTransform = nullptr;
		Macho* macho = nullptr;
		Transform* cherryTransform = nullptr;
		Cherry* cherry = nullptr;
		Transform* pearTransform = nullptr;
		Pear* pear = nullptr;
		Transform* barterTransform = nullptr;
		Barter* barter = nullptr;

		Transform* ui_BoxTransform = nullptr;
		UI_Box* ui_Box = nullptr;

		GUI_Selector* selector = nullptr;

		bool choosingStage = false;
		unsigned int cc_At = 0;
		bool useAbility = false;

		int npc_Count = 0; 

		bool isLevelClear = false;
		int cc_Count = 0;
		bool isUI_BoxPresent = false;
		/*float xPoint;
		float yPoint;
		float yLine_Min;
		float yLine_Max;*/

		CC::ccTag lastCC_Control = CC::ccTag::DEFAULT;;
		bool lastUI_Control = false;

		CC::ccTag controlled_Tag = CC::ccTag::DEFAULT;
		Transform* controlled_Transform = nullptr;

		WindowsInput input;

	public:
		static LevelManager& get()
		{
			if (s_instance == nullptr)
				s_instance = new LevelManager();

			return *s_instance;
		}
		~LevelManager()
		{
			for (GameObject* obj : cc_List)
				delete obj;
			delete s_instance;
		}
		inline void AddObject(GameObject* obj)
		{
			cc_List.push_back(obj);

		}

		inline void Clean()
		{
			cc_List.clear();
			cc_Tag.clear();

			inRange_List.clear();
			inRange_Tag.clear();

			bennyObj = nullptr;
			machoObj = nullptr;
			cherryObj = nullptr;
			pearObj = nullptr;
			barterObj = nullptr;
			ui_BoxObj = nullptr;

			bennyTransform = nullptr;
			benny = nullptr;
			machoTransform = nullptr;
			macho = nullptr;
			cherryTransform = nullptr;
			cherry = nullptr;
			pearTransform = nullptr;
			pear = nullptr;
			barterTransform = nullptr;
			barter = nullptr;

			choosingStage = false;
			cc_At = 0;
			useAbility = false;
			isSwitchCC_Down = false;
			isCancel = false;

			goalCollider = nullptr;
			goalObj = nullptr;
			isLevelClear = false;
			cc_Count = 0;
			npc_Count = 0;

			ui_BoxTransform = nullptr;
			ui_Box = nullptr;

			selector = nullptr;

			isUI_BoxPresent = false;

			lastCC_Control = CC::ccTag::DEFAULT;;
			lastUI_Control = false;
		}

		inline int VectorSize() { return cc_List.size(); }
		GameObject* operator[](int i) { return cc_List[i]; }
		
		std::vector<GameObject*>::iterator begin() { return cc_List.begin(); }
		std::vector<GameObject*>::iterator end() { return cc_List.end(); }
		
		inline void SetUpCC() {
			
			bool isMachoFound = false;

			for (int i = 0; i < cc_List.size(); i++) {		// find Benny first
				if (cc_List[i]->HasComponent<Benny>()) {
					SR_SYSTEM_TRACE("Level: Found Benny");
					bennyObj = cc_List[i];

					bennyTransform = &bennyObj->GetComponent<Transform>();
					benny = &bennyObj->GetComponent<Benny>();
					cc_Tag.push_back(benny->GetTag());
					cc_Count++;
				}
			}

			for (int i = 0; i < cc_List.size(); i++) {		// other CCs
				if (cc_List[i]->HasComponent<Macho>()) {
					machoObj = cc_List[i];

					machoTransform = &machoObj->GetComponent<Transform>();
					macho = &machoObj->GetComponent<Macho>();
					cc_Tag.push_back(macho->GetTag());
					isMachoFound = true;
					cc_Count++;
					SR_SYSTEM_TRACE("Level: Found Macho");
				}
				else if (cc_List[i]->HasComponent<Cherry>()) {
					cherryObj = cc_List[i];
					cc_List[i]->GetComponent<Cherry>().SetCherry(bennyObj);

					cherryTransform = &cherryObj->GetComponent<Transform>();
					cherry = &cherryObj->GetComponent<Cherry>();
					cc_Tag.push_back(cherry->GetTag());
					cc_Count++;
					SR_SYSTEM_TRACE("Level: Found Cherry");
				}
				else if (cc_List[i]->HasComponent<Pear>()) {
					pearObj = cc_List[i];

					pearTransform = &pearObj->GetComponent<Transform>();
					pear = &pearObj->GetComponent<Pear>();
					cc_Tag.push_back(pear->GetTag());
					cc_Count++;
					SR_SYSTEM_TRACE("Level: Found Pear");
				}
				else if (cc_List[i]->HasComponent<Barter>()) {
					barterObj = cc_List[i];
					cc_List[i]->GetComponent<Barter>().SetBarter(bennyObj);

					barterTransform = &barterObj->GetComponent<Transform>();
					barter = &barterObj->GetComponent<Barter>();
					cc_Tag.push_back(barter->GetTag());
					cc_Count++;
					SR_SYSTEM_TRACE("Level: Found Barter");
				}
				else if (cc_List[i]->HasComponent<UI_Box>()) { // UI_Box
					ui_BoxObj = cc_List[i];

					isUI_BoxPresent = true;
					ui_BoxTransform = &ui_BoxObj->GetComponent<Transform>();
					ui_Box = &ui_BoxObj->GetComponent<UI_Box>();;
					cc_Tag.push_back(CC::ccTag::UI_Box);
					SR_SYSTEM_TRACE("Level: Found UI_Box");
				}
			}
			if (isMachoFound) { macho->CopyCC_List(cc_List); }
		}

		inline void AddNPC() {
			npc_Count++;
		}
		inline void SetSelector(GUI_Selector* selector) { 
			this->selector = selector; 
			selector->AttachOrigin(bennyTransform);
		}

		//inline bool GetIsChoosing() { return choosingStage; }

		inline void NpcFound() { npc_Count--; }

		void CheckInRange() {
			Vector2D_float deltaVect;
			float magnitude;
			float prevMag = -1.0f;
			float closestMag;
			int closestCC = -1;
			
			for (int i = 0; i < cc_Tag.size()-1; i++) { // exclude Benny
				closestMag = benny->GetRadius(); //reset closestMag
				for (int j = 0; j < cc_Tag.size(); j++) {

					if (cc_Tag[j] == CC::ccTag::MACHO && macho->GetIsOut()) { continue; }
					else if (cc_Tag[j] == CC::ccTag::CHERRY && cherry->GetIsOut()) { continue; }
					else if (cc_Tag[j] == CC::ccTag::PEAR && pear->GetIsOut()) { continue; }
					else if (cc_Tag[j] == CC::ccTag::BARTER && barter->GetIsOut()) { continue; }

					if (cc_Tag[j] != CC::ccTag::BENNY) {

						if (cc_Tag[j] == CC::ccTag::MACHO) { deltaVect = bennyTransform->position - machoTransform->position; }
						else if (cc_Tag[j] == CC::ccTag::CHERRY) { deltaVect = bennyTransform->position - cherryTransform->position; }
						else if (cc_Tag[j] == CC::ccTag::PEAR) { deltaVect = bennyTransform->position - pearTransform->position; }
						else if (cc_Tag[j] == CC::ccTag::BARTER) { deltaVect = bennyTransform->position - barterTransform->position; }
						else if (cc_Tag[j] == CC::ccTag::UI_Box) { deltaVect = bennyTransform->position - ui_BoxTransform->position; }

						magnitude = sqrt(pow(deltaVect.x, 2) + pow(deltaVect.y, 2));

						if (prevMag < magnitude && magnitude < closestMag) {
							closestMag = magnitude;
							closestCC = j;
						}
					}
				}
				if (closestMag < benny->GetRadius()) {
					inRange_List.push_back(cc_List[closestCC]);
					inRange_Tag.push_back(cc_Tag[closestCC]);
					prevMag = closestMag;
				}
			}
			//SR_SYSTEM_TRACE("inRange: {0}\n---------------------\n", inRange.size());
		}

		void ClearInRange() {
			inRange_List.clear();
			inRange_Tag.clear();
		}

		void AbilityControl() {
			//SR_SYSTEM_TRACE("cc_At: {0}", cc_At);
			if (!useAbility) {
				CheckInRange();

				// ActivateAbility
				if (input.IsKeyPressed(SR_KEY_Z) && !choosingStage) {
					//SR_SYSTEM_TRACE("Choosing...");
					
					// empty->cancel
					if (inRange_Tag.empty()) {
						cc_At = 0; // reset
						choosingStage = false;
					}
					else {
						choosingStage = true;
						//selector->SetDestination(&inRange_List[cc_At]->GetComponent<Transform>());
					}
				}
				else if(choosingStage && (input.IsKeyReleased(SR_KEY_Z))){
					
					if (inRange_Tag[cc_At] == CC::ccTag::MACHO) {
						controlled_Tag = CC::ccTag::MACHO;
						controlled_Transform = machoTransform;
						macho->Chosen(false);
						macho->SetActive(true);
						benny->SetActive(false);
						if (selector) { 
							selector->SetDestination(machoTransform); 
							selector->SetOffset(0, 50);
						}
					}
					else if (inRange_Tag[cc_At] == CC::ccTag::CHERRY) {
						controlled_Tag = CC::ccTag::CHERRY;
						controlled_Transform = cherryTransform;
						cherry->Chosen(false);
						cherry->SetActive(true);
						benny->SetActive(false);
						if (selector) {
							selector->SetDestination(cherryTransform);
							selector->SetOffset(0, 50);
						}
					}
					else if (inRange_Tag[cc_At] == CC::ccTag::PEAR) {
						controlled_Tag = CC::ccTag::PEAR;
						controlled_Transform = pearTransform;
						pear->Chosen(false);
						pear->SetActive(true);
						if (selector) {
							selector->SetDestination(pearTransform);
							selector->SetOffset(0, 50);
						}
					}
					else if (inRange_Tag[cc_At] == CC::ccTag::BARTER) {
						controlled_Tag = CC::ccTag::BARTER;
						controlled_Transform = barterTransform;
						barter->Chosen(false);
						barter->SetActive(true);
						if (selector) {
							selector->SetDestination(barterTransform);
							selector->SetOffset(0, 50);
						}
					}if (inRange_Tag[cc_At] == CC::ccTag::UI_Box) {
						controlled_Tag = CC::ccTag::UI_Box;
						controlled_Transform = ui_BoxTransform;
						if (selector) {
							selector->SetDestination(ui_BoxTransform);
							selector->SetOffset(-20, 420);
						}
						ui_Box->Chosen(false);
						benny->SetActive(false);
						ui_Box->SetAttach(true);
					}
					lastUI_Control = false;
					lastCC_Control = CC::ccTag::DEFAULT;

					useAbility = true;
					
					choosingStage = false;
					SR_SYSTEM_TRACE("Done_Choosing");
					AudioController::get().Play("Activate");
				}

				if (choosingStage && inRange_Tag.empty()) {
					cc_At = 0; // reset
					choosingStage = false;
					
				}

				if (choosingStage) {
					
					if (input.IsKeyPressed(SR_KEY_X) && delay) { delay = false; }
					else if (isSwitchCC_Down && !input.IsKeyPressed(SR_KEY_X)) { isSwitchCC_Down = false; }
					else if (input.IsKeyPressed(SR_KEY_X) && !isSwitchCC_Down) { 
						
						cc_At++; 
						cc_At = cc_At % inRange_Tag.size(); // mod incase if the cc_At exceeds Tag size or Tag size decrease
						isSwitchCC_Down = true;
						//selector->SetDestination(&inRange_List[cc_At]->GetComponent<Transform>());
					}
					//selector->SetDestination(&inRange_List[cc_At]->GetComponent<Transform>());

					if (inRange_Tag[cc_At] != lastCC_Control) {
						if (lastUI_Control) {
							lastUI_Control = false;
							ui_Box->Chosen(false);
						}
						else {
							if (lastCC_Control == CC::ccTag::MACHO) {
								macho->Chosen(false);
							}
							else if (lastCC_Control == CC::ccTag::CHERRY) {
								cherry->Chosen(false);
							}
							else if (lastCC_Control == CC::ccTag::PEAR) {
								pear->Chosen(false);
							}
							else if (lastCC_Control == CC::ccTag::BARTER) {
								barter->Chosen(false);
							}
						}
					}

					if (inRange_Tag[cc_At] == CC::ccTag::MACHO) {
						macho->Chosen(true);
						lastCC_Control = CC::ccTag::MACHO;
					}
					else if (inRange_Tag[cc_At] == CC::ccTag::CHERRY) {
						cherry->Chosen(true);
						lastCC_Control = CC::ccTag::CHERRY;
					}
					else if (inRange_Tag[cc_At] == CC::ccTag::PEAR) {
						pear->Chosen(true);
						lastCC_Control = CC::ccTag::PEAR;
					}
					else if (inRange_Tag[cc_At] == CC::ccTag::BARTER) {
						pear->Chosen(true);
						lastCC_Control = CC::ccTag::BARTER;
					}
					else if (inRange_Tag[cc_At] == CC::ccTag::UI_Box) {
						ui_Box->Chosen(true);
						lastUI_Control = true;
						lastCC_Control = CC::ccTag::DEFAULT;
					}
	
				}
				
			}
			else { // if (useAbility)

				
				Vector2D_float deltaVect = bennyTransform->position - controlled_Transform->position;;
				float magnitude = sqrt(pow(deltaVect.x, 2) + pow(deltaVect.y, 2));
				//SR_SYSTEM_TRACE("Magnitude: {0}\t({1})", magnitude, benny->GetRadius());
				if (magnitude > benny->GetRadius()) { isCancel = true; } //disconnect
				else if (input.IsKeyPressed(SR_KEY_Z)) {  } 
				else if (input.IsKeyPressed(SR_KEY_X)) { isCancel = true; delay = true; } // manual
				//else if (input.IsKeyReleased(SR_KEY_X) && isCancel) {}
				else if (controlled_Tag == CC::ccTag::BARTER) { isCancel = true; } // Barter
				
				if (isCancel) {
					isCancel = false;
					SR_SYSTEM_TRACE("CANCEL---CANCEL---CANCEL");

					AudioController::get().Play("Deactivate");

					if (controlled_Tag == CC::ccTag::MACHO) {
						benny->SetActive(true);
						macho->SetActive(false);
					
					}else if (controlled_Tag == CC::ccTag::CHERRY) {
						benny->SetActive(true);
						cherry->SetActive(false);
					}
					else if (controlled_Tag == CC::ccTag::PEAR) {
						pear->SetActive(false);
					}
					else if (controlled_Tag == CC::ccTag::UI_Box) {
						benny->SetActive(true);
						ui_Box->SetAttach(false);
					}
					/*else if (controlled_Tag == CC::ccTag::BARTER) {
						barter->SetActive(false);
					}*/

					controlled_Tag = CC::ccTag::DEFAULT;
					controlled_Transform = nullptr;

					cc_At = 0; // reset
					useAbility = false; 
					
				}
				if (selector != nullptr) { selector->SetPercentRange(magnitude / benny->GetRadius()); }
			}


			if (selector != nullptr) {
				selector->IsActive(useAbility);
			}

			//if (input.IsKeyPressed(SR_KEY_4)) {			// Cancel
			//	ClearActivation();
			//	useAbility = false;
			//}

			ClearInRange();
		}

		void SetGoal(GameObject& gameobj) {
			goalObj = &gameobj;
			goalCollider = &gameobj.GetComponent<BoxCollider2D>();
		}

		void CheckGoal() {
			if (npc_Count <= 0 && !isLevelClear) {
				bool cc_Out = false;
				for (int i = 0; i < cc_List.size(); i++) {
					if (Collision::AABB(*goalCollider, cc_List[i]->GetComponent<BoxCollider2D>())) {
						if (cc_Tag[i] == CC::ccTag::MACHO && !macho->GetIsOut()) {
							macho->OutOfLevel();
							cc_Out = true;
							cc_Count--;
						}
						else if (cc_Tag[i] == CC::ccTag::CHERRY && !cherry->GetIsOut()) {
							cherry->OutOfLevel();
							cc_Out = true;
							cc_Count--;
						}
						else if (cc_Tag[i] == CC::ccTag::PEAR && !pear->GetIsOut()) {
							pear->OutOfLevel();
							cc_Out = true;
							cc_Count--;
						}
						else if (cc_Tag[i] == CC::ccTag::BARTER && !barter->GetIsOut()) {
							barter->OutOfLevel();
							cc_Out = true;
							cc_Count--;
						}
						else if (cc_Tag[i] == CC::ccTag::BENNY && cc_Count == 1 /* last one */) {
							benny->OutOfLevel();
							cc_Count--;
							isLevelClear = true;
							Engine::get().NextScene();
							break;
						}

						
						if (cc_Out) {
							if (macho != nullptr) {
								if (!(cc_Tag[i] != CC::ccTag::MACHO && macho->GetIsActive()))
									isCancel = true;
							}
							else { isCancel = true; }
						}
					}

				}
			}
			if (isLevelClear) { SR_SYSTEM_TRACE("-----------------LEVEL_CLEAR----------------"); }
		}


		// discarded f()

		/*void ActivateCherry() {
			cherry->SetActive(true);
			benny->SetActive(false);
		}
		void ActivatePear() {
			pear->SetActive(true);
		}
		void ActivateBarter() { 
			barter->SetActive(true); 
		}

		void ClearActivation() { 
			benny->SetActive(true); 
			cherry->SetActive(false);
			pear->SetActive(false);
			barter->SetActive(false);
		}*/

		/*void Set_FinishPoint(Vector2D_float point){
			xPoint = point.x;
			yPoint = point.y;
			isFinishPoint = true;
		}*/
		
		/*void Set_FinishLine(float x, float yMax, float yMin) {
			xPoint = x;
			yLine_Min = yMin;
			yLine_Max = yMax;
			isFinishPoint = false;
		}*/

		/*void CC_Exit() {
			if (isFinishPoint) {
				for (int i = 0; i < cc_List.size(); i++) {
					BoxCollider2D* col = &cc_List[i]->GetComponent<BoxCollider2D>();
					bool x_Axis = 
					bool y_Axis =
					if()
				}
			}
			else {
				for (int i = 0; i < cc_List.size(); i++) {

				}
			}
		}*/
	};
}