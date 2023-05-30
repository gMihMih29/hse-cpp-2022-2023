#include <cassert>
#include <catch.hpp>

#include "reader.h"
#include "readers_util.h"

std::string ReadAll(Reader* in) {
    const size_t chunk_size = 128;

    std::string buf;
    std::string chunk;
    while (true) {
        chunk.resize(chunk_size);
        size_t read_res = in->Read(&(chunk[0]), chunk.size());
        if (read_res == 0) {
            break;
        }
        chunk.resize(read_res);
        buf += chunk;
    }

    return buf;
}

class StringReader : public Reader {
public:
    StringReader(const std::string& data) : data_(data) {
    }

    virtual size_t Read(char* buf, size_t len) override {
        size_t read_len = std::min(len, data_.size() - pos_);
        for (size_t i = 0; i < read_len; ++i) {
            buf[i] = data_[pos_++];
        }
        return read_len;
    }

private:
    std::string data_;
    size_t pos_ = 0;
};

class FdReader : public Reader {
public:
    FdReader(int fd) : fd_(fd) {
    }

    virtual size_t Read(char* buf, size_t len) override {
        ssize_t res = ::read(fd_, buf, len);
        if (res == -1) {  // treat errors as EOF
            res = 0;
        }
        return res;
    }

private:
    int fd_;
};

std::unique_ptr<Reader> MakeStringReader(const std::string& data) {
    return std::unique_ptr<StringReader>(new StringReader(data));
}

TEST_CASE("StringReader") {
    REQUIRE(ReadAll(MakeStringReader("").get()).empty());
    REQUIRE("a" == ReadAll(MakeStringReader("a").get()));

    std::string big_string(1 << 15, 'f');  // NOLINT
    REQUIRE(big_string == ReadAll(MakeStringReader(big_string).get()));
}

TEST_CASE("LimitReader") {
    LimitReader l1(MakeStringReader(""), 0);
    REQUIRE(ReadAll(&l1).empty());

    LimitReader l2(MakeStringReader(" "), 0);
    REQUIRE(ReadAll(&l2).empty());

    LimitReader l3(MakeStringReader("ab"), 1);
    REQUIRE("a" == ReadAll(&l3));
}

TeeReader MakeTee(std::vector<std::string> chunks) {
    std::vector<std::unique_ptr<Reader>> readers;
    for (auto c : chunks) {
        readers.emplace_back(MakeStringReader(c));
    }
    return TeeReader(std::move(readers));
}

TEST_CASE("TeeReader") {
    TeeReader t1({});
    REQUIRE(ReadAll(&t1).empty());

    TeeReader t2 = MakeTee({""});
    REQUIRE(ReadAll(&t2).empty());

    TeeReader t3 = MakeTee({"abc"});
    REQUIRE("abc" == ReadAll(&t3));

    TeeReader t4 = MakeTee({"abc", "def", "g"});
    REQUIRE("abcdefg" == ReadAll(&t4));

    TeeReader t5 = MakeTee({"abc", "", "def"});
    REQUIRE("abcdef" == ReadAll(&t5));

    TeeReader t6 = MakeTee({"abc", "", "", "", "", "def", "", ""});
    REQUIRE("abcdef" == ReadAll(&t6));
}

TEST_CASE("HexReader") {
    HexDecodingReader h1(MakeStringReader(""));
    REQUIRE(ReadAll(&h1).empty());

    HexDecodingReader h2(MakeStringReader("616263"));
    REQUIRE("abc" == ReadAll(&h2));

    std::string big_hex = "74657374666f6f626172";
    std::string answer = "testfoobar";
    for (int i = 0; i < 6; ++i) {
        big_hex += big_hex;
        answer += answer;
    }

    HexDecodingReader h3(MakeStringReader(big_hex));
    REQUIRE(answer == ReadAll(&h3));
}
