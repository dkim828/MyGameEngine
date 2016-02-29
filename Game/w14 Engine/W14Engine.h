#ifndef GAME_H
#define GAME_H

#include "Azul.h"

class Game : public Engine
{

public:
	Game( const char * const windowName, int widthScreen, int heightScreen );
	~Game(){};

private:
	static Game* ptrGame;

	void Initialize() override;
	void LoadContent() override;
	void Update() override;
	void Draw() override;
	void UnLoadContent() override;

	//USER defined
	virtual void initializeContext();
	virtual void loadGameContent();
	virtual void unloadGameContent();
	virtual void terminateContext();
};



#endif 