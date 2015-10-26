//CommandHandler
//Do properthings when input a command.
//Author:ShadowK
//email:zhu.shadowk@gmail.com
//2015.10.26
//Use Ctrl+M,Ctrl+O to fold the code.

#include "CommandHandler.h"
#include "ImageDisplayer.h"
#include <vector>
#include <string>

class CommandHandlerImpl
{
public:
	//Compare two strings.(Case insensitive)
	bool compare(const string& x, const string& y);
	//For split string.
	vector<string> split(string str, string pattern);

	void help();
	void load(string s);
	void save(string s);
	void display(string name);
	void hide();
	void exit();

	void calculate();

	void togray();
	void binaryzation();
	void erode();
	void dilate();
	void count();

	IplImage *input = nullptr;
	ImageDisplayer idis;
	int whites;
	int fulls;
};

CommandHandler::CommandHandler()
{
	_impl = new CommandHandlerImpl();
}
CommandHandler::~CommandHandler()
{
	delete _impl;
}
void CommandHandler::begin()
{
	printf("Input command.Input \"help\" for command help.\n$");
}
bool CommandHandler::handle(char *s)
{
	string sr(s);
	return handle(sr);
}
bool CommandHandler::handle(string s)
{
	try
	{
		vector<string> splitstr = _impl->split(s, " ");
		if (_impl->compare(splitstr[0], "help"))
			_impl->help();
		else if (_impl->compare(splitstr[0], "load"))
		{
			if (splitstr.size() < 2)
				printf("Error\n");
			else
				_impl->load(splitstr[1]);
		}
		else if (_impl->compare(splitstr[0], "save"))
		{
			if (splitstr.size() < 2)
				printf("Error\n");
			else
				_impl->save(splitstr[1]);
		}
		else if (_impl->compare(splitstr[0], "display"))
		{
			_impl->display("ImageNow");
		}
		else if (_impl->compare(splitstr[0], "hide"))
		{
			_impl->hide();
		}
		else if (_impl->compare(splitstr[0], "exit"))
		{
			printf("See you next time!\n");
			return true;
		}
		else if (_impl->compare(splitstr[0], "count"))
		{
			printf("Calculating...\n");
			_impl->calculate();
		}
		else
		{
			printf("Error\n");
		}
	}
	catch (...)
	{
		printf("Some error just happened. You may re-input your command if you wish.\n");
	}
	printf("\n");
	return false;
}

bool CommandHandlerImpl::compare(const string& x, const string& y)
{
	string::const_iterator p = x.begin();
	string::const_iterator q = y.begin();
	while (p != x.end() && q != y.end() && toupper(*p) == toupper(*q))
	{
		++p;
		++q;
	}
	if (p == x.end())
	{
		return (q == y.end());
	}
	if (q == y.end())
	{
		return false;
	}
	return false;
}
vector<string> CommandHandlerImpl::split(string str, string pattern)
{
	int pos;
	std::vector<std::string> result;
	if (str[str.length() - 1] == '\n')
		str.pop_back();
	str += pattern;
	int size = str.size();

	for (int i = 0; i < size; i++)
	{
		pos = str.find(pattern, i);
		if (pos < size)
		{
			std::string s = str.substr(i, pos - i);
			result.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}
	return result;
}
void CommandHandlerImpl::help()
{
	printf("\"load <FileName>\" Load or reload a image with full location.\n");
	printf("Sample: load C:\\Users\\WIN_20150404_144352.JPG\n");
	printf("\"display\"Display the image.\n");
	printf("Sameple: display\n");
	printf("\"hide\"Stop displaying the image.\n");
	printf("Sameple: hide\n");
	printf("\"save <FileName>\"Save the image.Input the Name without the path to save it at the location of the program.\n");
	printf("Sameple: save C:\\Users\\WIN_20150404_144352.JPG\n");
	printf("\"count\"Count the bottles\n");
	printf("Sameple: count\n");
	printf("\"exit\"Exit the program\n");
	printf("Sameple: exit\n");
	printf("WARNING:Do not use image which has spaces in its FileName.\n");

}
void CommandHandlerImpl::load(string s)
{
	input = cvLoadImage(s.c_str(), 1);
	if(input == nullptr)
		printf("Wrong FileName.\n");
	else
		printf("Load successful.\n");
}
void CommandHandlerImpl::save(string s)
{
	if (input == nullptr)
	{
		printf("You haven't load an image yet!\n");
	}
	cvSaveImage(s.c_str(), input);
	printf("Save successful.\n");
}
void CommandHandlerImpl::display(string s)
{
	if(input != nullptr)
		idis.display(input,s.c_str());
}
void CommandHandlerImpl::hide()
{
	idis.hide();
}
void CommandHandlerImpl::exit()
{
	printf("See you next time!\n");
}

void CommandHandlerImpl::calculate()
{
	if (input == nullptr)
		return;
	//hide();
	//cvWaitKey(1000);
	togray();
	binaryzation();
	erode();
	dilate();
	count();

	printf("Bottles:%d,Full bottles:%d\n", whites, fulls);
}

void CommandHandlerImpl::togray()
{
	IplImage *p;
	p = cvCreateImage(cvSize(input->width, input->height), input->depth, 1);
	for (int i = 0; i < input->height; i++)
	{
		uchar *pixel = (uchar *)input->imageData + i * input->widthStep;
		uchar *pixelp = (uchar *)p->imageData + i * p->widthStep;
		for (int j = 0; j < input->width; j++)
			pixelp[3 * j] = (uchar)(0.144 * pixel[3 * j] + 0.587 * pixel[3 * j + 1] + 0.299 * pixel[3 * j + 2]);
	}
	cvReleaseImage(&input);
	input = p;
}
void CommandHandlerImpl::binaryzation()
{
}
void CommandHandlerImpl::erode()
{
}
void CommandHandlerImpl::dilate()
{
}
void CommandHandlerImpl::count()
{
}
