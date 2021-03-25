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

		std::vector<GameObject*> inRange;

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

		bool useAbility = false;
		
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
			for (int i = 0; i < cc_Tag.size(); i++) {
				if (cc_Tag[i] != CC::ccTag::BENNY) {
					Vector2D_float deltaVect;
					if (cc_Tag[i] == CC::ccTag::MACHO) { deltaVect = bennyTransform->position - machoTransform->position; }
					else if (cc_Tag[i] == CC::ccTag::CHERRY) { deltaVect = bennyTransform->position - cherryTransform->position; }
					else if (cc_Tag[i] == CC::ccTag::PEAR) { deltaVect = bennyTransform->position - pearTransform->position; }
					else if (cc_Tag[i] == CC::ccTag::BARTER) { deltaVect = bennyTransform->position - barterTransform->position; }
					else { SR_SYSTEM_TRACE("CheckInRange: Error"); }


					float magnitude = sqrt(pow(deltaVect.x, 2) + pow(deltaVect.y, 2));
					if (magnitude < benny->GetRadius()) {
						inRange.push_back(cc_List[i]);
					}
				}
			}
			SR_SYSTEM_TRACE("inRange: {0}\n---------------------\n", inRange.size());
		}

		void ClearInRange() {
			inRange.clear();
		}



		void AbilityControl() {
			
			

			if (!useAbility) {

				CheckInRange();

				if (input.IsKeyPressed(SR_KEY_1)) {			// Cherry
					ActivateCherry();
					useAbility = true;
				}
				else if (input.IsKeyPressed(SR_KEY_2)) {	// Pear
					ActivatePear();
					useAbility = true;
				}
				else if (input.IsKeyPressed(SR_KEY_3)) {	// Barter
					ActivateBarter();
					useAbility = true;
				}
			}

			if (input.IsKeyPressed(SR_KEY_4)) {			// Cancel
				ClearActivation();
				useAbility = false;
			}

			ClearInRange();
		}

		void ActivateCherry() {
			cherryObj->GetComponent<Cherry>().SetActive(true);
			bennyObj->GetComponent<Benny>().SetActive(false);
		}
		void ActivatePear() {
			pearObj->GetComponent<Pear>().SetActive(true);
		}
		void ActivateBarter() { 
			barterObj->GetComponent<Barter>().SetActive(true); 
		}

		void ClearActivation() { 
			bennyObj->GetComponent<Benny>().SetActive(true); 
			cherryObj->GetComponent<Cherry>().SetActive(false);
			pearObj->GetComponent<Pear>().SetActive(false);
			barterObj->GetComponent<Barter>().SetActive(false);
		}
	};
}