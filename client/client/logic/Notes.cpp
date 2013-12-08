#include <iostream>
#include <cmath>
using namespace std;

typedef pair<unsigned int, unsigned int> banknote; //тип банкноти (номінал, кількість)

static unsigned int notes[6] = {10, 20, 50, 100, 200, 500}; //масив номіналів купюр
static banknote stackNotes[6] = {  //номінал та наявна кількість купюр
	make_pair(notes[0],12),
	make_pair(notes[1], 5),
	make_pair(notes[2],20),
	make_pair(notes[3], 5),
	make_pair(notes[4], 0),
	make_pair(notes[5], 3) };

bool check (unsigned int smth)
{
	return (smth % 10 == 0);
}

void give_some_money (unsigned int sum)
{
	if (!check(sum)) //перевірка чи кратна сума 10
	{
		cout<<"Invalid data: "<<sum<<endl;
		return;
	}
	unsigned int max_note = 500;
	unsigned int max_index = 5;
	for (int i=0; i<5; i++) //знайдемо у якому проміжку знаходиться необхідна сума
	{
		if ((sum/500 != 0))
			break;  //сума більша за 500 - максимальна купюра лишається 500
		if((sum/notes[i]!=0) && (sum/notes[i+1]==0))
		{ //якщо сума у заданому проміжку, запам'ятовуємо максимальний номінал та індекс
			max_note = notes[i];
			max_index = i;
			break;
		}
	}
	unsigned int temp_sum = sum; //змінна для зменшеня суми ще не виданих грошей
	banknote cash[6] = {make_pair(500,0), //набір купюр, яким буде видаватись сума
		make_pair(200,0), make_pair(100,0), make_pair(50,0),
		make_pair(20, 0), make_pair(10, 0)};
	int index(0); //індекс для cash[]
	while (temp_sum/10 != 0) //поки не видамо усю потрібну суму
	{
		unsigned int counter = temp_sum/max_note; //кількість купюр
		unsigned int min_num = min(counter,stackNotes[max_index].second); 
			//врахування наявної кількості
		temp_sum -= max_note*min_num; //зменшуємо суму ще не виданих грошей
		cash[index] = make_pair(max_note,min_num); //запам'ятовуємо набір купюр для видачі
		stackNotes[max_index].second -= min_num; //зменшуємо наявну кількість номіналу
		max_note = notes[max_index-1]; //переміщуємо значення макс. номіналу
		max_index--; //зменшуємо індекс макс. купюри
		index++; //збільшуємо індекс для набору видачі
	}
	cout<<"You can take your money: "<<sum<<endl;
	for (int i = 0; i<6; i++) //вивід інформації про набір, яким видається сума
	{
		cout<<"Note: "<<cash[i].first<<endl;
		cout<<"Count: "<<cash[i].second<<endl<<endl;
	}
}
