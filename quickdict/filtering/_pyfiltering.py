"""quickdict.filtering module pure Python implementation."""



from typing import Callable, TypeVar
from collections.abc import Mapping, MutableMapping



__all__ = ('qd_filter',   'qd_ifilter',
           'qd_kfilter',  'qd_ikfilter',
           'qd_kvfilter', 'qd_ikvfilter')



K, V = TypeVar('K'), TypeVar('V')



def qd_filter(p:None|Callable[[V],bool], m:Mapping[K,V]) -> dict[K,V]:
    """Return a filtered dict with the predicate applied to the values.
    
    `p` might be
    
    - `None`: filtered by `bool(v)`,
    - otherwise: filtered by `p(v)`.
    
    Python implementation.
    """
    if not (p is None or callable(p)):
        raise TypeError('p must be None or callable')
    if not isinstance(m, Mapping):
        raise TypeError('m must be a mapping')
    
    if p is None:
        return {k:v for k, v in m.items() if v}
    else:
        return {k:v for k, v in m.items() if p(v)}

def qd_kfilter(p:Callable[[K],bool], m:Mapping[K,V]) -> dict[K,V]:
    """Return a filtered dict with the predicate applied to the keys.
    
    Filtered by `p(k)`.
    
    Python implementation.
    """
    if not callable(p):
        raise TypeError('p must be callable')
    if not isinstance(m, Mapping):
        raise TypeError('m must be a mapping')
    
    return {k:v for k, v in m.items() if p(k)}

def qd_kvfilter(p:Callable[[K,V],bool], m:Mapping[K,V]) -> dict[K,V]:
    """Return a filtered dict with the predicate applied to the items.
    
    Filtered by `p(k, v)`.
    
    Python implementation.
    """
    if not callable(p):
        raise TypeError('p must be callable')
    if not isinstance(m, Mapping):
        raise TypeError('m must be a mapping')
    
    return {k:v for k, v in m.items() if p(k, v)}


#in-place
def qd_ifilter(p:None|Callable[[V],bool], m:MutableMapping[K,V]) -> MutableMapping[K,V]:
    """Filter with the predicate applied to the values.
    
    `p` might be
    
    - `None`: filtered by `bool(v)`,
    - otherwise: filtered by `p(v)`.
    
    Python implementation.
    """
    if not (p is None or callable(p)):
        raise TypeError('p must be None or callable')
    if not isinstance(m, MutableMapping):
        raise TypeError('m must be a mutable mapping')
    
    if p is None:
        for k in [k for k, v in m.items() if not v]:
            del m[k]
    else:
        for k in [k for k, v in m.items() if not p(v)]:
            del m[k]
    return m

def qd_ikfilter(p:Callable[[K],bool], m:MutableMapping[K,V]) -> MutableMapping[K,V]:
    """Filter a mapping with the predicate applied to the keys.
    
    Filtered by `p(k)`.
    
    Python implementation.
    """
    if not callable(p):
        raise TypeError('p must be callable')
    if not isinstance(m, MutableMapping):
        raise TypeError('m must be a mutable mapping')
    
    for k in [k for k, v in m.items() if not p(k)]:
        del m[k]
    return m

def qd_ikvfilter(p:Callable[[K,V],bool], m:MutableMapping[K,V]) -> MutableMapping[K,V]:
    """Filter a mapping with the predicate applied to the items.
    
    Filtered by `p(k, v)`
    
    Python implementation.
    """
    if not callable(p):
        raise TypeError('p must be callable')
    if not isinstance(m, MutableMapping):
        raise TypeError('m must be a mutable mapping')
    
    for k in [k for k, v in m.items() if not p(k, v)]:
        del m[k]
    return m
