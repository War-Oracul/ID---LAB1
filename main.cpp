
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <conio.h>
#include <malloc.h>

FILE  *data, *dataKey, *cdata, *ddata;

char* text;
char* ntext;
char* revntext;
char key[10];
void getText()
{
	int i = 0;
	
	data = fopen("data.cpp", "a+");
	fseek(data, 0, SEEK_END);
	int size = ftell(data);
	text = (char*)malloc(size * sizeof(char));
	text[size] = { };
	
	fseek(data, 0, SEEK_SET);
	i = 0;
	while (i < size) {
		text[i] = getc(data);
		i++;
	}
	fclose(data);
}

void getKey()
{
	int i = 0;

	dataKey = fopen("key.txt", "a+");
	for (i = 0; i < 10; i++)
		fscanf(dataKey, "%d", &key[i]);

	fclose(dataKey);
}

void Coder(int loop)
{
	int i, j;
	int start = 0;
	cdata = fopen("encrypted.txt", "w");
	for (j = 0; j < loop; j++) {
		for (i = start; i < start + 10; i++) {
			ntext[i] = text[key[i - start] + start - 1];
		}
		start = start + 10;
	}
	ntext[i] = '\0';

	fprintf(cdata, "%s", ntext);
	printf("Encrypted text: \n");
	printf(ntext);
	printf("\n");
	fclose(cdata);
}

void Decoder(int loop)
{
	int i, j;
	int n = 0;
	int start = 0;
	int loopQ = loop;
	ddata = fopen("decrytped.txt", "w");
	while (loopQ != 0) {
		for (i = start; i < start + 10; i++) {
			for (j = 0; j < 10; j++) {
				if ((i % 10) == (key[j] - 1))
					revntext[i] = ntext[j + n];
			}
		}
		start += 10;
		loopQ--;
		n += 10;
	}
	fprintf(ddata, "%s", revntext);
	fclose(ddata);
}

void ErrorTest()
{
	int s1, s2;
	int alarm = 0;
	data = fopen("data.cpp", "r");
	ddata = fopen("decrytped.txt", "r");

	while (!feof(ddata) && !feof(data)) {
		s1 = fgetc(data);
		s2 = fgetc(ddata);
		if (s1 != s2)
		{
			alarm = 1;
		}
	}
	if (alarm != 1)
		printf("\nFiles are the same");
	else
		printf("\nFiles are defferent");
	fclose(data);
	fclose(ddata);
}
int main()
{
	
	int loop;
	// Считывание текста
	getText();
	// Считывание ключа
	getKey();

	int length_text = strlen(text);
	printf("Initial text: \n");
	printf(text);
	printf("\n\n");

	while (length_text % 10 != 0)
	{
		text[length_text] = ' ';
		length_text++;
	}
	text[length_text] = '\0';
	
	ntext = (char*)malloc(length_text * sizeof(char));
	revntext = (char*)malloc(length_text * sizeof(char));

	ntext[length_text] = { };
	revntext[length_text] = { };
	loop = length_text / 10;

	data = fopen("data.cpp", "w");
	fprintf(data, "%s", text);
	fclose(data);

	//Шифровка
	Coder( loop);

	//Расшифровка
	Decoder(loop);

	printf("\n");
	printf("Final text: \n");
	printf(revntext);

	//Сравнение
	ErrorTest();
	
	getch();

}
