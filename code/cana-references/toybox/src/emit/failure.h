#ifndef FAILURE_H__
#define FAILURE_H__

#include "hiberlite.h"

#include <string>

class Failure
{
	friend class hiberlite::access;
	template<class Ar> void hibernate(Ar & ar)
	{
		ar & HIBERLITE_NVP(cmd_);
		ar & HIBERLITE_NVP(opt_);
	}
  public:
    Failure();
    Failure(const hiberlite::sqlid_t& cmd, const std::string& opt) ;
  public:
    ~Failure();
  private:
    hiberlite::sqlid_t cmd_;
    std::string opt_; 
  public:
    const hiberlite::sqlid_t& cmd(void) const;
    const std::string& opt(void) const;
};

#endif
