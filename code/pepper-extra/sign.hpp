#ifndef __PEPPER_XML_SIGN_H__
#define __PEPPER_XML_SIGN_H__

/**
 * TODO Implement a signing library
 */
#include <libxml/tree.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#include <libxslt/xslt.h>
#include <libxslt/security.h>

#include <xmlsec/xmlsec.h>
#include <xmlsec/xmltree.h>
#include <xmlsec/xmldsig.h>
#include <xmlsec/templates.h>
#include <xmlsec/crypto.h>

#include <boost/filesystem.hpp>

namespace pepper { namespace sign {

  namespace initializer
  {
    struct parser
    {
      parser();
      ~parser();
    };

    struct lib
    {
      lib();          
      ~lib();      
    };

    struct crypto
    {   
      crypto();           
      ~crypto();
    };
  }
  
  struct sign
  {
    // AuthorSignature
    std::string id;
    // #AuthorSignature
    std::string target; 
    // http://www.w3.org/ns/widgets-digsig#role-author
    std::string role;
  };

  class sig
  {
    friend class signer;

    private:
      const sign &_sign;      

    private:
      xmlDocPtr _Doc;
      xmlNodePtr _SignNode;

    public:
      sig(const sign &sign);
      ~sig();

    public:
      void add_reference(const boost::filesystem::path &path);
      void add_prop(void);
      void add_key(void);
      void add_object(void);
  };

  class signer
  {
    public:
      signer();
      ~signer();

    public:
      void sign(FILE *out, const sig& sig, const std::string &pkey, const std::string &pass);
  };

} }

#endif
