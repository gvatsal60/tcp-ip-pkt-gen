#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <unistd.h>

#include <cassert>
#include <iostream>

#include "packet_gen.hpp"
#include "utils.hpp"

struct PktArguments {
  uint32_t src_addr{};
  uint32_t dst_addr{};
  int src_port{};
  int dst_port{};
  std::string protocol{};
  std::string payload{};
};

inline void PrintUsage(const char *program_name) {
  std::cerr << "Usage: " << program_name
            << " --source|--src <source_address> --destination|--dst "
               "<destination_address> --src_port <source_port> "
               "--dst_port <destination_port> --protocol <protocol> "
               "--payload <payload>"
            << std::endl;
}

bool HandleArgument(const std::string &arg, const char *value,
                    PktArguments &pkt_args) {
  if (arg == "--source" || arg == "--src") {
    if (inet_pton(AF_INET, value, &pkt_args.src_addr) != 1)
      return false;
    pkt_args.src_addr = ntohl(pkt_args.src_addr);
  } else if (arg == "--destination" || arg == "--dst") {
    if (inet_pton(AF_INET, value, &pkt_args.dst_addr) != 1)
      return false;
    pkt_args.dst_addr = ntohl(pkt_args.dst_addr);
  } else if (arg == "--src_port") {
    pkt_args.src_port = std::stoi(value);
  } else if (arg == "--dst_port") {
    pkt_args.dst_port = std::stoi(value);
  } else if (arg == "--protocol") {
    pkt_args.protocol = value;
  } else if (arg == "--payload") {
    pkt_args.payload = value;
  } else {
    std::cerr << "Invalid argument: " << arg << std::endl;
    return false;
  }

  return true;
}

bool ParseArguments(int argc, const char *const argv[],
                    PktArguments &pkt_args) {

  if (constexpr int kMaxArgSupported = 13; argc != kMaxArgSupported) {
    return false;
  }

  for (int i = 1; i < argc; i += 2) {
    const std::string arg = argv[i];
    const char *value = argv[i + 1];

    if (!HandleArgument(arg, value, pkt_args)) {
      return false;
    }
  }

  return true;
}

int main(const int argc, const char *const argv[]) {
  PktArguments pkt_args{};

  if (!ParseArguments(argc, argv, pkt_args)) {
    PrintUsage(argv[0]);
    return 1;
  }

  const auto pkt_gen = std::make_unique<Packet_Generator>();

  const auto out_data = pkt_gen->GeneratePacket(
      pkt_args.protocol,
      reinterpret_cast<const uint8_t *>(pkt_args.payload.c_str()),
      pkt_args.payload.size(), pkt_args.src_addr, pkt_args.dst_addr,
      pkt_args.src_port, pkt_args.dst_port);

  if (out_data.get()) {
    PrintHexBuffer(out_data.get(),
                   pkt_args.payload.size() + (sizeof(ip) + sizeof(tcphdr)));
  } else {
    std::cerr << "\nError: Something went wrong!!!\n";
  }

  return 0;
}
