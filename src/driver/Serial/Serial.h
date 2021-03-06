/*
 * This file is modified, and part of the Doodle3D project (http://doodle3d.com).
 *
 * Original can be found here: https://github.com/Doodle3D/print3d
 *
 * Copyright (c) 2013, Doodle3D
 * This software is licensed under the terms of the GNU GPL v2 or later.
 * See file LICENSE.txt or visit http://www.gnu.org/licenses/gpl.html for full license details.
 */

#ifndef SERIAL_H_SEEN
#define SERIAL_H_SEEN

#include <string>

class Serial {
public:
    typedef enum ESERIAL_SET_SPEED_RESULT {
        SSR_OK = 0,
        SSR_IO_GET,
        SSR_IO_IOSSIOSPEED,
        SSR_IO_SET,
        SSR_IO_MGET,
        SSR_IO_MSET1,
        SSR_IO_MSET2
    } SET_SPEED_RESULT;

    int counter;

    Serial();

    int open(const char* file);
    int close();
    bool isOpen() const;
    SET_SPEED_RESULT setSpeed(int speed);
    bool send(const char* code);
    bool write(const unsigned char* data, size_t datalen);
    bool write(const unsigned char b);

    int readData(int timeout = 0, bool onlyOnce = false);
    int readDataWithLen(int len, int timeout); //may read more than len, but not less

    int readByteDirect(int timeout = 0);
    int readBytesDirect(unsigned char* buf, size_t buflen, int timeout = 0);

    char* getBuffer();
    int getBufferSize() const;
    int getFileDescriptor() const;
    void clearBuffer();
    int flushReadBuffer();

    int extractByte();
    int extractBytes(unsigned char* buf, size_t buflen);

    //convenience function for plain text data
    std::string* extractLine();

private:
    static const int READ_BUF_SIZE;

    Serial(const Serial& o);
    void operator=(const Serial& o);

    int portFd_;
    bool fake;

    char* buffer_;
    int bufferSize_;
};

#endif /* SERIAL_H_SEEN */
