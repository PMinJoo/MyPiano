#include <iostream>
#include <conio.h>
#include <fmod.hpp>

using namespace std;


int main()
{
	FMOD::System *system(nullptr);//시스템
	FMOD::Sound *sound(nullptr);//소리
	FMOD::Channel *channel(nullptr);//채널
	FMOD_RESULT result;//오류 확인

	void *extradriverdate(nullptr);

	char key = NULL;



	result = FMOD::System_Create(&system);//시스템 생성

	result = system->init(32, FMOD_INIT_NORMAL, extradriverdate);//시스템 초기화

	while (true)
	{
		cin >> key;

		switch (key)
		{
		case 'a':
			result = system->createSound("sound/25.wav", FMOD_LOOP_OFF, 0, &sound);//사운드 생성
			if (result != FMOD_OK) printf("여기서오류남");
			result = system->playSound(sound, 0, false, &channel);//사운드 재생
			break;
		case 's':
			result = system->createSound("sound/26.wav", FMOD_LOOP_OFF, 0, &sound);//사운드 생성
			if (result != FMOD_OK) printf("여기서오류남");
			result = system->playSound(sound, 0, false, &channel);//사운드 재생
			break;
		case 'd':
			result = system->createSound("sound/27.wav", FMOD_LOOP_OFF, 0, &sound);//사운드 생성
			if (result != FMOD_OK) printf("여기서오류남");
			result = system->playSound(sound, 0, false, &channel);//사운드 재생
			break;
		case 'f':
			result = system->createSound("sound/28.wav", FMOD_LOOP_OFF, 0, &sound);//사운드 생성
			if (result != FMOD_OK) printf("여기서오류남");
			result = system->playSound(sound, 0, false, &channel);//사운드 재생
			break;
		case 'g':
			result = system->createSound("sound/29.wav", FMOD_LOOP_OFF, 0, &sound);//사운드 생성
			if (result != FMOD_OK) printf("여기서오류남");
			result = system->playSound(sound, 0, false, &channel);//사운드 재생
			break;


		default:
			break;
		}
	}


	result = system->release();
	return 0;
}

