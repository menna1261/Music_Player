#include <iostream>
#include <fstream>
#include <string>
#include<DoublyLinkedList.h>
#include<playLists.h>
#include<favorites_queue.h>
#include <cstdlib>          // cls
#include <windows.h>        // Sleep
#include <cstring>          // string, to_string
#include <bits/stdc++.h>    // stringstream
#include <windows.h>        // Sleep
#include<unistd.h>

using namespace std;
  //  container<book>c;

HANDLE cout_handle = GetStdHandle(STD_OUTPUT_HANDLE);

/** ASSISTANT INLINE FUNCTIONS **/

inline void wait_or_clear(unsigned int sec, bool clear_screen = false)
{
    Sleep(sec*1000);
    if (clear_screen) system("cls");
}

inline void printline(string msg, bool end_line = true, int color_code=15)
{
    SetConsoleTextAttribute(cout_handle, color_code);
    cout <<  msg << (end_line?"\n":"\t");
}

inline void print_try_again()
{
    printline("\n\n\n\aInvalid Choice Try Again!!!!!!!!",1,2);
    wait_or_clear(3, 1);
}

/** MAIN PRINT MENU FUNCTION **/

int get_menu_choise(string menu, int level = 0)
{
    stringstream X(menu);
    string line, padding;
    int i = 1;
    for(int p=0; p<level+1; ++p)
        padding +="\t";

    while (getline(X, line, ','))
        printline(padding + to_string(i++) + ". " + line,1,level+3);

    printline(level?padding+"0. RETURN BACK":padding+"0. EXIT APP",1,4);
    int c;
    printline("ENTER YOUR CHOICE :",false,15);
    cin >> c;
 return c;
}
int main()
{
DoublyLinkedList myPlaylistManager;
    myPlaylistManager.loadPlaylistsAndSongsFromFile();
    myPlaylistManager.loadFavoritesFromFile();
    printline("START APPLICATION ....",1,11);
    wait_or_clear(1,1);
    int d = -1;
    while (d!=0)
    {
        wait_or_clear(0,1);
        printline("\n\nMAIN MENU ....",1,15);
        d = get_menu_choise("MANAGE PLAYLISTS ,GO INTO PLAYLISTS",0);
        switch(d)
        {
        case 1:
        {
          string name;


           system("cls");
            printline("\n\nMAIN MENU -> MANAGE PLAYLISTS ....");
             printline("\n(1)ADD A PLAYLIST\n(2)DELETE A PLAYLIST\n(3)SEARCH FOR A PLAYLIST\n(4)DISPLAY ALL PLAYLISTS\n(5)DISPLAY RECENTLY PLAYED SONGS\n(6)DISPLAY FAVORITES");
             int ch;
             cin>>ch;
             switch(ch){
         case 1:
             {
                 cout << "Enter playlist name: ";
                cin >> name;
                myPlaylistManager.addPlaylist(name);
                 sleep(2);

             }
            break;
              case 2:
             {

                cout << "Enter playlist name to delete: ";
                cin >> name;
                myPlaylistManager.deletePlaylist(name);
                sleep(2);
               // break;
  }
            break;
             case 3:
             {
                 cout << "Enter playlist name to Find: ";
                cin >> name;
             if( myPlaylistManager.findPlaylist(name))
                cout<<" PlayList is Found " <<endl;
             else
                cout<<"Error ! can't find the playlist "<<endl;
              sleep(2);


             }
            break;
             case 4:
             {

              myPlaylistManager.displayPlaylists();
              sleep(3);

             }
            break;
             case 5:
             {

              myPlaylistManager.displayLatestPlayedSongs();
              sleep(3);

             }
            break;
             case 6:
             {
             myPlaylistManager.displayFavorites();
             sleep(3);


             }
            break;
        }
        }
        break;
        case 2 :{
         string name;
         string song;
        printline("\n\nMAIN MENU -> GO INTO PLAYLISTS ....");
             cout<<"\nEnter PlayList name  : "<<endl;
             cin>>name;
             printline("\n(1)ADD A SONG\n\n(2)DELETE A SONG\n\n(3)SEARCH FOR A SONG\n\n(4)PLAY A SONG\n\n(5)SHUFFLE THE PLAYLIST\n\n(6)DISPLAY");

             int ch;
             cout<<"Enter your choice : "<<endl;
             cin>>ch;
             switch(ch){
        case 1 :
            {
            cout<<"Song name : ";
            cin>>song;
            cout<<endl;
            myPlaylistManager.addSong(name,song);
            sleep(3);


        }
        break;
        case 2 :
            {
                cout<<"Song name : ";
                 cin>>song;
                 cout<<endl;
                myPlaylistManager.deleteSong(name,song);
                sleep(3);
            }
            break;
        case 3 :
            {

                cout<<"Song name : ";
                 cin>>song;
                 cout<<endl;
                 myPlaylistManager.searchSong(name,song);
                 sleep(3);
            }
            break;
        case 4 :
            {
                cout<<"Song name : ";
                cin>>song;
                cout<<endl;
                myPlaylistManager.playSong(name,song);
                sleep(3);
            }
            break;
        case 5 :
            {
                myPlaylistManager.shuffle(name);
                sleep(3);

            }
            break;
        case 6 :
            {
                myPlaylistManager.display_p(name);
                sleep(3);
            }
            break;
        }
        }
        break;
         case 0:
            printline("\n\n\a\t\t\tGoodbye :)......\n\n\n\n\n\n",1,112);
            break;
        default:
            wait_or_clear(3, true);
        }
    }
    return 0;
}
