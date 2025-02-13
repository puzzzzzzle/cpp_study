#include <fcgi_stdio.h>

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

// spawn-fcgi -p 9000 ./fastcgi-demo
int main() {
  while (FCGI_Accept() >= 0) {
    // 获取请求方法
    const char* request_method = getenv("REQUEST_METHOD");

    // 读取输入数据
    std::string input_data;
    if (request_method && strcmp(request_method, "POST") == 0) {
      // 获取内容长度
      const char* content_length_str = getenv("CONTENT_LENGTH");
      int content_length = content_length_str ? std::atoi(content_length_str) : 0;

      if (content_length > 0) {
        char* buffer = new char[content_length + 1];
        std::cin.read(buffer, content_length);
        buffer[content_length] = '\0';
        input_data = buffer;
        delete[] buffer;
      }
    }

    // 输出响应头
    printf("Content-type: text/html\r\n\r\n");

    // 输出响应内容
    printf("<html><head><title>FastCGI Demo</title></head>");
    printf("<body><h1>Hello, FastCGI!</h1>");
    printf("<p>This is a simple FastCGI demo application.</p>");

    if (!input_data.empty()) {
      printf("<h2>Received POST Data:</h2>");
      printf("<pre>%s</pre>", input_data.c_str());
    } else {
      printf("<p>No POST data received.</p>");
    }

    printf("</body></html>");
  }
  return 0;
}