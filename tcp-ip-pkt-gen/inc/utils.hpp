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
 * @brief PrintFormattedHex prints a buffer of bytes in formatted hexadecimal.
 *
 * This helper function prints the contents of a buffer in hexadecimal format
 * to the standard output. Each byte is printed with or without a "0x" prefix,
 * depending on the `prefix` flag. A space separates each byte, and a newline
 * is printed after every 8 bytes for readability.
 *
 * @param buf Pointer to the buffer containing the bytes to be printed.
 * @param len The length of the buffer, in bytes.
 * @param prefix Boolean flag indicating whether to prefix each byte with "0x".
 */
inline void PrintFormattedHex(const uint8_t *const buf, const uint32_t len,
                              const bool prefix) {
  for (uint32_t i = 0; i < len; ++i) {
    if (prefix) {
      printf("0x%02x ", buf[i]);
    } else {
      printf("%02x ", buf[i]);
    }
    if ((i + 1) % 8 == 0) {
      printf("\n");
    }
  }
  if (len % 8 != 0) {
    printf("\n");
  }
}

/**
 * @brief PrintHexBuffer prints a buffer of bytes in two hexadecimal formats.
 *
 * This function prints the contents of a buffer in two styles of hexadecimal
 * format to the standard output. The first format includes a "0x" prefix for
 * each byte, and the second format omits the prefix for verification purposes.
 * Each byte is separated by a space, and a newline is printed after every 8
 * bytes.
 *
 * @param buf Pointer to the buffer containing the bytes to be printed.
 * @param len The length of the buffer, in bytes.
 */
inline void PrintHexBuffer(const uint8_t *const buf, const uint32_t len) {
  printf("\n---------- Generated Hex Packet ----------\n");
  PrintFormattedHex(buf, len, true);

  printf(
      "\n---------- Verify Hex Packet (https://hpd.gasmi.net/) ----------\n");
  PrintFormattedHex(buf, len, false);
}

#endif
