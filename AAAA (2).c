#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define file "data.txt"
FILE *fptr;
union Mark {
    float grade;
    char letter[3];
};
typedef struct {
    char name[50];
    int id;
    char type;
    union Mark mark;
} student;
void mod(student *pt,int N) {
    int i,mult=1,temp;
    printf("student number %d:\n", N);
retry :
    printf("Name:");
    fgets((*pt).name,50,stdin);
    for(i=0; i<strlen((*pt).name)-1; i++) {
        if((*pt).name[i]=='0'||(*pt).name[i]=='1'||(*pt).name[i]=='2'||(*pt).name[i]=='3'||(*pt).name[i]=='4'||(*pt).name[i]=='5'||(*pt).name[i]=='6'||(*pt).name[i]=='7'||(*pt).name[i]=='8'||(*pt).name[i]=='9') {
            printf("NAME CANNOT CONTAIN A NUMBER!\n");
            goto retry;
        }
retry_id:
        printf("id:");
        temp=scanf("%d", &(*pt).id);
        if(temp==0) {
            printf("ID MUST CONTAIN NUMBERS ONLY!\n");
            while(getchar()!='\n');
            goto retry_id;
        }
        if((*pt).id<0){
        printf("ID MUST BE A POSITIVE NUMBER!\n");
        goto retry_id;
        }
again:
        printf("type of grading : (P for percentage or L for letter)");
        scanf(" %c", &(*pt).type);
        if(pt->type=='p'||pt->type=='P') {
            do {
                printf("\ngrade in percentage :");
                temp=scanf("%f", &(*pt).mark.grade);
                if((*pt).mark.grade<0) {
                    printf("grade must be positive!");
                }
                if(temp==0){
                 printf("Grade must be a real number!");
                 while(getchar()!='\n');
                }
            } while((*pt).mark.grade<0||temp==0);
            return;
        } else {
            if(pt->type=='l'||pt->type=='L') {
                printf("\ngrade in letters:");
                while(getchar()!='\n');
                fgets((*pt).mark.letter,3,stdin);
                (*pt).mark.letter[strcspn((*pt).mark.letter,"\n")]='\0';
                return;
            } else {
                printf("\ninvalid choice, try again");
                goto again;
            }
        }
    }
}
void display(student *pt, int N) {
    printf("Student %d:\n", N);
    printf("Name : %s", (*pt).name);
    printf("ID : %d", (*pt).id);
    if(pt->type=='p'||pt->type=='P') {
        printf("\ngrade in percentage :");
        printf("%.2f%%\n", (*pt).mark.grade);
    } else {
        printf("\ngrade in letters:");
        printf("%s\n", (*pt).mark.letter);
    }
}
int compare(student *pt,char ans[50]) {
    char temp[50];
    int i;
    strcpy(temp,(*pt).name);
    for(i=0; temp[i]!='\n'; i++) {
        temp[i]=tolower(temp[i]);
    }
    if(strcmp(temp,ans)==0) {
        return 1;
    } else {
        return 0;
    }
}


int modify(student *pt,int std) {
    int c;
    char m;
loop :
    printf("What would you like to modify about them?\n1.Name\n2.id\n3.Grade\n4.Done\n");
    scanf("%d", &c);
    switch(c) {
    case 1:
        printf("New Name :");
        while(getchar()!='\n');
        fgets((*pt).name,50,stdin);
        goto loop;
        break;
    case 2:
        printf("New ID :");
        scanf("%d", &(*pt).id);
        goto loop;
        break;
    case 3:
mistake :
        printf("New Grade :\n Letter or Percentage?\n");
        scanf(" %c", &m);
        if(m=='p'||m=='P') {
            pt->type=m;
            printf("New grade:");
            scanf("%f", &(*pt).mark.grade);
        } else {
            if(m=='l'||m=='L') {
                pt->type=m;
                printf("New grade:");
                scanf("%s",&(*pt).mark.letter);
            } else {
                printf("Invalid choice, please try again\n");
                goto mistake;
            }
        }
        goto loop;
        break;
    case 4 :
        return 1;
        break;
    default:
        printf("Invalid choice, please try again\n");
        goto loop;
        fclose(fptr);
    }
}
void add_mod(student *pt, char ans[50]) {
    strcpy(pt->name,ans);
    printf("id:");
    scanf("%d", &(*pt).id);
again:
    printf("type of grading : (P for percentage or L for letter)");
    scanf(" %c", &(*pt).type);
    if(pt->type=='p'||pt->type=='P') {
        printf("\ngrade in percentage :");
        scanf("%f", &(*pt).mark.grade);
    } else {
        if(pt->type=='l'||pt->type=='L') {
            printf("\ngrade in letters:");
            scanf("%s", (*pt).mark.letter);
        } else {
            printf("\ninvalid choice, try again");
            goto again;
        }
    }
}
int convert(char l) {
    switch(l) {
    case '0' :
        return 0;
        break;
    case '1' :
        return 1;
        break;
    case '2' :
        return 2;
        break;
    case '3' :
        return 3;
        break;
    case '4' :
        return 4;
        break;
    case '5' :
        return 5;
        break;
    case '6':
        return 6;
        break;
    case '7' :
        return 7;
        break;
    case '8' :
        return 8;
        break;
    case '9' :
        return 9;
        break;
    }
}
void edit_file(student *pt, int N) {
    fptr=fopen(file,"a+");
    fprintf(fptr," %d :", N+1);
    fwrite((*pt).name,1,strcspn((*pt).name,"\n"),fptr);
    fprintf(fptr,"# %d",(*pt).id);
    if(pt->type=='p'||pt->type=='P') {
        fprintf(fptr," p: %.2f$ ",(*pt).mark.grade);
    } else {
        fprintf(fptr," L: %s$ ",(*pt).mark.letter);
    }
    fclose(fptr);
    return;
}
void read_file(student *pt) {
    int j,v;
    char c;
    while(fgetc(fptr)==':');
    fseek(fptr,2,SEEK_CUR);
    c=fgetc(fptr);
    for(j=0; c!='#'; j++) {
        v=j;
        (*pt).name[j]=c;
        fseek(fptr,0,SEEK_CUR);
        c=fgetc(fptr);
    }
    (*pt).name[j]='\n';
    (*pt).name[j+1]='\0';
    fseek(fptr,0,SEEK_CUR);
    fscanf(fptr,"%d",&(*pt).id);
    fseek(fptr,1,SEEK_CUR);
    (*pt).type=fgetc(fptr);
    fseek(fptr,2,SEEK_CUR);
    if(pt->type=='p'||pt->type=='P') {
        fscanf(fptr,"%f",&(*pt).mark.grade);
        fseek(fptr,1,SEEK_CUR);
    } else {
        fseek(fptr,0,SEEK_CUR);
        c=fgetc(fptr);
        for(j=0; c!='$'; j++) {
            (*pt).mark.letter[j]=c;
            fseek(fptr,0,SEEK_CUR);
            c=fgetc(fptr);
        }
    }
    fseek(fptr,2,SEEK_CUR);
}
int main() {
    int N=0, i, n, result, std, mult=1,x;
    char C[50], answer[50], add[50], t;
    student *temp,*st;
    if((fptr=fopen(file,"r"))!=NULL) {
        rewind(fptr);
        t=fgetc(fptr);
        while(t!=' ') {
            mult*=10;
            fseek(fptr,0,SEEK_CUR);
            t=fgetc(fptr);
        }
        mult/=10;
        rewind(fptr);
        t=fgetc(fptr);
        while(t!=' ') {
            N+=convert(t)*mult;
            mult/=10;
            fseek(fptr,0,SEEK_CUR);
            t=fgetc(fptr);
        }
        st = calloc(N,sizeof(*st));
        fseek(fptr,0,SEEK_CUR);
        for(i=0; i<N; i++) {
            read_file((st+i));
        }
        printf("Welcome back!\n");
        goto end;
    }
start:
    fptr=fopen(file,"w+");
    printf("Welcome!\n How many students are there?\n Answer :");
    do{
    x=scanf("%d", &N);
    if(x==0){
    printf("Invalid input\n");
    while(getchar()!='\n');
    goto start;
    }
    }while(x==0);
    fprintf(fptr,"%d",N);
    fclose(fptr);
    st = calloc(N, sizeof(*st));
    if(st==NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    for(i=0; i<N; i++) {
        while(getchar()!='\n');
        mod((st+i),i+1);
        edit_file((st+i),i);
    }
    fclose(fptr);
end:
    printf("would you like to see the results, modify them, erase your data, or leave the program? :\n");
    printf("1. See results\n");
    printf("2. Modify\n");
    printf("3. Erase Data\n");
    printf("4. Leave\n");
    printf("choice:");
    int choice;
    scanf("%d", &choice);
    switch (choice) {
    case 1 :
        for(i=0; i<N; i++) {
            display((st+i),i+1);
        }
        goto end;
        break;
    case 2:
        printf("Would you like to add more students?\n Answer:");
        while(getchar()!='\n');
        fgets(C,50,stdin);
        for(i=0; C[i]!='\0'; i++) {
            C[i] = tolower(C[i]);
        }
        if(strcmp(C,"yes\n")==0) {
            printf("How many students would you like to add?\n Answer:");
            scanf("%d", &n);
            temp=realloc(st,(n+N)*sizeof(*st));
            if(temp==NULL) {
                printf("Memory allocation failed!\n");
                return 1;
            }
            st=temp;
            N+=n;
            while(getchar()!='\n');
            for(i=N-n; i<N; i++) {
                mod((st+i),i+1);
            }
            fptr=fopen(file,"w+");
            fprintf(fptr,"%d",N);
            fclose(fptr);
            for(i=0; i<N; i++) {
                edit_file((st+i),i);
            }
        } else {
            if(strcmp(C,"no\n")==0) {
                printf("Which student would you like to edit?\nAnswer (name):");
                fgets(answer,50,stdin);
                for(i=0; answer[i]!='\0'; i++) {
                    answer[i] = tolower(answer[i]);
                }
                for(i=0; i<N; i++) {
                    result=compare((st+i),answer);
                    if(result!=0) {
                        std=i;
                        break;
                    }
                }
                if(result!=0) {
                    modify((st+std),std);
                    fptr=fopen(file,"w+");
                    fprintf(fptr,"%d",N);
                    fclose(fptr);
                    for(i=0; i<N; i++) {
                        edit_file((st+i),i);
                    }
                } else {
                    printf("That student does not exist, would you like to add them?\nAnswer:");
                    scanf("%s", add);
                    for(i=0; add[i]!='\0'; i++) {
                        add[i] = tolower(add[i]);
                    }
                    if(strcmp(add,"yes")==0) {
                        N+=1;
                        temp=realloc(st,(N)*sizeof(*st));
                        if(temp==NULL) {
                            printf("Memory allocation failed!\n");
                            return 1;
                        }
                        st=temp;
                        add_mod((st+N-1),answer);
                        fptr=fopen(file,"w+");
                        fprintf(fptr,"%d",N);
                        fclose(fptr);
                        for(i=0; i<N; i++) {
                            edit_file((st+i),i);
                        }
                    } else {
                        if(strcmp(add,"no")==0) {
                            goto end;
                        } else {
                            printf("Invalid choice, please try again\n");
                            goto end;
                        }
                    }
                }
            } else {
                printf("Invalid choice, please try again");
            }
        }
        goto end;
        break;
    case 3:
        printf("Are you sure you wish to delete your data?\nAnswer:");
        while(getchar()!='\n');
        fgets(C,50,stdin);
        for(i=0; C[i]!='\0'; i++) {
            C[i] = tolower(C[i]);
        }
        if(strcmp(C,"yes\n")==0) {
            goto start;
        } else {
            goto end;
        }
    case 4:
        printf("thank you for using the program!");
        break;
    default:
        printf("invalid choice, try again\n");
        goto end;
        break;
    }
    return 0;
}