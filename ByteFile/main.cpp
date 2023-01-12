#include <iostream>
#include <fstream>
#include <string> 
#include <windows.h>
using namespace std;

inline bool FileExists(const string& name) {
    struct stat buffer;
    int n = (stat(name.c_str(), &buffer) == 0);
    if (n == 0) { return false; }
    else { return true; }
}

void GetHexCode(string path, int space)
{
    ifstream fi(path, std::ios_base::in | std::ios_base::binary);
    fi.seekg(0, ios::end);
    int sizebytes = fi.tellg();
    fi.close();
    ofstream out;
    out.open("output.txt");
    if (out.is_open())
    {
        out << "char ByteArray[" << sizebytes << "]\n{\n";
        int mega = 0;
        ifstream in(path, std::ios_base::in | std::ios_base::binary);
        char buf;

        for (int i = 0; i < sizebytes; i++)
        {
            mega++;
            in.read(&buf, sizeof(char));
            out << "(char)0x" << hex << (uint64_t)buf << ", ";
            if (mega == space)
            {
                out << endl;
                mega = 0;
            }
        }
        out << "\n};";
    }
}

int main()
{
    SetConsoleTitle(L"BYTE++");
	string input;
    string FirstPath;
    int ArraySpace;
	while (1!=0)
	{
		cout << "Command>> ";
		cin >> input;
		if (input == "hex")
		{
            cout << "Target File Path>> ";
            cin >> FirstPath;
            if (!FileExists(FirstPath))
            {
                cout << "\n[File not existing]\n\n";
                continue;
            }

            cout << "Count bytes in line>> ";
            cin >> ArraySpace;

            GetHexCode(FirstPath,ArraySpace);
            cout << "\n[File output.txt created]\n\n";
            continue;
		}
	}
}