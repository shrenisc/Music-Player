#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<ctype.h>

struct node
{
    int song_no;
    char song_name[50];
    char song_artist[50];
    char song_time[50];
    struct node* next;
    struct node* prev;
}; 

typedef struct node* NODE;

NODE Queue=NULL,Playlist=NULL;
FILE *no,*song,*artist,*duration;
char line[50],artist_info[50],dur_info[50],song_info[50],info[50];
int q_no=1,p_no=1,view,num;
int choice_main=1,choice_songops=1,choice_viewops=1;

NODE display(NODE first)
{
    NODE cur=NULL;
    if(first==NULL && first==Queue)
    {
        printf("Queue is empty");
        return first;
    }
    else if(first==NULL && first==Playlist)
    {
        printf("Playlist is empty");
        return first;
    }
    cur=first;
    while(cur->next!=NULL)
    {
        printf("%-5d%-35s%-30s%12s\n",cur->song_no,cur->song_name,cur->song_artist,cur->song_time);
        cur=cur->next;
    }
        printf("%-5d%-35s%-30s%12s\n",cur->song_no,cur->song_name,cur->song_artist,cur->song_time);
        return first;
}

void open_file()
{
    no=fopen("nos.txt","r");
    song=fopen("songs.txt","r");
    artist=fopen("artists.txt","r");
    duration=fopen("duration.txt","r");
}

void close_file()
{
    fclose(no);
    fclose(song);
    fclose(artist);
    fclose(duration);
}

void print(FILE *data)
{

    while(1)
    { 
        memset(line,0,sizeof line);
        fflush(stdin);
        char show = (char)fgetc(data); 
        int k = 0; 
        while(show!='\n' && !feof(data)){
            line[k]=show;
            k++;
            show = (char)fgetc(data);
            fflush(stdin);
        }  
        if (data==no)
        {
            printf("%-5s",line);
        }
        else if (data==song)
        {
            printf("%-35s",line);
        }
        else if (data==artist)
        {
            printf("%-30s",line);
        }
        else
        {
            printf("%12s",line);
        }
        break;
        
    } 
}

int search_QP(NODE first,int choice_viewops)
{
    memset(song_info, 0, sizeof song_info);
    memset(artist_info, 0, sizeof artist_info);
    memset(dur_info, 0, sizeof dur_info);
    memset(info, 0, sizeof info);
    choice_songops=1;
    if (choice_viewops==1)
    {
        printf("Enter song name: ");
        fflush(stdin);
        scanf("%[^\n]",info);
        NODE cur=first;
        int result=strcasecmp(cur->song_name,info);
        while (result!=0)
        {
            cur=cur->next;
            if (cur==NULL)
            {
                return 0;
            }
            result=strcasecmp(cur->song_name,info);
            
        }
            strncpy(song_info,cur->song_name,strlen(cur->song_name)+1);
            strncpy(artist_info,cur->song_artist,strlen(cur->song_artist)+1);
            strncpy(dur_info,cur->song_time,strlen(cur->song_time)+1);
            return 1;
    }
    else if (choice_viewops==2)
    {
        printf("Enter song number: ");
        fflush(stdin);
        scanf("%d",&num);
        NODE cur=first;
        while (cur->song_no!=num)
        {
            cur=cur->next;
            if (cur==NULL)
            {
                return 0;
            }
        }
            strncpy(song_info,cur->song_name,strlen(cur->song_name));
            strncpy(artist_info,cur->song_artist,strlen(cur->song_artist));
            strncpy(dur_info,cur->song_time,strlen(cur->song_time));
        return 1;
    }
}


int search(FILE *file)
{  
    memset(info, 0, sizeof info);
    int p=0;
    choice_songops=1;
    if (file==song)
    {
        printf("Enter song name: ");
    }
    else if (file==no)
    {
        printf("Enter song number: ");
    }
    fflush(stdin);
    scanf("%[^\n]",info);
    open_file();
    unsigned int line_count=0;
    while (fgets(line, 50, file))
    {
        line[(int)(strchr(line, '\n') - line)]='\0';
        int result=strcasecmp(line,info);
        if (result==0)
        {
            for(int k=0;k<=p;k++)
            {
                fgets(artist_info,50,artist);
                fgets(dur_info,50,duration);
                    fclose(song);
                    song=fopen("songs.txt","r");
                    for (int k = 0; k <=p; k++)
                    {
                        fgets(song_info,50,song);
                    }
                    fclose(song); 
            }
            artist_info[(int)(strchr(artist_info, '\n') - artist_info)]='\0';
            song_info[(int)(strchr(song_info, '\n') - song_info)]='\0';
            dur_info[(int)(strchr(dur_info, '\n') - dur_info)]='\0';
            close_file();
            return 1;
        }
        p++;
    }
    close_file();
        return 0;
}

NODE deleteElement(NODE first,int choice_viewops)
{
    NODE cur = NULL;
    cur=first;
    if (choice_viewops==1)
    {
        int result;
        result=strcmp(cur->song_name,info);
        while(result!=0)
        {
        cur=cur->next;
        }
    }
    else if (choice_viewops==2)
    {
        while (cur->song_no!=num)
        {
            cur=cur->next;
        }
        
    }
    if (cur==first)
    {
        free(cur);
        printf("\nSong is deleted");
        return first;
    }
    cur->prev->next = cur->next;
    if (cur->next!=NULL)
    {
        cur->next->prev = cur->prev;
    }
    printf("\nSong is deleted");
    free(cur);
    return first;
}

NODE insertRear(NODE first)
{
    NODE temp=NULL,cur=first;
    temp=(NODE)malloc(sizeof(struct node));
    if(temp==NULL)
    {
        printf("Memory insufficient");
        return first;
    }
    if (first==Queue)
    {
           temp->song_no=q_no;
            q_no++;
    }
    else if (first==Playlist)
    {
        temp->song_no=p_no;
        p_no++;
    }
    int i,j,k;
    for (int p = 0; p < 50; p++)
    {
            temp->song_name[p]='\0';
            temp->song_artist[p]='\0';
            temp->song_time[p]='\0';
    }
        strncpy(temp->song_name,song_info,strlen(song_info));
        strncpy(temp->song_artist,artist_info,strlen(artist_info));
        strncpy(temp->song_time,dur_info,strlen(dur_info));
        

    temp->next=NULL;
    temp->prev=NULL;
    if(first==NULL)
    {
        first=temp;
        printf("%s added\n",temp->song_name);
        return first;
    }
    while(cur->next!=NULL)
    {
        cur=cur->next;
    }
    cur->next=temp;
    temp->prev=cur;
    printf("%s added\n",temp->song_name);
    return first;
}


void view_ops()
{
    while (choice_viewops!=3)
    {
        printf("\nFunctions:\n1.Search song by name\n2.Search song by number\n3.Back\nChoose: ");
        scanf("%d",&choice_viewops);
        switch (choice_viewops)
        {
            case 1:
                if(view==1 && search(song))
                {
                    while (choice_songops!=3)
                    {
                            printf("\nFunctions:\n1.Add to queue\n2.Add to playlist\n3.Back\nChoose: ");
                            fflush(stdin);
                            scanf("%d",&choice_songops);
                            switch (choice_songops)
                            {
                            case 1:
                                Queue=insertRear(Queue);
                                break;

                            case 2:
                                Playlist=insertRear(Playlist);
                                break;

                            case 3:
                                break;
                            }
                        }
                }
                else if (view==2 && search_QP(Queue,choice_viewops))
                {
                    while (choice_songops!=3)
                    {
                        printf("\nFunctions:\n1.Add to playlist\n2.Remove from queue\n3.Back\nChoose: ");
                        fflush(stdin);
                        scanf("%d",&choice_songops);
                        switch (choice_songops)
                        {
                        case 1:
                            Playlist=insertRear(Playlist);
                            break;

                        case 2:
                            Queue=deleteElement(Queue,choice_viewops);
                            break;

                        case 3:
                            break;
                        }
                    }
                                
                }
                else if (view==3 && search_QP(Playlist,choice_viewops))
                {
                    while (choice_songops!=3)
                    {
                        printf("\nFunctions:\n1.Add to queue\n2.Remove from playlist\n3.Back\nChoose: ");
                        fflush(stdin);
                        scanf("%d",&choice_songops);
                        switch (choice_songops)
                        {
                        case 1:
                            Queue=insertRear(Queue);
                            break;

                        case 2:
                            Playlist=deleteElement(Playlist,choice_viewops);
                            break;

                        case 3:
                            break;
                        }
                    }
                }
                else
                {
                    printf("Song not found\n");
                }
                break;
                        

            case 2:
                if(view==1 && search(no))
                {
                    while (choice_songops!=3)
                    {
                            printf("\nFunctions:\n1.Add to queue\n2.Add to playlist\n3.Back\nChoose: ");
                            fflush(stdin);
                            scanf("%d",&choice_songops);
                            switch (choice_songops)
                            {
                            case 1:
                                Queue=insertRear(Queue);
                                break;

                            case 2:
                                Playlist=insertRear(Playlist);
                                break;

                            case 3:
                                break;
                            }
                    }
                }
                else if (view==2 && search_QP(Queue,choice_viewops))
                {
                    while (choice_songops!=3)
                    {
                        printf("\nFunctions:\n1.Add to playlist\n2.Remove from queue\n3.Back\nChoose: ");
                        fflush(stdin);
                        scanf("%d",&choice_songops);
                        switch (choice_songops)
                        {
                        case 1:
                            Playlist=insertRear(Playlist);
                            break;

                        case 2:
                            Queue=deleteElement(Queue,choice_viewops);
                            break;

                        case 3:
                            break;
                        }
                    }
                                
                }
                else if (view==3 && search_QP(Playlist,choice_viewops))
                {
                    while (choice_songops!=3)
                    {
                        printf("\nFunctions:\n1.Add to queue\n2.Remove from playlist\n3.Back\nChoose: ");
                        fflush(stdin);
                        scanf("%d",&choice_songops);
                        switch (choice_songops)
                        {
                        case 1:
                            Queue=insertRear(Queue);
                            break;

                        case 2:
                            Playlist=deleteElement(Playlist,choice_viewops);
                            break;

                        case 3:
                            break;
                        }
                    }
                }
                else
                {
                    printf("Song not found\n");
                }
                break;
        }
    }
}

void View(int view)
{
    if(view==1)
    {
        open_file();
        printf("%-5s %-35s %-30s %12s\n", "No", "Name", "Artist","Duration");
        fflush(stdin);
        for (int p = 0; p < 25; p++)
        {
            print(no);
            print(song);
            print(artist);
            print(duration);
            printf("\n");
        }
        close_file();
        view_ops();
    }
    else if(view==2)
    {
        printf("\n\n\n***QUEUE***\n");
        printf("%-5s %-35s %-30s %12s\n", "No", "Name", "Artist","Duration");
        Queue=display(Queue);
        view_ops();
    }
    else if(view==3)
    {

        printf("\n\n\n***Playlist***\n");
        printf("%-5s %-35s %-30s %12s\n", "No", "Name", "Artist","Duration");
        Playlist=display(Playlist);
        view_ops();
    }
}

void main()
{

    printf("\n******MUSIC PLAYER******\n");
    while (1)
    {
        choice_viewops=1;
        printf("***MENU***\n");
        printf("1.View all songs\n2.View Queue\n3.View Playlist\n4.Exit\n");
        printf("Choose: ");
        scanf("%d",&choice_main);
        fflush(stdin);
        switch (choice_main)
        {
        case 1:
            view=1;
            View(1);
            break;
        
        case 2:
            view=2;
            View(2);
            break;

        case 3:
            view=3;
            View(3);
            break;
        
        case 4:
            printf("Exiting Music Player");
            exit(0);
        }
    }
}
