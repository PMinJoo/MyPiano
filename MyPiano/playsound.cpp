#include <iostream>
#include <conio.h>
#include <fmod.hpp>
#include <iostream>
#include <fstream>
#include <ctime>
#include <windows.h>

#pragma comment (lib, "winmm.lib")

#define NUM_MAX_NOTES 1000

using namespace std;
using namespace FMOD;

System *msystem(nullptr);//�ý��� ����
Sound* msound[12];//����� ������ ������ŭ �迭�� ����
Channel* mchannel[12];//����� ä��
FMOD_RESULT result;//���� Ȯ��

void *extradriverdate(nullptr);

int current_ix = 0;//������ �ٷ�� ���� ����
char notes[NUM_MAX_NOTES];
int length[NUM_MAX_NOTES];
char *rep_notes = NULL;//���÷��̽� �����Ҵ��� ����ϱ� ���ؼ�
int *rep_length = NULL;//���÷��̽� �����Ҵ��� ����ϱ� ���ؼ�

void init();//FMOD �ý��� �ʱ�ȭ, ���� ����
void playsound(char note);//������ ���� ���
void Release();//FMOD�� �Ҵ�� �޸� ����
void record();
void replay();

void main()
{
	char note = NULL;
	init();

	for (int n = 0; n < NUM_MAX_NOTES; n++)//���� ���� �ʱ�ȭ
	{
		notes[n] = '\0';
	}
	for (int n = 0; n < NUM_MAX_NOTES; n++)
	{
		length[n] = 0;
	}

	/*while (true)
	{
		cin >> note;
		playsound(note);
		//Release();
	}*/
	//record();

	replay();

	Release();
}
//Fmod�Լ��� �ʱ�ȭ
void init()
{
	result = FMOD::System_Create(&msystem);//�ý��� ����
	if (result != FMOD_OK) printf("�ý��� ���� ����");

	result = msystem->init(32, FMOD_INIT_NORMAL, extradriverdate);//�ý��� �ʱ�ȭ
	if (result != FMOD_OK) printf("�ý��� �ʱ�ȭ ����");

	msystem->createSound("sound/25.wav", FMOD_LOOP_OFF, 0, &msound[0]);//�Ҹ�����
	msystem->createSound("sound/27.wav", FMOD_LOOP_OFF, 0, &msound[1]);//���ϸ�, �ݺ� ����, Ȯ�� ����, ���� ���ϰ� ����
	msystem->createSound("sound/29.wav", FMOD_LOOP_OFF, 0, &msound[2]);
	msystem->createSound("sound/30.wav", FMOD_LOOP_OFF, 0, &msound[3]);
	msystem->createSound("sound/32.wav", FMOD_LOOP_OFF, 0, &msound[4]);
	msystem->createSound("sound/34.wav", FMOD_LOOP_OFF, 0, &msound[5]);
	msystem->createSound("sound/36.wav", FMOD_LOOP_OFF, 0, &msound[6]);
	msystem->createSound("sound/37.wav", FMOD_LOOP_OFF, 0, &msound[7]);
	msystem->createSound("sound/26.wav", FMOD_LOOP_OFF, 0, &msound[8]);
	msystem->createSound("sound/28.wav", FMOD_LOOP_OFF, 0, &msound[9]);
	msystem->createSound("sound/31.wav", FMOD_LOOP_OFF, 0, &msound[10]);
	msystem->createSound("sound/33.wav", FMOD_LOOP_OFF, 0, &msound[11]);
	msystem->createSound("sound/35.wav", FMOD_LOOP_OFF, 0, &msound[12]);
}

void playsound(char note)//�Ҹ� ���
{
	switch (note)
	{
	case 'a':
		msystem->playSound(msound[0], 0, false, &mchannel[0]);
		break;
	case 's':
		msystem->playSound(msound[1], 0, false, &mchannel[1]);
		break;
	case 'd':
		msystem->playSound(msound[2], 0, false, NULL);
		break;
	case 'f':
		msystem->playSound(msound[3], 0, false, NULL);
		break;
	case 'g':
		msystem->playSound(msound[4], 0, false, NULL);
		break;
	case 'h':
		msystem->playSound(msound[5], 0, false, NULL);
		break;
	case 'j':
		msystem->playSound(msound[6], 0, false, NULL);
		break;
	case 'k':
		msystem->playSound(msound[7], 0, false, NULL);
		break;
	case 'w':
		msystem->playSound(msound[8], 0, false, NULL);
		break;
	case 'e':
		msystem->playSound(msound[9], 0, false, NULL);
		break;
	case 't':
		msystem->playSound(msound[10], 0, false, NULL);
		break;
	case 'y':
		msystem->playSound(msound[11], 0, false, NULL);
		break;
	case 'u':
		msystem->playSound(msound[12], 0, false, NULL);
		break;
	}

}

void Release()
{
	msystem->release();
}

/*
	�Է��� �Ҹ����� ���� �ϴ� �κ�
	������ �׽�Ʈ �ϱ����� �ӽ÷� ����
*/
void record()
{
	ofstream outFile("record.txt");

	int time_temp = (int)timeGetTime();//winmm.lib
	char input_character;
	while (true)
	{

		input_character = (char)_getch();
		int current_time = (int)timeGetTime();
		int elapsed_time = current_time - time_temp;

		notes[current_ix] = input_character;

		if (current_ix > 0)
		{
			length[current_ix - 1] = elapsed_time;//��� �ð� ����
			printf("%dms ", elapsed_time);
		}

		current_ix++;

		time_temp = current_time;


		if (input_character == 13)//����Ű �Է½� ����
		{
			outFile << current_ix << endl;//current_ix���� ����
			for (int save = 0; save < current_ix; save++)//current_ix����ŭ for�� �ݺ�����
			{
				outFile << notes[save] << length[save] << endl;//fprintf(input_file, "%c %d\n", notes[save], length[save]);//�ݺ��� ������ txt���Ͽ� ����
			}

			printf("\n\n");
			return;
		}
		playsound(input_character);

		msystem->update();//fmod�� ��Ķ����� ����ؾ��ϴ� �Լ�
		//����غ��� �ʰ� ���� �Ẹ�� �߰��� ���� ������ �ʴ� ������ ���ܹ���

	}
	outFile.close();
	
}

void replay()
{
	ifstream fin;
	fin.open("record.txt");

	int re_notes;//current_ix�� ��
	char re_key;//����� Ű�� ��
	int re_length;//����� ���� ����
	
	fin >> re_notes;
	current_ix = re_notes;
	rep_notes = (char*)malloc(sizeof(char)*re_notes);
	rep_length = (int*)malloc(sizeof(int)*re_notes);

	for (int i = 0; i < re_notes; i++)//����� Ű ������ŭ for���� �ݺ�
	{
		fin >> re_key >>re_length;//Ű ���� ���� ���̸� ������
		rep_notes[i] = re_key;//����� Ű�� ���� �迭�� ����
		rep_length[i] = re_length;//����� ���� ���̸� �迭�� ����
		playsound(rep_notes[i]);//���� ���
		Sleep(rep_length[i]);//��� ����
		if (i != re_notes - 1)
		{
			printf("%dms ", rep_length[i]);
		}
		msystem->update();
	}
	printf("\n\n");
	fin.close();
	return;
}
/*
void practice()
{

}
*/