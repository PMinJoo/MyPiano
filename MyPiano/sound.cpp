#include <iostream>
#include <conio.h>
#include <fmod.hpp>

using namespace std;


int main()
{
	FMOD::System *system(nullptr);//�ý���
	FMOD::Sound *sound(nullptr);//�Ҹ�
	FMOD::Channel *channel(nullptr);//ä��
	FMOD_RESULT result;//���� Ȯ��

	void *extradriverdate(nullptr);

	char key = NULL;



	result = FMOD::System_Create(&system);//�ý��� ����

	result = system->init(32, FMOD_INIT_NORMAL, extradriverdate);//�ý��� �ʱ�ȭ

	while (true)
	{
		cin >> key;

		switch (key)
		{
		case 'a':
			result = system->createSound("sound/25.wav", FMOD_LOOP_OFF, 0, &sound);//���� ����
			if (result != FMOD_OK) printf("���⼭������");
			result = system->playSound(sound, 0, false, &channel);//���� ���
			break;
		case 's':
			result = system->createSound("sound/26.wav", FMOD_LOOP_OFF, 0, &sound);//���� ����
			if (result != FMOD_OK) printf("���⼭������");
			result = system->playSound(sound, 0, false, &channel);//���� ���
			break;
		case 'd':
			result = system->createSound("sound/27.wav", FMOD_LOOP_OFF, 0, &sound);//���� ����
			if (result != FMOD_OK) printf("���⼭������");
			result = system->playSound(sound, 0, false, &channel);//���� ���
			break;
		case 'f':
			result = system->createSound("sound/28.wav", FMOD_LOOP_OFF, 0, &sound);//���� ����
			if (result != FMOD_OK) printf("���⼭������");
			result = system->playSound(sound, 0, false, &channel);//���� ���
			break;
		case 'g':
			result = system->createSound("sound/29.wav", FMOD_LOOP_OFF, 0, &sound);//���� ����
			if (result != FMOD_OK) printf("���⼭������");
			result = system->playSound(sound, 0, false, &channel);//���� ���
			break;


		default:
			break;
		}
	}


	result = system->release();
	return 0;
}

