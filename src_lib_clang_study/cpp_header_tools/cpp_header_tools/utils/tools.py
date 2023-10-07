import datetime
import logging
from functools import wraps

logger = logging.getLogger(__name__)


def time_me(level=10, target_logger=None):
    '''
    run time for target func
    '''

    def time_decorator(func):
        @wraps(func)
        def wrap_function(*args, **kw):
            start_time = datetime.datetime.now()
            res = func(*args, **kw)
            over_time = datetime.datetime.now()
            real_logger = target_logger
            if real_logger is None:
                real_logger = logger
            real_logger.log(level,
                            f"current Function {func.__name__} run time is {(over_time - start_time).total_seconds()}")
            return res

        return wrap_function

    return time_decorator
