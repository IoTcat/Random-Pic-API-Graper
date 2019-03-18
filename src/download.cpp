#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <istream>
#include <vector>
#include <cstdio>
#include "md5.h"
#include "ovo.h"

using namespace std;

void vbs_body(string s, unsigned int i)
{

    ofstream o;
    o.open("tmp_download.vbs");

    o << "Dim Url, Target" << endl;
    o << "Url = \"" << s << "\"" << endl;
    o << "dim a" << endl << endl;
    o << "a=0" << endl;
    o << "do" << endl << endl;
    o << "a=a+1" << endl << endl;
    o << "Target = a&\".jpg\" " << endl;
    o << "Download Url,Target " << endl << endl;
    o << "loop while a<" << i << endl << endl;
    o << "Sub Download(url,target) " << endl;
    o << "  Const adTypeBinary = 1 " << endl;
    o << "  Dim http,ado  " << endl;
    o << "  Const adSaveCreateOverWrite = 2 " << endl;
    o << "  Set http = CreateObject(\"Msxml2.ServerXMLHTTP\") " << endl;
    o << "  http.open \"GET\",url,False " << endl;
    o << "  http.send " << endl;
    o << "  Set ado = createobject(\"Adodb.Stream\") " << endl;
    o << "  ado.Type = adTypeBinary " << endl;
    o << "  ado.Open " << endl;
    o << "  ado.Write http.responseBody " << endl;
    o << "  ado.SaveToFile target " << endl;
    o << "  ado.Close " << endl;
    o << "End Sub " << endl;

    o.close();
}

void vbs_body_force(int t, string s, unsigned int i)
{
    ofstream o;
    o.open("tmp_download.vbs");

    o << "Dim Url, Target" << endl;
    o << "Url = \"" << s << "\"" << endl;
    o << "dim a" << endl << endl;
    o << "a=" << t << endl;
    o << "Target = a&\".jpg\" " << endl;
    o << "Download Url,Target " << endl << endl;
    o << "Sub Download(url,target) " << endl;
    o << "  Const adTypeBinary = 1 " << endl;
    o << "  Dim http,ado  " << endl;
    o << "  Const adSaveCreateOverWrite = 2 " << endl;
    o << "  Set http = CreateObject(\"Msxml2.ServerXMLHTTP\") " << endl;
    o << "  http.open \"GET\",url,False " << endl;
    o << "  http.send " << endl;
    o << "  Set ado = createobject(\"Adodb.Stream\") " << endl;
    o << "  ado.Type = adTypeBinary " << endl;
    o << "  ado.Open " << endl;
    o << "  ado.Write http.responseBody " << endl;
    o << "  ado.SaveToFile target " << endl;
    o << "  ado.Close " << endl;
    o << "End Sub " << endl;

    o.close();
}

int main(int argc, char const *argv[])
{
    string ss;
    cout << "Input the API url to grap = ";
    cin >> ss;

    unsigned int i;
    cout << "What's the number you are expected = ";
    cin >> i;

    cout << "Please input '1' for quick mode and '2' for force mode = ";

    int mode;
    cin >> mode;

    system("md download");

    system("cls & echo Start to grap...");

    if(mode == 1){
        vbs_body(ss, i);

        system("wscript tmp_download.vbs");

        system("del tmp_download.vbs");
    }
    else{

        for(int ii =0; ii < i; ii++){

            vbs_body_force(ii, ss, i);
            system("wscript tmp_download.vbs");
            system("del tmp_download.vbs");
            cout << "Downloading " << ii << "/" << i << " ..." << endl;
        }
    }


    system("echo Grap finished !!!");

    system("echo Begin to remove repeated file...");

    /** remove repeat part  **/

    ovo::file f,t_f;
    vector<string> s;
    vector<string> fs;


    t_f.get_files_info(".\\","*.jpg");


    for(int i = 0; i < t_f.num(); i++){cout << t_f.file[i].name << endl;

        string tts = "move \"";

        tts += t_f.file[i].name;

        tts += "\" download\\";

        std::cout << tts << "\n";

        system(tts.c_str());
    }

    f.get_files_info("download\\");

    int count;

    system("cd download");
    for(int i = 0; i < f.num(); i++){

        string t_name = "download\\" + f.file[i].name;
        
        string t = md5file((t_name).c_str());

        for(count = -1; ++count < s.size(); ){

            if(s[count] == t) break;
        }

        if(count == s.size()){

            s.push_back(t);
            fs.push_back(f.file[i].name);
        }else{

            string ts = "del download\\\"";

            ts += f.file[i].name;

            ts += "\"";

            std::cout << ts << "\n";

            system(ts.c_str());
        }
    }

    system("cls & echo Start to reorder files...");

    system("setlocal enabledelayedexpansion");
    system("set /a b=0");
    system("dir /b/od");
    system("for /f \"delims=\" %%f in ('dir /b/od *.*') do (");
    system("  if not \"%%f\"==\"%~nx0\" (");
    system("           set /a b+=1 ");
    system("           ren \"%%f\" \"!b!%%~xf\"");
    system("           echo. !b!%%~xf");
    system(")");
    system(")");

    system("cls & echo All Finished!!");

    cout << "Graped " << s.size() << " pics!!" << endl;

    return 0;
}



