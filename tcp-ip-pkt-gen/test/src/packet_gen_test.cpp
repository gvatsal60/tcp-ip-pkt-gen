// cppcheck-suppress-file missingIncludeSystem
// cppcheck-suppress-file missingInclude
#include <gtest/gtest.h>

#include <arpa/inet.h>
#include <cstring>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>

#include "packet_gen.hpp"

class PacketGenTest : public ::testing::Test {
protected:
  void SetUp() override { pg_ = std::make_unique<Packet_Generator>(); }

  std::unique_ptr<Packet_Generator> pg_;
};

TEST_F(PacketGenTest, GeneratesTcpPacketAndCopiesPayload) {
  const uint8_t payload[] = {0x01, 0x02, 0x03, 0x04};
  const size_t payload_len = sizeof(payload);
  const uint32_t src_ip = 0x0a000001; // 10.0.0.1 in host order
  const uint32_t dst_ip = 0x0a000002; // 10.0.0.2
  const uint16_t src_port = 12345;
  const uint16_t dst_port = 80;

  auto pkt = pg_->GeneratePacket("TCP", payload, payload_len, src_ip, dst_ip,
                                 src_port, dst_port);
  ASSERT_TRUE(pkt);

  auto *ip_hdr = reinterpret_cast<struct ip *>(pkt.get());
  EXPECT_EQ(ip_hdr->ip_p, IPPROTO_TCP);
  EXPECT_EQ(ntohs(ip_hdr->ip_len),
            static_cast<uint16_t>(sizeof(struct ip) + sizeof(struct tcphdr) +
                                  payload_len));
  EXPECT_EQ(ntohl(ip_hdr->ip_src.s_addr), src_ip);
  EXPECT_EQ(ntohl(ip_hdr->ip_dst.s_addr), dst_ip);

  auto *tcp_hdr =
      reinterpret_cast<struct tcphdr *>(pkt.get() + sizeof(struct ip));
  EXPECT_EQ(ntohs(tcp_hdr->source), src_port);
  EXPECT_EQ(ntohs(tcp_hdr->dest), dst_port);

  uint8_t *payload_start =
      pkt.get() + sizeof(struct ip) + sizeof(struct tcphdr);
  EXPECT_EQ(0, memcmp(payload_start, payload, payload_len));
}

TEST_F(PacketGenTest, GeneratesUdpPacketAndCopiesPayload) {
  const uint8_t payload[] = {0xde, 0xad, 0xbe, 0xef, 0x00};
  const size_t payload_len = sizeof(payload);
  const uint32_t src_ip = 0xc0a80001; // 192.168.0.1
  const uint32_t dst_ip = 0xc0a80002; // 192.168.0.2
  const uint16_t src_port = 54321;
  const uint16_t dst_port = 53;

  auto pkt = pg_->GeneratePacket("UDP", payload, payload_len, src_ip, dst_ip,
                                 src_port, dst_port);
  ASSERT_TRUE(pkt);

  auto *ip_hdr = reinterpret_cast<struct ip *>(pkt.get());
  EXPECT_EQ(ip_hdr->ip_p, IPPROTO_UDP);
  EXPECT_EQ(ntohs(ip_hdr->ip_len),
            static_cast<uint16_t>(sizeof(struct ip) + sizeof(struct udphdr) +
                                  payload_len));
  EXPECT_EQ(ntohl(ip_hdr->ip_src.s_addr), src_ip);
  EXPECT_EQ(ntohl(ip_hdr->ip_dst.s_addr), dst_ip);

  auto *udp_hdr =
      reinterpret_cast<struct udphdr *>(pkt.get() + sizeof(struct ip));
  EXPECT_EQ(ntohs(udp_hdr->source), src_port);
  EXPECT_EQ(ntohs(udp_hdr->dest), dst_port);
  EXPECT_EQ(ntohs(udp_hdr->len),
            static_cast<uint16_t>(sizeof(struct udphdr) + payload_len));

  uint8_t *payload_start =
      pkt.get() + sizeof(struct ip) + sizeof(struct udphdr);
  EXPECT_EQ(0, memcmp(payload_start, payload, payload_len));
}

TEST_F(PacketGenTest, GeneratePacketReturnsNullOnInvalidArgs) {
  const uint8_t payload[] = {0x00};
  // data_len == 0 should return nullptr
  auto pkt =
      pg_->GeneratePacket("TCP", payload, 0, 0x01010101, 0x02020202, 1, 2);
  EXPECT_FALSE(pkt);
}
