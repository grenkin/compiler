#include <iostream>

#include "run\run.h"

int main(int argc, char* argv[])
{
    bool flag = false;
    if (argc == 3) {
        flag = true;
        if (strcmp(argv[1], "/l") == 0)
			RunLexer(argv[2], std::cout);
        else if (strcmp(argv[1], "/s") == 0)
			RunParser(argv[2], std::cout);
		else if (strcmp(argv[1], "/noopt") == 0) {
			RunCompiler(argv[2]);
			RunCompiler(argv[2], true);
		}
        else
            flag = false;
    }
    else if (argc == 2) {
        flag = true;
		RunCompiler(argv[1]);
    }

    if (!flag) {
		std::cout << "C compiler" << "\n" << "Gleb Grenkin, 2010" << std::endl;
		std::cout << "compiler.exe [/l | /s | /noopt] <file>" << std::endl;
    }

    return 0;
}
