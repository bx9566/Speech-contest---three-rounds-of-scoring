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
		tmp.name = "ѡ��";
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
	//С��ı����÷� ��¼���� ���ǰ���� ������  
	multimap<int, int, greater<int>> mg;//����key�Ӵ�С����  
	int tmpCount = 0;
	int num = 1;
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		tmpCount++;
		{//��ί��ÿ��ѡ�ִ��  
			deque<int> dscore;//�淽�÷�  
			for (int i = 0; i<10; i++)
			{
				int score = 50 + rand() % 51;
				dscore.push_back(score);
			}
			//�Ե÷����� ȥ��� ���  
			sort(dscore.begin(), dscore.end());
			dscore.pop_back();//ȥ��ͷ�  
			dscore.pop_front();//ȥ��߷�  
			//��ƽ��  
			int sum = accumulate(dscore.begin(), dscore.end(), 0);
			float average = sum / dscore.size();
			//ѡ�ֵ÷ִ�  
			m[*it].score[index] = average;
			mg.insert(pair<int, int>(average, *it));//ƽ���� ���  
		}
		//�������  
		if (tmpCount % 6 == 0)
		{
			cout << "��" << index + 1 << "��С��" << num << "�ı����ɼ�" << endl;
			cout << "���\t" << "����\t" << "�÷�" << endl;
			for (multimap<int, int, greater<int>>::iterator mit = mg.begin(); mit != mg.end(); mit++)
			{
				//��� ���� �÷�  
				cout << mit->second << "\t" << m[mit->second].name << "\t" << m[mit->second].score[index] << endl;
			}
			//ǰ��������v2 ���� ��������    
			while (mg.size()>3)
			{
				multimap<int, int, greater<int>>::iterator it = mg.begin();
				v2.push_back(it->second);//ǰ��������  
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
	cout << "��" << index + 1 << "�ֱ�����������" << endl;
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << "\t" << m[*it].name << "\t" << m[*it].score[index] << endl;
	}
	return 0;
}
int main()
{
	map<int, Speaker> mapSpeaker;//���в���ѡ������  

	vector<int> v1;//��1���ݽ���������  
	vector<int> v2;//��2���ݽ���������  
	vector<int> v3;//��3���ݽ���������  
	vector<int> v4;//�ݽ�����  

	//����ѡ�� �õ���1��ѡ�ֱ�������  
	GenSpeaker(mapSpeaker, v1);
	//��1�� ѡ�ֳ�ǩ ѡ�ֱ��� �鿴���  
	
	speech_contest_draw(v1);
	speech_contest(0, v1, mapSpeaker, v2);
	speech_contest_print(0, v2, mapSpeaker);
	//��2�� ѡ�ֳ�ǩ ѡ�ֱ��� �鿴���  
	
	speech_contest_draw(v2);
	speech_contest(1, v2, mapSpeaker, v3);
	speech_contest_print(1, v3, mapSpeaker);
	//��3�� ѡ�ֳ�ǩ ѡ�ֱ��� �鿴���  
	
	speech_contest_draw(v3);
	speech_contest(2, v3, mapSpeaker, v4);
	speech_contest_print(2, v4, mapSpeaker);
	system("pause");
	return 0;
}