typedef struct
{   int studentId,bookId;
    MyDate issDate;
    MyDate retDate;
}ReturnBook;

void returningBook()
{    time_t t=time(NULL);
     ReturnBook ret;
     IssuedBook iss;
     printf("\n ========================   Returning book ==================================");
     struct tm tm = *localtime(&t);
     ret.retDate.y=tm.tm_year+1900;
     ret.retDate.m=tm.tm_mon+1;
     ret.retDate.d=tm.tm_mday;
     printf("\nreturning date is : %d/%d/%d\n", ret.retDate.d, ret.retDate.m,ret.retDate.y);
     printf("Enter Book ID:");
     scanf("%d",&ret.bookId);
     if(searchBook(ret.bookId)==0)
     {   printf("\ninvalid book-id entered\n");
         getch();
         return;
     }
     iss=getIssuedBookDetails(ret.bookId);
     if(iss.bookId==0)
     {   printf("record not found");
         getch();
         return;
     }
      printf("\n the issued details are ");
      printf("%d  %d   %d/%d/%d", iss.bookId, iss.studentId, iss.issuedDate.d, iss.issuedDate.m, iss.issuedDate.y);
      ret.studentId=iss.studentId;
      ret.issDate=iss.issuedDate;
      updateBookStatus(iss.bookId,1);
      addRecordToReturnedFile(ret);
      deleteRecordFromIssuedFile(iss.bookId);
      getch();
}
//=========================================================================================================================
void addRecordToReturnedFile(ReturnBook r)
{	FILE *fp;
    fp=fopen("return.dat", "ab");
	if(fp==NULL)
	{	printf("Unable to open book.dat file");
        getch();
		return;
    }
	fwrite(&r,sizeof(r),1,fp);
	fclose(fp);
	printf("\nsuccessfully added");
	getch();
}
//=========================================================================================================================
void displayAllReturnedBooks()
{	FILE *fp;
	ReturnBook r;
	int count=0,k;
    fp=fopen("return.dat", "rb");
	if(fp==NULL)
    {	printf("no records found");
        getch();
        return;
    }
	printf("\nAll Book Returned Details:");
	while(1)
	{    k=fread(&r, sizeof(r),1 , fp);
         if(k==0)break;
         printf("\n%d  %d    %d/%d/%d       %d/%d/%d ",r.bookId,r.studentId,r.issDate.d,r.issDate.m,r.issDate.y, r.retDate.d, r.retDate.m, r.retDate.y);
         count++;
    }
	fclose(fp);
	printf("\ntotal (%d) recrods are found", count);
	getch();
}
//=========================================================================================================================
