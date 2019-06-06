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

	//FMOD 시스템 초기화, 사운드 생성
	void init();

	//생성된 사운드 출력
	void playsound(char note);

	//FMOD로 할당된 메모리 해제
	void Release();

	// 입력 및 텍스트 파일 생성용 
	void record();

	//전체곡 연주 모드
	void play();

	//자유 연주 모드
	void free_play();

	//연습 연주 모드
	void practice_play();

};