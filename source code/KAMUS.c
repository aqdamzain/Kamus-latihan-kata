#include "kamus.h" // terdapat struct dan semua fungsi modular yang mendukung applikasi kamus

#include <conio.h>
#include <windows.h>
#include <process.h>



void gotoxy (int x, int y)
{
	COORD coord;
	coord.X=x;
	coord.Y=y;

	SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


int main (void)
{
	int r,q;
	kamusPtr head = NULL, headCpy = NULL, node = NULL, temp;
	int choice, soal;

	gotoxy(50,25);
	printf("Loading....");
	gotoxy(50,27);
	for (r=1; r<=20; r++)
		{
			for (q=0; q<=100000000; q++);
			printf ("%c", 177);
		}

		inputKamus(&head);
	do
	{

		system ("cls");

		printf("  		    `-::://///:+...-.......-..`                `--....--.........`                \n"
"	            .s::::///::--`             .---.         ---.`                `----`                    \n"
"	       ``...-o::--`                       `.:-     -:.```                      .--.                 \n"
"	      -+```         KAMUS                  ``.:- .:.`````  BAHASA INDONESIA       `...-...-.`       \n"
"	 `--/:./                                   ````-o:```````                                 :`-+--.   \n"
"	+yyo/-`/                                   `````+.```````    .....................        : .+..ss. \n"
"	yy:..-`:`                                  `````/.```````                                 : ./` +y+ \n"
"	yy/.`-`:`     1. Lihat Kamus               `````:.```````    .....................        : ..` +yo \n"
"	sy+.`.`-.                                  `````:-```````                                 / ` ` /yo \n"
"	oyo..``.-     2. Cari Kata                 `````-:```````    .....................        /   ` /yo \n"
"	+ys..```/                                  `````.:```````                                 : `   /yo \n"
"	/yy..```/     3. Masukan Kata              `````./```````    .....................       `:`.   /y+ \n"
"	:yh-.```/                                  `````./```````                                ..`.   /y/ \n"
"	.yy:.```:`    4. Latihan Kata              `````./```````    .....................       :```   +y: \n"
"	`yy+````-.                                 `````./```````                                / .`   oy- \n"
"	 yyo`````:    5. Bantuan                   `````./```````    .....................      `: .`   sh. \n"
"	 ssy```` /                                 `````./```````                               -.`. . `yy` \n"
"	 +yy.`.``:`   6. Keluar                    `````./```````    .....................      / `  - `ys  \n"
"	 /yy-`..`-.                                ``````/```````                              .- ` .. -yo  \n"
"	 -yy/``- `:                                ``````/```````    ```.------.----...```     :` ` :` /y/  \n"
"	 `hyo``:` /       ````...............```  ```````/````````.-............``````.....--`.:  ``/  sy-  \n"
"	  yys`.-. :` ``--.....```````````````...--.``````/`````--..  `` `````                `-:```:- `yy`  \n"
"	  osy...: -:...      ````       ````````` .--.``./``.:-`  ``.``.`````````              `-:`+` -ys   \n"
"	  /yy-.`+--`       ``..-:///+++++++/:-.```   .:-./.:-` ``..:+ossyyyyyyysso++/:.``````....:o:  +y/   \n"
"	  -yy+.::`   ``.-/oosyhhyyyyyyyyyyyyyhhys/.`  `-/o:.`  `/shhhyyyyyyyyyyyyyyyyhhyso+:-.`...-:-`yy.   \n"
"	  `hss/-.-:+osyhhyyyhhhhhhhhhhhhhhhyyysyhdh+.` .-+-.` -yddyyyyyyhhhhhhhhhhhhhhhhyyyhhyso+//:/oys    \n"
"	   syhhhhhhhhhhyysso+//:::--..``        sdhyoo+++o+++oyhhd-        ``..-::://++ossyyhhhhhhhhyyh:    \n"
"	   ./+/:--.`                            `-/+ossssssssso+:.                            `..-::/+:");
		printf ("\n\t\t\t\tInput Pilihan :");
		scanf ("%d", &choice);
		getchar();
		int llen, radnum, correct, jwb, i, j;
		kamusPtr* soalArr;
		char** jwbArr;
		int* intArr;
		char* key;
		char pilihC;
		switch (choice)
		{
			case 1://Lihat kata
				system ("cls");
				listkata (head);
				printf("\nTekan Enter untuk lanjutkan: ");
				getchar();
				system ("cls");
				break;
			case 2://Cari kata
				system ("cls");
				temp = head;
				key = malloc(100*sizeof(char));
				printf(" Input kata kunci: ");
				gets(key);
				realloc(key,(strlen(key)+1)*sizeof(char));
				up_str(key);
				while(temp!=NULL)
                {
                    if(strcmp(key,temp->kata)==0)
                    {
                        printf("Kata:       %s\n", temp->kata);
                        printf("Definisi:   %s\n", temp->definisi);
                        printf("Tipe:       %s\n", temp->tipe);
                    }
                    temp = temp->next;
                }
				getch();
				//free the memory allocation after used
				free(key);
				system ("cls");
				break;
			case 3://Masukan kata
				system ("cls");
   				inputKata(&head);
   				printKamusF(head, listLen(head));
   				printf("\nTekan Enter untuk lanjutkan: ");
   				getchar();
   				system ("cls");
    			break;
            case 4://Latihan kata
                system("cls");
                printf(" Masukan jumlah soal: ");
                scanf("%d", &soal);
                getchar();
                system("cls");
                correct = 0;
                listCpy(head, &headCpy);
                llen = listLen(headCpy);

                soalArr = malloc(soal*sizeof(kamusPtr));
                jwbArr = malloc(4*sizeof(char*));
                intArr = malloc(4*sizeof(int));

                for(i=0; i<soal; i++) // mengambil soal dari linked list
                {
                    radnum = rand()%(llen);
                    takeNode(&headCpy, radnum, &node);//mengambi node dalam list yang telah dicopy kemudian menghapus node tersebut pada list yang telah dicopy, seperti mengambil kelereng dalam toples
                    soalArr[i] = node; // Memasukan address node yang telah diambil dari list ke dalam array
                    // soalArr = kumpulan address dari node yang akan menjadi soal dari latihan
                    llen = llen-1;
                }

                for(i=0; i<soal; i++)
                {
                    randnumArr(intArr, 4);//menyusun 4 bilangan dari 0 sampai 3 secara acak kedalam array intArr
                    do
                    {
                        printf(" %s\n\n", (soalArr[i]->definisi));
                        jwbArr[intArr[0]] = soalArr[i]->kata;//Input pilihan benar ke array dengan nilai index yg random sesuai urutan
                        for(j=1; j<4; j++)
                        {//input pilihan salah ke array dengan nilai index yg random sesuai urutan
                            answerChKat(head, listLen(head), soalArr[i]->kata, &jwbArr[intArr[j]]);//mengambil pilihan salah dari linked list secara acak yang berbeda dengan
                                                                                                        //pilihan benar.
                        }
                        for(j=0; j<4; j++)
                        {
                            printf(" %d. %s\n",(j+1), jwbArr[j]);
                        }
                        printf(" Jawaban: ");
                        scanf("%d", &jwb);
                        getchar();
                        system("cls");

                    }while(jwb<1 || jwb>4);

                    if(strcmp(jwbArr[jwb-1], soalArr[i]->kata)==0)//menghitung nilai jawaban yang benar
                    {
                        correct = correct + 1;
                        printf("\a");
                        printf("\n BENAR!\n");
                    }
                    else
                    {
                        printf("\n SALAH!\n");
                    }
                    Sleep(200);
                    system("cls");
                }
                //menampilkan jawaban benar dan salah
                printf("\n\n Jumlah Benar: %d\n", correct);
                printf(" Salah       : %d\n", (soal-correct));

                printf("\n Kunci Jawaban: \n");

                for(i=0; i<soal; i++)
                {
                    printf(" %d. Definisi: %s\n", (i+1), soalArr[i]->definisi);
                    printf("     Kata    : %s\n\n", soalArr[i]->kata);
                }

                //free the memory allocation after used
                free(soalArr);
                free(jwbArr);
                free(intArr);
                while(headCpy!=NULL)
                {
                    temp = headCpy;
                    headCpy = headCpy->next;
                    free(temp);
                }

                printf("\n Enter untuk kembali ke menu: ");
                getchar();
                system("cls");
                break;
            case 5://Bantuan
                system("cls");
                printf("\n\n        1. About\n");
                printf("        2. tutorial\n");
                printf(" Pilih: ");
                scanf("%d", &choice);
                getchar();
                switch(choice)
                {
                case 1:
                    system("cls");
                    printf("\n\n\n    Aplikasi ini adalah Kamus bahasa Indonesia dengan latihan kosakata.\n"
                           "    Bertujuan untuk mempermudah pengguna mempelajari kosakata bahasa Indonesia.\n"
                           "    \nCreate by:\n      Aqdam Zain Hajj & Muhammad Alfiyansyah\n"
                           "                      Teknik Komputer\n"
                           "                   Universitas Indonesia\n");
                    break;
                case 2:
                    system("cls");
                    printf("\n\n   1. Tutorial input pilihan: \n\n"
                           "       *input pilihan angka \n"
                           "        input dari pilihan haruslah sesuai dengan pilihan angka(integer) yang tertera!\n"
                           "       *input pilihan y/n \n"
                           "        input dari pilihan adalah berupa karakter y atau n(tidak boleh integer) \n"
                           "\n   2. Tutorial masukan kata: \n\n"
                           "        input dari kata, definisi, dan tipe adalah string(dapat berupa kumpulan angka atau karakter\n"
                           );
                default:
                    printf("Invalid Choice!");
                }

                printf("\n\n\n      Enter untuk kembali ke menu: ");
                getchar();
                system("cls");
                break;
    		case 6://Keluar
    		    printf("\a\n\n\t Anda yakin ingin keluar aplikasi?(y/n): ");
    		    scanf("%c", &pilihC);
    		    getchar();

    		    //free the memory allocation after used
    		    if(pilihan_yn(pilihC)==0)
                {
                    while(headCpy!=NULL)
                    {
                        temp = headCpy;
                        headCpy = headCpy->next;

                        free(temp->definisi);
                        free(temp->kata);
                        free(temp->tipe);
                        free(temp);
                    }
                    return 0;
                }
    			break;
    		default:
            	system("cls");
            	printf("\n\n\n\t\t INVALID COICE!\n\t\t TRY AGAIN!\n");
            	printf("\nPress enter to continue: ");
            	getchar();
            	getchar();
            	system("cls");
    	}
	}while (choice!=-1);
}
