#include <boost/asio.hpp>
#include <boost/asio/experimental/awaitable_operators.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <boost/beast.hpp>
#include <iostream>
#include <vector>

namespace asio = boost::asio;
namespace beast = boost::beast;
using tcp = asio::ip::tcp;
using namespace boost::asio::experimental::awaitable_operators;

// 异步 HTTP GET 请求协程
asio::awaitable<std::string> async_fetch(asio::io_context& io,
                                         const std::string& host,
                                         const std::string& port,
                                         const std::string& target) {
  std::cout << "Fetching " << host << "...\n";
  try {
    tcp::resolver resolver(io);
    beast::tcp_stream stream(io);

    // 异步解析域名
    auto endpoints =
        co_await resolver.async_resolve(host, port, asio::use_awaitable);

    // 异步连接
    co_await stream.async_connect(endpoints, asio::use_awaitable);

    // 构造 HTTP 请求
    beast::http::request<beast::http::string_body> req{beast::http::verb::get,
                                                       target, 11};
    req.set(beast::http::field::host, host);
    req.set(beast::http::field::user_agent, "C++20 Coroutine");

    // 异步发送请求
    co_await beast::http::async_write(stream, req, asio::use_awaitable);

    // 异步读取响应
    beast::flat_buffer buffer;
    beast::http::response<beast::http::string_body> res;
    co_await beast::http::async_read(stream, buffer, res, asio::use_awaitable);

    // 关闭连接
    beast::error_code ec;
    stream.socket().shutdown(tcp::socket::shutdown_both, ec);

    co_return res.body();
  } catch (const std::exception& e) {
    std::cerr << "Error fetching " << ": " << e.what() << '\n';
    co_return "";  // 返回空字符串表示失败
  }
}

// 主协程：并行收集结果
asio::awaitable<std::vector<std::string>> fetch_all_sites(
    asio::io_context& io) {
  // 同时启动三个异步任务
  auto task1 = async_fetch(io, "en.cppreference.com", "80", "/");
  auto task2 = async_fetch(io, "www.boost.org", "80", "/");
  auto task3 = async_fetch(io, "www.github.com", "80", "/");

  // 并行等待所有任务完成
  auto results =
      co_await (std::move(task1) && std::move(task2) && std::move(task3));
  // 解包结果
  std::vector<std::string> ret;
  ret.reserve(3);
  std::apply(
      [&ret](auto&&... args) {
        (ret.push_back(std::forward<decltype(args)>(args)), ...);
      },
      results);

  co_return ret;
}

// 运行入口
int main() {
  asio::io_context io;
  asio::co_spawn(
      io, fetch_all_sites(io),
      [](std::exception_ptr e, std::vector<std::string> results) {
        if (e) std::rethrow_exception(e);
        std::cout << "Received " << results.size() << " responses:\n";
        for (const auto& res : results) {
          std::cout << "Response length: " << res.size() << " bytes\n";
        }
      });
  io.run();
  return 0;
}
