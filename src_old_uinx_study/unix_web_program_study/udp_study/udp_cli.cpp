//
// Created by tao on 19-1-17.
//

#include "udp_cli.h"

#include <arpa/inet.h>
#include <log_macro.h>
#include <netinet/in.h>

#include "udp_svr.h"

int do_request(const char *msg, ssize_t len, char *receive_buff,
               size_t buff_len) {
  // init addr
  int client_fd;
  sockaddr_in svr_addr{};
  ssize_t send_len;
  socklen_t svr_addr_len = sizeof(svr_addr);

  if ((client_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) <= 0) {
    ERROR("svr socket get err fd : " << client_fd)
    exit(-1);
  }

  svr_addr.sin_family = AF_INET;
  if (inet_pton(AF_INET, ADDR, &svr_addr.sin_addr.s_addr) != 1) {
    ERROR("translate ip address err!")
    exit(-2);
  }
  svr_addr.sin_port = htons(PORT);

  //    ///
  //    connect(client_fd,(sockaddr *)&svr_addr, sizeof(svr_addr));
  //    svr_addr.sin_port=htons(8966);
  //    ///

  if ((send_len = sendto(client_fd, msg, len, 0, (sockaddr *)&svr_addr,
                         sizeof(svr_addr))) != len) {
    ERROR("need to send : " << len << " real send : " << send_len)
  }
  return recvfrom(client_fd, receive_buff, buff_len, 0, (sockaddr *)&svr_addr,
                  &svr_addr_len);
}