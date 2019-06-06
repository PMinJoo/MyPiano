
#include <nana/gui/wvl.hpp>
#include <nana/gui/filebox.hpp>
#include <nana/gui/wvl.hpp>
#include <nana/gui/widgets/button.hpp>
#include <iostream> 
#include <string>

using namespace std;
using namespace nana;

string get_file_path();

int main()
{

	form mainform;

	mainform.size({ 600, 200 });
	
	mainform.caption("My Piano");

	button btn1(mainform, rectangle(50, 10, 100, 60));//x축 y축 가로,세로
	btn1.caption("Select File");

	button btn2(mainform, rectangle(250, 10, 100, 60));
	btn2.caption("Play");

	button btn3(mainform, rectangle(450, 10, 100, 60));
	btn3.caption("Pratice Play");

	btn1.events().click(get_file_path);

	mainform.show();

	exec(
#ifdef NANA_AUTOMATIC_GUI_TESTING
		2, 1, [&btn1]()
	{
		click(btn1);
	}
#endif
	);

}

string get_file_path()
{
	string pathtoStr;//입력 받은 파일 값을 저장

	filebox::path_type path;
	filebox fb(0, true);
	fb.add_filter(("Image File"), ("*.png;*.jpg"));
	fb.add_filter(("All Files"), ("*.*"));

	auto files = fb();

	path = files.front();//파일의 경로를 가져온다.

	pathtoStr = path.u8string();

	cout << pathtoStr;

	return pathtoStr;
}
