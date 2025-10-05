#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <unistd.h>

#include <cassert>
#include <iostream>

#include "packet_gen.hpp"
#include "utils.hpp"

int main(const int argc, const char *const argv[]) {
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

  uint32_t src_addr{};
  uint32_t dst_addr{};
  int src_port{};
  int dst_port{};
  std::string protocol{};
  std::string payload{};

  for (int i = 1; i < argc; i += 2) {
    const std::string arg = argv[i];
    if ((arg == "--source") || (arg == "--src")) {
      inet_pton(AF_INET, argv[i + 1], &src_addr);
      src_addr = ntohl(src_addr);
    } else if ((arg == "--destination") || (arg == "--dst")) {
      inet_pton(AF_INET, argv[i + 1], &dst_addr);
      dst_addr = ntohl(dst_addr);
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

  const auto out_data = pkt_gen->GeneratePacket(protocol, reinterpret_cast<const uint8_t *>(payload.c_str()),
                                                payload.size(), src_addr, dst_addr, src_port, dst_port);

  if (out_data.get()) {
    PrintHexBuffer(out_data.get(), payload.size() + (sizeof(ip) + sizeof(tcphdr)));
  } else {
    printf("\nError: Something went wrong!!!\n");
  }

  return 0;
}
