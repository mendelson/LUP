#include "State.h"
#include "Collision.h"
#include "Game.h"

State::State() {
	popRequested = false;
	quitRequested = false;
}

State::~State() {
	objectArray.clear();
}

void State::AddObject(GameObject* gameObject) {
	objectArray.emplace_back(gameObject);
}

bool State::PopRequested() {
	return popRequested;
}

void State::SetPopRequested(bool pop) {
	popRequested = pop;
}

bool State::QuitRequested() {
	return quitRequested;
}

void State::UpdateArray(float dt) {
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		if (objectArray[i]->IsDead()) {
			objectArray.erase(objectArray.begin() + i);
			i--;
			if (i < 0) {
				i = 0;
				continue;
			}
		}
	}
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Update(Game::GetInstance().GetDeltaTime());

		for (unsigned int j = 0; j < objectArray.size(); j++) {
			if (i != j) {
				if (Collision::IsColliding(objectArray[i]->box,
						objectArray[j]->box, objectArray[i]->rotation,
						objectArray[j]->rotation)) {
					objectArray[j]->NotifyCollision(*objectArray[i]);
				}
			}
		}
	}
}

void State::RenderArray() {
	for (unsigned int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Render();
	}
}

