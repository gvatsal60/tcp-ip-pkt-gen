#pragma once
#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstddef>
#include <cstdint>
#include <cstdio>

/**
 * @brief NullPtrCheck checks if a pointer is not null.
 *
 * This template function checks if the provided pointer is not null.
 *
 * @tparam T The type of the pointer.
 * @param buf The pointer to be checked.
 * @return true if the pointer is not null, false otherwise.
 */
template <typename T> bool NullPtrCheck(T buf) {
  return ((buf != nullptr) ? true : false);
}

/**
 * @brief PrintHexBuffer prints a buffer of bytes in hexadecimal format.
 *
 * This function prints the contents of a buffer in hexadecimal format to the
 * standard output. Each byte in the buffer is printed as a hexadecimal value,
 * with a space between each byte. Additionally, a newline character is printed
 * after every 8 bytes.
 *
 * @param buf Pointer to the buffer containing the bytes to be printed.
 * @param len The length of the buffer, in bytes.
 */
void PrintHexBuffer(const uint8_t *const buf, const uint32_t len) {
  printf("\n---------- Generated Hex Packet ----------\n");
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

  printf(
      "\n---------- Verify Hex Packet (https://hpd.gasmi.net/) ----------\n");
  for (i = 0; i < len; i++) {
    printf("%02x ", buf[i]);
    if (i != 0 && ((i + 1) % 8) == 0) {
      printf("\n");
    }
  }
  if (i != 0 && (i % 8) != 0) {
    printf("\n");
  }
}

#endif
