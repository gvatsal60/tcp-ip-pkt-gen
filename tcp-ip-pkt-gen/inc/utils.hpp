#pragma once
#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstddef>
#include <cstdint>
#include <cstdio>

/// @brief
/// @tparam T
/// @param buf
/// @return
template <typename T>
bool NullPtrCheck(T buf) {
  return ((buf != nullptr) ? true : false);
}

/// @brief
/// @param buf
/// @param len
void PrintHexBuffer(const uint8_t *const buf, const uint32_t len) {
  printf("\n---------- Generated Packet ----------\n");
  size_t i = 0;
  for (i = 0; i < len; i++) {
    printf("0x%02x ", buf[i]);
    if (i != 0 && ((i + 1) % 8) == 0) {
      printf("\n");
    }
  }
  if (i != 0 && (i % 8) != 0) {
    printf("\n");
  }
}

#endif
