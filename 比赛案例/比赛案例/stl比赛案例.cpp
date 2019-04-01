#include<map>   
#include<vector>  
#include<algorithm>            
#include<functional>      
#include<iterator>  
#include<iostream>  
#include <string>  
#include <deque>  
#include <numeric>  
using namespace std;

class Speaker
{
public:
protected:
public:
	string name;
	float score[3];
};

int GenSpeaker(map<int, Speaker> &m, vector<int>&v)
{
	string str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	random_shuffle(str.begin(), str.end());

	for (int i = 0; i<24; i++)
	{
		Speaker tmp;
		tmp.name = "选手";
		tmp.name = tmp.name + str[i];
		//tmp.score = 0;  
		m.insert(pair<int, Speaker>(100 + i, tmp));
	}

	for (int i = 0; i<24; i++)
	{
		v.push_back(100 + i);
	}
	return 0;
}
int speech_contest_draw(vector<int>&v)
{
	random_shuffle(v.begin(), v.end());
	return 0;
}
int speech_contest(int index, vector<int>&v, map<int, Speaker> &m, vector<int>&v2)
{
	//小组的比赛得分 记录下来 求出前三名 后三名  
	multimap<int, int, greater<int>> mg;//按照key从大到小排列  
	int tmpCount = 0;
	int num = 1;
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		tmpCount++;
		{//评委给每个选手打分  
			deque<int> dscore;//存方得分  
			for (int i = 0; i<10; i++)
			{
				int score = 50 + rand() % 51;
				dscore.push_back(score);
			}
			//对得分排序 去最高 最低  
			sort(dscore.begin(), dscore.end());
			dscore.pop_back();//去最低分  
			dscore.pop_front();//去最高分  
			//求平均  
			int sum = accumulate(dscore.begin(), dscore.end(), 0);
			float average = sum / dscore.size();
			//选手得分存  
			m[*it].score[index] = average;
			mg.insert(pair<int, int>(average, *it));//平均分 编号  
		}
		//处理分组  
		if (tmpCount % 6 == 0)
		{
			cout << "第" << index + 1 << "轮小组" << num << "的比赛成绩" << endl;
			cout << "编号\t" << "姓名\t" << "得分" << endl;
			for (multimap<int, int, greater<int>>::iterator mit = mg.begin(); mit != mg.end(); mit++)
			{
				//编号 姓名 得分  
				cout << mit->second << "\t" << m[mit->second].name << "\t" << m[mit->second].score[index] << endl;
			}
			//前三名存入v2 晋级 遍历容器    
			while (mg.size()>3)
			{
				multimap<int, int, greater<int>>::iterator it = mg.begin();
				v2.push_back(it->second);//前三名晋级  
				mg.erase(it);
			}
			mg.clear();
			num++;
		}
	}
	return 0;
};
int speech_contest_print(int index, vector<int>&v, map<int, Speaker>&m)
{
	cout << "第" << index + 1 << "轮比赛晋级名单" << endl;
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << "\t" << m[*it].name << "\t" << m[*it].score[index] << endl;
	}
	return 0;
}
int main()
{
	map<int, Speaker> mapSpeaker;//所有参赛选手名单  

	vector<int> v1;//第1轮演讲比赛名单  
	vector<int> v2;//第2轮演讲比赛名单  
	vector<int> v3;//第3轮演讲比赛名单  
	vector<int> v4;//演讲名单  

	//产生选手 得到第1轮选手比赛名单  
	GenSpeaker(mapSpeaker, v1);
	//第1轮 选手抽签 选手比赛 查看结果  
	
	speech_contest_draw(v1);
	speech_contest(0, v1, mapSpeaker, v2);
	speech_contest_print(0, v2, mapSpeaker);
	//第2轮 选手抽签 选手比赛 查看结果  
	
	speech_contest_draw(v2);
	speech_contest(1, v2, mapSpeaker, v3);
	speech_contest_print(1, v3, mapSpeaker);
	//第3轮 选手抽签 选手比赛 查看结果  
	
	speech_contest_draw(v3);
	speech_contest(2, v3, mapSpeaker, v4);
	speech_contest_print(2, v4, mapSpeaker);
	system("pause");
	return 0;
}