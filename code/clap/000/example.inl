class Example final : public clap::BasicApp<Example>
{
private: // Declaration
  StrArg arg_cmd;
  StrArg arg_code;

public: // Configuration
  Example()
  {
    option(&arg_cmd)
      .name('x')
      .required()
    ;

    option(&arg_code)
      .name('c')
      .required()
    ;
  }

public: // Describe Behavior
  int entry(const Session *sess) const final
  {
    auto cmd_filepath = sess->get(arg_cmd);
    auto code_filepath = sess->get(arg_code);

    return 0;
  }
};

CLAP_MAIN(Example);
