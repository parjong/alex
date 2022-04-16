import logging
import sys

def create_driver_logger():
  """Create a logger for MAS drivers"""

  # WARNING! DO NOT use root logger
  #
  # It turns out that logging.basicConfig call from .mas script has no effect if
  # a MAS driver creates any log with root logger before logging.basicConfig call.
  #
  # Let's use a named logger to workaround this problem.
  logger = logging.getLogger(f'mas.driver')

  handler = logging.StreamHandler(sys.stdout)
  # Ref: https://docs.python.org/3/library/logging.html#logrecord-attributes
  handler.setFormatter(logging.Formatter('%(asctime)s %(levelname)s %(filename)s:%(lineno)s %(message)s'))

  logger.addHandler(handler)

  return logger
# def create_driver_logger: END
