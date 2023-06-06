#pragma once

#include <memory>
#include <vector>

#include "reader.h"

class LimitReader : public Reader {
public:
    LimitReader(std::unique_ptr<Reader> reader, size_t limit);

    virtual size_t Read(char* buf, size_t len) override;

private:
    std::unique_ptr<Reader> reader_;
    size_t limit_;
};

class TeeReader : public Reader {
public:
    TeeReader(std::vector<std::unique_ptr<Reader>> readers);

    virtual size_t Read(char* buf, size_t len) override;

private:
    size_t current_ = 0;
    std::vector<std::unique_ptr<Reader>> readers_;
};

class HexDecodingReader : public Reader {
public:
    HexDecodingReader(std::unique_ptr<Reader> reader);

    virtual size_t Read(char* buf, size_t len) override;

private:
    std::unique_ptr<Reader> reader_;
};
