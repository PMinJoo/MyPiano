#include <iostream>
#include <conio.h>
#include <fmod.hpp>
#include <iostream>
#include <fstream>
#include <ctime>
#include <windows.h>

#pragma comment (lib, "winmm.lib")

class PlayNote
{
public:
	PlayNote();

	~PlayNote();

	//FMOD �ý��� �ʱ�ȭ, ���� ����
	void init();

	//������ ���� ���
	void playsound(char note);

	//FMOD�� �Ҵ�� �޸� ����
	void Release();

	// �Է� �� �ؽ�Ʈ ���� ������ 
	void record();

	//��ü�� ���� ���
	void play();

	//���� ���� ���
	void free_play();

	//���� ���� ���
	void practice_play();

};