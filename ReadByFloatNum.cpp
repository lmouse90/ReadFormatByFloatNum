/*
题目：
一个浮点数，输出他的英文读法，
比如456456.222读four hundred fifty six thousand four hundred fifty six point two two two，
默认小数点后3位，小数点前最长12位，也就是到billion。
*/


/*
从后往前，每三位为一组转化为十进制数从低到高存放在数组中
然后从高往低依次处理
由于长度为12并且小数点后默认3位，所以可以进行特殊处理
*/

#include <iostream>
#include <string>
using namespace std;

string str;
int data[5] = {0}; //存放划分的数据，0位存放小数部分，1-4存放整数部分
string sigleNum[10] = {"zero","one","two","three","four","five","six","seven","eight","nine"};
string eleven2Nineteen[10] = {"ten","eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen"};
string twenty2Ninety[8] = {"twenty","thirty","forty","fifty","sixty","seventy","eighty","ninety"};
string largeNum[] = {"thousand","million","billion"};

//根据三位数据获得相应的英文字母
//0 - zero
//12 - twelve
//345 - three hundred forty five
string getString(int data)
{
	string str;
	if(data == 0)
	{
		str = sigleNum[0];
		str += " ";
	}
	else
	{
		if(data/100)
		{
			str = sigleNum[data/100];
			str += " ";
			str += "hundred";
			str += " ";
		}

		data = data - data/100*100;
		if(data/10 > 1)
		{
			str += twenty2Ninety[data/10-2];
			str += " ";
			if(data%10)
			{
				str += sigleNum[data%10];
				str += " ";
			}
		}
		else if(data/10 == 1)
		{
			str += eleven2Nineteen[data%10];
			str += " ";
		}
		else
		{
			if(data%10)
			{
				str += sigleNum[data%10];
				str += " ";
			}
		}
	}
	return str;
}
int main()
{
	while(cin >> str)
	{
		int len = str.length();
		if(len > 12) return;

		int startIndex = len - 1;  //字符串处理起始位，从后向前处理

		bool bExistPoint = false;  //是否存在小数
		if(len >= 5 && str[len-4] == '.') //题目固定如果存在小数则长度为3，所以此处直接判断倒数第4位，并把小数部分保存为为一个整数
		{
			data[0] = (str[len-3]-'0')*100 + (str[len-2]-'0')*10 + (str[len-1]-'0') ;
			startIndex = len - 5;
			len = len - 4;
			bExistPoint = true;
		}
		int segment = len%3 == 0? len/3 : len/3+1; //整数部分总共几部分，3位为一个单元
		 //把每部分的值转化为十进制整数，存在数组中
		for(int i=0; i<segment; i++)
		{
			if(startIndex >= 0)
			{
				data[i+1] += (str[startIndex]   - '0');
				startIndex--;
			}
			if(startIndex >= 0)
			{
				data[i+1] += (str[startIndex]   - '0')*10;
				startIndex--;
			}
			if(startIndex >= 0)
			{
				data[i+1] += (str[startIndex]   - '0')*100;
				startIndex--;
			}
		}
		 //从高位到低位依次输出
		while(segment > 0)
		{
			int tmpData = data[segment];
			string tmpStr = getString(tmpData);
			cout << tmpStr;
			if(segment > 1)  //此处输出是否是千、十万、千万的数
			{
				cout << largeNum[segment-2] << " ";
			}
			segment--;
		}
		if(bExistPoint)   //如果小数存在则输出小数
		{
			cout << "point " << sigleNum[data[0]/100] << " " << sigleNum[(data[0]-data[0]/100*100)/10] << " " << sigleNum[data[0]%10];
		}
		cout << endl;

		for(int i=0; i<5; i++) data[i] = 0;
	}
	
	return 0;
}
