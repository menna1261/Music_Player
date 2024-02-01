#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include <iostream>
#include<playLists.h>
#include<favorites_queue.h>
#include<Stack.h>
class DoublyLinkedList
{
private:
    playLists* head;
    playLists* tail;
    favorites_queue* fav;
    Stack<string> latestPlayedSongs;
    static const int MAX_FAVORITES = 100; // Adjust as needed
    string favoriteSongs[MAX_FAVORITES];
    int numFavorites;
    // int s= recently_played.size();


public:
    // Constructor
    DoublyLinkedList() : head(nullptr), tail(nullptr),numFavorites(0) {}

 void addPlaylist(const string& playlistName, bool createFile = true)
    {
        // Check if the playlist already exists
        playLists* existingPlaylist = findPlaylist(playlistName);
        if (existingPlaylist != nullptr)
        {
            cout << "Playlist with name " << playlistName << " already exists." << endl;
            return;
        }

        // Create a new playlist node
        playLists* newPlaylist = new playLists(playlistName);

        // Add the new playlist to the doubly linked list
        if (head == nullptr)
        {
            head = newPlaylist;
            tail = newPlaylist;
        }
        else
        {
            tail->next = newPlaylist;
            newPlaylist->prev = tail;
            tail = newPlaylist;
        }

        // Check if the playlist file already exists
        if (createFile)
        {
            ifstream fileCheck(newPlaylist->fileName);
            if (fileCheck)
            {
                cout << "Playlist file " << newPlaylist->fileName << " already exists." << endl;
            }
            else
            {
                // Create the file that stores playlist songs
                ofstream outFile(newPlaylist->fileName);
                if (!outFile.is_open())
                {
                    cerr << "Error opening file for writing playlist." << endl;
                    return;
                }
                cout<<"Playlist is added successfully "<<endl;
                outFile.close();

                // Update "playlists.txt" file
                createPlaylistsFile();
            }
        }

    }
      void createPlaylistsFile() const
    {
        ofstream outFile("playlists.txt");
        if (!outFile.is_open())
        {
            cerr << "Error opening file for writing playlists." << endl;
            return;
        }

        playLists* current = head;
        while (current != nullptr)
        {
            outFile << current->playlistName << endl;
            current = current->next;
        }

        outFile.close();
    }
 void addSong(const string& playlistName, const string& song)
    {
        playLists* current = head;
        while (current != nullptr)
        {
            if (current->playlistName == playlistName)
            {
                current->addSong(song);
                cout<<"Song is added to the playlist "<<endl;
                return; // Song added to playlist
            }

            current = current->next;
        }

        cout << "Playlist not found." << endl;
    }
     void deletePlaylist(const string& playlistName)
    {
        playLists* current = head;
        while (current != nullptr)
        {
            if (current->playlistName == playlistName)
            {
                if (current->prev != nullptr)
                {
                    current->prev->next = current->next;
                }
                else
                {
                    head = current->next;
                }

                if (current->next != nullptr)
                {
                    current->next->prev = current->prev;
                }
                else
                {
                    tail = current->prev;
                }

                // Delete the file associated with the playlist
                remove(current->fileName.c_str());

                delete current;
                cout<<"PlayList is deleted successfully "<<endl;
                return; // Playlist found and deleted
            }

            current = current->next;
        }
        createPlaylistsFile();

        cout << "Playlist is not found ." << endl;
    }
   void playSong(const string& playlistName, const string& song)
    {
        playLists* current = findPlaylist(playlistName);
        if(current)
        {
            //SongNode* nowPlaying =  current->play_song(current->currentlyPlaying->song);
            SongNode* nowPlaying = current->search_p(song);
            if(nowPlaying)
            {
                cout<<nowPlaying->song<<" is now playing ... "<<endl;
                latestPlayedSongs.push(nowPlaying->song);
                current->currentlyPlaying = nowPlaying;
            }

            char choice = '-1';
            // cout << "Song found in the playlist. Do you want to:" << endl;
            cout << "\n1. Play next song\n2. Play previous song\n3. Add to favorites\n0. Terminate" << endl;
            while(choice!=0)
            {
                cout << "Enter your choice (1/2/3/0): ";
                cin >> choice;

                switch (choice)
                {

                case '1':
                {
                    if(current->playNext(nowPlaying)!=nullptr)
                    {
                        cout<<current->playNext(nowPlaying)->song<<" is now playing ... "<<endl;
                        latestPlayedSongs.push(current->playNext(nowPlaying)->song);

                    }
                    else
                        cout<<"This is the last song in the playlist "<<endl;
                }
                break;

                case '2':
                {
                    if(current->playPrevious(nowPlaying)!=nullptr)
                    {
                        cout<<current->playPrevious(nowPlaying)->song<<" is now playing ... "<<endl;
                        latestPlayedSongs.push(current->playPrevious(nowPlaying)->song);
                    }
                    else
                        cout<<"This is the first song in the playlist " <<endl;
                }

                break;
                case '3':
                {
                    //nowPlaying->isFavorite=true;
                    //add_to_favs(nowPlaying->song,playlistName);
                    //favArray[index++]=;
                    //size++;
                    addToFavorites(nowPlaying->song);
                    cout<<"Song is added to favorites "<<endl;
                    //saveFavoritesToFile();
                }
                break;
                case '0' :
                    return;

                default:
                    cout << "Invalid choice. Terminating the playSong function." << endl;

                }

                //return; // Song found and action performed
            }
            return;
        }
        cout << "Song not found in the playlist." << endl;
        return;
        //current = current->next;

        // songNode = songNode->next;
    }

    void addToFavorites(const string& song)
    {
        if (numFavorites < MAX_FAVORITES)
        {
            favoriteSongs[numFavorites++] = song;
            saveFavoritesToFile();
        }
        else
        {
            cout << "Favorites list is full. Cannot add more songs." << endl;
        }
    }

    // Function to display favorite songs
    void displayFavorites() const
    {
        if (numFavorites == 0)
        {
            cout << "No favorite songs." << endl;
        }
        else
        {
            cout << "Favorite Songs:" << endl;
            for (int i = 0; i < numFavorites; ++i)
            {
                cout << i + 1 << ". " << favoriteSongs[i] << endl;
            }
        }
    }

    // Function to save favorite songs to file
    void saveFavoritesToFile() const
    {
        ofstream outFile("favorites.txt");
        if (!outFile.is_open())
        {
            cerr << "Error opening file for writing favorites." << endl;
            return;
        }

        for (int i = 0; i < numFavorites; ++i)
        {
            outFile << favoriteSongs[i] << endl;
        }

        outFile.close();
    }

    // Function to load favorite songs from file
    void loadFavoritesFromFile()
    {
        ifstream inFile("favorites.txt");
        if (!inFile.is_open())
        {
       //     cerr << "Error opening file for reading favorites." << endl;
            return;
        }

        numFavorites = 0;
        string song;
        while (getline(inFile, song) && numFavorites < MAX_FAVORITES)
        {
            favoriteSongs[numFavorites++] = song;
        }

        inFile.close();
    }
    void displayLatestPlayedSongs() const
    {
        if(latestPlayedSongs.isEmpty())
        {
            cout<<" No songs have been played for a while  "<<endl;
            return ;
        }
        cout << "Latest Played Songs: ";
        latestPlayedSongs.display();
    }

    void displayPlaylists() const
    {
        playLists* current = head;
        while (current != nullptr)
        {
            cout << "Playlist: " << current->playlistName << endl;
            SongNode* songCurrent = current->head;
            while (songCurrent != nullptr)
            {
                cout << "  - " << songCurrent->song << endl;
                songCurrent = songCurrent->next;
            }
            cout << endl;

            current = current->next;
        }
    }

    void loadPlaylistsAndSongsFromFile()
    {
        ifstream playlistsFile("playlists.txt");
        if (!playlistsFile.is_open())
        {
           // cerr << " Error opening file for reading playlists." << endl;
            return;
        }

        string playlistName;
        while (getline(playlistsFile, playlistName))
        {
            // Add the playlist to the doubly linked list
            addPlaylist(playlistName, false); // Pass false to avoid creating new files

            // Find the playlist node
            playLists* current = findPlaylist(playlistName);
            if (current != nullptr)
            {
                // Load songs for the playlist from its file
                current->readSongsFromFile();
            }
        }

        playlistsFile.close();
    }

    playLists* findPlaylist(const string& playlistName) const
    {
        playLists* current = head;
        while (current != nullptr)
        {
            if (current->playlistName == playlistName)
            {

                return current;
                return current; // Playlist found
            }
            current = current->next;
        }
        //cout<<"Playlist not fount "<<endl;
        return nullptr; // Playlist not found
    }

    void display_p(string name )
    {
        playLists*curr = findPlaylist(name);
        curr->display();
    }

    void deleteSong(const string& playlistName, const string& song)
    {
        playLists* current = head;
        while (current != nullptr)
        {
            if (current->playlistName == playlistName)
            {
                current->deleteSong(song);
             //   cout<<"Song is deleted successfully "<<endl;
                return; // Song deleted from playlist
            }

            current = current->next;
        }

        cout << "Playlist not found." << endl;
    }
    bool searchSong(string playlistName, string songName)
    {
        playLists* current = head;
        while (current != nullptr)
        {
            if (current->playlistName == playlistName)
            {
                return current->searchSong(songName);
                // Song deleted from playlist
            }

            current = current->next;
        }
        cout<<"Playlist not found " <<endl;
        return false;


    }
    void shuffle(string playlistName)
    {

        playLists* current = findPlaylist(playlistName);
        if (current != nullptr)

                current->shufflePlaylist();
               // break;

            }



    // Destructor to free memory
    ~DoublyLinkedList()
    {
        playLists* current = head;
        while (current != nullptr)
        {
            playLists* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
};


#endif // DOUBLYLINKEDLIST_H
