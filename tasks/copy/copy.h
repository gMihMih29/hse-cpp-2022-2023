#pragma once

template <typename T, typename U>
U Copy(T src_begin, T src_end, U dest);

template <typename T, typename U>
U CopyBackward(T src_begin, T src_end, U dest);