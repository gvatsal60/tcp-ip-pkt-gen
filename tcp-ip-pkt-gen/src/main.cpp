#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <unistd.h>

#include <cassert>
#include <iostream>
#include <memory>

#include "packet_gen.hpp"
#include "utils.hpp"

int main(int argc, char const* argv[]) {
  uint32_t src_addr{};
  uint32_t dst_addr{};
  int src_port{};
  int dst_port{};
  std::string protocol{};
  std::string payload{};

  constexpr int kMaxArgSupported = 13;

  if (argc != kMaxArgSupported) {
    std::cerr << "Usage: " << argv[0]
              << " --source|src <source_address> --destination|dst "
                 "<destination_address> "
                 "--src_port <source_port> --dst_port <destination_port> "
                 "--protocol <protocol> --payload <payload>"
              << std::endl;
    return 1;
  }

  for (int i = 1; i < argc; i += 2) {
    const std::string arg = argv[i];
    if ((arg == "--source") || (arg == "--src")) {
      inet_pton(AF_INET, argv[i + 1], &src_addr);
      src_addr = ntohl(src_addr);
    } else if ((arg == "--destination") || (arg == "--dst")) {
      inet_pton(AF_INET, argv[i + 1], &dst_addr);
      dst_addr = ntohl(src_addr);
    } else if (arg == "--src_port") {
      src_port = std::stoi(argv[i + 1]);
    } else if (arg == "--dst_port") {
      dst_port = std::stoi(argv[i + 1]);
    } else if (arg == "--protocol") {
      protocol = argv[i + 1];
    } else if (arg == "--payload") {
      payload = argv[i + 1];
    } else {
      std::cerr << "Invalid argument: " << arg << std::endl;
      return 1;
    }
  }

  const auto pkt_gen = std::make_unique<Packet_Generator>();

  const auto out_data = pkt_gen->GenerateTcpIpPacket(
      reinterpret_cast<const uint8_t*>(payload.c_str()), payload.size(),
      src_addr, dst_addr, src_port, dst_port);

  assert(out_data != nullptr);

  PrintHexBuffer(out_data.get(),
                 payload.size() + (sizeof(ip) + sizeof(tcphdr)));

  return 0;
}
