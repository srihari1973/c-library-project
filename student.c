#include<stdio.h>
#include<stdlib.h>
typedef  struct			// structure of student
{   int  studentId;
    char studentName[30];
}Student;

void appendStudent();
void modifyStudent();
void deleteStudent();
void printAllStudents();// fn proto-types

 void studentMenu()
 {      int ch;
        while(1)
        {   system("cls");
            printf("\n--------------------------   Student Menu --------------------------------");
            printf("\n\n\t\t\t1. add student \
                \n\t\t\t2. modify student \
                \n\t\t\t3. delete student \
                \n\t\t\t4. print all students  \
                \n\t\t\t0. exit  ");
            printf("\n\t\t\t\t Enter choice :");
            scanf("%d", &ch);

            switch(ch)
            {   case 1: appendStudent();
                        break;
                case 2: modifyStudent();
                        break;
                case 3: deleteStudent();
                        break;
                case 4: printAllStudents();
                        break;
                case 0: return ;
            }
        }
      return;
 }

// this append function appends a record in the file
	void appendStudent()
	{	FILE *fp;
		Student e;
		system("cls");
		printf("\n ================   adding student details ===================");
		while(1)
        {   printf("\nenter student no:");
            scanf("%d",&e.studentId);
            if(searchStudent(e.studentId)==1)
                printf("\n duplicate id found, press any key to continue");
            else break;
        }

		printf("Enter student Name:");
		fflush(stdin);
		gets(e.studentName);
		fp=fopen("student.dat", "ab");
		if(fp==NULL)
		{	printf("Unable to open student.dat file");
            getch();
			return;
		}
		fwrite(&e,sizeof(e),1,fp);
		fclose(fp);
		printf("successfully added");
		getch();
	}

// Delete function, deleting student record
	void deleteStudent()
	{	FILE *fp,*ft;
		Student  e;
		int studentId,found=0,k;
		fp=fopen("student.dat", "rb");
		ft=fopen("temp.dat","wb");
		if(fp==NULL || ft==NULL )
		{	printf("unable to open file");
			fclose(fp);
		    fclose(ft);
		    getch();
			return;
		}
		system("cls");
		printf("\n ======================= deleting student record =====================================");
 		printf("\nenter student no to delete record :");
		scanf("%d",&studentId);
		while(1)
		{	k=fread(&e,sizeof(e),1,fp);
			if(k==0) break;  // eof is reached
			if(studentId==e.studentId)
				found=1;	// record is found
			else
				fwrite(&e,sizeof(e), 1 ,ft);
		}
		if(found==1)
			printf("Record deleted success fully");
		else
            printf("Record Not found");
		fclose(fp);
		fclose(ft);
		remove("student.dat");
		rename("temp.dat","student.dat");
		getch();
	}

//Modifying record ( modifies student name like spelling mistakes )
	void modifyStudent()
	{	Student e ;
		int found=0;
		int studentId,k;
		long int pos;
		FILE *fp;
		fp=fopen("student.dat","rb+");
		if(fp==NULL)
		{	printf("file not found ");
			return;
		}
		system("cls");
		printf("\n =======================         modify student (address) ======================================== ");
		printf("\n enter student number:");
		scanf("%d",&studentId);
		while(1)
		{	k=fread(&e,sizeof(e),1,fp);
			if(k==0)     // if eof then stop.
				break;
			if(studentId==e.studentId)
			{	found= 1;	// record is found
				break;
			}
		}
		if(found==0)
			printf("\n Record not found");
		else
		{	pos=ftell(fp);
			pos=pos-sizeof(e);
			fseek(fp, pos, SEEK_SET);	// move the file pointer one position back
			printf("existing name is : %s", e.studentName);
			printf("\n Enter New name :");
			fflush(stdin);
			gets(e.studentName);
			fwrite(&e,sizeof(e), 1 ,fp);// overwriting old record
			printf("\n student name suceessfully changed\n press any key ");
		}
		fclose(fp);
		getch();
	}
// print function, printing all records from students.dat file
	void printAllStudents()
	{	Student e;
		int count=0,k;
		FILE *fp;
		fp=fopen("student.dat", "rb");
		if(fp==NULL)
		{	printf("file is empty, no records found");
		    getch();
			return;
		}
		system("cls");
		printf("\n ======================= all student details ======================================== ");
		printf("\n studnet-idno      student-name    ");
		while(1)
		{	k=fread(&e,sizeof(e), 1,fp);
			if(k==0) break;
			printf("\n%10d     %15s",e.studentId, e.studentName);
			count++;
		}
		printf("\n\n total (%d) records found", count);
		printf("\n\npress any key to continue");
		fclose(fp);
		fflush(stdin);
		getch();
	}

// searching student
	int searchStudent(int studentId)
	{	Student e;
		int found=0,k;
		FILE *fp;
		fp=fopen("student.dat", "rb");
		if(fp==NULL)
			return 0;
		while(1)
		{	k=fread(&e,sizeof(e), 1,fp);
			if(k==0)  break;
			if(e.studentId==studentId)
            {   found=1;
                break;
            }
		}
		fclose(fp);
		return found;
	}
