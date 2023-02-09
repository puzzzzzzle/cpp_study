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
static auto port = 22345;


static bool ip6 = false;
static auto ip = "127.0.0.1";

// 注意： ipv6下， 需要确认自己的机器支持且网卡开启了
// static bool ip6 = true;
// static auto ip = "::1";

static int count = 10;
static std::string echo = "echo:";
static int client_count = 10;

void ServerFunc(Udp::Udp &server) {
  LOG_DEBUG("server start at : " << server.InitAddress().ToString())
  const auto [recv_addr, buf, buf_len] = server.GetBuf();
  int count_inner = count * client_count;
  while (count_inner > 0) {
    while (true) {
      auto size = server.Recv();
      if (size <= 0) {
        LOG_PERROR("err ")
        continue;
      }
      // req
      std::string req(buf, size);
      LOG_DEBUG("server recv : " << req << "\tfrom: " << recv_addr->ToString())
      // rsp
      auto rsp = echo + req;
      auto send = server.SendTo(rsp.c_str(), rsp.length(), recv_addr);
      ASSERT_EQ(send, rsp.length());
      LOG_DEBUG("server send : " << rsp)
      --count_inner;
      break;
    }
  }
}
void ClientFunc(Udp::Udp &client, int id) {
  const auto [recv_addr, buf, buf_len] = client.GetBuf();
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
}
TEST(udp, simple) {
  auto port = 22345;
  std::vector<std::thread> threads{};
  // server
  CutDownLatch latch(1);
  threads.emplace_back([=, &latch]() {
    Udp::Udp server{};
    server.Address(ip, port).Config(Udp::UdpConfig::kUseIpV6, ip6).Bind();
    latch.CountDown();
    ServerFunc(server);
  });
  // wait server start up
  latch.Wait();

  auto client_func = [=](int id) {
    Udp::Udp client{};
    client.Address(ip, port).Config(Udp::UdpConfig::kUseIpV6, ip6).Conn();
    ClientFunc(client, id);
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

TEST(udp, share) {
  std::vector<std::thread> threads{};
  // server
  Udp::Udp server{};
  server.Address(ip, port).Config(Udp::UdpConfig::kUseIpV6, ip6).Bind();


  threads.emplace_back([server_move = std::move(server)]() mutable {
    ServerFunc(server_move);
  });
  // wait server start up

  for (int i = 0; i < client_count; ++i) {
    threads.emplace_back(
        [](int id) mutable {
          Udp::Udp client{};
          client.Address(ip, port).Config(Udp::UdpConfig::kUseIpV6, ip6).Conn();
          auto client_clone = client.Clone();
          ClientFunc(client_clone, id);
        },
        i);
  }
  for (auto &t : threads) {
    if (t.joinable()) {
      t.join();
    }
  }
}