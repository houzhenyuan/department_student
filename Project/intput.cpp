#include <iostream> 
#include <string>
#include <fstream>
#include <stdlib.h> 
#include <time.h> 
#include <sstream>

using namespace std;

int main()
{
	srand((unsigned)time(NULL));
	string output;
	string week[7] = { "Mon", "Tues", "Wed", "Thur", "Fri", "Sat", "Sun" };
	string tags[10] = { "basketball", "film", "reading", "chess", "study", "football", "music", "dance", "English", "Game" };
	output = "{\"students\": [";
	for(int i=0;i<300;i++)
	{
		output = output + "{\"free_time\": [";
		int num = (rand() % 9) + 2;
		for (int k = 0; k<num; k++)
		{
			string stime = week[rand() % 7];
			int hour = rand() % 23;
			int hour1 = hour + 2; 
			stringstream ss1;
			string str;
			ss1<<hour;
			ss1>>str;
			stringstream ss2;
			string str1;
			ss2<<hour1;
			ss2>>str1;
			stime = stime + "." + str + ":00~" + str1 + ":00";
			output = output + "\"" + stime + "\"";
			if(k != num-1)
			{
				output = output + ",";
			}
		}
		output = output + "],";
		output = output + "\"" + "student_no" + "\"" + ": ";
		int no = 31502339+i;
		stringstream ss3;
		string str3;
		ss3<<no;
		ss3>>str3;
		output = output + "\"" + "0" + str3 + "\"" + ",";
		output = output + "\"" + "applications_department" + "\"" + ": [";
		int num1 = (rand() % 5) + 1;
		for (int m = 0; m<num1; m++)
		{
			int dep = (rand() % 20) + 1;
			stringstream ss4;
			string str4;
			ss4<<dep;
			ss4>>str4;
			if(dep < 10)
			{
				output = output + "\"D00" + str4 + "\"";
				if(m != num1-1)
				{
					output = output + ",";
				}
			}else{
				output = output + "\"D0" + str4 + "\"";
				if(m != num1-1)
				{
					output = output + ",";
				}
			}
		}
		output = output + "],\"tags\": [";
		int num2 = (rand() % 9) + 2;
		string old1[10];
		int onum1 = 0;
		for (int n = 0; n<num2; n++)
		{
			string tag;
			int flag1;
			do
			{
				flag1 = 0;
				tag = tags[rand() % 10];
				for(int p=0;p<onum1;p++)
				{
					if(old1[p] == tag)
					{							
						flag1 = 1;
						break;
					}
				}
			}
			while(flag1 == 1);
			output = output + "\"" + tag + "\"";
			old1[onum1++] = tag;
			if(n != num2-1)
			{
				output = output + ",";
			}
		}
		output = output + " ]}";
		if(i != 299){
			output = output + ",";
		}
	}
	output = output + "],\"departments\": [";
	for(int t=0;t<20;t++)
	{
		output = output + "{\"event_schedules\": [";
		int num3 = (rand() % 9) + 2;
		for (int n = 0; n<num3; n++)
		{
			string stime1 = week[rand() % 7];
			int hour2 = rand() % 24;
			int hour3 = hour2 + 1; 
			stringstream ss5;
			string str5;
			ss5<<hour2;
			ss5>>str5;
			stringstream ss6;
			string str6;
			ss6<<hour3;
			ss6>>str6;
			stime1 = stime1 + "." + str5 + ":00~" + str6 + ":00";
			output = output + "\"" + stime1 + "\"";
			if(n != num3-1)
			{
				output = output + ",";
			}
		}
		output = output + "],\"member_limit\": ";
		int hour4 = (rand() % 6) + 10;
		stringstream ss7;
		string str7;
		ss7<<hour4;
		ss7>>str7;
		output = output + str7 + ",\"department_no\": ";
		int num4 = t+1;
		stringstream ss8;
		string str8;
		ss8<<num4;
		ss8>>str8;
		if(num4 < 10)
		{
			output = output + "\"D00" + str8 + "\",";
		}else{
			output = output + "\"D0" + str8 + "\",";
		}
		output = output + "\"tags\": [";
		int num5 = (rand() % 9) + 2;
		string old[10];
		int onum = 0;
		for (int l = 0; l<num5; l++)
		{
			string tag1;
			int flag;
			do
			{
				flag = 0;
				tag1 = tags[rand() % 10];
				for(int p=0;p<onum;p++)
				{
					if(old[p] == tag1)
					{
						flag = 1;
						break;
					}
				}
			}
			while(flag == 1);
			output = output + "\"" + tag1 + "\"";
			old[onum++] = tag1;
			if(l != num5-1)
			{
				output = output + ",";
			}
		}
		output = output + " ]}";
		if(t != 19){
			output = output + ",";
		}	
	}
	output = output + " ]}";
		
	ofstream mycout("input_data.txt");
	mycout << output << endl;
	mycout.close();
}
