#pragma once
#ifndef PACKET_GEN_HPP
#define PACKET_GEN_HPP

#include <memory>
#include <string>

/// @brief
class Packet_Generator {
 public:
  Packet_Generator() = default;
  ~Packet_Generator() = default;

  std::unique_ptr<uint8_t[]> GenerateTcpIpPacket(const uint8_t *const data,
                                                 const size_t data_len,
                                                 const uint32_t source_ip,
                                                 const uint32_t dest_ip,
                                                 const uint16_t source_port,
                                                 const uint16_t dest_port);

 private:
  const uint32_t DEFAULT_WINDOW_SIZE = 65535;
};

#endif