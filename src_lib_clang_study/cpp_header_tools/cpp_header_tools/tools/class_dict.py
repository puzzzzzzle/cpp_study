#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Author  : puzzzzzzle
# @Content : 通过.号访问的Storage
from copy import deepcopy


def _dict_to_storage(arg):
    result = None
    if isinstance(arg, dict):
        result = Storage()
        for k, v in arg.items():
            result[k] = _dict_to_storage(v)
    elif isinstance(arg, list):
        result = []
        for v in arg:
            result.append(_dict_to_storage(v))
    else:
        result = arg
    return result


class Storage(dict):
    def __init__(self, *args, **kwargs):
        super(Storage, self).__init__(*args, **kwargs)
        for arg in args:
            if isinstance(arg, dict):
                for k, v in arg.items():
                    self[k] = v

        if kwargs:
            for k, v in kwargs.items():
                self[k] = v

    def __getattr__(self, attr):
        return self.get(attr)

    def __setattr__(self, key, value):
        self.__setitem__(key, value)

    def __setitem__(self, key, value):
        super(Storage, self).__setitem__(key, value)
        self.__dict__.update({key: value})

    def __delattr__(self, item):
        self.__delitem__(item)

    def __delitem__(self, key):
        super(Storage, self).__delitem__(key)
        del self.__dict__[key]

    def __repr__(self):
        """
        str(obj)的显示内容
        :return:
        """
        return '<Storage ' + dict.__repr__(self) + '>'

    def __deepcopy__(self, memo=None, _nil=None):
        if _nil is None:
            _nil = []
        if memo is None:
            memo = {}
        d = id(self)
        y = memo.get(d, _nil)
        if y is not _nil:
            return y

        new_obj = Storage()
        memo[d] = id(new_obj)
        for key in self.keys():
            new_obj.__setattr__(deepcopy(key, memo),
                                deepcopy(self.__getattr__(key), memo))
        return new_obj
