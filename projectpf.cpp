#include<iostream>
#include<fstream>
#include<string>
using namespace std;
void  with_out_Normalization(int pos, int neg);//function of with_out_Normalization
void  Normalization(float pos, float neg);//function of Normalization
string **Check_stop_word(char word[][10], int row, int &size_of_key);//function of Check_stop_word
void words_in_dictionary(string **keyword, int&pos, int &neg,float &nor_pos,float &nor_neg, int size_of_key);//function for read words_in_dictionary
int main()
{
	char sen_enter[1000] = { '\0' };//arr for write sentens...
	cout << "text is\n";
	cin.getline(sen_enter, 1000,'.');
	char word[100][10];//array for separate words in sentens...
	int row = 0, col = 0, colum = 10;
	for (int i = 0; ; i++)
	{
		if (sen_enter[i] == ' ' || sen_enter[i] == '\0')//for separate words..
		{
			word[row][col]='\0';
			row++;
			col = 0;
		}
		else
		{
			word[row][col] =sen_enter[i];
			col++;
		}
		if (sen_enter[i] == '\0')
		{
			break;
		}
	}
    string **keywords=NULL;//string for keywords...
	int size_of_key = 0, pos = 0, neg = 0;
	float nor_pos = 0, nor_neg = 0;
	keywords = Check_stop_word(word, row, size_of_key);//calling function for keywords...
	words_in_dictionary(keywords, pos, neg, nor_pos, nor_neg, size_of_key);//calling function for chack words in dictionary,,,
	with_out_Normalization(pos, neg);//calling function to show with_out_Normalization
	Normalization( nor_pos, nor_neg);//calling function to show Normalization
	system("pause");
	return 0;
	
}
void  with_out_Normalization(int pos, int neg)//function of with_out_Normalization
{
	cout << "\nwith_out_Normalization\n";
	cout << "positive count: " << pos;
	cout << "\nNegative count: " << neg;
	if (pos >= neg)
	{
		cout << "\nsentens is positive......";
	}
	else
	{
		cout << "\nsentens is negative......";
	}
}
void  Normalization( float pos, float neg)//function of Normalization
{

	
	cout << "\nwith_Normalization\n";
	cout << "positive count: " << pos;
	cout << "\nNegative count: " << neg;
	if (pos>= neg)
	{
		cout << "\nsentens is positive......";
	}
	else
	{
		cout << "\nsentens is negative......";
	}
}
string **Check_stop_word(char word[][10], int row, int &size_of_key)//function of Check_stop_word
{
	bool check = false;
	bool check2 = true;
	string **keyword = new string*[1];
	for (int n = 0; n < row; n++)//loop for making colums..
	{
		keyword[0] = new string[n];
	}
	char aar[1][20];
	for (int i = 0; i < row; i++)
	{
		//check for non_alphabets
		for (int j = 0; word[i][j] != '\0'; j++)
		{
			if ((word[i][j] >= 'a' && word[i][j] <= 'z') || (word[i][j] >= 'A' &&word[i][j] <= 'Z'))
			{


				check = true;

			}
			else
			{

				check = false;
				break;

			}
			
		}
		//end.....
		
		if (check == true )//check for stop word.....
		{
			ifstream fin;
			fin.open("stopwords.txt");
			int count = 0, f = 0;
			for (int l = 0; !fin.eof(); l++){
				
				char stop_word[1][20] = { '\0' };
				fin >> stop_word[0];
				for (; word[i][f] != '\0'; f++)
				{
					if (word[i][f] == stop_word[0][f])
					{
						count++;
					}
					
				}
				
				
				if (count == f)
				{
					check2 = false;
					break;
				}
				count = 0;
				f = 0;
			}
			
		}

      if (check == true && check2 == true)//store key words in string...
		{
		  keyword[0][size_of_key] = word[i];
		  size_of_key++;

		}
	  check2 = true;
	  }
	
	return  keyword;
	}
void words_in_dictionary(string **keyword, int &pos, int &neg, float &nor_pos, float &nor_neg, int size_of_key)//function for read words_in_dictionary
{
	int totalcounts = 0;
	for (int j = 0; j < size_of_key; j++){

		ifstream red;
		red.open("dictionary.txt");
		for (int i = 0; !red.eof(); i++){
			string red_dic;
			float total_v = 0, positive = 0, negative = 0;
			red >> red_dic;
			red >> total_v;
			red >> positive;
			red>>negative ;
			if (keyword[0][j] == red_dic)//check keyword and dictionary word are similar,...
			{
				pos = pos + positive;//saving positive value with out normalization..
				neg = neg + negative;//saving negative value with out normalization..
				nor_pos = nor_pos +( positive / total_v);//saving positive value with  normalization..
				nor_neg = nor_neg + (negative / total_v);//saving negative value with  normalization..
				break;
			}
			
		}
		
		
		
	}
	
}