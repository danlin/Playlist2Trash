/*
  ==============================================================================

    CopyThread.h
    Created: 3 Nov 2013 8:11:54pm
    Author:  Daniel Lindenfelser

  ==============================================================================
*/

#ifndef COPYTHREAD_H_INCLUDED
#define COPYTHREAD_H_INCLUDED

#include "JuceHeader.h"

enum ProgressStatus {
    drag,
    running_even,
    running_uneven,
    ready
};

class TrashMessage : public Message {
public:
    ProgressStatus status;
    String message;
};

class TrashThread : public Thread {
public:
    TrashThread(MessageListener *listener)
    :Thread("Playlist2Trash TrashThread")
    {
        this->listener = listener;
    }
    void run();
    void start(StringArray playlistFiles);
private:
    StringArray playlistFiles;
    MessageListener *listener;
};



#endif  // COPYTHREAD_H_INCLUDED
