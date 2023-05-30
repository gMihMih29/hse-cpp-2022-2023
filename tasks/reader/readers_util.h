#pragma once

#include <vector>
#include <memory>

#include "reader.h"

class LimitReader : public Reader {
public:
    LimitReader(std::unique_ptr<Reader> reader, size_t limit) {
    }

    virtual size_t Read(char* buf, size_t len) override;
};

class TeeReader : public Reader {
public:
    TeeReader(std::vector<std::unique_ptr<Reader>> readers) {
    }

    virtual size_t Read(char* buf, size_t len) override;
};

class HexDecodingReader : public Reader {
public:
    HexDecodingReader(std::unique_ptr<Reader> reader) {
    }

    virtual size_t Read(char* buf, size_t len) override;
};
