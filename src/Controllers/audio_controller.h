#include <SFML/Audio/Sound.hpp>
#include <memory>
#include <list>

#include "../Loaders/audio_loader.h"

enum class SoundType
{
	MARIO_JUMP,
	MARIO_DIES,
	MARIO_STOMPS
};

class AudioController
{
public:
	AudioController();
	void startPlayingMusic();
	void stopPlayingMusic();
	void playSound(SoundsID soundID);

	// return is audio muted
	bool toggleMute();
	void mute();
	void unmute();
	
	// If currrent music ended, then this function start playing the next one
	void update();

private:
	bool isStoppedMusic = true;
	MusicLoader musicLoader;
	SoundsLoader soundsLoader;

	size_t currentMusicIndex = 0;
	std::vector<SoundsID> currentSoundsID;
	unsigned int volume = 100;
};
