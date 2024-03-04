#include <ctime>
#include <thread>

#include "common_includes.h"
struct ResourceHandle {
  int resource_{};
};
class NetWorkMock {
  public:
  static NetWorkMock *get_instance() {
    static NetWorkMock netWorkMock{};
    return &netWorkMock;
  }

  public:
  void business_func_a(
      const std::string &req,
      const std::function<void(int, const std::string &)> &callback) {
    std::string data =
        req + " a test data " + std::to_string(std::time(nullptr));
    callback(0, data);
  }
  void business_func_b(double req,
                       const std::function<void(int, double)> &callback) {
    callback(0, 42.5 + req);
  }
};
class Business {
  private:
  ResourceHandle resource_;
  std::atomic<bool> running_{true};

  private:
  using TaskT = std::function<void(ResourceHandle *)>;
  std::mutex mutex_;
  std::vector<TaskT> callbacks_;
  void do_on_business_thread(const TaskT &callback) {
    std::lock_guard<std::mutex> lock(mutex_);
    callbacks_.push_back(callback);
  }

  public:
  void stop() { running_.store(false); }
  void run_thread() {
    while (running_.load()) {
      std::this_thread::sleep_for(std::chrono::seconds(1));
      {
        std::lock_guard<std::mutex> lock(mutex_);
        for (const auto &item : callbacks_) {
          item(&resource_);
        }
        callbacks_.clear();
      }
    }
  }
  template <typename Func, typename Callback, typename Arg>
  void network_call_and_schedule_callback(Func func, Callback callback,
                                          Arg arg) {
    (NetWorkMock::get_instance()->*func)(
        arg, [this, callback](int result, auto data) {
          do_on_business_thread(
              [this, callback, result, data](ResourceHandle *resource) {
                (this->*callback)(resource, result, data);
              });
        });
  }
  template <typename Func, typename Callback, typename Arg>
  void network_call_and_schedule_callback_lambda(Func func, Callback callback,
                                                 Arg arg) {
    (NetWorkMock::get_instance()->*func)(
        arg, [this, callback](int result, auto data) {
          do_on_business_thread(
              [this, callback, result, data](ResourceHandle *resource) {
                callback(resource, result, data);
              });
        });
  }
  void business_func_a(const std::string &req) {
    // do something
    LOG_DEBUG("a do something " << req)
    // call rpc
    network_call_and_schedule_callback_lambda(
        &NetWorkMock::business_func_a,
        [this](ResourceHandle *resource, int result, const std::string &data) {
          LOG_DEBUG("a get data " << resource->resource_ << "\t" << data);
        },
        req);
  }

  void business_func_b(double req) {
    // do something
    LOG_DEBUG("b do something " << req)
    // call rpc
    network_call_and_schedule_callback(&NetWorkMock::business_func_b,
                                       &Business::on_b_call_back, req);
  }
  void on_b_call_back(ResourceHandle *resource, int result, double data) {
    LOG_DEBUG("b get data " << resource->resource_ << "\t" << data);
  }

  void business_func_c(const std::string &req) {
    // do something
    LOG_DEBUG("a do something " << req)
    // call rpc
    network_call_and_schedule_callback_lambda(
        &NetWorkMock::business_func_a,
        [this](ResourceHandle *resource, int result, const std::string &data) {
          LOG_DEBUG("a get data " << resource->resource_ << "\t" << data);
        },
        req);
  }
};
TEST(BusinessTest, TestCase1) {
  Business business;
  std::thread thread([&business]() { business.run_thread(); });

  business.business_func_a("ssss");
  business.business_func_a("kkkk");
  business.business_func_b(77);
  business.business_func_b(88);

  sleep(3);
  business.stop();
  thread.join();
}
int main(int argc, char **argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}