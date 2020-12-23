#include<stdio.h>
#include<stdlib.h>
#include"student.c"
#include"book.c"
#include"IssuingBook.c"
#include"returningBook.c"
void bookMenu();
void studentMenu();
int main()
{  int ch;
    while(1)
    {   system("cls");
        printf("\n--------------------------   Main Menu --------------------------------");
        printf("\n\n\t\t\t1. Student Entry \
                \n\t\t\t2. Book Entry \
                \n\t\t\t3. Issuing Book \
                \n\t\t\t4. returning Book  \
                \n\t\t\t5. dispplay all issued book details \
                \n\t\t\t6. dispaly all returned book details\
                \n\t\t\t0. exit  ");
        printf("\n\t\t\t\t Enter choice :");
        scanf("%d", &ch);
        switch(ch)
        {   case 1:  studentMenu();
                     break;
            case 2:  bookMenu();
                     break;
            case 3:  issuingBook();
                     break;
            case 4:  returningBook();
                     break;
            case 5:  displayAllIssuedBooks();
                     break;
            case 6:  displayAllReturnedBooks();
                     break;
            case 0:  return 0;
        }
      }
      return 0;
 }
//================================================================================================================

