#pragma once

#include <srpch.h>

#include "Source/ObjectManager.h"
#include "Entity/Benny.h"
#include "Entity/Macho.h"
#include "Entity/Cherry.h"
#include "Entity/Pear.h"
#include "Entity/Barter.h"


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

		bool choosingStage = false;
		unsigned int cc_At = 0;
		bool useAbility = false;

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
		}

		inline int VectorSize() { return cc_List.size(); }
		GameObject* operator[](int i) { return cc_List[i]; }
		
		std::vector<GameObject*>::iterator begin() { return cc_List.begin(); }
		std::vector<GameObject*>::iterator end() { return cc_List.end(); }
		
		inline void SetUpCC() {
			for (int i = 0; i < cc_List.size(); i++) {		// find Benny first
				if (cc_List[i]->HasComponent<Benny>()) {
					SR_SYSTEM_TRACE("Level: Found Benny");
					bennyObj = cc_List[i];

					bennyTransform = &bennyObj->GetComponent<Transform>();
					benny = &bennyObj->GetComponent<Benny>();
					cc_Tag.push_back(benny->GetTag());
				}
			}

			for (int i = 0; i < cc_List.size(); i++) {		// other CCs
				if (cc_List[i]->HasComponent<Macho>()) {
					SR_SYSTEM_TRACE("Level: Found Macho");
					machoObj = cc_List[i];

					machoTransform = &machoObj->GetComponent<Transform>();
					macho = &machoObj->GetComponent<Macho>();
					cc_Tag.push_back(macho->GetTag());
				}
				else if (cc_List[i]->HasComponent<Cherry>()) {
					SR_SYSTEM_TRACE("Level: Found Cherry");
					cherryObj = cc_List[i];
					cc_List[i]->GetComponent<Cherry>().SetCherry(bennyObj);

					cherryTransform = &cherryObj->GetComponent<Transform>();
					cherry = &cherryObj->GetComponent<Cherry>();
					cc_Tag.push_back(cherry->GetTag());

				}
				else if (cc_List[i]->HasComponent<Pear>()) {
					pearObj = cc_List[i];
					SR_SYSTEM_TRACE("Level: Found Pear");

					pearTransform = &pearObj->GetComponent<Transform>();
					pear = &pearObj->GetComponent<Pear>();
					cc_Tag.push_back(pear->GetTag());
				}
				else if (cc_List[i]->HasComponent<Barter>()) {
					barterObj = cc_List[i];
					cc_List[i]->GetComponent<Barter>().SetBarter(bennyObj);
					SR_SYSTEM_TRACE("Level: Found Barter");

					barterTransform = &barterObj->GetComponent<Transform>();
					barter = &barterObj->GetComponent<Barter>();
					cc_Tag.push_back(barter->GetTag());
					
				}
			}
		}

		void CheckInRange() {
			Vector2D_float deltaVect;
			float magnitude;
			float prevMag = -1.0f;
			float closestMag;
			int closestCC = -1;
			
			for (int i = 0; i < cc_Tag.size()-1; i++) { // exclude Benny
				closestMag = benny->GetRadius(); //reset closestMag
				for (int j = 0; j < cc_Tag.size(); j++) {
					if (cc_Tag[j] != CC::ccTag::BENNY) {

						if (cc_Tag[j] == CC::ccTag::MACHO) { deltaVect = bennyTransform->position - machoTransform->position; }
						else if (cc_Tag[j] == CC::ccTag::CHERRY) { deltaVect = bennyTransform->position - cherryTransform->position; }
						else if (cc_Tag[j] == CC::ccTag::PEAR) { deltaVect = bennyTransform->position - pearTransform->position; }
						else if (cc_Tag[j] == CC::ccTag::BARTER) { deltaVect = bennyTransform->position - barterTransform->position; }
						else { SR_SYSTEM_TRACE("CheckInRange: Error"); }

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
					SR_SYSTEM_TRACE("Choosing...");
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

					}

					useAbility = true;
					choosingStage = false;
					SR_SYSTEM_TRACE("Done_Choosing");
				}

				// empty->cancel
				if (choosingStage && inRange_Tag.empty()) {
					cc_At = 0; // reset
					choosingStage = false;
				}

				if (choosingStage) {
					if (input.IsKeyPressed(SR_KEY_X)) { cc_At++; /*SR_SYSTEM_TRACE("cc_AT++_cc_AT++_cc_AT++_cc_AT++_");*/  } // Minor Promblem
					
					cc_At = cc_At % inRange_Tag.size(); // mod incase if the cc_At exceeds Tag size or Tag size decrease

					/*-------debug-------*/
					SR_SYSTEM_TRACE("inRange_Size: {0}	cc_At: {1}", inRange_Tag.size(), cc_At);
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
					
				}
				

				// CancelAbility

				//if (input.IsKeyPressed(SR_KEY_1)) {			// Cherry
				//	ActivateCherry();
				//	useAbility = true;
				//}
				//else if (input.IsKeyPressed(SR_KEY_2)) {	// Pear
				//	ActivatePear();
				//	useAbility = true;
				//}
				//else if (input.IsKeyPressed(SR_KEY_3)) {	// Barter
				//	ActivateBarter();
				//	useAbility = true;
				//}
			}
			else { // if (useAbility)
				/*if (input.IsKeyPressed(SR_KEY_Z)) {
					SR_SYSTEM_TRACE("Nothing");
				}
				else*/ 
				if (input.IsKeyPressed(SR_KEY_X)) { 
					SR_SYSTEM_TRACE("CANCEL---CANCEL---CANCEL---CANCEL---CANCEL");

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
					/*else if (controlled_Tag == CC::ccTag::BARTER) {
						barter->SetActive(false);
					}*/

					controlled_Tag = CC::ccTag::DEFAULT;
					controlled_Transform = nullptr;

					cc_At = 0; // reset
					useAbility = false; 
				}else if(controlled_Tag == CC::ccTag::BARTER){
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
	};
}