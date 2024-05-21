#include "packet_gen.hpp"

#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <unistd.h>

#include <cstring>
#include <memory>

/// @brief
/// @param data
/// @param data_len
/// @param source_ip
/// @param dest_ip
/// @param source_port
/// @param dest_port
/// @return
std::unique_ptr<uint8_t[]> Packet_Generator::GenerateTcpIpPacket(
    const uint8_t *const data, const size_t data_len, const uint32_t source_ip,
    const uint32_t dest_ip, const uint16_t source_port,
    const uint16_t dest_port) {
  std::unique_ptr<uint8_t[]> packet;

  if (!data || !data_len || !source_ip || !dest_ip || !source_port ||
      !dest_port) {
    return packet;
  }

  const auto packet_size = sizeof(ip) + sizeof(tcphdr) + data_len;
  packet.reset(new uint8_t[packet_size]);
  memset(packet.get(), 0, packet_size);

  auto *ip_header = reinterpret_cast<ip *>(packet.get());
  ip_header->ip_v = 4;
  ip_header->ip_hl = 5;
  ip_header->ip_tos = 0;
  ip_header->ip_len = htons(packet_size);
  ip_header->ip_id = htons(getpid());
  ip_header->ip_off = 0;
  ip_header->ip_ttl = 64;
  ip_header->ip_p = IPPROTO_TCP;
  ip_header->ip_sum = 0;
  ip_header->ip_src.s_addr = htonl(source_ip);
  ip_header->ip_dst.s_addr = htonl(dest_ip);

  auto *tcp_header = reinterpret_cast<tcphdr *>(packet.get() + sizeof(ip));
  tcp_header->source = htons(source_port);
  tcp_header->dest = htons(dest_port);
  tcp_header->seq = 0;
  tcp_header->ack_seq = 0;
  tcp_header->doff = 5;
  tcp_header->window = htons(DEFAULT_WINDOW_SIZE);
  tcp_header->th_sum = 0;

  memcpy(packet.get() + (sizeof(ip) + sizeof(tcphdr)), data, data_len);

  return packet;
}
