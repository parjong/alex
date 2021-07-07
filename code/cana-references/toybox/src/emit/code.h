#ifndef CODE_H__
#define CODE_H__

#include "hiberlite.h"

#include <string>
#include <vector>

class Code
{
	friend class hiberlite::access;
	template<class Ar> void hibernate(Ar & ar)
	{
		ar & HIBERLITE_NVP(cmd_);
		ar & HIBERLITE_NVP(lines_);
	}
  public:
    Code();
    Code(const hiberlite::sqlid_t& cmd, const std::string& path);
    Code(const hiberlite::sqlid_t& cmd, FILE *fp);
  public:
    ~Code();
  private:
    void load(FILE *fp);
  private:
    hiberlite::sqlid_t cmd_;
    std::vector<std::string> lines_;    
  public:
    hiberlite::sqlid_t cmd(void) const;
  public:
    const std::vector<std::string>& lines(void) const;
    std::string content(void) const;
};

#endif
