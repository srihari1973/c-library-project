 typedef  struct			// structure of an employee
 {  int  bookId;
	char bookTitle[20];
	char authorName[20];
	int status;
  }Book;

 void bookMenu()
 {      int ch;
        while(1)
        {   system("cls");
            printf("\n--------------------------  Book Menu --------------------------------");
            printf("\n\n\t\t\t1. add book \
                \n\t\t\t2. modify book \
                \n\t\t\t3. delete book \
                \n\t\t\t4. print all  \
                \n\t\t\t0. exit  ");
            printf("\n\t\t\t\t Enter choice :");
            scanf("%d", &ch);
            switch(ch)
            {   case 1: appendBook();
                        break;
                case 2: modifyBook();
                        break;
                case 3: deleteBook();
                        break;
                case 4: printAllBooks();
                        break;
                case 0: return ;
            }
        }
      return;
 }

// ------------------this append function appends a record in the file ---------------------
	void appendBook()
    {	FILE *fp;
		Book e;
		system("cls");
		printf("\n ================   adding book details ===================");
		while(1)
        {   printf("\nenter Book No:");
            scanf("%d",&e.bookId);
            if(searchBook(e.bookId)==1)
                printf("\n duplicate id found");
            else break;
        }
		printf("Enter Book Name:");
		fflush(stdin);
		gets(e.bookTitle);
		printf("enter Author Name :");
		gets(e.authorName);
		fp=fopen("book.dat", "ab");
		if(fp==NULL)
		{	printf("Unable to open book.dat file");
            getch();
			return;
		}
		e.status=1;
		fwrite(&e,sizeof(e),1,fp);
		fclose(fp);
		printf("record successfully added");
		getch();
	}

// -------------------  Delete function, deletes a record in the file --------------------
	void deleteBook()
	{   FILE *fp,*ft;
		Book  e;
		int bookId,found=0,k;
		fp=fopen("book.dat", "rb");
		ft=fopen("temp.dat","wb");
		if(fp==NULL || ft==NULL )
		{	printf("unable to open file");
			fclose(fp);
		    fclose(ft);
		    getch();
			return;
		}
		system("cls");
		printf("\n =======================         deleting Book ======================================== ");
 		printf("\nenter book-id to delete record :");
		scanf("%d",&bookId);
		while(1)
		{	k=fread(&e,sizeof(e),1,fp);
			if(k==0)   // eof is reached
				break;
			if(bookId==e.bookId)
				found=1;	// record is found
			else
				fwrite(&e,sizeof(e), 1 ,ft);
		}
		if(found==1)
			printf("Book deleted success fully");
		else
			printf("record not found with book-id %d", bookId);
		fclose(fp);
		fclose(ft);
		remove("book.dat");
		rename("temp.dat","book.dat");
		getch();
	}

// -----------------------------  Modifying information of book ----------------------------
	void modifyBook()
	{	Book e;
		int found=0;
		int bookId,k;
		long int pos;
		FILE *fp;
		fp=fopen("book.dat","rb+");
		if(fp==NULL)
		{	printf("file not found ");
			return;
		}
		system("cls");
		printf("\n =======================         modify Book    ======================================== ");
		printf("\n enter Book ID number:");
		scanf("%d",&bookId);
		while(1)
		{	k=fread(&e,sizeof(e),1,fp);
			if(k==0)     // if eof then stop.
				break;
			if(bookId==e.bookId)
			{	found= 1;	// record is found
				break;
			}
		}
		if(found==0)
		    printf("\n Book not found");
        else
		{	pos=ftell(fp);
			pos=pos-sizeof(e);
			fseek(fp, pos, SEEK_SET);	// move the file pointer one position back
			printf("old Tittle : %s", e.bookTitle);
			printf("\n Enter New Title :");
			fflush(stdin);
			gets(e.bookTitle);
			fwrite(&e,sizeof(e), 1 ,fp);// overwriting old record
			printf("\n book tittle suceessfully changed\n press any key ");
		}
		fclose(fp);
		getch();
	}

//------------------------------- print all books detailes ------------------------------------------------------
	void printAllBooks()
	{	Book e;
		int count=0,k;
		FILE *fp;
		fp=fopen("book.dat", "rb");
		if(fp==NULL)
		{	printf("file not found ");
		    getch();
			return;
		}
		system("cls");
		printf("\n\t\t\t  all books details  \n");
		printf("\n book-id    book-tittle       author-name    status");
		printf("\n ===================================================\n");
		while(1)
		{	k=fread(&e,sizeof(e), 1,fp);
			if(k==0) break;
			printf("%-5d ",e.bookId);
			printf("%-20s",e.bookTitle);
			printf("%-20s",e.authorName);
			printf("%5d\n",e.status);
			count++;
		}
		printf("\n total (%d) records found", count);
		printf("\n\t press any key to continue");
		fclose(fp);
		fflush(stdin);
		getch();
	}

// -----------------------   searching student -----------------------------------------
	int searchBook(int bookId)
	{	Book e;
		int found=0,k;
		FILE *fp;
		fp=fopen("book.dat", "rb");
		if(fp==NULL)
			return 0;
		while(1)
		{	k=fread(&e,sizeof(e), 1,fp);
			if(k==0) break;
			if(e.bookId==bookId)
            {   found=1;
                break;
            }
		}
		fclose(fp);
		return found;
	}
//------------------------------------------------------------------------------------------
int isBookAvailableInLibrary(int bookId)
{       Book e;
		int found=0,k;
		FILE *fp;
		fp=fopen("book.dat", "rb");
		if(fp==NULL)
			return 0;
		while(1)
		{	k=fread(&e,sizeof(e), 1,fp);
			if(k==0) break;
			if(e.bookId==bookId && e.status==1)
            {   found=1;
                break;
            }
		}
		fclose(fp);
		return found;
}
//--------------------------------------------------------------------------------------
void updateBookStatus(int bookId, int bookStatus)
{       Book e;
		int found=0;
		int eno,k;
		long int pos;
		FILE *fp;
		fp=fopen("book.dat","rb+");
		if(fp==NULL)
		{	printf("file not found ");
			return;
		}
		while(1)
		{	k=fread(&e,sizeof(e),1,fp);
			if(k==0)     // if eof then stop.
				break;
			if(bookId==e.bookId)
			{	found= 1;	// record is found
				break;
			}
		}
		if(found==0)
		    printf("\n Book not found");
        else
		{	pos=ftell(fp);
			pos=pos-sizeof(e);
			fseek(fp, pos, SEEK_SET);	// move the file pointer one position back
            e.status=bookStatus;
			fwrite(&e,sizeof(e), 1 ,fp);// overwriting old record
		}
		fclose(fp);
	}

