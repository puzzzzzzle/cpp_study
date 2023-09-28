_global_dict = {}


def set_value(key, value):
    global _global_dict
    _global_dict[key] = value


def get_value(key, default=None):
    global _global_dict
    return _global_dict.get(key, default)
