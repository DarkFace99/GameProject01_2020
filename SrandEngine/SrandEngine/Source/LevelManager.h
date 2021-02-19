#pragma once

#include <srpch.h>
#include "ecspch.h"
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

		LevelManager() {}
		static LevelManager* s_instance;
		GameObject* benny = nullptr;
		GameObject* macho = nullptr;
		GameObject* cherry = nullptr;
		GameObject* pear = nullptr;
		GameObject* barter = nullptr;

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
			for (int i = 0; i < cc_List.size(); i++) {
				if (cc_List[i]->HasComponent<Benny>()) {
					printf("Level: Found Benny\n");
					benny = cc_List[i];
				}
				else if (cc_List[i]->HasComponent<Macho>()) {
					printf("Level: Found Macho\n");
					macho = cc_List[i];
				}
				else if (cc_List[i]->HasComponent<Cherry>()) {
					printf("Level: Found Cherry\n");
					cherry = cc_List[i];
					cc_List[i]->GetComponent<Cherry>().SetCherry(benny);
				}
				else if (cc_List[i]->HasComponent<Pear>()) {
					pear = cc_List[i];
					printf("Level: Found Pear\n");
				}
				else if (cc_List[i]->HasComponent<Barter>()) {
					barter = cc_List[i];
					cc_List[i]->GetComponent<Barter>().SetBarter(benny);
					printf("Level: Found Barter\n");
					
				}
			}
		}

		void ActivateCherry() {
			cherry->GetComponent<Cherry>().SetActive(true);
			benny->GetComponent<Benny>().SetActive(false);
		}
		void ActivatePear() {
			pear->GetComponent<Pear>().SetActive(true);
		}
		void ActivateBarter() { 
			barter->GetComponent<Barter>().SetActive(true); 
			benny->GetComponent<Benny>().SetActive(false);
		}

		void ClearActivation() { 
			benny->GetComponent<Benny>().SetActive(true); 
			cherry->GetComponent<Cherry>().SetActive(false);
			pear->GetComponent<Pear>().SetActive(false);
			barter->GetComponent<Barter>().SetActive(false);
		}
	};
}