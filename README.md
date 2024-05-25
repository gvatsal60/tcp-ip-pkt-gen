[![License](https://img.shields.io/badge/License-Apache_2.0-blue.svg)](https://img.shields.io/github/license/gvatsal60/tcp-ip-pkt-gen)
![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/gvatsal60/tcp-ip-pkt-gen/build.yml)
[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=gvatsal60_tcp-ip-pkt-gen&metric=alert_status)](https://sonarcloud.io/summary/new_code?id=gvatsal60_tcp-ip-pkt-gen)
[![Maintenance](https://img.shields.io/badge/Maintained%3F-Yes-green.svg)](https://GitHub.com/gvatsal60/tcp-ip-pkt-gen/graphs/commit-activity)
[![GitHub pull-requests](https://img.shields.io/github/issues-pr/gvatsal60/tcp-ip-pkt-gen.svg)](https://GitHub.com/gvatsal60/tcp-ip-pkt-gen/pull/)
[![GitHub issues](https://img.shields.io/github/issues/gvatsal60/tcp-ip-pkt-gen.svg)](https://GitHub.com/gvatsal60/tcp-ip-pkt-gen/issues/)
[![GitHub forks](https://img.shields.io/github/forks/gvatsal60/tcp-ip-pkt-gen.svg)](https://GitHub.com/gvatsal60/tcp-ip-pkt-gen/network/)
[![GitHub stars](https://img.shields.io/github/stars/gvatsal60/tcp-ip-pkt-gen.svg)](https://GitHub.com/gvatsal60/tcp-ip-pkt-gen/stargazers)

# TCP/IP Packet Generator (C++)

## Overview

The TCP/IP Packet Generator is a lightweight tool written in C++ for creating customized TCP/IP packets. It's designed for network testing, simulation, and educational purposes.

## Features

- **Customization**: Easily configure packet parameters such as source and destination addresses, port numbers, protocol types, payload data, etc.
- **Multiple Packet Types**: Supports the generation of various TCP/IP packet types including TCP, UDP, ICMP, etc.
- **Efficiency**: Optimized for fast packet generation without compromising on accuracy.
- **Simple Interface**: Intuitive command-line interface for easy usage.

## Usage

1. Compile the source code using your preferred C++ compiler.
2. Run the executable file with appropriate command-line arguments to specify packet parameters.
3. Generated packets will be outputted according to the provided settings.

## Example

```
./tcp_ip_pkt_gen --source 192.168.56.11 --destination 194.190.124.17 --src_port 59198 --dst_port 53 --protocol TCP --payload "Hello, world!"
```
# Verification Required
To ensure the integrity and authenticity of the packet, kindly verify its contents through the designated platform: [Decode Packet](https://hpd.gasmi.net/). This verification process is crucial for maintaining the security and reliability of the information exchanged. Thank you for your cooperation.

## Debug

```
gdb ./tcp_ip_pkt_gen
set args --source 192.168.56.11 --destination 194.190.124.17 --src_port 59198 --dst_port 53 --protocol TCP --payload "Hello, world!"
```

## Note

This README assumes the existence of a command-line executable `tcp_ip_packet_generator` built from the provided C++ source code. Adjustments might be necessary based on the actual structure and implementation of your project.

## Contributing

Contributions are welcome! If you have suggestions for improvements, bug fixes, or new features, feel free to submit a pull request or open an issue on the GitHub repository.

## License

This project is licensed under the [Apache License](https://github.com/gvatsal60/tcp-ip-pkt-gen/blob/master/LICENSE).
