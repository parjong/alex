#include <gtest/gtest.h>

#include <string>
#include <sstream>
#include <memory>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <pepper/tokens/stream/array.h>
#include <pepper/tokens/action/consume.h>

#include <pepper/tokens/scanner.h>
#include <pepper/tokens/tokens.h>

#include <boost/algorithm/string.hpp>

using namespace pepper::tokens;

/**
 *
 */
TEST(tokens_array_stream, okay) {
  const char *arr[] = {
    "ls",
    "-al",
    NULL
  };

  stream::array stream(arr);

  ASSERT_EQ(strcmp(stream.lookup(0).value(), arr[0]), 0);
  ASSERT_EQ(strcmp(stream.lookup(1).value(), arr[1]), 0);
  ASSERT_EQ(stream.lookup(2), boost::none);

  stream.forward(1);

  ASSERT_EQ(strcmp(stream.lookup(0).value(), arr[1]), 0);
  ASSERT_EQ(stream.lookup(1), boost::none);

  stream.forward(1);
}

/**
 *
 */
struct counting_consumer : public consumer<2> {
  std::size_t count_ = 0;

  virtual void consume(const std::array<const char *, 2> &args) {
    std::cout << "HELLO?" << std::endl;
    count_++;
  }
};

TEST(tokens_scanner, valid) {
  const char *tokens[] = {
    "ls",
    "-al",
    NULL
  };

  stream::array stream(tokens);
  
  action::consume<2> c;
  counting_consumer p;

  c.add(p);

  scanner scn;

  scn.add("ls", &c);

  scn.scan(stream);  

  ASSERT_EQ(p.count_, 1);
}

TEST(tokens_scanner, invalid)
{
  const char *tokens[] = {
    "ls",
    "-al",
    "ls",
    NULL
  };

  stream::array stream(tokens);
  
  action::consume<2> c;
  counting_consumer p;

  c.add(p);

  scanner scn;

  scn.add("ls", &c);
  scn.scan(stream);  

  ASSERT_EQ(p.count_, 1);
}

/**
 *
 */
struct collecting_consumer : public consumer<1> {
  std::vector<std::string> tokens_;

  virtual void consume(const std::array<const char *, 1> &args) {
    tokens_.push_back(args[0]);
  }
};

TEST(tokens_scanner, full) {
  collecting_consumer c;

  action::consume<1> ignore_1;
  action::consume<2> ignore_2;
  action::consume<1> source;
  source.add(c);

  scanner s;

  s.add("-o", &ignore_2);
  s.add("-c", &ignore_1);
  s.add([](const std::string &tag){ return !boost::algorithm::starts_with(tag, "-"); }, &source);


  const char *arr[] = {
    "-o",
    "sample.o",
    "-c",
    "a.c",
    NULL
  };

  stream::array stream(arr);

  s.scan(stream);

  ASSERT_EQ(stream.lookup(0), boost::none);
  ASSERT_EQ(c.tokens_.size(), 1);
  ASSERT_EQ(c.tokens_[0], arr[3]);
}

/**
 *
 */
TEST(tokens_configurator, valid) {
  const char *arr[] = {
    "-o",
    "sample.o",
    "-c",
    NULL
  };

  stream::array stream(arr);
  
  context ctxt;
  configurator cfg(ctxt);

  std::stringstream ss;

  ss << "<actions>" << std::endl;
  ss << "<action> <name>ignore-1</name> <type>consume(1)</type> </action>" << std::endl;
  ss << "<action> <name>ignore-2</name> <type>consume(2)</type> </action>" << std::endl;
  ss << "</actions>" << std::endl;
  ss << "<scanner>" << std::endl;
  ss << "<tag> <value>-o</value> <action>ignore-2</action> </tag>" << std::endl;
  ss << "<tag> <value>-c</value> <action>ignore-1</action> </tag>" << std::endl;
  ss << "</scanner>" << std::endl;

  boost::property_tree::ptree pt;
  boost::property_tree::read_xml(ss, pt);

  scanner *s = cfg.configure(pt);

  s->scan(stream);

  ASSERT_EQ(stream.lookup(0), boost::none);
}

