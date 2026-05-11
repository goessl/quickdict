"""quickdict.filtering module pure Python implementation."""



from typing import TypeVar
from collections.abc import Mapping, MutableMapping



__all__ = ('pyqd_filter', 'pyqd_ifilter')



K, V = TypeVar('K'), TypeVar('V')



def pyqd_filter(m:Mapping[K,V]) -> dict[K,V]:
    """Return a dict with items that have a false value removed.
    
    Python implementation.
    """
    if not isinstance(m, Mapping):
        raise TypeError('m must be a mapping')
    
    return {k:v for k, v in m.items() if v}

def pyqd_ifilter(m:MutableMapping[K,V]) -> MutableMapping[K,V]:
    """Remove all items that have a false value.
    
    Python implementation.
    """
    if not isinstance(m, MutableMapping):
        raise TypeError('m must be a mutable mapping')
    
    for k in [k for k, v in m.items() if not v]:
        del m[k]
    return m
