#pragma once

#include <string>
#include <algorithm>

#include <unistd.h>

class Reader {
public:
    virtual ~Reader() {
    }

    // Читает не более чем @len байт из потока.
    // Помещает результат чтения в буффер @buf.
    // Возвращает, сколько байт удалось прочитать.
    // Возвращаемое значение 0 означает конец потока.

    virtual size_t Read(char* buf, size_t len) = 0;
};

