#include <stdio.h>
#include <conio.h>
#include <string.h>
#define _CRT_SECURE_NO_DEPRECATE
#include <errno.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

//Strukturat
struct student
{
	int id_student;
	char emri[30];
	char mbiemri[30];
	char emriPerdoruesit[100];
	char datelindja[11];
	int piket;
	char password[30];
	int status;
};

struct pedagog
{
	int id_pedagog;
	char emri[30];
	char mbiemri[30];
	char emriPerdoruesit[100];
	char password[30];
	char lenda[30];
	int status;
};

struct pyetjet
{
	char pyetja[256];
	int pedagogId;
	char al1[32];
	char al2[32];
	char al3[32];
	int IdProvimi; //ID e provimit ku gjendet pyetja
	char pergjigja[1];

};

struct admin
{
 int id_admin;
 char emri[30];
 char password[30];	
 int pedagog;
};

struct rezultateProvimi //Rezultate per cdo provim qe jep studenti
{
	char TemaProvimit[32];
	int id_pedagog;
	int idStudenti;
	int Id_provimi;
	char emriStudent[30];
	char mbiemriStudent[30];
	int piketEFituara;
	int kalues; //1 nese studenti eshte kalues
	float mesatarja;
};

struct  rezultatIDetajuar //Rezultate per cdo pyetje qe jep studenti
{
	char pergjigjeSakte[200];
	char pergjigjaStudentit[200];
	int piketPerPyetje;
	int pedagogID; // ID e Pedagogut qe harton provimin
	int studentId; //ID e studentit qe futet ne provim
	int Id_provimi;//ID e provimit
	char lenda[32];
	int rezultati;        //1 nese studenti e gjetur pyetjen 0 nese se ka gjetur
	char pyetja[500];

};

struct provimi
{
	int IdProvimi;// ID e Pedagogut qe harton provimin
	int idPedagogu;
	char TemeProvimi[32];
};



//Deklarimi i Funksioneve
int gjejIdMaxProvim(); //fnx qe ben autoincrementimin e IDse se provimit
int gjejIdMaxProfesor();//fnx qe ben autoincrementimin e IDse se profesorit
int gjejIdMaxStudent();//fnx qe ben autoincrementimin e IDse se studentit
void ShtoStudent(); //
void ShtoPedagog(); //
void hartoProvim(int pedaogog); //
student KerkoStudent(int studentId); //
void ShfaqPyetjet(); //
void FshiPedagog(); //
void FshiStudent(); //
void shikoRezultatinTeDetajuar(int s,int d ,int p); //
void shikoPyetjenKuEshteGabuarMeShume(int pedagogID); //  
void shfaqTeGjitheProvimet(int studentId); //
void futuNeProvim(int pedagogId , int studentId , int provimi); //
pedagog Kerko_pedagog(char emri[32] , char mbiemri[32]); //
void LogimSiStudent(); //
void LogimSiPedagog(); //
void LogimSiAdmin(); //
void GjejStudent(int studentid); //
void AfishoPiketMeTeUleta(int pedagogID); //
void AfishoPiketMeTeLarta(int pedagogID); //
void shikoTegjitheStudentet(); //
void ShikoRezultatet(int pedagogId); //
void ShikoRezultatetStudent(int studentID); //
void shikoTegjithePedagoget(); //
pedagog Kerko_pedagogID(int pedagog); //
void shikoRezultatetMeZeroPike(int pedagog); //
long gjeneroFjalekalim(int id, char emerMbiemer[32]); //
int shikoProvimet(int pedagog);//
void ndrshoPassword(); //
void ShikoTeGjithaRezultatetTotal(int studentId);//
void shfaqRezultatet();


char fstudent[32], fpedagog[32], fpyetjet[32], fKredenciale[32], frezultateProvimi[32], frezultateDetajuar[32] , fprovimi[32];
//Main
int main(int argc, char * argv[])
{
	if(argc != 8)
	{
		printf("Gabim ne argumenta(Jepni emrat e kater skedareve ku keni ruajtur te dhenat e studenteve ,pedagogeve dhe pyetjeve ).");
		return 0;
	}


	strcpy(fstudent, argv[1]);
	strcpy(fpedagog, argv[2]);
	strcpy(fpyetjet, argv[3]);
	strcpy(fKredenciale, argv[4]);
	strcpy(frezultateProvimi, argv[5]);
	strcpy(frezultateDetajuar, argv[6]);
	strcpy(fprovimi, argv[7]);



	while (1)
	{
		printf("Menu e programit : \n");
		printf("Te lutem logou te kryhesh veprime :\n");
		printf("Logohuni si  :\n");
		printf("1 - Admin\n2 - Student\n3 - Profesor\n");
		int kodi;
		char term;
		scanf("%d", &kodi);
		switch (kodi)
		{
		case 1: LogimSiAdmin();
			break;
		case 2: LogimSiStudent();
			break;
		case 3: LogimSiPedagog();
			break;
		case 0: return 0;
		default: printf("Kod i gabuar\n");
		}
		
		
	}

	
	//printf("1 - Per shtimin e nje studenti\n2 - Per shtimin e nje pedagogu\n3 - Per shtimin e nje pyetjeje\n4 - Per te kerkuar te dhenat e nje studenti\n5 - Per te shfaqur te gjitha pyetjet e pedagogeve\n");
	//printf("6 - Per te fshire te dhenat e nje pedagogu\n7 - Per te futur nje student ne testim\n8 - Per te afishuar studentet me piket me te larta dhe me te uleta\n9 - Per te kerkuar nje pedagog \n0 - Per te mbyllur programin\n\n");
}
//End Main

//Implementimi i funskioneve
void LogimSiAdmin()
{
	struct admin s;
	char emri[30];
	char fjalekalimi[30];
	printf("Ju lutem futni kredencialet e adminit : \n");
	scanf("%s %s", &emri, &fjalekalimi);
    char filename[100] = "\\Kredencialet.txt";
	FILE *f = fopen(fKredenciale, "rb");
	if(f != NULL)
	{
		struct admin strukture_temp;
		while(fscanf(f, "%d %s %s", &strukture_temp.id_admin, &strukture_temp.emri, &strukture_temp.password) != EOF) // ben brdhjen ne skedar
		{
			if(strcmp(strukture_temp.emri, emri) == 0 && strcmp(strukture_temp.password, fjalekalimi) == 0) //Kontrollon nqs emri i perdoruesit dhe fjalekalimi jaen te barabarte me emrin dhe fjalekalimin e dhene 
			{
				printf("Ju jeni loguar me sukses si admin. \n");
				fclose(f);
				while (1)
				{
					printf("Kryeni veprine  :\n");
					printf("1 - Shto Student\n2 - Shto Pedagog\n3 - Fshi student\n4 - Fshi Pedagog\n5 - Shiko te gjithe studentet\n6 - Shiko te gjthe pedagoget\n7 - Kerko Student \n8 - Ndrysho Fjalekalimin\n9 - Shfaq rezultatet\n0 - Dil \n");
					int kodi;
					int id = 0;
					scanf("%d", &kodi);
					switch (kodi)
					{
					case 1: ShtoStudent();
						break;
					case 2: ShtoPedagog();
						break;
					case 3: FshiStudent();
						break;
					case 4: FshiPedagog();
						break;
					case 5: shikoTegjitheStudentet();
						break;
					case 6: shikoTegjithePedagoget();
						break;
					case 7:
						printf("Jepni Id e studentit");
						scanf("%d", &id);
						GjejStudent(id);
						break;
					case 9:shfaqRezultatet();
						break;
					case 8:ndrshoPassword();
						break;
					case 0:
						return;
					default: printf("Kod i gabuar\n");
					}
				}
				
				return;
			}
			else
			{
				printf("Password ose username i gabuar!");
				break;
				return;
			}
		}
		

	}

} 

void LogimSiStudent()
{
	struct student s;

	//char filename[100] = "\\Kredencialet.txt";
	FILE *f = fopen(fstudent, "r");
	if (f != NULL)
	{
		char emriPerdoruesit[30];
		char fjalekalimi[30];
		printf("Ju lutem futni kredencialet tuaja (Emri i Perdoruesit Password ): \n");
		scanf("%s %s", &emriPerdoruesit, &fjalekalimi);
		struct student strukture_temp;
		while (fscanf(f, "%d %s %s %s %s %d %s %d", &strukture_temp.id_student, &strukture_temp.emri, &strukture_temp.mbiemri, &strukture_temp.emriPerdoruesit, &strukture_temp.datelindja , &strukture_temp.piket, &strukture_temp.password , &strukture_temp.status) != EOF)
		{
			if (strcmp(strukture_temp.emriPerdoruesit, emriPerdoruesit) == 0 && strcmp(strukture_temp.password, fjalekalimi) == 0 && strukture_temp.status == 1)
			{
				printf("Ju jeni loguar me sukses si student. \n");
				fclose(f);
				printf("Kryeni veprine  :\n");
				while (1)
				{
					printf("1 - Futu ne provim\n2 - Shiko rezultatet \n3 - Dil\n");
					int kodi = 0;
					scanf("%d", &kodi);
					switch (kodi)
					{
					case 1:
						shfaqTeGjitheProvimet(strukture_temp.id_student);
						break;
					case 2:
						ShikoRezultatetStudent(strukture_temp.id_student);
						break;
					case 3:
						return;

					}
				}

				return;
			}
		
		}

	}
	else
	{
		printf("Dicka shkoi keq! %s\n", strerror(errno)); 
	//	return;

	}
	//printf("ID e pedagogut nuk ekziston ose password i gabuar!");
	//return;
}

void LogimSiPedagog()
{
	struct pedagog p;

	FILE* f = fopen(fpedagog, "r");
	if (f != NULL)
	{
		char emriPerdoruesit[30];
		char fjalekalimi[30];
		char mbiemri[30];
		printf("Ju lutem futni kredencialet tuaja (Emri perdoruesit Password: \n");
		scanf("%s %s", &emriPerdoruesit, &fjalekalimi);
		struct pedagog strukture_temp;
		while (fscanf(f, "%d %s %s %s %s %s %d", &strukture_temp.id_pedagog, &strukture_temp.emri, &strukture_temp.mbiemri, &strukture_temp.emriPerdoruesit,&strukture_temp.password , &strukture_temp.lenda , &strukture_temp.status) != EOF)
		{
			if (strcmp(strukture_temp.emriPerdoruesit, emriPerdoruesit) == 0 && strcmp(strukture_temp.password, fjalekalimi) == 0)
			{
				struct pedagog Pedagog = Kerko_pedagogID(strukture_temp.id_pedagog);
				int pedagogId = Pedagog.id_pedagog;
				printf("Ju jeni loguar me sukses si pedagog. \n");
				fclose(f);
				printf("Kryeni veprine  :\n");
				while (1)
				{
					printf("1 - Harto Provim\n2 - Shiko Rezultatet\n3 - Afisho Piket Me Te Uleta \n4 - Afisho Piket Me Te Larta\n5 - Shiko Rezultatet Me Zero Pike \n6 - Shiko pyetjen ku eshte gabuar me shume\n7 - Dil \n");
					int kodi = 0;
					scanf("%d", &kodi);
					switch (kodi)
					{
					case 1:
						hartoProvim(pedagogId);
						break;
					case 2:
						ShikoRezultatet(pedagogId); //Rezultatet jane renditur ne rendin zbrites
						break;
					case 3:
						AfishoPiketMeTeUleta(pedagogId);
						break;
					case 4:
						AfishoPiketMeTeLarta(pedagogId);
						break;
					case 5:shikoRezultatetMeZeroPike(pedagogId); //shikoRezultatetMeZeroPike
						break;
					case 6:shikoPyetjenKuEshteGabuarMeShume(pedagogId); //shikoRezultatetMeZeroPike
						break;
					case 7:
						return;

					}
				}
				
			}
			
		}
		printf("ID e pedagogut nuk ekziston ose password i gabuar!");
		return;
		printf("out");

	}
	else
	{
		printf("Something went wrong with read()! %s\n", strerror(errno));

	}


}

long gjeneroFjalekalim(int id, char emerMbiemer[])// ID* (shuma e karaktereve te emer + mbiemer sipas kodit ASCII).
{
	int len = strlen(emerMbiemer);
	int sum = 0;
	for (int i = 0; i < len; i++)
	{
		sum = sum + emerMbiemer[i];

	}
	
	long fjalekalimi = id * (sum);
	return fjalekalimi;
}

void ShtoStudent()
{
	struct student s;
	printf("Jepni te dhenat e studentit ne formatin: [Emer] [Mbiemer]  [Datelindja (DD/MM/YYYY)] [Piket]  [Status]: \n");
	scanf("%s %s %s %d %d", &s.emri, &s.mbiemri, &s.datelindja, &s.piket , &s.status);
	FILE * f = fopen(fstudent, "r");
	if(f != NULL)
	{
		struct student strukture_temp;

		while (fscanf(f, "%d %s %s %s %s %d %s %d", &strukture_temp.id_student, &strukture_temp.emri, &strukture_temp.mbiemri, &strukture_temp.emriPerdoruesit, &strukture_temp.datelindja, &strukture_temp.piket, &strukture_temp.password , &strukture_temp.status) != EOF)
		{
			if(strukture_temp.id_student == s.id_student)
			{
				printf("Ekziston nje student me kete ID.");
				return;
			}
		}
		fclose(f);
	}
	f = fopen(fstudent, "a");
	if(f != NULL)
	{
		int studentId = gjejIdMaxStudent() + 1;
		
		char EmriPerdoruesit[100]; //krijimi i emrit te perdoruesit
		strcpy(EmriPerdoruesit, s.emri); //kopjon te EmriPerdoruesit emrin
		strcat(EmriPerdoruesit, s.mbiemri);//shton te EmriPerdoruesit mbiemrin -> krjohet EmriPerdoruesit
		long fjalekamlimi = gjeneroFjalekalim(studentId, EmriPerdoruesit); //gjenerimi i fjalekalimit 
		char password[1000];
		sprintf(password, "%d", fjalekamlimi); //konvertimi i fjalekalimit ne string
		fprintf(f,"%d %s %s %s %s %d %s %d \n", studentId, s.emri, s.mbiemri, EmriPerdoruesit, s.datelindja, s.piket, password, s.status);
		fclose(f);
		printf("Studenti u shtua.\n");
		return;
	}
	else printf("Veprimi nuk u krye.");
	return;
}

void ShtoPedagog()
{
	struct pedagog p; 
	printf("Jepni te dhenat e pedagogut ne formatin: [Emer] [Mbiemer] [Lenda] [Status]: \n "); //Leximi nga command line
	scanf("%s %s %s  %d", &p.emri, &p.mbiemri  , &p.lenda  ,&p.status );
	FILE *f = fopen(fpedagog, "r");
	if(f != NULL)
	{
		struct pedagog strukture_temp;
		while(fscanf(f,"%d %s %s %s %s %s %d", &strukture_temp.id_pedagog, &strukture_temp.emri, &strukture_temp.mbiemri, &strukture_temp.emriPerdoruesit,&strukture_temp.password, &strukture_temp.lenda , &strukture_temp.status) != EOF)
		{
			if(strukture_temp.id_pedagog == p.id_pedagog)
			{
				printf("Ekziston nje pedagog me kete ID.");
				return;
			}
		}
		fclose(f);
	}
	f = fopen(fpedagog, "a");
	if(f != NULL)
	{
		int pedagogId = gjejIdMaxProfesor() + 1;
		char EmriPerdoruesit[100]; //krijimi i emrit te perdoruesit
		strcpy(EmriPerdoruesit, p.emri);
		strcat(EmriPerdoruesit, p.mbiemri);
		long fjalekamlimi = gjeneroFjalekalim(pedagogId, EmriPerdoruesit);
		char password[1000];
		sprintf(password, "%d", fjalekamlimi);
		fprintf(f,"%d %s %s %s %s %s %d \n", pedagogId, p.emri, p.mbiemri, EmriPerdoruesit,password, p.lenda,p.status); //Ruan ne skedar
		fclose(f);
		printf("Pedagogu u shtua.\n");
	}
	else printf("Veprimi nuk u krye.");
	return;
}

void shikoTegjitheStudentet()
{
	struct student s;
	FILE* f = fopen(fstudent, "r");
	if (f != NULL)
	{
		//printf(" ID\tEmer\tMbiemer\t\tEmri i Perdoruesit\tDatelidnja\tPiket\tPassword\t\tStatus \n");
		while (fscanf(f, " %d %s %s %s %s %d %s %d", &s.id_student, &s.emri, &s.mbiemri, &s.emriPerdoruesit,&s.datelindja, &s.piket,&s.password,&s.status) != EOF)
		{
			
			char status[32] = "Alumni";
			if (s.status == 1)
			{
				strcpy(status, "Aktiv");
			}
			//printf(" %d\t%s\t%s\t\t%s\t\t%s\t%d\t%s\t\t%s \n", s.id_student,s.emri, s.mbiemri, s.emriPerdoruesit,s.datelindja,s.piket,s.password ,status);
			printf("\nID studenti:\t%d\nEmer:\t\t%s\nMbiemer:\t%s\nEmri i Perdoruesit :\t%s\nDatelindja:\t%s\nPiket:\t\t%d\nPassword:\t\t%s\nStatus:\t\t%s\n", s.id_student, s.emri, s.mbiemri, s.emriPerdoruesit, s.datelindja, s.piket, s.password, status);
			printf("----------------------------------------------------------------------------------------------  \n");
			memset(status, 0, 32);
		}
		fclose(f);
		return;

	}
	printf("Ky student nuk ekziston!");
	return;
}

void shikoTegjithePedagoget()
{
	struct pedagog s;
	FILE* f = fopen(fpedagog, "r");
	if (f != NULL)
	{
		while (fscanf(f, "%d %s %s %s %s %s %d", &s.id_pedagog, &s.emri, &s.mbiemri, &s.emriPerdoruesit,&s.password, &s.lenda, &s.status) != EOF)
		{

			char status[32] = "Larguar";
			if (s.status == 1)
			{
				strcpy(status, "Aktiv");
			}
			printf("\nID Pedagogu:\t%d\nEmer:\t\t%s\nMbiemer:\t%s\nEmri i Perdoruesit :\t%s\nPassword:\t%s\nLenda:\t\t%s\nStatus:\t\t%s\n", s.id_pedagog, s.emri, s.mbiemri, s.emriPerdoruesit,s.password, s.lenda, status);
			printf("----------------------------------------------------------------------------------------------  \n");
			memset(status, 0, 32);

		}
		fclose(f);
		return;

	}
	printf("Ky student nuk ekziston!");
	return;
}

void hartoProvim(int pedagogId)
{
	struct pyetjet p;
	int pedagogu;
	struct provimi Provimi;
	int IdProvimi = gjejIdMaxProvim() + 1;
	FILE* f = fopen(fpyetjet, "a"); //krijimi i provimit
	if (f != NULL)
	{
		FILE* pr = fopen(fprovimi, "a");
		if (pr != NULL)
		{
			printf("Temen e provimit : \n");
			scanf("%s", &Provimi.TemeProvimi);
			fprintf(pr, "%d %d %s \n",IdProvimi, pedagogId, Provimi.TemeProvimi);
		}
		fclose(pr);

		printf("Jepni numrin e pyetjeve : \n"); //Krijimi i pyetjeve per provimin
		int nmrPyetjeve = 0;
		scanf("%d", &nmrPyetjeve);
		for (int i = 1; i <= nmrPyetjeve; i++)
		{
     		printf("Jepni pyetjen: \n");
			getchar();
			gets_s(p.pyetja);//Nqs do e ranosh ne Dev-C ++ gets_s() duhet thjesht gets()
			printf("Jepni 3 alternativa : (Nje alternative duhet te jete Nuk e di ): \n");
			scanf("%s %s %s", &p.al1,&p.al2,&p.al3);
			char al4[32] = "Nuk e di";
			printf("Jepni pergjigjen (a ,b ose c): \n");
			scanf("%s", &p.pergjigja);
			fprintf(f, "%d %s %s %s %s %d %s \n", pedagogId,p.al1,p.al2,p.al3,p.pergjigja, IdProvimi,p.pyetja);
		}
		fclose(f);
		printf("----------------------------------------------------------------------------------------------\n");

	}
	else
	{
		printf("Veprimi nuk u krye");

	}
		
	printf("Pyetjet u shtuan me sukses!\n");
	return;
}

void shikoRezultatetMeZeroPike(int pedagogID)
{
	struct rezultateProvimi s;
	int pmax, pmin;
	pedagog p = Kerko_pedagogID(pedagogID);
	FILE* f = fopen(frezultateProvimi, "r");
	int provimiID = shikoProvimet(pedagogID);
	if (provimiID == 0)
	{
		if (f != NULL)
		{
			int nmr = 0;
			printf("Rezultatet zero pike per lenden %s : ", p.lenda);
			//printf("Emer \tMbiemer \t Piket \t Eshte kalues \t Mesatarja \n");
			while (fscanf(f, "%s %d %d %d %s %s %d %d %f", &s.TemaProvimit, &s.id_pedagog, &s.idStudenti, &s.Id_provimi, &s.emriStudent, &s.mbiemriStudent, &s.piketEFituara, &s.kalues, &s.mesatarja) != EOF)
			{
				if (s.id_pedagog == pedagogID)
				{
					char kalimi[32] = "Jo";
					if (s.piketEFituara == 0)
					{
						nmr++;
						if (s.kalues == 1)
						{
							strcpy(kalimi, "po");
						}
						printf("\nEmer:\t\t%s\nMbiemer:\t%s\n", s.emriStudent ,s.mbiemriStudent);
					}
				}
			}
			fclose(f);
			printf("----------------------------------------------------------------------------------------------\n");
			if (nmr == 0)
			{
				printf("Nuk ka rezultate me kete provim \t");
				printf("----------------------------------------------------------------------------------------------\n");
				return;
			}

		}
		

	}
	else if (provimiID != 0)
	{
		if (f != NULL)
		{
			int nmrRe = 0;
			printf("Rezultatet zero pike per lenden %s : ", p.lenda);
			printf("Emer \tMbiemer \t Piket \t Eshte kalues \t Mesatarja \n");
			while (fscanf(f, "%s %d %d %d %s %s %d %d %f", &s.TemaProvimit, &s.id_pedagog, &s.idStudenti, &s.Id_provimi, &s.emriStudent, &s.mbiemriStudent, &s.piketEFituara, &s.kalues, &s.mesatarja) != EOF)
			{
				if (s.id_pedagog == pedagogID)
				{
					char kalimi[32] = "Jo";
					if (s.piketEFituara == 0 && s.Id_provimi == provimiID)
					{
						nmrRe++;
						if (s.kalues == 1)
						{
							strcpy(kalimi, "po");
						}
						printf("%s %s\n", s.emriStudent, s.mbiemriStudent);
					}
				}
		
			}
			fclose(f);
			if (nmrRe == 0)
			{
				printf("Nuk ka rezultate me kete provim \t");
				return;
			}
		}
	}
	
}

int shikoProvimet(int pedagogId)
{
	struct provimi p;
	FILE* f = fopen(fprovimi, "r");
	int i = 0;
	if (f != NULL)
	{
		printf("Zgjidh provimin ku doni te futeni : \n");
		printf(" \t Tema Provimit\n");
		while (fscanf(f, "%d %d %s", &p.IdProvimi, &p.idPedagogu, &p.TemeProvimi) != EOF)
		{
			i++;
			if (p.idPedagogu == pedagogId)
				printf("%d \t %s\n", p.IdProvimi, p.TemeProvimi);
		}
		if (i == 0)
		{
			printf("Ky professor ska provime");
			fclose(f);
			return 0;

		}
		printf("0 - Shiko te gjitha provimet \n");
		int provimi = 0;
		scanf("%d", &provimi);
		return provimi;
	}
	else printf("Veprimi nuk u krye.");
	fclose(f);
	return 0;
}

int shikoProvimetStudent(int pedagogId)
{
	struct provimi p;
	FILE* f = fopen(fprovimi, "r");
	int i = 0;
	if (f != NULL)
	{
		printf("Zgjidh provimin qe doni te shikoni : \n");
		printf(" \t Tema Provimit\n");
		while (fscanf(f, "%d %d %s", &p.IdProvimi, &p.idPedagogu, &p.TemeProvimi) != EOF)
		{
			if (p.idPedagogu == pedagogId)
				printf("%d \t %s\n", p.IdProvimi, p.TemeProvimi);
		}
		printf("0 - Shiko te gjitha provimet \n");
		int provimi = 0;
		scanf("%d", &provimi);
		return provimi;
	}
	else printf("Veprimi nuk u krye.");
	fclose(f);
	return 0;
}

void ShikoRezultatet(int pedagogID)
{
	struct rezultateProvimi s;
	FILE* f = fopen(frezultateProvimi, "r");
	const int size = 1000;
	int piket[size];
	int i = 0;
	int nmrRez = 0;
	pedagog p = Kerko_pedagogID(pedagogID);
	int provimID = shikoProvimet(pedagogID);
	if (provimID == 0)
	{
		if (f != NULL)
		{
			int nmr = 0;
			printf("Rezultatet \n");
			//printf("Provimi \t Emer \tMbiemer \t Piket \t Eshte kalues \t Mesatarja \n");
			while (fscanf(f, "%s %d %d %d %s %s %d %d %f", &s.TemaProvimit, &s.id_pedagog, &s.idStudenti, &s.Id_provimi, &s.emriStudent, &s.mbiemriStudent, &s.piketEFituara, &s.kalues, &s.mesatarja) != EOF)
			{
				if (pedagogID == s.id_pedagog )
				{
					nmr++;
					char kalimi[32] = "Jo";
					piket[i] = s.piketEFituara;
					i++;
					nmrRez++;

				}
			}
			fclose(f);
			if (nmr == 0)
			{
				printf("Nuk ka rezultate me kete provim \t");
				return;
			}
			for (int i = 0; i < nmrRez; i++) //Renditja e pikeve ne rendin rrites
			{
				for (int j = 0; j < nmrRez; j++)
				{
					if (piket[j] > piket[i])
					{
						int tmp = piket[i];
						piket[i] = piket[j];
						piket[j] = tmp;
					}
				}
			}

			int k = 0;
			for (int i = nmrRez - 1; i >= 0; i--) //printimi ne rendin zbrites
			{
				f = fopen(frezultateProvimi, "r");
				while (fscanf(f, "%s %d %d %d %s %s %d %d %f", &s.TemaProvimit, &s.id_pedagog, &s.idStudenti, &s.Id_provimi, &s.emriStudent, &s.mbiemriStudent, &s.piketEFituara, &s.kalues, &s.mesatarja) != EOF)
				{
					char kalimi[32] = "Jo";

					if (piket[i] == s.piketEFituara && s.id_pedagog == pedagogID)
					{
						if (s.kalues == 1)
						{
							strcpy(kalimi, "po");
						}
						printf("\nTema e provimit:\t%s\nEmer:\t\t%s\nMbiemer:\t%s\nPiket:\t%d\nKalues:\t%s\nMesatarja:\t\t%f\n", s.TemaProvimit, s.emriStudent, s.mbiemriStudent, s.piketEFituara, kalimi, s.mesatarja);
						printf("----------------------------------------------------------------------------------------------\n");
					}

				}
			}
			fclose(f);
			return;
		}
		
	}
	else if(provimID != 0)
	{
		if (f != NULL)
		{
			int nmr = 0;
			printf("Rezultatet \n");
			//printf("Provimi \t Emer \tMbiemer \t Piket \t Eshte kalues \t Mesatarja \n");
			while (fscanf(f, "%s %d %d %d %s %s %d %d %f", &s.TemaProvimit, &s.id_pedagog, &s.idStudenti, &s.Id_provimi, &s.emriStudent, &s.mbiemriStudent, &s.piketEFituara, &s.kalues, &s.mesatarja) != EOF)
			{
				if (pedagogID == s.id_pedagog && s.Id_provimi == provimID)
				{
					nmr++;
					char kalimi[32] = "Jo";
					piket[i] = s.piketEFituara;
					i++;
					nmrRez++;

				}
			}
			fclose(f);
			if (nmr == 0)
			{
				printf("Nuk ka rezultate me kete provim \t");
				return;
			}
			for (int i = 0; i < nmrRez; i++)
			{
				for (int j = 0; j < nmrRez; j++)
				{
					if (piket[j] > piket[i])
					{
						int tmp = piket[i];
						piket[i] = piket[j];
						piket[j] = tmp;
					}
				}
			}

			int k = 0;
			for (int i = nmrRez - 1; i >= 0; i--)
			{
				f = fopen(frezultateProvimi, "r");
				while (fscanf(f, "%s %d %d %d %s %s %d %d %f", &s.TemaProvimit, &s.id_pedagog, &s.idStudenti, &s.Id_provimi, &s.emriStudent, &s.mbiemriStudent, &s.piketEFituara, &s.kalues, &s.mesatarja) != EOF)
				{
					char kalimi[32] = "Jo";

					if (piket[i] == s.piketEFituara && pedagogID == s.id_pedagog && s.Id_provimi == provimID)
					{
						if (s.kalues == 1)
						{
							strcpy(kalimi, "po");
						}
						printf("\nTema e provimit:\t%s\nEmer:\t\t%s\nMbiemer:\t%s\nPiket:\t%d\nKalues:\t%s\nMesatarja:\t\t%f\n", s.TemaProvimit, s.emriStudent, s.mbiemriStudent, s.piketEFituara, kalimi, s.mesatarja);
						printf("----------------------------------------------------------------------------------------------\n");
					}




				}
			}
			fclose(f);
			return;
		}
	}
	
}

void GjejStudent(int studentid)
{
	struct student s;
	FILE* f = fopen(fstudent, "r");
	int i = 0;
	if (f != NULL)
	{
		while (fscanf(f, " %d %s %s %s %s %d %s %d", &s.id_student, &s.emri, &s.mbiemri, &s.emriPerdoruesit, &s.datelindja, &s.piket, &s.password, &s.status) != EOF)
		{
			
			if (studentid == s.id_student)
			{
				i++;
				printf("\nID studenti:\t%d\nEmer:\t\t%s\nMbiemer:\t%s\nEmri i Perdoruesit :\t%s\nDatelindja:\t%s\nPiket:\t\t%d\nPassword:\t\t%s\nStatus:\t\t%d\n", s.id_student, s.emri, s.mbiemri, s.emriPerdoruesit, s.datelindja, s.piket, s.password, s.status);
				fclose(f);
				return ;
			}
		}
		if (i == 0)
		{
			printf("Ky student nuk ekziston!");
			fclose(f);
			return;
		}
	
	}
	else printf("Veprimi nuk u krye.");
	return ;
}

student KerkoStudent(int studentId)
{
	struct student s;
	FILE *f = fopen(fstudent, "r");
	if(f != NULL)
	{
		while (fscanf(f, " %d %s %s %s %s %d %s %d", &s.id_student, &s.emri, &s.mbiemri, &s.emriPerdoruesit, &s.datelindja, &s.piket, &s.password, &s.status) != EOF)
		{
			if(studentId == s.id_student)
			{
				//printf("\nID studenti:\t%d\nEmer:\t\t%s\nMbiemer:\t%s\nDatelindja:\t%s\nMosha:\t\t%d\nPiket:\t\t%d\n", s.id_student, s.emri, s.mbiemri, s.datelindja,s.piket ,s.status);
				fclose(f);
				return s;
			}
		}
		printf("Ky student nuk ekziston!");
		fclose(f);
	}
	else printf("Veprimi nuk u krye.");
	return s;
}

void ShfaqPyetjet()
{
	struct pyetjet p;
	FILE *f = fopen(fpyetjet, "r");
	if(f != NULL)
	{
		printf("tPergjigje\tPiket\tPyetja\n");
		while(fread(&p, sizeof(p), 1, f))
		printf("%d\t%d\t\t1\t%s\n", p.pergjigja, p.pyetja);
	}
	else printf("Veprimi nuk u krye.");
	fclose(f);
	return;
}

void FshiPedagog()
{
	struct pedagog p;
	int id;
	printf("Jepni ID e pedagogut qe doni te fshini: ");
	scanf("%d", &id);
	FILE *f = fopen(fpedagog, "r");
	struct pedagog stmp;
	if(f != NULL)
	{
		FILE *temp = fopen("skedartemp.txt", "w");
		while (fscanf(f, "%d %s %s %s %s %s %d", &p.id_pedagog, &p.emri, &p.mbiemri, &p.emriPerdoruesit,&p.password, &p.lenda, &p.status) != EOF)
		{
			if (p.id_pedagog == id)
			{
				p.status = 0;
			}
			fprintf(temp, "%d %s %s %s %s %s %d \n", p.id_pedagog, p.emri, p.mbiemri, p.emriPerdoruesit,p.password, p.lenda, p.status);

		}
		fclose(f);
		fclose(temp);
		remove(fpedagog);
		int o = rename("skedartemp.txt", fpedagog);
		printf("Pedagogu me ID %d u diaktivizua.\n", id);
		printf("----------------------------------------------------------------------------------------------\n");
	}
	else printf("Veprimi nuk u krye.");
	return;
}

void FshiStudent()
{
	struct student s;
	int id;
	printf("Jepni ID e studentit qe doni te fshini: ");
	scanf("%d", &id);
	FILE* f = fopen(fstudent, "r");
	struct student stmp;
	if (f != NULL)
	{
		FILE* temp = fopen("skedartemp.txt", "w");
		while (fscanf(f, "%d %s %s %s %s %d %s %d", &s.id_student, &s.emri, &s.mbiemri, &s.emriPerdoruesit,&s.datelindja, &s.piket, &s.password, &s.status) != EOF)
		{
			if (s.id_student == id)
			{
				s.status = 0;
			}
			fprintf(temp, "%d %s %s %s %s %d %s %d \n", s.id_student, s.emri, s.mbiemri, s.emriPerdoruesit,s.datelindja, s.piket, s.password, s.status);

		}
		fclose(f);
		fclose(temp);
		remove(fstudent);
		int o = rename("skedartemp.txt", fstudent);
		printf("Studenti me ID %d u diaktivizua.\n", id);
		printf("----------------------------------------------------------------------------------------------\n");
	}
	else printf("Veprimi nuk u krye.");
	return;
}

void shfaqProvimePerPedagog(int pedagog , int studentId)
{
	struct provimi p;
	FILE* f = fopen(fprovimi, "r");
	int i = 0;
	if (f != NULL)
	{
		printf("----------------------------------------------------------------------------------------------\n");
		printf("Zgjidh provimin ku doni te futeni : \n");
		printf(" \t Tema Provimit\n");
		while (fscanf(f, "%d %d %s", &p.IdProvimi, &p.idPedagogu, &p.TemeProvimi) != EOF)
		{
			if (p.idPedagogu == pedagog)
			{
				i++;
				printf("%d \t %s\n", p.IdProvimi, p.TemeProvimi);

			}
		}
		if (i == 0)
		{
			printf("Kjo lende ska provime . \n");
			printf("----------------------------------------------------------------------------------------------\n");
			return;
		}
		int provimi = 0;
		scanf("%d", &provimi);
		futuNeProvim(pedagog, studentId, provimi);
	}
	else printf("Veprimi nuk u krye.");
	fclose(f);
	return;
}

void shfaqTeGjitheProvimet(int studentId)
{
	struct pedagog p;
	FILE* f = fopen(fpedagog, "r");
	if (f != NULL)
	{
		printf("Zgjidh Lenden ku doni te futeni : \n");
		printf("\tProfesori\tLenda\n");
		while (fscanf(f, "%d %s %s %s %s %s %d", &p.id_pedagog, &p.emri, &p.mbiemri, &p.emriPerdoruesit,&p.password, &p.lenda, &p.status) != EOF)
		{
			printf("%d\t%s %s\t%s\n", p.id_pedagog, p.emri, p.mbiemri, p.lenda);
			

		}
		int pedagogu = 0;
		scanf("%d", &pedagogu);
		shfaqProvimePerPedagog(pedagogu, studentId);
	}
	else printf("Veprimi nuk u krye.");
	fclose(f);
	return;
}

int ShfaqPedagoget()
{
	struct pedagog p;
	FILE* f = fopen(fpedagog, "r");
	if (f != NULL)
	{
		printf("Zgjidh Lenden te cilen doni te shikoni : \n");
		printf("\tProfesori\tLenda\n");
		while (fscanf(f, "%d %s %s %s %s %s %d", &p.id_pedagog, &p.emri, &p.mbiemri, &p.emriPerdoruesit,&p.password, &p.lenda, &p.status) != EOF)
		{
			printf("%d\t%s %s\t%s\n", p.id_pedagog, p.emri, p.mbiemri, p.lenda);


		}
		printf("0 - Shiko te gjitha lendet .\n", p.id_pedagog, p.emri, p.mbiemri, p.lenda);
		int pedagogu = 0;
		scanf("%d", &pedagogu);
		return pedagogu;
	}
	else printf("Veprimi nuk u krye.");
	fclose(f);
	return 0;
}

provimi kerkoProvim(int pedagog,int provimi)
{
	struct provimi s;
	FILE* f = fopen(fprovimi, "r");
	if (f != NULL)
	{
		while (fscanf(f, "%d %d %s", &s.IdProvimi, &s.idPedagogu, &s.TemeProvimi) != EOF)
		{
			if (pedagog == s.idPedagogu && s.IdProvimi == provimi)
			{
				//printf("\nID studenti:\t%d\nEmer:\t\t%s\nMbiemer:\t%s\nDatelindja:\t%s\nMosha:\t\t%d\nPiket:\t\t%d\n", s.id_student, s.emri, s.mbiemri, s.datelindja,s.piket ,s.status);
				fclose(f);
				return s;
			}
		}
		printf("Ky student nuk ekziston!");
		fclose(f);
	}
}

void futuNeProvim(int pedagogID , int studentId ,int provimID) //Futu ne provim
{
	struct pyetjet p;
	struct student s;
	s = KerkoStudent(studentId);
	pedagog PED = Kerko_pedagogID(pedagogID);
	provimi PROVIMI = kerkoProvim(pedagogID, provimID);
	int i = 0;
	float shumaPikeve = 0;
	FILE *f = fopen(fpyetjet, "r");
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	float pikeProvimi = 0;
	// This function is used to get 
	// system's current date 
	int SkaProvim = 0;
	int nmrProvimeve = 0;
	FILE* temp = fopen("skedarTEmp.txt", "w"); //Ruajtja e rezulatateve ne nje skedar temp per tu shfaqur ne fund te provimit
	printf("----------------------------------------------------------------------------------------------\n");
	printf("Data : %d-%02d-%02d \n" , tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);

	if(f != NULL)
	{
		char ans[32] = "";
		while(fscanf(f, "%d %s %s %s %s %d %[^\n]" ,  &p.pedagogId, &p.al1, &p.al2,&p.al3,&p.pergjigja ,&p.IdProvimi, &p.pyetja) != EOF)
		{
			nmrProvimeve++;
			if (p.pedagogId == pedagogID && p.IdProvimi == provimID) //Ky kushte eshte qe te shfaqet provimi qe eshte zgjedhur nga studenti
			{

				printf("Pyetja %d: %s \t 1 pike. \n", i, p.pyetja );
				printf("a. %s b. %s c. %s d. Nuk e di \n", p.al1 , p.al2,p.al3);
				printf(" Zgjidh alternativen (1 fjale) \n");
				scanf("%s", &ans);
				struct rezultatIDetajuar rz;
				rz.pedagogID = pedagogID;
				strcpy(rz.pergjigjaStudentit, ans);
				strcpy(rz.pergjigjeSakte, p.pergjigja);
				strcpy(rz.pyetja, p.pyetja);
				rz.piketPerPyetje = 1;
				rz.studentId = studentId;
				rz.Id_provimi = provimID;
				strcpy(rz.lenda, PED.lenda);
				int rez = 0;
				if (strcmp(ans, p.pergjigja) == 0) //Nqs pergjigja e dhene nga studenti eshte e sakte shto nje pike
				{
					rez = 1;
					pikeProvimi += 1;
				} 
				if (strcmp(ans, "d") == 0 && pikeProvimi > 0) //Nqs pergjigja e dhene nga studenti eshte e Nuk e di hiq nje pike 
				{
					rez = 1;
					pikeProvimi -= 1;
				}
				FILE* fz = fopen(frezultateDetajuar, "a"); //Ruajtja e rezultateve ne skedarin e rezultateve te detajuar 
				if (fz != NULL)
				{

					fprintf(fz, "%s %s %d %d %d %d %s %d %s \n", rz.pergjigjeSakte, rz.pergjigjaStudentit, rz.piketPerPyetje, rz.pedagogID, rz.studentId,rz.Id_provimi, rz.lenda, rez, rz.pyetja);
				}
				fclose(fz);
				if (temp != NULL)
				{
					fprintf(temp, "%s %s %d %d %d %d %s %d %s \n", rz.pergjigjeSakte, rz.pergjigjaStudentit, rz.piketPerPyetje, rz.pedagogID, rz.studentId, rz.Id_provimi, rz.lenda, rez, rz.pyetja);

				}
				i++;
				shumaPikeve += 1;
				memset(ans, 0, 32);

			}
			else
			{
				SkaProvim++;
			}
		}
		fclose(temp);
		if (SkaProvim == nmrProvimeve)
		{
			printf("Kjo lende ska provim . \n");
			return;
		}
		
		int kalimi = 0;
		printf("------------------------------------------------------------------------------------------ \n");
		printf("Provimi mbaroi. \n");
		printf("Ju keni marre %f pike. \n", pikeProvimi);
		float perqindjeNota = pikeProvimi / shumaPikeve;
		perqindjeNota = perqindjeNota * 100;
		printf("Ju keni marre %f perqind te pikeve. \n", perqindjeNota);
		if (perqindjeNota < 45)
		{
			printf("Ju nuk rezultoni kalues. \n");
		}
		else
		{
			printf("Ju  rezultoni kalues. \n");
			kalimi = 1;

		}
		printf("Doni te shikoni provimin ne menyre te detajuar ? \n1 - Po \n2 - jo \n");
		int prgj = 0;
		scanf("%d", &prgj);
		if (prgj == 1)
		{
			struct rezultatIDetajuar p;
			FILE* f = fopen("skedartemp.txt", "r");
			if (f != NULL)
			{
				printf("\Pergjigja e sakte \t Pergjigja e studentit \t Piket \t Pyetja \t \n");
				while (fscanf(f, "%s %s %d %d %d %d %s %d %[^\n]", &p.pergjigjeSakte, &p.pergjigjaStudentit, &p.piketPerPyetje, &p.pedagogID, &p.studentId, &p.Id_provimi, &p.lenda, &p.rezultati, &p.pyetja) != EOF)
				{

					char rezultati[32] = "Gabuar";
					if (p.rezultati == 1)
					{
						strcpy(rezultati, "Sakte");
					}
					printf("%s \t \t \t %s \t \t \t %d \t %s \t \t \t \t %s\n", p.pergjigjeSakte, p.pergjigjaStudentit, p.piketPerPyetje, p.pyetja, rezultati);
				}
				printf("----------------------------------------------------------------------------------------------\n");
			}
			fclose(f);
		}
		remove("skedartemp.txt");
		FILE *fs = fopen(fstudent, "r"); //Perditesimi i pikeve te studentit
		FILE *tmp = fopen("skedartemp.txt", "w");
		struct student stmp;
		s.piket += pikeProvimi;
		while(fscanf(fs, "%d %s %s %s %s %d %s %d", &stmp.id_student, &stmp.emri, &stmp.mbiemri, &stmp.emriPerdoruesit, &stmp.datelindja, &stmp.piket,&stmp.password , &stmp.status) != EOF)
		{
			if (studentId == stmp.id_student)
			{
				//fwrite(&s, sizeof(s), 1, tmp);
				fprintf(tmp, "%d %s %s %s %s %d %s %d \n", s.id_student, s.emri, s.mbiemri, s.emriPerdoruesit,s.datelindja, s.piket, s.password, s.status);

			}
			else
			{
				//fwrite(&stmp, sizeof(stmp), 1, tmp);
				fprintf(tmp, "%d %s %s %s %s %d %s %d \n", stmp.id_student, stmp.emri, stmp.mbiemri, stmp.emriPerdoruesit,stmp.datelindja, stmp.piket, stmp.password, stmp.status);

			}
		}
		fclose(fs);
		fclose(tmp);
		remove(fstudent);
		int o = rename("skedartemp.txt", fstudent);
		
		FILE* fr = fopen(frezultateProvimi, "a");//Regjistrimi i rezultateve ne skedarin rezultatet
		float mesatarja = 0.0;
		mesatarja = pikeProvimi / i;
		if (fr != NULL)
		{
			struct rezultateProvimi rezultate;
			strcpy(rezultate.emriStudent, s.emri);
			strcpy(rezultate.mbiemriStudent, s.mbiemri);
			rezultate.piketEFituara = pikeProvimi;
			rezultate.kalues = kalimi;
			//rezultate.id_pedagog = pedagogID;
			fprintf(fr, "%s %d %d %d %s %s %d %d %f \n", PROVIMI.TemeProvimi, pedagogID, studentId, provimID,rezultate.emriStudent, rezultate.mbiemriStudent, rezultate.piketEFituara, rezultate.kalues, mesatarja);

		}
		fclose(fr);


	}
	fclose(f);
	return;
}

void shikoRezultatinTeDetajuar(int sID , int pID ,int prvId)
{
	struct rezultatIDetajuar p;
	FILE* f = fopen(frezultateDetajuar, "r");
	if (f != NULL)
	{
		printf("\Pergjigja e sakte \t Pergjigja e studentit \t Piket \t Pyetja \t \n");
		while (fscanf(f, "%s %s %d %d %d %d %s %d %[^\n]", &p.pergjigjeSakte, &p.pergjigjaStudentit, &p.piketPerPyetje, &p.pedagogID, &p.studentId, &p.Id_provimi, &p.lenda, &p.rezultati, &p.pyetja) != EOF)
		{
			if (p.studentId == sID && p.pedagogID == pID && p.Id_provimi == prvId)
			{
				char rezultati[32] = "Gabuar";
				if (p.rezultati == 1)
				{
					strcpy(rezultati, "Sakte");
				}
				printf("%s \t \t \t %s \t \t \t %d \t %s \t \t \t \t %s\n", p.pergjigjeSakte, p.pergjigjaStudentit, p.piketPerPyetje, p.pyetja, rezultati);

				

			}
		}
		fclose(f);
	}
	return;

}

void AfishoPiketMeTeUleta(int pedagogID)
{
	struct rezultateProvimi s;
	int  pmin;
	int provimi = shikoProvimet(pedagogID);
	FILE* f = fopen(frezultateProvimi, "r");
	if (f != NULL)
	{
		if (provimi == 0)
		{
			while (fscanf(f, " %s %s %d %d %d %d", &s.emriStudent, &s.mbiemriStudent, &s.piketEFituara, &s.kalues, &s.id_pedagog, &s.mesatarja) != EOF)
				if (s.id_pedagog == pedagogID)
				{
					pmin = s.piketEFituara;
					while (fscanf(f, " %s %s %d %d %d %d", &s.emriStudent, &s.mbiemriStudent, &s.piketEFituara, &s.kalues, &s.id_pedagog, &s.mesatarja) != EOF)
					{
						if (s.piketEFituara < pmin)
							pmin = s.piketEFituara;

					}
				}
			printf("----------------------------------------------------------------------------------------------\n");
			fclose(f);
		}
		f = fopen(frezultateProvimi, "r");
		if (f != NULL)
		{
			printf("Piket maksimale: %d, te arritura nga: \n", pmin);
			while (fscanf(f, " %s %s %d %d %d %d", &s.emriStudent, &s.mbiemriStudent, &s.piketEFituara, &s.kalues, &s.id_pedagog, &s.mesatarja) != EOF)
			{
				if (s.id_pedagog == pedagogID)
				{
					if (s.piketEFituara == pmin) printf("%s %s\n", s.emriStudent, s.mbiemriStudent);
				}
			}
			printf("----------------------------------------------------------------------------------------------\n");
			fclose(f);
		}
		return;
		if (provimi != 0)
		{
			int nmrprov = 0;
			while (fscanf(f, " %s %s %d %d %d %d", &s.emriStudent, &s.mbiemriStudent, &s.piketEFituara, &s.kalues, &s.id_pedagog, &s.mesatarja) != EOF)
				if (s.id_pedagog == pedagogID && s.id_pedagog == provimi)
				{
					nmrprov++;
					pmin = s.piketEFituara;
					while (fscanf(f, " %s %s %d %d %d %d", &s.emriStudent, &s.mbiemriStudent, &s.piketEFituara, &s.kalues, &s.id_pedagog, &s.mesatarja) != EOF)
					{
						if (s.piketEFituara > pmin)
							pmin = s.piketEFituara;

					}
				}
			fclose(f);
			if (nmrprov == 0)
			{
				printf("Nuk ka rezultate ne kete provim. \n");
				return;
			}
			f = fopen(frezultateProvimi, "r");
			if (f != NULL)
			{
				printf("Piket maksimale: %d, te arritura nga: \n", pmin);
				while (fscanf(f, " %s %s %d %d %d %d", &s.emriStudent, &s.mbiemriStudent, &s.piketEFituara, &s.kalues, &s.id_pedagog, &s.mesatarja) != EOF)
				{
					if (s.id_pedagog == pedagogID && s.Id_provimi == provimi)
					{
						if (s.piketEFituara == pmin) printf("%s %s\n", s.emriStudent, s.mbiemriStudent);
					}
				}
				fclose(f);
			}
			return;
		}
	}

}

void AfishoPiketMeTeLarta(int pedagogID)
{
	struct rezultateProvimi s;
	int pmax, pmin;
	int provimi = shikoProvimet(pedagogID);
	FILE* f = fopen(frezultateProvimi, "r");
	if (f != NULL)
	{
		if (provimi == 0)
		{
			while (fscanf(f, " %s %s %d %d %d %d", &s.emriStudent, &s.mbiemriStudent, &s.piketEFituara, &s.kalues, &s.id_pedagog, &s.mesatarja) != EOF)
				if (s.id_pedagog == pedagogID)
				{
					pmax = s.piketEFituara;
					while (fscanf(f, " %s %s %d %d %d %d", &s.emriStudent, &s.mbiemriStudent, &s.piketEFituara, &s.kalues, &s.id_pedagog, &s.mesatarja) != EOF)
					{
						if (s.piketEFituara > pmax)
							pmax = s.piketEFituara;

					}
				}
			fclose(f);
		}
		f = fopen(frezultateProvimi, "r");
		if (f != NULL)
		{
			printf("Piket maksimale: %d, te arritura nga: \n", pmax);
			while (fscanf(f, " %s %s %d %d %d %d", &s.emriStudent, &s.mbiemriStudent, &s.piketEFituara, &s.kalues, &s.id_pedagog, &s.mesatarja) != EOF)
			{
				if (s.id_pedagog == pedagogID)
				{
					if (s.piketEFituara == pmax) printf("%s %s\n", s.emriStudent, s.mbiemriStudent);
				}
			}
			printf("----------------------------------------------------------------------------------------------\n");
			fclose(f);
		}
		return;
		if (provimi != 0)
		{
			int nmrprov = 0;
			while (fscanf(f, " %s %s %d %d %d %d", &s.emriStudent, &s.mbiemriStudent, &s.piketEFituara, &s.kalues, &s.id_pedagog, &s.mesatarja) != EOF)
				if (s.id_pedagog == pedagogID && s.id_pedagog == provimi)
				{
					nmrprov++;
					pmax = s.piketEFituara;
					while (fscanf(f, " %s %s %d %d %d %d", &s.emriStudent, &s.mbiemriStudent, &s.piketEFituara, &s.kalues, &s.id_pedagog, &s.mesatarja) != EOF)
					{
						if (s.piketEFituara > pmax)
							pmax = s.piketEFituara;

					}
				}
			fclose(f);
			if (nmrprov == 0)
			{
				printf("Nuk ka rezultate ne kete provim. \n");
				return;
			}
			f = fopen(frezultateProvimi, "r");
			if (f != NULL)
			{
				printf("Piket maksimale: %d, te arritura nga: \n", pmax);
				while (fscanf(f, " %s %s %d %d %d %d", &s.emriStudent, &s.mbiemriStudent, &s.piketEFituara, &s.kalues, &s.id_pedagog, &s.mesatarja) != EOF)
				{
					if (s.id_pedagog == pedagogID && s.Id_provimi == provimi)
					{
						if (s.piketEFituara == pmax) printf("%s %s\n", s.emriStudent, s.mbiemriStudent);
					}
				}
				printf("----------------------------------------------------------------------------------------------\n");
				fclose(f);
			}
			return;
		}
	}
		

}

pedagog Kerko_pedagog(char emri[32] , char mbiemri[32])
{
	struct pedagog p;
	int id;
	struct pedagog strukture_temp;
	FILE *f=fopen(fpedagog,"r");
	if(f != NULL)
	{
		while (fscanf(f, "%d %s %s %s %s %s %d", &p.id_pedagog, &p.emri, &p.mbiemri,&p.emriPerdoruesit, &p.password,  &p.lenda, &p.status ) != EOF)
		{
			if (strcmp(p.emri, emri) == 0 && strcmp(p.mbiemri, mbiemri) == 0)
			{
				fclose(f);
				return p;
			}
		}
	}	

}

pedagog Kerko_pedagogID(int pedagog)
{
	struct pedagog p;
	int id;
	struct pedagog strukture_temp;
	FILE* f = fopen(fpedagog, "r");
	if (f != NULL)
	{
		while (fscanf(f, "%d %s %s %s %s %s %d", &p.id_pedagog, &p.emri, &p.mbiemri, &p.emriPerdoruesit,&p.password, &p.lenda, &p.status) != EOF)
		{
			if (p.id_pedagog == pedagog)
			{
				fclose(f);
				return p;
			}
		}
	}

}

void shikoPyetjenKuEshteGabuarMeShume(int pedagog)
{
	struct rezultatIDetajuar p;
	struct pedagog pe = Kerko_pedagogID(pedagog);
	FILE* f = fopen(frezultateDetajuar, "r");
	int provimiID = shikoProvimet(pedagog);
	struct rezultatIDetajuar temp;
	int piket[100];
	int count = 0;
	int i = 0;
	int max = 0;
	char s[100];
	FILE* f2;
	if (provimiID == 0)
	{
		if (f != NULL)
		{
			int nmr = 0;
			f2 = f;
			while (fscanf(f, "%s %s %d %d %d %d %s %d %[^\n]", &p.pergjigjeSakte, &p.pergjigjaStudentit, &p.piketPerPyetje, &p.pedagogID, &p.studentId, &p.Id_provimi, &p.lenda, &p.rezultati, &p.pyetja) != EOF)
			{
				
					count = 0;
					FILE* f2 = fopen(frezultateDetajuar, "r");
					while (fscanf(f2, "%s %s %d %d %d %d %s %d %[^\n]", &temp.pergjigjeSakte, &temp.pergjigjaStudentit, &temp.piketPerPyetje, &temp.pedagogID, &temp.studentId, &temp.Id_provimi, &temp.lenda, &temp.rezultati, &temp.pyetja) != EOF)
					{
						if (strcmp(p.pyetja, temp.pyetja) == 0 && p.pedagogID == pedagog)
						{
							if (strcmp(temp.pergjigjaStudentit, temp.pergjigjeSakte) != 0) //Kontrollon nqs sjane te barabarta
								count++;
						}

					}
					fclose(f2);
					if (max == 0)
					{
						max = count;
						strcpy(s, p.pyetja);

					}
					//printf("%s \t %d \n" , p.pyetja , piket[i]);
					
					if (count > max)
					{
						max = count;
						strcpy(s, p.pyetja);

					}				

			}
			printf("Pyetja ku eshte gabuar me shume eshte : \n");
			printf("%s \t %d \n", s, max);
			printf("----------------------------------------------------------------------------------------------\n");
			fclose(f);
			return;


		}
	}
	else if (provimiID != 0)
	{
		if (f != NULL)
		{
			int nmr = 0;
			f2 = f;
			while (fscanf(f, "%s %s %d %d %d %d %s %d %[^\n]", &p.pergjigjeSakte, &p.pergjigjaStudentit, &p.piketPerPyetje, &p.pedagogID, &p.studentId, &p.Id_provimi, &p.lenda, &p.rezultati, &p.pyetja) != EOF)
			{
				if (provimiID == p.Id_provimi)
				{
					count = 0;
					FILE* f2 = fopen(frezultateDetajuar, "r");
					while (fscanf(f2, "%s %s %d %d %d %d %s %d %[^\n]", &temp.pergjigjeSakte, &temp.pergjigjaStudentit, &temp.piketPerPyetje, &temp.pedagogID, &temp.studentId, &temp.Id_provimi, &temp.lenda, &temp.rezultati, &temp.pyetja) != EOF)
					{
						if (strcmp(p.pyetja, temp.pyetja) == 0 && p.pedagogID == pedagog && provimiID == p.Id_provimi)
						{
							if (strcmp(temp.pergjigjaStudentit, temp.pergjigjeSakte) != 0)
								count++;
						}
					}
					fclose(f2);
					//piket[i] = count;
					//printf("%s \t %d \n" , p.pyetja , piket[i]);
					if (max == 0)
					{
						max = count;
						strcpy(s, p.pyetja);

					}
					if (count > max)
					{
						max = count;
						strcpy(s, p.pyetja);

					}
				

				}

			}
			printf("Pyetja ku eshte gabuar me shume eshte : \n ------------------------------------------------------------- \n");
			printf("%s \t %d \n", s, max);

			fclose(f);
			return;


		}
	}

}

void ShikoRezultatetStudent(int studentId)
{
	int pedagogu = ShfaqPedagoget();
	if (pedagogu == 0)
	{
		ShikoTeGjithaRezultatetTotal(studentId);
		return;
	}
	int provim = shikoProvimetStudent(pedagogu);
	struct rezultateProvimi s;
	FILE* f = fopen(frezultateProvimi, "r");
	const int size = 1000;
	int piket[size];
	int i = 0;
	int nmrRez = 0;
	if (provim == 0)
	{
		if (f != NULL)
		{
			int nmr = 0;
			printf("----------------------------------------------------------------------------------------------\n");
			printf("Rezultatet \n");
			//printf("Provimi \t  Emer \t \t Mbiemer \t Piket \t Eshte kalues \t Mesatarja \n");
			while (fscanf(f, "%s %d %d %d %s %s %d %d %f", &s.TemaProvimit, &s.id_pedagog, &s.idStudenti, &s.Id_provimi, &s.emriStudent, &s.mbiemriStudent, &s.piketEFituara, &s.kalues, &s.mesatarja) != EOF)
			{
				if (pedagogu == s.id_pedagog && s.idStudenti == studentId)
				{
					nmr++;
					char kalimi[32] = "Jo";
					piket[i] = s.piketEFituara;
					i++;
					nmrRez++;

				}
			}
			fclose(f);
			if (nmr == 0)
			{
				printf("Nuk ka rezultate me kete provim \n");
				return;
			}
			for (int i = 0; i < nmrRez; i++)
			{
				for (int j = 0; j < nmrRez; j++)
				{
					if (piket[j] > piket[i])
					{
						int tmp = piket[i];
						piket[i] = piket[j];
						piket[j] = tmp;
					}
				}
			}

			int k = 0;
			for (int i = nmrRez - 1; i >= 0; i--)
			{
				f = fopen(frezultateProvimi, "r");
				while (fscanf(f, "%s %d %d %d %s %s %d %d %f", &s.TemaProvimit, &s.id_pedagog, &s.idStudenti, &s.Id_provimi, &s.emriStudent, &s.mbiemriStudent, &s.piketEFituara, &s.kalues, &s.mesatarja) != EOF)
				{
					char kalimi[32] = "Jo";

					if (piket[i] == s.piketEFituara && s.id_pedagog == pedagogu && s.idStudenti == studentId)
					{
						if (s.kalues == 1)
						{
							strcpy(kalimi, "po");
						}
						//printf("%s \t \t %s \t %s \t  \t %d \t %s \t \t %f \n", s.TemaProvimit, s.emriStudent, s.mbiemriStudent, s.piketEFituara, kalimi, s.mesatarja);
						printf("\nTema e provimit:\t%s\nEmer:\t\t%s\nMbiemer:\t%s\nPiket:\t%d\nKalues:\t%s\nMesatarja:\t\t%f\n", s.TemaProvimit, s.emriStudent, s.mbiemriStudent, s.piketEFituara, kalimi, s.mesatarja);
						printf("----------------------------------------------------------------------------------------------\n");

					}

				}
			}
			fclose(f);
			return;
		}

	}
	else if (provim != 0)
	{
		if (f != NULL)
		{
			int nmr = 0;
			printf("----------------------------------------------------------------------------------------------\n");
			printf("Rezultatet \n");
			//printf("Provimi \t  Emer \t \t Mbiemer \t Piket \t Eshte kalues \t Mesatarja \n");
			while (fscanf(f, "%s %d %d %d %s %s %d %d %f", &s.TemaProvimit, &s.id_pedagog, &s.idStudenti, &s.Id_provimi, &s.emriStudent, &s.mbiemriStudent, &s.piketEFituara, &s.kalues, &s.mesatarja) != EOF)
			{
				if (pedagogu == s.id_pedagog && s.Id_provimi == provim && s.idStudenti == studentId)
				{
					nmr++;
					char kalimi[32] = "Jo";
					piket[i] = s.piketEFituara;
					i++;
					nmrRez++;

				}
			}
			fclose(f);
			if (nmr == 0)
			{
				printf("Nuk ka rezultate me kete provim \n");
				return;
			}
			for (int i = 0; i < nmrRez; i++)
			{
				for (int j = 0; j < nmrRez; j++)
				{
					if (piket[j] > piket[i])
					{
						int tmp = piket[i];
						piket[i] = piket[j];
						piket[j] = tmp;
					}
				}
			}

			int k = 0;
			for (int i = nmrRez - 1; i >= 0; i--)
			{
				f = fopen(frezultateProvimi, "r");
				while (fscanf(f, "%s %d %d %d %s %s %d %d %f", &s.TemaProvimit, &s.id_pedagog, &s.idStudenti, &s.Id_provimi, &s.emriStudent, &s.mbiemriStudent, &s.piketEFituara, &s.kalues, &s.mesatarja) != EOF)
				{
					char kalimi[32] = "Jo";

					if (piket[i] == s.piketEFituara && s.id_pedagog == pedagogu && s.idStudenti == studentId && s.Id_provimi == provim)
					{
						if (s.kalues == 1)
						{
							strcpy(kalimi, "po");
						}
						printf("\nTema e provimit:\t%s\nEmer:\t\t%s\nMbiemer:\t%s\nPiket:\t%d\nKalues:\t%s\nMesatarja:\t\t%f\n", s.TemaProvimit, s.emriStudent, s.mbiemriStudent, s.piketEFituara, kalimi, s.mesatarja);
						printf("----------------------------------------------------------------------------------------------\n");

					}




				}
			}
			fclose(f);
			return;
		}
	}
}

void ShikoTeGjithaRezultatetTotal(int studentId)
{
	struct rezultateProvimi s;
	FILE* f = fopen(frezultateProvimi, "r");
	const int size = 1000;
	int piket[size];
	int i = 0;
	int nmrRez = 0;
	if (f != NULL)
	{
		int nmr = 0;
		printf("----------------------------------------------------------------------------------------------\n");
		printf("Rezultatet \n");
		//printf("Provimi \t  Emer \t \t Mbiemer \t Piket \t Eshte kalues \t Mesatarja \n");
		while (fscanf(f, "%s %d %d %d %s %s %d %d %f", &s.TemaProvimit, &s.id_pedagog, &s.idStudenti, &s.Id_provimi, &s.emriStudent, &s.mbiemriStudent, &s.piketEFituara, &s.kalues, &s.mesatarja) != EOF)
		{
			if ( s.idStudenti == studentId)
			{
				nmr++;
				char kalimi[32] = "Jo";
				piket[i] = s.piketEFituara;
				i++;
				nmrRez++;

			}
		}
		fclose(f);
		if (nmr == 0)
		{
			printf("Nuk keni rezultate \n");
			return;
		}
		for (int i = 0; i < nmrRez; i++)
		{
			for (int j = 0; j < nmrRez; j++)
			{
				if (piket[j] > piket[i])
				{
					int tmp = piket[i];
					piket[i] = piket[j];
					piket[j] = tmp;
				}
			}
		}

		int k = 0;
		for (int i = nmrRez - 1; i >= 0; i--)
		{
			f = fopen(frezultateProvimi, "r");
			while (fscanf(f, "%s %d %d %d %s %s %d %d %f", &s.TemaProvimit, &s.id_pedagog, &s.idStudenti, &s.Id_provimi, &s.emriStudent, &s.mbiemriStudent, &s.piketEFituara, &s.kalues, &s.mesatarja) != EOF)
			{
				char kalimi[32] = "Jo";

				if (piket[i] == s.piketEFituara && s.idStudenti == studentId)
				{
					if (s.kalues == 1)
					{
						strcpy(kalimi, "po");
					}
					printf("\nTema e provimit:\t%s\nEmer:\t\t%s\nMbiemer:\t%s\nPiket:\t%d\nKalues:\t%s\nMesatarja:\t\t%f\n", s.TemaProvimit, s.emriStudent, s.mbiemriStudent, s.piketEFituara, kalimi, s.mesatarja);
					printf("----------------------------------------------------------------------------------------------\n");

				}

			}
		}
		fclose(f);
		return;
	}
}

int gjejIdMaxProvim()
{
	struct provimi p;
	FILE* f = fopen(fprovimi, "r");
	int max = 0;
	if (f != NULL)
	{
		printf("Zgjidh provimin ku doni te futeni : \n");
		printf(" \t Tema Provimit\n");
		while (fscanf(f, "%d %d %s", &p.IdProvimi, &p.idPedagogu, &p.TemeProvimi) != EOF)
		{
			max = p.IdProvimi;
			if (p.IdProvimi > max)
			{
				max = p.IdProvimi;
			}
		}
		return max;
	}
	else printf("Veprimi nuk u krye.");
	fclose(f);
	return 0;
}

int gjejIdMaxStudent()
{
	struct student s;
	FILE* f = fopen(fstudent, "r");
	int max = 0;
	if (f != NULL)
	{
		while (fscanf(f, "%d %s %s %s %s %d %s %d", &s.id_student, &s.emri, &s.mbiemri, &s.emriPerdoruesit, &s.datelindja, &s.piket, &s.password, &s.status) != EOF)
		{
			max = s.id_student;
			if (s.id_student > max)
			{
				max = s.id_student;
			}
		}
		return max;
		fclose(f);
	}
	else printf("Veprimi nuk u krye.");
	return 0;
}

int gjejIdMaxProfesor()
{
	struct pedagog p;
	int id;
	struct pedagog strukture_temp;
	FILE* f = fopen(fpedagog, "r");
	int max = 0;
	if (f != NULL)
	{
		while (fscanf(f, "%d %s %s %s %s %s %d", &p.id_pedagog, &p.emri, &p.mbiemri, &p.emriPerdoruesit, &p.password, &p.lenda, &p.status) != EOF)
		{
			max = p.id_pedagog;
			if (p.id_pedagog > max)
			{
				max = p.id_pedagog;
			}
		}
		return max;
		fclose(f);
	}
	else printf("Veprimi nuk u krye.");
	return 0;
}

void ndrshoPassword()
{
	printf("\n 1 - Student \n 2 - Pedagog \n");
	int kodi = 0;
	scanf("%d", &kodi);
	char fjalekamlimi[50];
	long password;
	switch (kodi)
	{
	case 1://Ndrysho password Student
		int studentId;
		printf("Jepni ID e studentit: \n");
		scanf("%d", &studentId);
		FILE* fs;
		fs = fopen(fstudent, "r");
		//struct student stmp;
		struct student s;
		if (fs != NULL)
		{
			FILE* temp = fopen("skedartemp.txt", "w");
			while (fscanf(fs, "%d %s %s %s %s %d %s %d", &s.id_student, &s.emri, &s.mbiemri, &s.emriPerdoruesit, &s.datelindja, &s.piket, &s.password, &s.status) != EOF)
			{
				
				if (s.id_student == studentId)
				{
					password = gjeneroFjalekalim(s.id_student,s.emriPerdoruesit);
					sprintf(fjalekamlimi ,"%d", password);
					strcpy(s.password, fjalekamlimi);
				}
				fprintf(temp, "%d %s %s %s %s %d %s %d \n", s.id_student, s.emri, s.mbiemri, s.emriPerdoruesit, s.datelindja, s.piket, s.password, s.status);

			}
			fclose(fs);
			fclose(temp);
			remove(fstudent);
			rename("skedartemp.txt", fstudent);
			printf("Studenti me ID %d iu ndryshua fjalekalimi.\n Fjalekalimi ri : %s \n", studentId , fjalekamlimi);
			printf("----------------------------------------------------------------------------------------------\n");
			return;
		}
		else
		{
			printf("Veprimi nuk u krye.");
		}
		break;

	case 2://Ndrysho password Pedagog
		struct pedagog p;
		int id;
		printf("Jepni ID e pedagogut qe doni te fshini: ");
		scanf("%d", &id);
		FILE* f = fopen(fpedagog, "r");
		//struct pedagog stmp;
		if (f != NULL)
		{
			FILE* temp = fopen("skedartemp.txt", "w");
			while (fscanf(f, "%d %s %s %s %s %s %d", &p.id_pedagog, &p.emri, &p.mbiemri, &p.emriPerdoruesit, &p.password, &p.lenda, &p.status) != EOF)
			{
				if (p.id_pedagog == id)
				{
					//fjalekalimi = gjeneroFjalekalim(p.id_pedagog,p.emri,p.mbiemri);
					password = gjeneroFjalekalim(p.id_pedagog, p.emriPerdoruesit);
					sprintf(fjalekamlimi, "%d", password);
					strcpy(s.password, fjalekamlimi);
				}
				fprintf(temp, "%d %s %s %s %s %s %d \n", p.id_pedagog, p.emri, p.mbiemri, p.emriPerdoruesit, p.password, p.lenda, p.status);

			}
			fclose(f);
			fclose(temp);
			remove(fpedagog);
			rename("skedartemp.txt", fpedagog);
			printf("Pedagogu me ID %d iu ndryshua fjalekalimi.\n Fjalekalimi ri : %s \n", id, fjalekamlimi);
			printf("----------------------------------------------------------------------------------------------\n");
			return;
		}
		else printf("Veprimi nuk u krye.");
		break;
	}
	return;
		
}

void shfaqRezultatet()
{
	struct rezultateProvimi s;
	FILE* f = fopen(frezultateProvimi, "r");
	const int size = 1000;
	int piket[size];
	int i = 0;
	int nmrRez = 0;
	if (f != NULL)
	{
		int nmr = 0;
		printf("----------------------------------------------------------------------------------------------\n");
		printf("Rezultatet \n");
		//printf("Provimi \t  Emer \t \t Mbiemer \t Piket \t Eshte kalues \t Mesatarja \n");
		while (fscanf(f, "%s %d %d %d %s %s %d %d %f", &s.TemaProvimit, &s.id_pedagog, &s.idStudenti, &s.Id_provimi, &s.emriStudent, &s.mbiemriStudent, &s.piketEFituara, &s.kalues, &s.mesatarja) != EOF)
		{
			
				nmr++;
				char kalimi[32] = "Jo";
				piket[i] = s.piketEFituara;
				i++;
				nmrRez++;

			
		}
		fclose(f);
		if (nmr == 0)
		{
			printf("Nuk keni rezultate \n");
			return;
		}
		for (int i = 0; i < nmrRez; i++)
		{
			for (int j = 0; j < nmrRez; j++)
			{
				if (piket[j] > piket[i])
				{
					int tmp = piket[i];
					piket[i] = piket[j];
					piket[j] = tmp;
				}
			}
		}

		int k = 0;
		for (int i = nmrRez - 1; i >= 0; i--)
		{
			f = fopen(frezultateProvimi, "r");
			while (fscanf(f, "%s %d %d %d %s %s %d %d %f", &s.TemaProvimit, &s.id_pedagog, &s.idStudenti, &s.Id_provimi, &s.emriStudent, &s.mbiemriStudent, &s.piketEFituara, &s.kalues, &s.mesatarja) != EOF)
			{
				char kalimi[32] = "Jo";

				if (piket[i] == s.piketEFituara)
				{
					if (s.kalues == 1)
					{
						strcpy(kalimi, "po");
					}
					printf("\nTema e provimit:\t%s\nEmer:\t\t%s\nMbiemer:\t%s\nPiket:\t%d\nKalues:\t%s\nMesatarja:\t\t%f\n", s.TemaProvimit, s.emriStudent, s.mbiemriStudent, s.piketEFituara, kalimi, s.mesatarja);
					printf("----------------------------------------------------------------------------------------------\n");

				}

			}
		}
		fclose(f);
		return;
	}
}
