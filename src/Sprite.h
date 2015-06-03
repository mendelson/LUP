#ifndef SRC_SPRITE_H_
#define SRC_SPRITE_H_

#include <SDL_rect.h>
#include <string>

struct SDL_Texture;

using std::string;

class Sprite{
public:
	Sprite();
	Sprite(string file,float frameTime = 1, float rows = 1, float columns = 1);
	~Sprite();
	void Open(string file);
	void SetClip(int x, int y,int w,int h);
	void Render(int x,int y,float angle = 0);
	int GetWidth();
	int GetFrameWidth();
	int GetHeight();
	bool IsOpen();
	void SetScaleX(float scale);
	void SetScaleY(float scale);
	void Update(float dt);
	void SetFrame(int frame);
	void SetFrameCount(int frameCount);
	void SetFrameTime(float frameTime);
	void SetFlipH(bool flipH);
	void SetLoop(int start, int end);
	int GetCurrentFrame();
private:
	SDL_Texture* texture;
	int width;
	int height;
	SDL_Rect clipRect;
	float scaleX;
	float scaleY;
	int frameCount;
	int currentFrame;
	int loopStart;
	int loopEnd;
	float timeElapsed;
	float frameTime;
	int rows;
	int columns;
	bool flipH;
};

#endif /* SRC_SPRITE_H_ */
