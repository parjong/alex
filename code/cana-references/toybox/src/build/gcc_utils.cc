#include "build/gcc_utils.h"

void extrSourcesFromGNUOptions(std::vector<std::string>& sources, const GNUOptions& options)
{
  GNUSourceExtractor extr(sources);
  options.accept(extr);
}

void extrPPOptionsFromGNUOptions(GNUOptions& pp_options, const GNUOptions& options)
{
  GNUPreprocessorOptionExtractor extr(pp_options);
  options.accept(extr);
}
