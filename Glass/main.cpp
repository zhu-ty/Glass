//Glass
//To count the glass.
//Author:ShadowK
//email:zhu.shadowk@gmail.com
//2015.10.26
//Use Ctrl+M,Ctrl+O to fold the code.

#include <string>
#include "CommandHandler.h"

int main()
{
	CommandHandler cmd;
	while (1)
	{
		string str;
		cmd.begin();
		getline(cin, str);
		if (cmd.handle(str))
			break;
	}
	return 0;
}