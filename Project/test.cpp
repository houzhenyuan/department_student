// test.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>  
#include <string>  
#include <iostream>  
#include <fstream>
#include "json/json.h"
#include <stdlib.h> 
#include <time.h> 

using namespace std;



#ifdef DEBUG
#pragma comment(lib, "lib/json_vc71_libmtd.lib") 
#else
#pragma comment(lib, "lib/json_vc71_libmt.lib") 
#endif // DEBUG

int order[300];
string unlucky[300];
string admitted1[300];
string admitted2[300];
int sscore[300];
int unlucky_department[21];


class Student
{
public:
	string student_no;
	string free_time[15];
	string applications_department[20];
	string tags[15];
	int free_time_n;
	int applications_department_n;
	int tags_n;

}Student[300];

class Department
{
public:	string department_no;
		string event_schedules[15];
		string tags[15];
		int member_limit;
		int event_schedules_n;
		int tags_n;

}Department[20];

Json::Reader reader;
Json::Value root;

void Input()
{

	//给Student类赋值
	for (int i = 0; i < root["students"].size(); i++)
	{
		Student[i].student_no = root["students"][i]["student_no"].asString();
		for (int j = 0; j < root["students"][i]["free_time"].size(); j++)
		{
			Student[i].free_time[j] = root["students"][i]["free_time"][j].asString();
		}
		for (int m = 0; m < root["students"][i]["applications_department"].size(); m++)
		{
			Student[i].applications_department[m] = root["students"][i]["applications_department"][m].asString();
		}
		for (int n = 0; n < root["students"][i]["tags"].size(); n++)
		{
			Student[i].tags[n] = root["students"][i]["tags"][n].asString();
		}
		Student[i].free_time_n = root["students"][i]["free_time"].size();
		Student[i].applications_department_n = root["students"][i]["applications_department"].size();
		Student[i].tags_n = root["students"][i]["tags"].size();

	}
	//给Department类赋值
	for (int i = 0; i < root["departments"].size(); i++)
	{
		Department[i].department_no = root["departments"][i]["department_no"].asString();
		for (int j = 0; j < root["departments"][i]["event_schedules"].size(); j++)
		{
			Department[i].event_schedules[j] = root["departments"][i]["event_schedules"][j].asString();
		}
		for (int n = 0; n < root["departments"][i]["tags"].size(); n++)
		{
			Department[i].tags[n] = root["departments"][i]["tags"][n].asString();
		}
		Department[i].member_limit = root["departments"][i]["member_limit"].asInt();
		Department[i].event_schedules_n = root["departments"][i]["event_schedules"].size();
		Department[i].tags_n = root["departments"][i]["tags"].size();
	}
}

void bubble_sort()
{
	for (int k = 0; k<300; k++)
	{
		order[k] = k;
	}
	int i, j, temp;
	for (j = 0; j < 299; j++)
	{
		for (i = 0; i < 299 - j; i++)
		{
			if (Student[order[i]].applications_department_n > Student[order[i + 1]].applications_department_n)
			{
				temp = order[i];
				order[i] = order[i + 1];
				order[i + 1] = temp;
			}
		}
	}
}



int match()
{
	bubble_sort();
	int admitted_num = 0;
	int unlucky_num = 0;
	for (int i = 0; i<300; i++)
	{
		int lucky = 0;
		for (int j = 0; j<Student[i].applications_department_n; j++)
		{
			int score = 0;
			int li = 0;
			for (int k = 0; k<20; k++)
			{
				if (Student[i].applications_department[j] == Department[k].department_no)
				{
					for (int t = 0; t < Department[k].event_schedules_n; t++)
					{
						for (int p = 0; p < Student[i].free_time_n; p++)
						{
							int xq;
							if (Department[k].event_schedules->find("Mon.") != -1) xq = 3;
							if (Department[k].event_schedules->find("Tues.") != -1) xq = 4;
							if (Department[k].event_schedules->find("Wed.") != -1) xq = 3;
							if (Department[k].event_schedules->find("Thur.") != -1) xq = 4;
							if (Department[k].event_schedules->find("Fri.") != -1) xq = 3;
							if (Department[k].event_schedules->find("Sat.") != -1) xq = 3;
							if (Department[k].event_schedules->find("Sun.") != -1) xq = 3;

							string De_week, St_week;
							De_week = Department[k].event_schedules->substr(0, xq);
							St_week = Student[i].free_time->substr(0, xq);
							if (De_week == St_week)
							{
								double De_time1_l, De_time2_l, St_time1_l, St_time2_l;
								double De_time1_r, De_time2_r, St_time1_r, St_time2_r;

								//閮ㄩ棬鏃堕棿璁＄畻
								if (Department[k].event_schedules->substr(xq + 2, 1) == ":")
								{
									De_time1_l = atof(Department[k].event_schedules->substr(xq + 1, 1).c_str());
									De_time2_l = atof(Department[k].event_schedules->substr(xq + 3, 2).c_str());
									if (Department[k].event_schedules->substr(xq + 7, 1) == ":")
									{
										De_time1_r = atof(Department[k].event_schedules->substr(xq + 6, 1).c_str());
										De_time2_r = atof(Department[k].event_schedules->substr(xq + 8, 2).c_str());
									}
									else
									{
										De_time1_r = atof(Department[k].event_schedules->substr(xq + 6, 2).c_str());
										De_time2_r = atof(Department[k].event_schedules->substr(xq + 9, 2).c_str());
									}
								}
								else
								{
									De_time1_l = atof(Department[k].event_schedules->substr(xq + 1, 2).c_str());
									De_time2_l = atof(Department[k].event_schedules->substr(xq + 4, 2).c_str());
									if (Department[k].event_schedules->substr(xq + 8, 1) == ":")
									{
										De_time1_r = atof(Department[k].event_schedules->substr(xq + 7, 1).c_str());
										De_time2_r = atof(Department[k].event_schedules->substr(xq + 9, 2).c_str());
									}
									else
									{
										De_time1_r = atof(Department[k].event_schedules->substr(xq + 7, 2).c_str());
										De_time2_r = atof(Department[k].event_schedules->substr(xq + 10, 2).c_str());
									}
								}

								//瀛︾敓鏃堕棿璁＄畻
								if (Student[i].free_time->substr(xq + 2, 1) == ":")
								{
									St_time1_l = atof(Student[i].free_time->substr(xq + 1, 1).c_str());
									St_time2_l = atof(Student[i].free_time->substr(xq + 3, 2).c_str());
									if (Student[i].free_time->substr(xq + 7, 1) == ":")
									{
										St_time1_r = atof(Student[i].free_time->substr(xq + 6, 1).c_str());
										St_time2_r = atof(Student[i].free_time->substr(xq + 8, 2).c_str());
									}
									else
									{
										St_time1_r = atof(Student[i].free_time->substr(xq + 6, 2).c_str());
										St_time2_r = atof(Student[i].free_time->substr(xq + 9, 2).c_str());
									}
								}
								else
								{
									St_time1_l = atof(Student[i].free_time->substr(xq + 1, 2).c_str());
									St_time2_l = atof(Student[i].free_time->substr(xq + 4, 2).c_str());
									if (Student[i].free_time->substr(xq + 8, 1) == ":")
									{
										St_time1_r = atof(Student[i].free_time->substr(xq + 7, 1).c_str());
										St_time2_r = atof(Student[i].free_time->substr(xq + 9, 2).c_str());
									}
									else
									{
										St_time1_r = atof(Student[i].free_time->substr(xq + 7, 2).c_str());
										St_time2_r = atof(Student[i].free_time->substr(xq + 10, 2).c_str());
									}
								}

								if ((St_time1_l * 60 + St_time1_r) >= 0.8*(De_time1_l * 60 + De_time1_r) && 0.8*(St_time2_l * 60 + St_time2_r) <= (De_time2_l * 60 + De_time2_r))
									li = 1;
							}
						}
					}

					if (li == 1)
					{
						score = score + (10 - j);
						for (int m = 0; m<Student[i].tags_n; m++)
						{
							for (int n = 0; n<Department[k].tags_n;n++)
							{
								if (Student[i].tags[m] == Department[k].tags[n])
								{
									score++;
									break;
								}
							}
						}
						admitted1[admitted_num] = Department[k].department_no;
						admitted2[admitted_num] = Student[i].student_no;
						sscore[admitted_num] = score;
						admitted_num++;
						lucky = 1;
						break;
					}
				}
			}
		}
		if (lucky == 0)
		{
			unlucky[unlucky_num] = Student[i].student_no;
			unlucky_num++;
		}
	}
	return 0;
}

void output()
{
	ofstream mycout("output_data.txt");
	mycout <<'{'<< endl;
	//输出unlucky
	mycout << "    " << '\"' << "unlucky_student" << '\"' << ":  ";
	mycout << '[' << endl;
	int x = 1;
	for (int i = 0; i < sizeof(unlucky) / sizeof(unlucky[0]); i++)
	{
		if (unlucky[i] != ""&&x!=0)
		{
			mycout << "        " ;
			mycout  << '\"' << unlucky[i] << '\"' ;
			x--;
		}
		else
		if (unlucky[i] != ""&&x == 0)
		{
			mycout << ',' << endl;
			mycout << "        ";
			mycout << '\"' << unlucky[i] << '\"';
		}
	}
	mycout <<"    "<< ']' <<','<< endl;

	//输出admitted
	mycout << "    "<<'\"'<<"admitted"<<'\"'<<":  ";
	mycout << '[' << endl;
	for (int i = 1; i <= 20; i++)
	{
		mycout << "        {" << endl;
		//输出member
		mycout << "            " << '\"' << "member" << '\"' << ":  ";
		mycout << '[' << endl;
		int x = 1;
		for (int j = 0; j < 300; j++)
		{
			if (admitted1[j] != "")
			{
				double ad1 = atof(admitted1[j].substr(2, 2).c_str());
				if (ad1 == i)
				{
					if (admitted2[j] != ""&& x!=0)
					{
						mycout << "                " << '\"' << admitted2[j] << '\"' ;
						unlucky_department[i] = 1;
						x--;
					}
					else
					if (admitted2[j] != ""&& x == 0)
					{
						 mycout << ',' << endl;
						mycout << "                " << '\"' << admitted2[j] << '\"';
						unlucky_department[i] = 1;
					}
				}
			}
		}
		mycout << "            ]," << endl;
		mycout << "            " << '\"' << "department_no" << '\"' << ":  ";
		mycout << '\"' <<  "D00" << i<<'\"' <<  endl;
		if(i!=20)
		mycout << "        }," << endl;
		else
			mycout << "        }" << endl;
	}
	mycout << "    " << ']' << ',' << endl;

	//输出unlucky_department
	mycout << "    " << '\"' << "unlucky_department" << '\"' << ":  ";
	mycout << '[' << endl;
	int z=1;
	for (int i = 1; i <= 20; i++)
	{
		if (unlucky_department[i] != 1 && z != 0)
		{
			mycout << "        " << '\"' << "D00" << i << '\"';
			z--;
		}
		else
			if (unlucky_department[i] != 1 && z != 0)
			{
				mycout << ',' << endl;
				mycout << "        " << '\"' << "D00" << i << '\"';
			}
	}
	mycout << "    " << ']'  << endl;

	mycout << '}' << endl;
	mycout.close();

}

int main()
{
	
	//从文件中读取
	ifstream is;
	is.open("input_data.txt", ios::binary);

	if (reader.parse(is, root))
	{

		Input();
		match();
		output();
	}
	is.close();
	return 0;
}

