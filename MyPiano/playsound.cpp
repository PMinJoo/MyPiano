#include "playsound.h"

#define NUM_MAX_NOTES 1000

using namespace std;
using namespace FMOD;

System *msystem(nullptr);//�ý��� ����
Sound* msound[15];//����� ������ ������ŭ �迭�� ����
Channel* mchannel[15];//����� ä��
FMOD_RESULT result;//���� Ȯ��



void *extradriverdate(nullptr);

int current_ix = 0;//������ �ٷ�� ���� ����
char notes[NUM_MAX_NOTES];
int length[NUM_MAX_NOTES];

PlayNote::PlayNote()
{

}

PlayNote::~PlayNote()
{

}

void main()
{
	char note = NULL;
	PlayNote test;

	test.init();

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

	//replay();

	//play();

	//test.free_play();

	test.practice_play();
	
	//Release();

	while (1);
}

/*************************************************************************
	FMOD �Լ� �ʱ�ȭ
	sound���� �κ�
**************************************************************************/
void PlayNote::init()
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
	msystem->createSound("o.wav", FMOD_LOOP_OFF, 0, &msound[13]);
	msystem->createSound("x.wav", FMOD_LOOP_OFF, 0, &msound[14]);
}


/****************************************************************************
	�Ҹ��� ����ϴ� �κ�
	FMOD�� channel�� �̿��� �Ҹ��� ��ġ�� ��� �� �� �ִ�.
**************************************************************************/

void PlayNote::playsound(char note)
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

void PlayNote::Release()
{
	msystem->release();
}

/*****************************************************************
	�Է��� �Ҹ����� ���� �ϴ� �κ�
	������ �׽�Ʈ �ϱ����� �ӽ÷� ����
*****************************************************************/
void PlayNote:: record()
{
	ofstream outFile("output.txt");

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

		msystem->update();
	}
	outFile.close();
}


/***********************************************************************************
	��ü ���� ����Ѵ�.
************************************************************************************/
void PlayNote::play()
{

	char *rep_notes = NULL;//��ü ��Ʈ�� ��
	int *rep_length = NULL;//��Ʈ�� ����

	ifstream fin;
	fin.open("1.txt");

	int re_notes;//current_ix�� ��
	char re_key;//����� Ű�� ��
	int re_length;//����� ���� ����
	
	fin >> re_notes;
	current_ix = re_notes;
	rep_notes = (char*)malloc(sizeof(char)*re_notes);//��ü ��Ʈ�� ���� ��ŭ �Ҵ�
	rep_length = (int*)malloc(sizeof(int)*re_notes);

	for (int i = 0; i < re_notes; i++)//����� Ű ������ŭ for���� �ݺ�
	{
		fin >> re_key >>re_length;//Ű ���� ���� ���̸� ������
		rep_notes[i] = re_key;//����� Ű�� ���� �迭�� ����
		rep_length[i] = re_length;//����� ���� ���̸� �迭�� ����
		if (rep_length[i] == '\n')
		{
			re_notes++;
		}
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
/******************************************************************************
	��������
*******************************************************************************/
void PlayNote::free_play()
{
	char input_character;
	while (true)
	{
		input_character = (char)_getch();

		playsound(input_character);

		msystem->update();
	}

}

/******************************************************************************
	�ݺ�����
*******************************************************************************/

void PlayNote::practice_play()
{
	char *rep_notes = NULL;//��ü ��Ʈ�� ��
	int *rep_length = NULL;//��Ʈ�� ����

	ifstream fin;
	fin.open("2.txt");

	int re_notes;//current_ix�� ��
	char re_key;//����� Ű�� ��
	int re_length;//����� ���� ����

	fin >> re_notes;
	current_ix = re_notes;
	rep_notes = (char*)malloc(sizeof(char)*re_notes);//��ü ��Ʈ�� ���� ��ŭ �Ҵ�
	rep_length = (int*)malloc(sizeof(int)*re_notes);

	int size = re_notes;
	int line = 0;
	int line_note_size = 0;
	for (int i = 0; i < re_notes; i++)//����� Ű ������ŭ for���� �ݺ�
	{
		fin >> re_key >> re_length;//Ű ���� ���� ���̸� ������
		rep_notes[i] = re_key;//����� Ű�� ���� �迭�� ����
		rep_length[i] = re_length;//����� ���� ���̸� �迭�� ����

		if (rep_notes[i] == 'x')
		{
			size++;//�ܶ��� ������ŭ ������ ����
			line++;//�ܶ��� ���� ����.
		}
		//printf("%c\n", rep_notes[i]);
	}

	int* line_place= (int*)malloc(sizeof(int)*line);
	int temp = 0;
	for (int i = 0; i < size; i++)
	{
		if (rep_notes[i] == 'x')
		{
			line_place[temp++] = i;
		}
	}
	
	int* line_note = (int*)malloc(sizeof(int)*line);
	int buf = 0;
	for (int i = 0; i < line; i++)
	{
		if(buf == 0) line_note[buf++] = line_place[i] - 1;
		else line_note[buf++] = line_place[i] - line_place[i - 1] - 1;
	}

	for (int i = 0; i < line; i++)
	{
		cout << line_place[i] << '/';
		cout << line_note[i] << endl;
	}

	char input_character = NULL;
	char temp_note[100];
	int count = 0;
	int check = 1;
	for (int i = 0; i < line; i++)
	{
	
			for (int j = 0; j < line_note[i]+1; j++)
			{
				if(i ==0) playsound(rep_notes[j]);
				else playsound(rep_notes[j + line_place[i-1]+1]);
				Sleep(500);
			}

			for (int k = 0; k < line_note[i]+1; k++)
			{
				input_character = (char)_getch();
				temp_note[k] = input_character;
				playsound(temp_note[k]);
				Sleep(500);
			}

			for (int z = 0; z < line_note[i]+1; z++)
			{
				if (rep_notes[z] != temp_note[z])
				{
					count++;
					Sleep(300);
				}
			}

			if (count == 0)
			{
				msystem->playSound(msound[13], 0, false, NULL);
				Sleep(600);
				
			}
			else
			{
				count = 0;
				msystem->playSound(msound[14], 0, false, NULL);
				Sleep(300);
			}
		

	}
	



}
/*
void PlayNote::parser(char* note, int note_size)
{
	char test[4][10];
	for (int i = 0; i < note_size; i++)
	{
		
	}

}

char* note_save(int size)
{
	char input_character;
	char* save = (char*)malloc(sizeof(char)*size);

	for(int i = 0; i < size; i++)
	{
		input_character = (char)_getch();

		save[i] = input_character;

		playsound(input_character);

		msystem->update();
	}
	return save;
}
*/