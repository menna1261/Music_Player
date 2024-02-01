#ifndef PLAYLISTS_H
#define PLAYLISTS_H
#include<DoublyLinkedList.h>
#include<iostream>
#include<fstream>
#include <algorithm> // for random shuffle
#include<vector>
using namespace std;
struct SongNode {
    string song;
    SongNode* next;
    SongNode* prev;
  //  bool isFavorite = false;

};

// Define a node for the doubly linked list of playlists
class playLists {
    private:

     public:
    string playlistName;
    string fileName;  // File name for the playlist
    SongNode* head;    // Head of the doubly linked list of songs
    SongNode* tail;    // Tail of the doubly linked list of songs
    SongNode* currentlyPlaying;  // Pointer to the currently playing song
    playLists* next;
    playLists* prev;
    // Constructor
    playLists(const string& name) : playlistName(name), fileName(name + ".txt"), head(nullptr), tail(nullptr), currentlyPlaying(nullptr), next(nullptr), prev(nullptr) {}
void addSong(const string& song) {
        SongNode* newSong = new SongNode{song, nullptr, nullptr};
        if (head == nullptr) {
            head = tail = newSong;
        } else {
            tail->next = newSong;
            newSong->prev = tail;
            tail = newSong;
        }

        // Append the song to the file associated with the playlist
        ofstream outFile(fileName, ios::app);
        outFile << song << endl;
        outFile.close();

    }
    void updateFile() const {
        ofstream outFile(fileName);
        if (!outFile.is_open()) {
            cerr << "Error opening file for writing." << endl;
            return;
        }

        SongNode* current = head;
        while (current != nullptr) {
            outFile << current->song << endl;
            current = current->next;
        }

        outFile.close();
    }

    void readSongsFromFile() {
    ifstream inFile(fileName);
    if (!inFile.is_open()) {
      //  cerr << "Error opening file for reading songs." << endl;
        return;
    }

    string song;
    while (getline(inFile, song)) {
        addSong_(song);
    }

    inFile.close();
}
    void display(){
        if(!head){
            cout<<"The PlayList is empty " <<endl;
            return ;}
    for(SongNode* current = head;current;current=current->next ){
        cout<<"- " <<current->song<<endl;
    }

    }


    // Function to delete a song from the playlist
    void deleteSong(const string& song) {
        SongNode* current = head;
        while (current != nullptr) {
            if (current->song == song) {
                if (current->prev != nullptr) {
                    current->prev->next = current->next;
                } else {
                    head = current->next;
                }

                if (current->next != nullptr) {
                    current->next->prev = current->prev;
                } else {
                    tail = current->prev;
                }

                // Update the file associated with the playlist after deleting the song
                updateFile();

                delete current;

                // If the currently playing song is deleted, set currentlyPlaying to nullptr
                if (currentlyPlaying == current) {
                    currentlyPlaying = nullptr;
                }

                return; // Song found and deleted
            }

            current = current->next;
        }

        cout << "Song not found in the playlist." << endl;
    }

    // Function to search for a song in the playlist
    bool searchSong(const string& song) const {
        SongNode* current = head;
        while (current != nullptr) {
            if (current->song == song) {
                    cout<<"Song exists "<<endl;
                return true; // Song found
            }

            current = current->next;
        }
        cout<<"song doesn't exist "<<endl;
        return false; // Song not found
    }
    SongNode*search_p(const string& song) const {

       SongNode* current = head;
        while (current != nullptr) {
            if (current->song == song) {
                return current; // Song found
            }

            current = current->next;
        }
        return nullptr;

    }


void addSong_(const string song){
 SongNode* newSong = new SongNode{song, nullptr, nullptr};
        if (head == nullptr) {
            head = tail = newSong;
        } else {
            tail->next = newSong;
            newSong->prev = tail;
            tail = newSong;
        }

}

    // Function to update the file associated with the playlist


    // Function to play the next song in the playlist
    SongNode* playNext( SongNode*nowPlaying) {
        if(nowPlaying){
                 if(nowPlaying->next)
            return nowPlaying->next;
        else
            return nullptr;
            return nowPlaying->next;
        }
    }

    // Function to play the previous song in the playlist
    SongNode* playPrevious(SongNode*nowPlaying) {
        if(nowPlaying)
            if(nowPlaying->prev)
            return nowPlaying->prev;
        else
            return nullptr;

    }

    // Destructor to free memory
    ~playLists() {
        SongNode* current = head;
        while (current != nullptr) {
            SongNode* nextSong = current->next;
            delete current;
            current = nextSong;
        }
    }
    SongNode* play_song(string name){
        if(searchSong(name)){
        currentlyPlaying->song = name;
        cout<<name <<" is now playing ..."<<endl;
    }
        else
            cout<<"This song doesn't exist in the playlist "<<endl;


    return currentlyPlaying;
}
 void shufflePlaylist() const {
        // Convert the linked list to an array
       // cout<<"now";
        if(!head){
            cout<<"PlayList is empty "<<endl;
            return;
        }
        SongNode* current = head;
        int size = 0;
        while (current != nullptr) {
            size++;
            current = current->next;
        }

        if (size < 2) {
            cout << "Not enough songs to shuffle." << endl;
            return;
        }

        string* songArray = new string[size];
        current = head;
        int index = 0;
        while (current != nullptr) {
            songArray[index++] = current->song;
            current = current->next;
        }

        // Perform Fisher-Yates shuffle
        for (int i = size - 1; i > 0; --i) {
            int j = rand() % (i + 1);
            swap(songArray[i], songArray[j]);
        }

        // Display the shuffled playlist
        cout << "Shuffled Playlist: " << playlistName << endl;
        for (int i = 0; i < size; ++i) {
            cout << songArray[i] << " ";
        }
        cout << endl;

        delete[] songArray;
    }

};

#endif // PLAYLISTS_H
