 /* -*- mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*- */
// vim: ft=cpp:expandtab:ts=8:sw=4:softtabstop=4:

#ifndef BACKUP_MANAGER_H
#define BACKUP_MANAGER_H

#include "backup_directory.h"
#include "file_description.h"
#include <sys/types.h>
#include <vector>
#include <pthread.h>

class backup_manager
{
private:
    bool m_doing_backup;
    bool m_doing_copy;

    // TODO: Make this an array or vector of directories.
    backup_directory m_dir;
    file_descriptor_map m_map;
    pthread_mutex_t m_mutex; // Used to serialize multiple backup operations.
    int m_capture_error;
    
public:
    backup_manager();
    void start_backup();
    void stop_backup();
    void add_directory(const char *source_dir, const char *dest_dir);

    // Methods used during interposition:
    void create(int fd, const char *file);
    void open(int fd, const char *file, int oflag);
    void close(int fd);
    ssize_t write(int fd, const void *buf, size_t nbyte); // Actually performs the write on fd (so that a lock can be obtained).
    void pwrite(int fd, const void *buf, size_t nbyte, off_t offset);
    ssize_t read(int fd, void *buf, size_t nbyte);        // Actually performs the read (so a lock can be obtained).
    off_t   lseek(int fd, size_t nbyte, int whence);      // Actually performs the seek (so a lock can be obtained).
    void rename(const char *oldpath, const char *newpath);
    void ftruncate(int fd, off_t length);
    void truncate(const char *path, off_t length);
    void mkdir(const char *pathname);
    
private:
    backup_directory* get_directory(int fd);
    backup_directory* get_directory(const char *file);
};

#endif // End of header guardian.
