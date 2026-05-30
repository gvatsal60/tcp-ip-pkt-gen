#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <string_view>

/**
 * @brief Packet_Generator class for generating network packets.
 *
 * This class provides functionality to generate
 * network packets with various protocols.
 */
class Packet_Generator final {
public:
  Packet_Generator() = default;
  ~Packet_Generator() = default;

  std::unique_ptr<uint8_t[]>
  GeneratePacket(std::string_view protocol, const uint8_t *data,
                 size_t data_len, uint32_t source_ip, uint32_t dest_ip,
                 uint16_t source_port, uint16_t dest_port) const;

private:
  void GenerateIpHeader(uint8_t *packet, size_t data_len, uint32_t source_ip,
                        uint32_t dest_ip, uint16_t protocol) const;
  std::unique_ptr<uint8_t[]>
  GenerateTcpIpPacket(const uint8_t *data, size_t data_len, uint32_t source_ip,
                      uint32_t dest_ip, uint16_t source_port,
                      uint16_t dest_port) const;
  std::unique_ptr<uint8_t[]>
  GenerateUdpIpPacket(const uint8_t *data, size_t data_len, uint32_t source_ip,
                      uint32_t dest_ip, uint16_t source_port,
                      uint16_t dest_port) const;
  uint16_t CheckSum(const uint16_t *data, size_t length) const;

  /* Default window size for TCP packets. */
  static constexpr uint16_t DEFAULT_WINDOW_SIZE = 65535;
};
