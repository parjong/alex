#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/optional.hpp>

#include <pepper/tokens/stream/array.h>
#include <pepper/tokens/action/consume.h>

#include <pepper/tokens/scanner.h>
#include <pepper/tokens/tokens.h>

#include <string>
#include <sstream>
#include <iostream>

using namespace pepper::tokens;

void func_1(void) {
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

  //std::cout << ss.str() << std::endl;

  //return;

  boost::property_tree::ptree pt;
  boost::property_tree::read_xml(ss, pt);

  scanner *s = cfg.configure(pt);

  s->scan(stream);

  std::cout << (stream.lookup(0) == boost::none) << std::endl;
}

void func_0(void) {
  std::string xml = 
  "<scanner>"
    "<tag>"
      "<value>-cc1</value>"
      "<action>ignore-1</action>"
    "</tag>"
  "</scanner>";

  std::stringstream ss(xml);

  boost::property_tree::ptree pt;
  boost::property_tree::read_xml(ss, pt);

  for (auto &child : pt.get_child("scanner")) {
    if ( child.first == "tag" ) {
      auto &tag = child.second;
      std::cout << tag.get<std::string>("value") << "," << tag.get<std::string>("action") << std::endl;
    }
  }
}  

int main(int argc, char **argv) {
  func_1();

  return 0;
} 
