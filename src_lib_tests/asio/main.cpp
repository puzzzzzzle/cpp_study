#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <asio.hpp>
#include "common_includes.h"

using asio::ip::tcp;

// 每个客户端连接对应一个 session, 通过 shared_from_this prevent destroy during async ops
class session : public std::enable_shared_from_this<session> {
  public:
  session(tcp::socket socket) : socket_(std::move(socket)) {}

  void start() { do_read(); }

  private:
  void do_read() {
    // 捕获 self (shared_ptr) 延长生命周期, 确保异步回调执行时 session 仍然存活
    auto self(shared_from_this());
    socket_.async_read_some(
        asio::buffer(data_, max_length),
        [this, self](std::error_code ec, std::size_t length) {
          if (!ec) {
            // 读到数据后原样写回 (echo)
            do_write(length);
          }
          // ec 非零时不再继续读写, session 引用计数归零后自动销毁
        });
  }

  void do_write(std::size_t length) {
    auto self(shared_from_this());
    // async_write 保证将 data_ 中 length 字节全部写出 (与 async_read_some 不同)
    asio::async_write(socket_, asio::buffer(data_, length),
                      [this, self](std::error_code ec, std::size_t /*length*/) {
                        if (!ec) {
                          // 写完后继续读, 形成 read -> write -> read 的异步循环
                          do_read();
                        }
                      });
  }

  tcp::socket socket_;
  enum { max_length = 1024 };
  char data_[max_length];  // 读写共用的缓冲区
};

// 监听端口, 接受新连接并为每个连接创建 session
class server {
  public:
  server(asio::io_context& io_context, short port)
      : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {
    do_accept();
  }

  private:
  void do_accept() {
    acceptor_.async_accept([this](std::error_code ec, tcp::socket socket) {
      if (!ec) {
        // 每个连接创建独立的 session, 用 shared_ptr 管理生命周期
        std::make_shared<session>(std::move(socket))->start();
      }

      // 无论成功与否都继续接受下一个连接
      do_accept();
    });
  }

  tcp::acceptor acceptor_;
};

int main(int argc, char** argv) {
  try {
    if (argc != 2) {
      std::cerr << "Usage: async_tcp_echo_server <port>\n";
      return 1;
    }

    asio::io_context io_context;

    server s(io_context, std::atoi(argv[1]));

    // 启动事件循环, 阻塞直到所有异步操作完成 (此处不会自然退出, 因为 do_accept 会不断注册新的异步操作)
    io_context.run();
  } catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }
  return 0;
}