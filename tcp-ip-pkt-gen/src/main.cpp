#include <random>

#include "tcp_ip_gen.hpp"

int main(int argc, char const* argv[]) {
  constexpr uint32_t kMaxInputPktSize = 20;
  std::array<uint8_t, kMaxInputPktSize> inp_data = {0x0};

  std::random_device rd{};
  std::mt19937 gen(rd());
  for (size_t i = 0; i < kMaxInputPktSize; i++) {
    std::uniform_int_distribution<> dis(0, 255);
    inp_data[i] = dis(gen);
  }

  constexpr uint32_t src_ip = 0xC0A8380B;
  constexpr uint32_t dst_ip = 0xC2BE7C11;

  constexpr uint16_t src_port = 59198;
  constexpr uint16_t dst_port = 53;

  const auto out_data = GenerateTcpIpPacket(inp_data.data(), kMaxInputPktSize,
                                            src_ip, dst_ip, src_port, dst_port);

  PrintHexBuffer(out_data.get(),
                 kMaxInputPktSize + (sizeof(ip) + sizeof(tcphdr)));

  return 0;
}
