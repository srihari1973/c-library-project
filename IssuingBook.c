#include<time.h>
typedef struct
{   int d,m,y;
}MyDate;

typedef struct
{   int studentId,bookId;
    MyDate issuedDate;
}IssuedBook;

 //==========================================================================================================
void issuingBook()
{   time_t t=time(NULL);
    IssuedBook iss;
    printf("\n ========================   issuing book ==================================");
    struct tm tm = *localtime(&t);
    iss.issuedDate.y=tm.tm_year+1900;
    iss.issuedDate.m=tm.tm_mon+1;
    iss.issuedDate.d=tm.tm_mday;
    printf("\nissuing date is : %d/%d/%d\n", iss.issuedDate.d,iss.issuedDate.m,iss.issuedDate.y);
    printf("Enter Book ID:");
    scanf("%d",&iss.bookId);
    if(isBookAvailableInLibrary(iss.bookId)==0)
    {    printf("error wrong book-id found (or) book is not availabe in the library \n");
         getch();
         return;
    }
    printf("Enter student ID:");
    scanf("%d",&iss.studentId);
    if(searchStudent(iss.studentId)==0)
    { printf("invalid student id entered, enter valid student id \n");
      return;
    }
    addBookToIssueFile(iss);
    updateBookStatus(iss.bookId,0);
 }
 // add entry to file issue.dat
 //==========================================================================================================
void addBookToIssueFile(IssuedBook iss)
{   FILE *fp;
    fp=fopen("issue.dat", "ab");
	if(fp==NULL)
	{	printf("Unable to open book.dat file");
        getch();
        return;
	}
	printf("\n %d   %d    %d/%d/%d", iss.bookId, iss.studentId, iss.issuedDate.d, iss.issuedDate.m , iss.issuedDate.y);
	fwrite(&iss,sizeof(iss),1,fp);
	fclose(fp);
	printf("\nrecord successfully added");
	getch();
}
 //==========================================================================================================
 void displayAllIssuedBooks()
 {  IssuedBook iss;
	int count=0,k;
	FILE *fp;
	fp=fopen("issue.dat", "rb");
	if(fp==NULL)
	{   printf("no records found");
	    getch();
	    return;
	}
    printf("\n book-id  student-id  date of issued");
	while(1)
	{   k=fread(&iss,sizeof(iss),1,fp);
		if(k==0)
           break;
        count++;
        printf("\n  %d          %d         %d/%d/%d", iss.bookId, iss.studentId, iss.issuedDate.d, iss.issuedDate.m , iss.issuedDate.y);
    }
	fclose(fp);
	printf("\n\n total %d record found ", count);
	fflush(stdin);
	getch();
 }
//==========================================================================================================
    IssuedBook getIssuedBookDetails(int bookId)
	{	IssuedBook iss={0};
		int k, boool=0;
		FILE *fp;
		fp=fopen("issue.dat", "rb");
		if(fp==NULL)
			return iss;
		while(1)
		{	k=fread(&iss,sizeof(iss), 1,fp);
			if(k==0) break;
			if(iss.bookId==bookId)
			{   boool=1;
			    break;
			}
		}
		fclose(fp);
		if(boool==0)
		   iss.bookId=0;
		return iss;
	}
//---------------------------  deleting record from file ----------------------------
    void deleteRecordFromIssuedFile(int bookId)
    {   IssuedBook iss={0};
		int k;
		FILE *fp, *ft;
		fp=fopen("issue.dat", "rb");
		ft=fopen("t.dat", "rb");
		if(fp==NULL || ft==NULL)
		{   fclose(fp);
            fclose(ft);
		}
		while(1)
		{	k=fread(&iss,sizeof(iss), 1,fp);
			if(k==0) break;
			if(iss.bookId!=bookId)
                fwrite(&iss,sizeof(iss),1,fp);
		}
		fclose(fp);
		fclose(ft);
		remove("issue.dat");
		rename("t.dat","issue.dat");
    }
