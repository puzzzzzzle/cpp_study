//
// Created by khalidzhang on 2023/2/7.
//
#include "kcp.h"

#include <condition_variable>

#include "common_includes.h"
#include "udp.h"
class CutDownLatch {
  private:
  std::mutex mutex_{};
  std::condition_variable cv_{};
  uint32_t count_{};

  public:
  explicit CutDownLatch(uint32_t count) : count_(count) {}

  void CountDown() noexcept {
    std::lock_guard<std::mutex> guard(mutex_);
    if (0 == count_) {
      return;
    }
    --count_;
    if (count_ <= 0) {
      cv_.notify_all();
    }
  }

  void Wait() noexcept {
    std::unique_lock<std::mutex> lock(mutex_);
    cv_.wait(lock, [this] { return count_ <= 0; });
  }
};
template <typename T>
class ThreadWrapper {
  private:
  bool is_running_{false}, stopped_{true};
  // 如果启动了本地线程的话
  std::thread local_thread_{};
  T *runnable_{};

  public:
  ThreadWrapper(T *t) : runnable_(t) {}
  ~ThreadWrapper() { WaitStop(); }
  void Start() {
    is_running_ = true;
    stopped_ = false;
    local_thread_ = std::thread([this]() {
      while (is_running_) {
        runnable_->OneLoop();
      }
      stopped_ = true;
    });
  }
  void MarkStop() { is_running_ = false; }
  void WaitStop() {
    MarkStop();
    while (!stopped_) {
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
  }
};
TEST(udp, simple) {
  auto ip = "0.0.0.0";
  auto port = 3344;
  int count = 10;
  std::string echo = "echo:";
  int client_count = 5;
  std::vector<std::thread> threads{};

  // server
  CutDownLatch latch(1);
  threads.emplace_back([=, &latch]() {
    LOG_DEBUG("server start")
    Udp::Udp server{};
    server.Address(ip, port).Bind();
    const auto [recv_addr, recv_addr_len, buf, buf_len] = server.GetBuf();
    int count_inner = count * client_count;
    latch.CountDown();
    while (count_inner > 0) {
      while (true) {
        auto size = server.Recv();
        if (size <= 0) {
          continue;
        }
        // req
        std::string req(buf, size);
        LOG_DEBUG("server recv : " << req << "\tfrom: "
                                   << server.AddrToString(recv_addr))
        // rsp
        auto rsp = echo + req;
        auto send =
            server.SendTo(rsp.c_str(), rsp.length(), recv_addr, *recv_addr_len);
        ASSERT_EQ(send, rsp.length());
        LOG_DEBUG("server send : " << rsp)
        --count_inner;
        break;
      }
    }
  });
  // wait server start up
  latch.Wait();

  auto client_func = [=](int id) {
    Udp::Udp client{};
    client.Address(ip, port).Conn();
    const auto [recv_addr, recv_addr_len, buf, buf_len] = client.GetBuf();
    int count_inner = count;

    while (count_inner > 0) {
      std::string req =
          "client_" + std::to_string(id) + "_" + std::to_string(count_inner);

      // send
      auto send = client.ClientSend(req.c_str(), req.length());
      if (send <= 0) {
        LOG_PERROR("fail");
      }
      ASSERT_EQ(send, req.length());
      LOG_DEBUG("client send : " << req)
      // wait recv
      while (true) {
        auto size = client.Recv();
        if (size <= 0) {
          continue;
        }
        std::string rsp(buf, size);
        ASSERT_EQ(size, req.length() + echo.length());
        ASSERT_EQ(echo + req, rsp);
        LOG_DEBUG("client recv : " << rsp)
        --count_inner;
        break;
      }
    }
  };

  for (int i = 0; i < client_count; ++i) {
    threads.emplace_back(client_func, i);
  }

  for (auto &t : threads) {
    if (t.joinable()) {
      t.join();
    }
  }
}