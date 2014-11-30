/*
  ==============================================================================

    CopyThread.cpp
    Created: 3 Nov 2013 8:11:54pm
    Author:  Daniel Lindenfelser

  ==============================================================================
*/

#include "TrashThread.h"

void TrashThread::start(StringArray playlistFiles) {
    if (!this->isThreadRunning()) {
        this->playlistFiles = playlistFiles;
        this->startThread();
    }
}

void TrashThread::run() {
    for (auto i = 0; i <= playlistFiles.size(); i++) {
        File playlistFile(playlistFiles[i]);
        StringArray lines;
        TrashMessage *message;
        playlistFile.readLines(lines);
        for (auto j = 0; j <= lines.size(); j++) {
            if (this->threadShouldExit()) {
                return;
            }
            File playlistContent;
            if (File::isAbsolutePath(lines[j])) {
                playlistContent = File(lines[j]);
            } else {
                playlistContent = File(playlistFile.getParentDirectory().getFullPathName() + "/" + lines[j]);
            }
                
            if (playlistContent.existsAsFile()) {
                if (j % 2) {
                    message = new TrashMessage();
                    message->status = ProgressStatus::running_even;
                    message->message = "Delete " + playlistContent.getFileName();
                    listener->postMessage(message);
                } else {
                    message = new TrashMessage();
                    message->status = ProgressStatus::running_uneven;
                    message->message = "Delete " + playlistContent.getFileName();
                    listener->postMessage(message);
                }
                
                playlistContent.moveToTrash();
            }
        }
        message = new TrashMessage();
        message->status = ProgressStatus::ready;
        message->message = "Done";
        listener->postMessage(message);
    }
}