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

System *msystem(nullptr);//시스템 선언
Sound* msound[12];//사용할 사운드의 개수만큼 배열을 선언
Channel* mchannel[12];//사용할 채널
FMOD_RESULT result;//오류 확인

void *extradriverdate(nullptr);

int current_ix = 0;//파일을 다루기 위한 변수
char notes[NUM_MAX_NOTES];
int length[NUM_MAX_NOTES];
char *rep_notes = NULL;//리플레이시 동적할당을 사용하기 위해서
int *rep_length = NULL;//리플레이시 동적할당을 사용하기 위해서

void init();//FMOD 시스템 초기화, 사운드 생성
void playsound(char note);//생성된 사운드 출력
void Release();//FMOD로 할당된 메모리 해제
void record();
void replay();

void main()
{
	char note = NULL;
	init();

	for (int n = 0; n < NUM_MAX_NOTES; n++)//파일 변수 초기화
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
//Fmod함수의 초기화
void init()
{
	result = FMOD::System_Create(&msystem);//시스템 생성
	if (result != FMOD_OK) printf("시스템 생성 실패");

	result = msystem->init(32, FMOD_INIT_NORMAL, extradriverdate);//시스템 초기화
	if (result != FMOD_OK) printf("시스템 초기화 실패");

	msystem->createSound("sound/25.wav", FMOD_LOOP_OFF, 0, &msound[0]);//소리생성
	msystem->createSound("sound/27.wav", FMOD_LOOP_OFF, 0, &msound[1]);//파일명, 반복 여부, 확장 정보, 사운드 파일과 연결
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

void playsound(char note)//소리 출력
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
	입력한 소리들을 녹음 하는 부분
	파일을 테스트 하기위해 임시로 만듬
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
			length[current_ix - 1] = elapsed_time;//재생 시간 저장
			printf("%dms ", elapsed_time);
		}

		current_ix++;

		time_temp = current_time;


		if (input_character == 13)//엔터키 입력시 실행
		{
			outFile << current_ix << endl;//current_ix값을 저장
			for (int save = 0; save < current_ix; save++)//current_ix값만큼 for문 반복실행
			{
				outFile << notes[save] << length[save] << endl;//fprintf(input_file, "%c %d\n", notes[save], length[save]);//반복할 때마다 txt파일에 저장
			}

			printf("\n\n");
			return;
		}
		playsound(input_character);

		msystem->update();//fmod의 방식때문에 사용해야하는 함수
		//사용해보지 않고 직접 써보니 중간에 음이 나오지 않는 구간이 생겨버림

	}
	outFile.close();
	
}

void replay()
{
	ifstream fin;
	fin.open("record.txt");

	int re_notes;//current_ix의 값
	char re_key;//저장된 키의 값
	int re_length;//저장된 음의 길이
	
	fin >> re_notes;
	current_ix = re_notes;
	rep_notes = (char*)malloc(sizeof(char)*re_notes);
	rep_length = (int*)malloc(sizeof(int)*re_notes);

	for (int i = 0; i < re_notes; i++)//저장된 키 개수만큼 for문을 반복
	{
		fin >> re_key >>re_length;//키 값과 음의 길이를 저장함
		rep_notes[i] = re_key;//저장된 키의 값을 배열에 저장
		rep_length[i] = re_length;//저장된 음의 길이를 배열에 저장
		playsound(rep_notes[i]);//사운드 재생
		Sleep(rep_length[i]);//재생 길이
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