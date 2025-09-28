#pragma once
#ifndef PACKET_GEN_HPP
#define PACKET_GEN_HPP

#include <memory>
#include <string_view>

/**
 * @brief Packet_Generator class for generating network packets.
 *
 * This class provides functionality to generate network packets with various
 * protocols.
 */
class Packet_Generator {
public:
  Packet_Generator() = default;
  ~Packet_Generator() = default;

  std::unique_ptr<uint8_t[]>
  GeneratePacket(const std::string_view protocol, const uint8_t *const data,
                 const size_t data_len, const uint32_t source_ip,
                 const uint32_t dest_ip, const uint16_t source_port,
                 const uint16_t dest_port);

private:
  void GenerateIpHeader(uint8_t *const packet, const uint32_t data_len,
                        const uint32_t source_ip, const uint32_t dest_ip,
                        const uint16_t protocol);
  std::unique_ptr<uint8_t[]>
  GenerateTcpIpPacket(const uint8_t *const data, const size_t data_len,
                      const uint32_t source_ip, const uint32_t dest_ip,
                      const uint16_t source_port, const uint16_t dest_port);
  std::unique_ptr<uint8_t[]>
  GenerateUdpIpPacket(const uint8_t *const data, const size_t data_len,
                      const uint32_t source_ip, const uint32_t dest_ip,
                      const uint16_t source_port, const uint16_t dest_port);
  uint16_t CheckSum(const uint16_t *data, size_t length) const;

  /* Default window size for TCP packets. */
  const uint32_t DEFAULT_WINDOW_SIZE = 65535;
};

#endif
