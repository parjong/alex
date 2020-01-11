#include "pepper/sign.hpp"

#include <libxml/uri.h>

#include <sstream>
#include <cassert>

#include <iostream>

namespace pepper { namespace sign { namespace initializer {

  parser::parser()
  {
    xmlInitParser();
  }

  parser::~parser()
  {
    xmlCleanupParser();
  }

} } }

namespace pepper { namespace sign { namespace initializer {

  lib::lib()
  {
    xmlLoadExtDtdDefaultValue = XML_DETECT_IDS | XML_COMPLETE_ATTRS;
    xmlSubstituteEntitiesDefault(1);

    // Disable everything 
    xsltSecurityPrefsPtr xsltSecPrefs = xsltNewSecurityPrefs(); 

    xsltSetSecurityPrefs(xsltSecPrefs,  XSLT_SECPREF_READ_FILE,        xsltSecurityForbid);
    xsltSetSecurityPrefs(xsltSecPrefs,  XSLT_SECPREF_WRITE_FILE,       xsltSecurityForbid);
    xsltSetSecurityPrefs(xsltSecPrefs,  XSLT_SECPREF_CREATE_DIRECTORY, xsltSecurityForbid);
    xsltSetSecurityPrefs(xsltSecPrefs,  XSLT_SECPREF_READ_NETWORK,     xsltSecurityForbid);
    xsltSetSecurityPrefs(xsltSecPrefs,  XSLT_SECPREF_WRITE_NETWORK,    xsltSecurityForbid);

    xsltSetDefaultSecurityPrefs(xsltSecPrefs); 

    assert( xmlSecInit() == 0 );
  }

  lib::~lib()
  {
    xmlSecShutdown();
  }

} } }

namespace pepper { namespace sign { namespace initializer {

  crypto::crypto() 
  {
    assert( xmlSecCryptoAppInit(NULL) == 0 );
    assert( xmlSecCryptoInit() == 0 );
  }

  crypto::~crypto()
  {
    xmlSecCryptoShutdown();
    xmlSecCryptoAppShutdown();
  }

} } }

namespace pepper { namespace sign {

  sig::sig(const sign &sign)
    : _sign(sign)
  {
    _Doc = xmlNewDoc((const unsigned char *) "1.0");

    _SignNode = 
      xmlSecTmplSignatureCreate(_Doc, 
                                xmlSecTransformExclC14NId, 
                                xmlSecOpenSSLTransformRsaSha256Id, 
                                (const unsigned char *) _sign.id.c_str());

    xmlDocSetRootElement(_Doc, _SignNode);
  }

  sig::~sig()
  {
    xmlFreeDoc(_Doc); 
  }

  void sig::add_reference(const boost::filesystem::path &path)
  {
    xmlChar *uri = xmlURIEscapeStr((const xmlChar *) path.string().c_str(), NULL);

    xmlSecTmplSignatureAddReference(_SignNode, 
                                    xmlSecTransformSha256Id, 
                                    NULL, 
                                    uri, 
                                    NULL);

    free(uri);
  }

  // Add #prop
  void sig::add_prop(void)
  {
    xmlNodePtr refNode =
      xmlSecTmplSignatureAddReference(_SignNode, 
          xmlSecTransformSha256Id, 
          NULL, 
          (const unsigned char *)"#prop",
          NULL);

    xmlSecTmplReferenceAddTransform(refNode, xmlSecTransformInclC14N11Id);
  }

  void sig::add_key(void)
  {
    // Key Info
    xmlNodePtr keyInfoNode =      
      xmlSecTmplSignatureEnsureKeyInfo(_SignNode, NULL);

    xmlNodePtr X509DataNode = 
      xmlSecTmplKeyInfoAddX509Data(keyInfoNode);

    xmlSecTmplX509DataAddCertificate(X509DataNode);
  }

  void sig::add_object(void)
  {   
    xmlNodePtr objectNode =
      xmlSecTmplSignatureAddObject(_SignNode, (const unsigned char *) "prop", NULL, NULL);

    xmlNodePtr propertiesNode =
      xmlNewChild(objectNode, NULL, (const unsigned char *) "SignatureProperties", NULL);

    auto ns = 
      xmlNewNs(propertiesNode, 
               (const unsigned char *) "http://www.w3.org/2009/xmldsig-properties", 
               (const unsigned char *) "dsp");

    //
    {
      xmlNodePtr propNode =
        xmlNewChild(propertiesNode, NULL, (const unsigned char *) "SignatureProperty", NULL);

      xmlNewProp(propNode, (const unsigned char *) "Id", 
          (const unsigned char *) "profile" );
      xmlNewProp(propNode, (const unsigned char *) "Target", 
          (const unsigned char *) _sign.target.c_str() );

      xmlNodePtr valueNode =
        xmlNewChild(propNode, ns, (const unsigned char*) "Profile", NULL);

      xmlNewProp(valueNode, (const unsigned char *) "URI",
          (const unsigned char *) "http://www.w3.org/ns/widgets-digsig#profile"); 
    }

    //
    {
      xmlNodePtr propNode =
        xmlNewChild(propertiesNode, NULL, (const unsigned char *) "SignatureProperty", NULL);

      xmlNewProp(propNode, (const unsigned char *) "Id", 
          (const unsigned char *) "role" );
      xmlNewProp(propNode, (const unsigned char *) "Target", 
          (const unsigned char *) _sign.target.c_str() );

      xmlNodePtr valueNode =
        xmlNewChild(propNode, ns, (const unsigned char*) "Role", NULL);

      // TODO Revise this!
      xmlNewProp(valueNode, (const unsigned char *) "URI",
          (const unsigned char *) _sign.role.c_str()); 
    }

    //
    {
      xmlNodePtr propNode =
        xmlNewChild(propertiesNode, NULL, (const unsigned char *) "SignatureProperty", NULL);

      xmlNewProp(propNode, (const unsigned char *) "Id", 
          (const unsigned char *) "identifier" );
      xmlNewProp(propNode, (const unsigned char *) "Target", 
          (const unsigned char *) _sign.target.c_str() );

      xmlNodePtr valueNode =
        xmlNewChild(propNode, ns, (const unsigned char*) "Identifier", NULL);
    }
  }

  signer::signer()  { }   
  signer::~signer() { }

  void signer::sign(FILE *out, const sig& sig, const std::string &pkey, const std::string &pass)
  {       
    xmlSecKeyPtr keyPtr =
      xmlSecOpenSSLAppKeyLoad(pkey.c_str(), xmlSecKeyDataFormatPkcs12, pass.c_str(), NULL, NULL); 

    xmlSecDSigCtxPtr dsigCtx = xmlSecDSigCtxCreate(NULL);

    dsigCtx->signKey = keyPtr;

    assert( xmlSecDSigCtxSign(dsigCtx, sig._SignNode) == 0 );
    xmlDocDump(out, sig._Doc);

    xmlSecDSigCtxDestroy(dsigCtx);
  }

} }
