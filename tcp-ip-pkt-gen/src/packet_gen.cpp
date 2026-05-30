#include "packet_gen.hpp"

#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <unistd.h>

#include <cstring>

/**
 * @brief Calculate checksum for a given data buffer.
 *
 * This function calculates the checksum for the given
 * data buffer using the one's complement sum method.
 *
 * @param data Pointer to the data buffer.
 * @param length Length of the data buffer in bytes.
 * @return The calculated checksum value.
 */
uint16_t Packet_Generator::CheckSum(const uint16_t *data, size_t length) const {
  uint32_t sum = 0;

  while (length > 1) {
    sum += *data++;
    length -= 2;
  }
  if (length > 0) {
    const auto *byte_data = reinterpret_cast<const uint8_t *>(data);
    sum += *byte_data;
  }
  while (sum >> 16) {
    sum = (sum & 0xFFFF) + (sum >> 16);
  }

  return ~sum;
}

/**
 * @brief GenerateIpHeader generates an IP header.
 *
 * This function generates an IP header with the specified parameters.
 *
 * @param packet Pointer to the buffer where the IP header will be written.
 * @param source_ip The source IP address for the packet.
 * @param dest_ip The destination IP address for the packet.
 * @param protocol The IP protocol to use for the packet.
 */
void Packet_Generator::GenerateIpHeader(uint8_t *const packet,
                                        const size_t data_len,
                                        const uint32_t source_ip,
                                        const uint32_t dest_ip,
                                        const uint16_t protocol) const {
  auto *ip_header = reinterpret_cast<ip *>(packet);
  ip_header->ip_v = 4;
  ip_header->ip_hl = 5;
  ip_header->ip_tos = 0;
  ip_header->ip_len = htons(static_cast<uint16_t>(sizeof(ip) + data_len));
  ip_header->ip_id = htons(static_cast<uint16_t>(getpid()));
  ip_header->ip_off = 0;
  ip_header->ip_ttl = 64;
  ip_header->ip_p = protocol;
  ip_header->ip_src.s_addr = htonl(source_ip);
  ip_header->ip_dst.s_addr = htonl(dest_ip);

  ip_header->ip_sum = 0;
  ip_header->ip_sum =
      CheckSum(reinterpret_cast<const uint16_t *>(packet), sizeof(ip));
}

/**
 * @brief GenerateTcpIpPacket generates a TCP/IP packet.
 *
 * This function generates a TCP/IP packet with the specified data, source IP,
 * destination IP, source port, and destination port.
 *
 * @param data Pointer to the data to include in the packet.
 * @param data_len The length of the data, in bytes.
 * @param source_ip The source IP address for the packet.
 * @param dest_ip The destination IP address for the packet.
 * @param source_port The source port for the packet.
 * @param dest_port The destination port for the packet.
 * @return A unique pointer to the generated packet buffer.
 */
std::unique_ptr<uint8_t[]> Packet_Generator::GenerateTcpIpPacket(
    const uint8_t *const data, const size_t data_len, const uint32_t source_ip,
    const uint32_t dest_ip, const uint16_t source_port,
    const uint16_t dest_port) const {
  constexpr uint16_t kDefaultWindowSize = 65535;

  /* Calculate sizes */
  const size_t ip_header_size = sizeof(ip);
  const size_t tcp_header_size = sizeof(tcphdr);
  const size_t packet_size = ip_header_size + tcp_header_size + data_len;

  /* Allocate and zero-initialize packet buffer */
  auto packet = std::make_unique<uint8_t[]>(packet_size);
  std::memset(packet.get(), 0, packet_size);

  /* Generate IP header */
  GenerateIpHeader(packet.get(), tcp_header_size + data_len, source_ip, dest_ip,
                   IPPROTO_TCP);

  /* Generate TCP header */
  auto *tcp_header = reinterpret_cast<tcphdr *>(packet.get() + ip_header_size);
  tcp_header->source = htons(source_port);
  tcp_header->dest = htons(dest_port);
  tcp_header->seq = 0;
  tcp_header->ack_seq = 0;
  tcp_header->doff = 5;
  tcp_header->window = htons(kDefaultWindowSize);
  tcp_header->th_sum = 0;

  /* Copy payload data */
  uint8_t *payload_start = packet.get() + ip_header_size + tcp_header_size;
  const size_t payload_offset =
      static_cast<size_t>(payload_start - packet.get());
  if (payload_offset > packet_size || data_len > packet_size - payload_offset) {
    return nullptr;
  }
  std::memcpy(payload_start, data, data_len);
  tcp_header->th_sum =
      CheckSum(reinterpret_cast<const uint16_t *>(tcp_header),
               tcp_header_size + data_len);

  return packet;
}

/**
 * @brief GenerateUdpIpPacket generates a UDP/IP packet.
 *
 * This function generates a UDP/IP packet with the specified data, source IP,
 * destination IP, source port, and destination port.
 *
 * @param data Pointer to the data to include in the packet.
 * @param data_len The length of the data, in bytes.
 * @param source_ip The source IP address for the packet.
 * @param dest_ip The destination IP address for the packet.
 * @param source_port The source port for the packet.
 * @param dest_port The destination port for the packet.
 * @return A unique pointer to the generated packet buffer.
 */
std::unique_ptr<uint8_t[]> Packet_Generator::GenerateUdpIpPacket(
    const uint8_t *const data, const size_t data_len, const uint32_t source_ip,
    const uint32_t dest_ip, const uint16_t source_port,
    const uint16_t dest_port) const {

  /* Calculate sizes */
  const size_t ip_header_size = sizeof(ip);
  const size_t udp_header_size = sizeof(udphdr);
  const size_t packet_size = ip_header_size + udp_header_size + data_len;

  /* Allocate memory for packet */
  auto packet = std::make_unique<uint8_t[]>(packet_size);
  std::memset(packet.get(), 0, packet_size);

  /* Generate IP header */
  GenerateIpHeader(packet.get(), udp_header_size + data_len, source_ip, dest_ip,
                   IPPROTO_UDP);

  /* Generate UDP header */
  auto *udp_header = reinterpret_cast<udphdr *>(packet.get() + ip_header_size);
  udp_header->source = htons(source_port);
  udp_header->dest = htons(dest_port);
  udp_header->len = htons(static_cast<uint16_t>(udp_header_size + data_len));
  udp_header->check = 0;

  /* Copy payload data */
  uint8_t *payload_start = packet.get() + ip_header_size + udp_header_size;
  const size_t payload_offset =
      static_cast<size_t>(payload_start - packet.get());
  if (payload_offset > packet_size || data_len > packet_size - payload_offset) {
    return nullptr;
  }
  std::memcpy(payload_start, data, data_len);
  udp_header->check =
      CheckSum(reinterpret_cast<const uint16_t *>(udp_header),
               udp_header_size + data_len);

  return packet;
}

/**
 * @brief GeneratePacket generates a packet with the specified protocol.
 *
 * This function generates a network packet with the specified protocol, data,
 * source IP, destination IP, source port, and destination port.
 *
 * @param protocol The protocol to use for the packet (e.g., "TCP", "UDP").
 * @param data Pointer to the data to include in the packet.
 * @param data_len The length of the data, in bytes.
 * @param source_ip The source IP address for the packet.
 * @param dest_ip The destination IP address for the packet.
 * @param source_port The source port for the packet.
 * @param dest_port The destination port for the packet.
 * @return A unique pointer to the generated packet buffer.
 */
std::unique_ptr<uint8_t[]> Packet_Generator::GeneratePacket(
    const std::string_view protocol, const uint8_t *const data,
    const size_t data_len, const uint32_t source_ip, const uint32_t dest_ip,
    const uint16_t source_port, const uint16_t dest_port) const {
  if (!data || data_len == 0 || source_ip == 0 || dest_ip == 0 ||
      source_port == 0 || dest_port == 0) {
    return nullptr;
  }

  if (protocol == "TCP") {
    return GenerateTcpIpPacket(data, data_len, source_ip, dest_ip, source_port,
                               dest_port);
  } else if (protocol == "UDP") {
    return GenerateUdpIpPacket(data, data_len, source_ip, dest_ip, source_port,
                               dest_port);
  }

  return nullptr;
}
