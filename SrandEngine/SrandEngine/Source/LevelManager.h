#pragma once

#include <srpch.h>

#include "Source/ObjectManager.h"
#include "Entity/Benny.h"
#include "Entity/Macho.h"
#include "Entity/Cherry.h"
#include "Entity/Pear.h"
#include "Entity/Barter.h"
#include "Entity/UI_Box.h"

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

			Transform* ui_BoxTransform = nullptr;
			Barter* ui_Box = nullptr;

			isUI_BoxPresent = false;
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
				if (input.IsKeyPressed(SR_KEY_Z)) {
					//SR_SYSTEM_TRACE("Choosing...");
					choosingStage = true; 
				}
				else if(choosingStage && (input.IsKeyReleased(SR_KEY_Z))){

					if (inRange_Tag[cc_At] == CC::ccTag::MACHO) {
						controlled_Tag = CC::ccTag::MACHO;
						controlled_Transform = machoTransform;
						macho->SetActive(true);
						benny->SetActive(false);
					}
					else if (inRange_Tag[cc_At] == CC::ccTag::CHERRY) {
						controlled_Tag = CC::ccTag::CHERRY;
						controlled_Transform = cherryTransform;
						cherry->SetActive(true);
						benny->SetActive(false);
					}
					else if (inRange_Tag[cc_At] == CC::ccTag::PEAR) {
						controlled_Tag = CC::ccTag::PEAR;
						controlled_Transform = pearTransform;
						pear->SetActive(true);
					}
					else if (inRange_Tag[cc_At] == CC::ccTag::BARTER) {
						controlled_Tag = CC::ccTag::BARTER;
						controlled_Transform = barterTransform;
						barter->SetActive(true);
					}if (inRange_Tag[cc_At] == CC::ccTag::UI_Box) {
						controlled_Tag = CC::ccTag::UI_Box;
						controlled_Transform = ui_BoxTransform;
						benny->SetActive(false);
						ui_Box->SetActive(true);
					}

					useAbility = true;
					choosingStage = false;
					SR_SYSTEM_TRACE("Done_Choosing");
					AudioController::get().Play("Activate");
				}

				// empty->cancel
				if (choosingStage && inRange_Tag.empty()) {
					cc_At = 0; // reset
					choosingStage = false;
				}

				if (choosingStage) {
					if (input.IsKeyPressed(SR_KEY_X)) { isSwitchCC_Down = true; /*SR_SYSTEM_TRACE("cc_AT++_cc_AT++_cc_AT++_cc_AT++_");*/  } // Minor Promblem
					else if (isSwitchCC_Down && !input.IsKeyPressed(SR_KEY_X)) { cc_At++; isSwitchCC_Down = false;}
					
					cc_At = cc_At % inRange_Tag.size(); // mod incase if the cc_At exceeds Tag size or Tag size decrease

					/*-------debug-------*/
					//SR_SYSTEM_TRACE("inRange_Size: {0}", inRange_Tag.size());
					if (inRange_Tag[cc_At] == CC::ccTag::MACHO) {
						SR_SYSTEM_TRACE("Choose: MACHO");
					}
					else if (inRange_Tag[cc_At] == CC::ccTag::CHERRY) {
						SR_SYSTEM_TRACE("Choose: CHERRY");
					}
					else if (inRange_Tag[cc_At] == CC::ccTag::PEAR) {
						SR_SYSTEM_TRACE("Choose: PEAR");
					}
					else if (inRange_Tag[cc_At] == CC::ccTag::BARTER) {
						SR_SYSTEM_TRACE("Choose: BARTER");
					}
					else if (inRange_Tag[cc_At] == CC::ccTag::UI_Box) {
						SR_SYSTEM_TRACE("Choose: UI_Box");
					}
					
				}
				
			}
			else { // if (useAbility)

				
				Vector2D_float deltaVect = bennyTransform->position - controlled_Transform->position;;
				float magnitude = sqrt(pow(deltaVect.x, 2) + pow(deltaVect.y, 2));
				//SR_SYSTEM_TRACE("Magnitude: {0}\t({1})", magnitude, benny->GetRadius());
				if (magnitude > benny->GetRadius()) { isCancel = true; } //disconnect
				else if (input.IsKeyPressed(SR_KEY_X)) { isCancel = true; } // manual
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
						ui_Box->SetActive(false);
					}
					/*else if (controlled_Tag == CC::ccTag::BARTER) {
						barter->SetActive(false);
					}*/

					controlled_Tag = CC::ccTag::DEFAULT;
					controlled_Transform = nullptr;

					cc_At = 0; // reset
					useAbility = false; 
				}
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