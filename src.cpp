#include<iostream>
#include<stack>
#include<string>
using namespace std;
//Basic caculator I, the string only contains +£¬-£¬£¨£¬£©£¬and space.
int calculate_v1(string& s)
{
	int len = s.length(), i = 0;
	stack<char> op;
	stack<int> data;
	while (i < len)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			int x = s[i] - '0';
			i++;
			while (i < len && s[i] >= '0' && s[i] <= '9')
			{
				x = x * 10 + s[i] - '0';
				i++;
			}
			data.push(x);
		}
		else if (s[i] == '(')
		{
			op.push('(');
			i++;
		}
		else if (s[i] == ')')
		{
			while (op.top() != '(')
			{
				int z = data.top();
				data.pop();
				int y = data.top();
				data.pop();
				if (op.top() == '+')
					data.push(y + z);
				else
					data.push(y - z);
				op.pop();
				//op.push(s[i]);
			}
			op.pop();
			i++;
		}
		else if (s[i] == '+' || s[i] == '-')
		{
			if (op.empty() || op.top() == '(')
				op.push(s[i]);
			else
			{
				int z = data.top();
				data.pop();
				int y = data.top();
				data.pop();
				if (op.top() == '+')
					data.push(y + z);
				else
					data.push(y - z);
				op.pop();
				op.push(s[i]);
			}
			i++;
		}
		else
			i++;
	}
	if (!data.empty())
	{
		while (!op.empty())
		{
			int z = data.top();
			data.pop();
			int y = data.top();
			data.pop();
			if (op.top() == '+')
				data.push(y + z);
			else
				data.push(y - z);
			op.pop();
		}
		return data.top();
	}
	else
		return 0;
}

//Basic caculator II, the string contains only non-negative, -,*,/,+ and spaces.
int calculate(const string&s)
{
	
	int len = s.length();
	stack<char> op;
	stack<int> data;
	int i = 0;
	while (i < len)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			int x = s[i] - '0';
			i++;
			while (i < len && s[i] >= '0' && s[i] <= '9') 
			{
				x = x * 10 + s[i] - '0';
				i++;
			}
			data.push(x);
		}
		else
		{
			switch (s[i])
			{
			case '+':
			case '-':
				if (op.empty())
					op.push(s[i]);
				else
				{
					while (!op.empty()) 
					{
						int z = data.top();
						data.pop();
						int y = data.top();
						data.pop();
						switch (op.top())
						{
						case '+':
							data.push(y + z);
							break;
						case '-':
							data.push(y - z);
							break;
						case '/':
							data.push(y / z);
							break;
						case '*':
							data.push(y * z);
							break;
						}
						op.pop();
					}
					op.push(s[i]);
				}
				break;
			case '*':
			case '/':
				if (op.empty())
					op.push(s[i]);
				else
				{
					if (op.top() == '*' || op.top() == '/')
					{

						int z = data.top();
						data.pop();
						int y = data.top();
						data.pop();
						if (op.top() == '*')
							data.push(y * z);
						else if (op.top() == '/')
							data.push(y / z);
						op.pop();
						//op.push(s[i]);
					}
					op.push(s[i]);
				}
				break;
			}
			i++;
		}
	}
	if (!data.empty())
	{
		while (!op.empty())
		{
			int z = data.top();
			data.pop();
			int y = data.top();
			data.pop();
			switch (op.top())
			{
			case '+':
				data.push(y + z);
				break;
			case '-':
				data.push(y - z);
				break;
			case '/':
				data.push(y / z);
				break;
			case '*':
				data.push(y * z);
				break;
			}
			op.pop();
		}
		return data.top();
	}
	else
		return 0;
}

int main()
{
	string expression = "1*2-3/4+5*6*3+4-7*8+9/10 ";
	int ret = calculate(expression);
	//cout << ret << endl;
	//int sum = calculate(experssion);
	cout << expression << " = " << ret << endl;
	return 0;
}