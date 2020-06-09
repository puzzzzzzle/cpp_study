#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/common.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sources/channel_feature.hpp>
#include <boost/log/sources/channel_logger.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_channel_logger.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/from_stream.hpp>
#include <boost/log/utility/setup/settings.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <fstream>
#include <string>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;
namespace attrs = boost::log::attributes;
namespace sinks = boost::log::sinks;

using namespace std;
using namespace logging::trivial;
src::severity_channel_logger<severity_level, std::string> logger1(
    keywords::channel = "MySink1");
src::severity_channel_logger<severity_level, std::string> logger2(
    keywords::channel = "MySink2");

int log_init() {
  logging::add_common_attributes();
  logging::core::get()->add_thread_attribute("Scope", attrs::named_scope());

  logging::register_simple_formatter_factory<severity_level, char>("Severity");
  logging::register_simple_filter_factory<severity_level, char>("Severity");

  std::ifstream file("./data/properties/boost_log_settings.ini");
  if (!file.is_open()) {
    std::cerr << "open settings fail" << std::endl;
    return -1;
  }
  logging::init_from_stream(file);
  file.close();
  return 0;
}