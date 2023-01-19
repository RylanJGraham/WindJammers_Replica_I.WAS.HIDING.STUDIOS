#ifndef __ChooseCharacter_H__
#define __ChooseCharacter_H__

#define MaxCharacters 3

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

enum CharacterType
{
	Japanese,
	German,
	Spanish,
};

enum Player_Confirm {
	OneYes,
	TwoYes
};


class ChooseCharacter : public Module
{
public:
	ChooseCharacter(bool startEnabled);

	~ChooseCharacter();

	bool Start() override;

	Update_Status Update() override;

	Update_Status PostUpdate() override;

	bool CleanUp();

public:
	/*int player1conf;
	int player2conf;*/
	SDL_Texture* chooseCharacterTexture = nullptr;
	SDL_Texture* playerIcon = nullptr;

	Animation* currentAnimation1 = nullptr;
	Animation* currentAnimation2 = nullptr;

	Animation p1;
	Animation p2;

	uint chooseJapAudio = 0;
	uint chooseGerAudio = 0;
	uint chooseEngAudio = 0;
	
	uint changeOption = 0;

private:
	int yMove1, xMove1, yMove2, xMove2;
};

#endif 