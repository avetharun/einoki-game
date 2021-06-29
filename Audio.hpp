#pragma once
#ifndef AUDIO_H
#define AUDIO_H
#include <iosfwd>
#include <sdl/SDL_mixer.h>
#include <iostream>
class AudioWAV {
private:
	int selectedChannel = -1;
	const char* status;
	Mix_Music* chunk = nullptr;
	Mix_Chunk* chunkw = nullptr;
	bool music = false;
	bool loop = false;
public:
	const char
		*SDL_UNABLE_TO_INIT = "sdl_unable_to_init",
		*WAV_FILE_MISSING = "wav_file_missing",
		*WAV_FILE_NULL = "wav_file_null",
		*WAV_SUCCESS = "wav_ok",
		*WAV_UNINIT = "wav_uninitialized",
		*WAV_UNABLE_TO_PLAY = "wav_unable_to_play"
		;
	AudioWAV(const char* filename, bool _music = false) {
		music = _music;
		if (music) {
			chunk = Mix_LoadMUS(filename);

			status = (chunk == nullptr) ? Mix_GetError() : WAV_SUCCESS;

		}
		else {
			chunkw = Mix_LoadWAV(filename);
			status = (chunkw == nullptr) ? Mix_GetError() : WAV_SUCCESS;
		}
	}
	AudioWAV() {
		status = WAV_UNINIT;
		chunk = nullptr;
		chunkw = nullptr;
	}
	const char* GetError() { return status; }
	void Loop () {
		loop = true;
	}
	void unLoop () {
		loop = false;
	}
	void Play() {
		int channel = selectedChannel;
		bool success;
		if (music) {
			if (chunk != nullptr) {
				success = Mix_PlayMusic(chunk, (loop)?-1:0);
			}
			else { std::cout << "Error playing sound, Music is null!"; }
		}
		else {
			if (chunkw != nullptr) {
				if (Mix_Playing(selectedChannel) || selectedChannel == -2 ) {
					selectedChannel = Mix_PlayChannel(-1, chunkw, (loop)?-1:0);
					Mix_HaltChannel(selectedChannel);
				}
				Mix_PlayChannel(selectedChannel, chunkw, (loop) ? -1 : 0);
			}
			else { std::cout << "Error playing sound, Audio is null!"; }
		}
	}

	bool isPlaying() {
		int channel = selectedChannel;
		return (music)?Mix_PlayingMusic():Mix_Playing (channel); 
	}
	
	void SetVolume(int v) {
		/*VOLUME: 0-128*/
		Mix_Volume(selectedChannel, v);
	}
	int GetVolume() {
		return Mix_Volume(selectedChannel, -1);
	}
	bool operator ==(AudioWAV o) {
	}
	bool operator == (nullptr_t) {
		return ((music && (chunk == nullptr)) && (!music && (chunk==nullptr))) ? true : false;
	}
	bool operator != (nullptr_t) {
		return ((music && (chunk != nullptr)) && (!music && (chunk != nullptr))) ? true : false;
	}
	void operator ~() {
		(music) ? Mix_HaltMusic() : Mix_HaltChannel(selectedChannel);
	}
	void operator !() {
		// Toggle loop
		loop = !loop;
	}
};
#endif